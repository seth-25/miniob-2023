/* Copyright (c) 2021 Xie Meiyi(xiemeiyi@hust.edu.cn) and OceanBase and/or its affiliates. All rights reserved.
miniob is licensed under Mulan PSL v2.
You can use this software according to the terms and conditions of the Mulan PSL v2.
You may obtain a copy of Mulan PSL v2 at:
         http://license.coscl.org.cn/MulanPSL2
THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND,
EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT,
MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
See the Mulan PSL v2 for more details. */

//
// Created by Meiyi & Wangyunlai on 2021/5/13.
//

#include <limits.h>
#include <string.h>
#include <algorithm>

#include "common/defs.h"
#include "storage/table/table.h"
#include "storage/table/table_meta.h"
#include "common/log/log.h"
#include "common/lang/string.h"
#include "common/lang/typecast.h"
#include "storage/buffer/disk_buffer_pool.h"
#include "storage/record/record_manager.h"
#include "storage/common/condition_filter.h"
#include "storage/common/meta_util.h"
#include "storage/index/index.h"
#include "storage/index/bplus_tree_index.h"
#include "storage/trx/trx.h"

Table::~Table()
{
  if (record_handler_ != nullptr) {
    delete record_handler_;
    record_handler_ = nullptr;
  }

  if (data_buffer_pool_ != nullptr) {
    data_buffer_pool_->close_file();
    data_buffer_pool_ = nullptr;
  }

  for (std::vector<Index *>::iterator it = indexes_.begin(); it != indexes_.end(); ++it) {
    Index *index = *it;
    delete index;
  }
  indexes_.clear();

  LOG_INFO("Table has been closed: %s", name());
}

RC Table::create(int32_t table_id, 
                 const char *meta_path,
                 const char *name, 
                 const char *base_dir, 
                 int attribute_count, 
                 const AttrInfoSqlNode attributes[])
{
  if (table_id < 0) {
    LOG_WARN("invalid table id. table_id=%d, table_name=%s", table_id, name);
    return RC::INVALID_ARGUMENT;
  }

  if (common::is_blank(name)) {
    LOG_WARN("Name cannot be empty");
    return RC::INVALID_ARGUMENT;
  }
  LOG_INFO("Begin to create table %s:%s", base_dir, name);

  if (attribute_count <= 0 || nullptr == attributes) {
    LOG_WARN("Invalid arguments. table_name=%s, attribute_count=%d, attributes=%p", name, attribute_count, attributes);
    return RC::INVALID_ARGUMENT;
  }

  RC rc = RC::SUCCESS;

  // 使用 table_name.table记录一个表的元数据
  // 判断表文件是否已经存在
  int fd = ::open(meta_path, O_WRONLY | O_CREAT | O_EXCL | O_CLOEXEC, 0600);
  if (fd < 0) {
    if (EEXIST == errno) {
      LOG_ERROR("Failed to create table file, it has been created. %s, EEXIST, %s", meta_path, strerror(errno));
      return RC::SCHEMA_TABLE_EXIST;
    }
    LOG_ERROR("Create table file failed. filename=%s, errmsg=%d:%s", meta_path, errno, strerror(errno));
    return RC::IOERR_OPEN;
  }

  close(fd);

  // 创建文件
  if ((rc = table_meta_.init(table_id, name, attribute_count, attributes)) != RC::SUCCESS) {
    LOG_ERROR("Failed to init table meta. name:%s, ret:%d", name, rc);
    return rc;  // delete table file
  }

  std::fstream fs;
  fs.open(meta_path, std::ios_base::out | std::ios_base::binary);  // 元数据文件
  if (!fs.is_open()) {
    LOG_ERROR("Failed to open file for write. file name=%s, errmsg=%s", meta_path, strerror(errno));
    return RC::IOERR_OPEN;
  }

  // 记录元数据到文件中
  table_meta_.serialize(fs);
  fs.close();

  std::string data_file = table_data_file(base_dir, name);
  BufferPoolManager &bpm = BufferPoolManager::instance();
  rc = bpm.create_file(data_file.c_str());  // 创建数据文件，存放行数据
  if (rc != RC::SUCCESS) {
    LOG_ERROR("Failed to create disk buffer pool of data file. file name=%s", data_file.c_str());
    return rc;
  }

  rc = init_record_handler(base_dir);
  if (rc != RC::SUCCESS) {
    LOG_ERROR("Failed to create table %s due to init record handler failed.", data_file.c_str());
    // don't need to remove the data_file
    return rc;
  }

  base_dir_ = base_dir;
  LOG_INFO("Successfully create table %s:%s", base_dir, name);
  return rc;
}


RC Table::destroy() {
  RC rc = sync();//刷新所有脏页

  if(rc != RC::SUCCESS) return rc;

  const int index_num = table_meta_.index_num();
  for (int i = 0; i < index_num; i++) {  // 清理所有的索引相关文件数据与索引元数据
    ((BplusTreeIndex*)indexes_[i])->close();
    const IndexMeta* index_meta = table_meta_.index(i);
    std::string index_file = table_index_file(base_dir_.c_str(), name(), index_meta->name());
    if(remove(index_file.c_str()) != 0) {
      LOG_ERROR("Failed to remove index file=%s, errno=%d", index_file.c_str(), errno);
      return RC::IOERR_DELETE;
    }
  }

  std::string data_file = table_data_file(base_dir_.c_str(), name());
  if(remove(data_file.c_str()) != 0) { // 删除描述表元数据的文件
    LOG_ERROR("Failed to remove data file=%s, errno=%d", data_file.c_str(), errno);
    return RC::IOERR_DELETE;
  }

  std::string path = table_meta_file(base_dir_.c_str(), name());
  if(remove(path.c_str()) != 0) {
    LOG_ERROR("Failed to remove meta file=%s, errno=%d", path.c_str(), errno);
    return RC::IOERR_DELETE;
  }

//  std::string text_data_file = std::string(dir) + "/" + name() + TABLE_TEXT_DATA_SUFFIX;
//  if(unlink(text_data_file.c_str()) != 0) { // 删除表实现text字段的数据文件（后续实现了text case时需要考虑，最开始可以不考虑这个逻辑）
//    LOG_ERROR("Failed to remove text data file=%s, errno=%d", text_data_file.c_str(), errno);
//    return RC::IOERR_DELETE;
//  }

  return RC::SUCCESS;
}

RC Table::open(const char *meta_file, const char *base_dir)
{
  // 加载元数据文件
  std::fstream fs;
  std::string meta_file_path = std::string(base_dir) + common::FILE_PATH_SPLIT_STR + meta_file;
  fs.open(meta_file_path, std::ios_base::in | std::ios_base::binary);
  if (!fs.is_open()) {
    LOG_ERROR("Failed to open meta file for read. file name=%s, errmsg=%s", meta_file_path.c_str(), strerror(errno));
    return RC::IOERR_OPEN;
  }
  if (table_meta_.deserialize(fs) < 0) {
    LOG_ERROR("Failed to deserialize table meta. file name=%s", meta_file_path.c_str());
    fs.close();
    return RC::INTERNAL;
  }
  fs.close();

  // 加载数据文件
  RC rc = init_record_handler(base_dir);
  if (rc != RC::SUCCESS) {
    LOG_ERROR("Failed to open table %s due to init record handler failed.", base_dir);
    // don't need to remove the data_file
    return rc;
  }

  base_dir_ = base_dir;

  const int index_num = table_meta_.index_num();
  for (int i = 0; i < index_num; i++) {
    const IndexMeta *index_meta = table_meta_.index(i);
    const std::vector<std::string> *index_field_names = index_meta->field();
    std::vector<FieldMeta> field_metas;

    for (const auto & index_field_name : *index_field_names) {
      const char *field_name = index_field_name.data();
      const FieldMeta *field_meta = table_meta_.field(field_name);
      if (field_meta == nullptr) {
        LOG_ERROR("Found invalid index meta info which has a non-exists field. table=%s, index=%s",
            name(),
            index_meta->name());
        return RC::INTERNAL;
      }
      field_metas.push_back(*field_meta);
    }

    BplusTreeIndex *index = new BplusTreeIndex();
    std::string index_file = table_index_file(base_dir, name(), index_meta->name());
    rc = index->open(index_file.c_str(), *index_meta, field_metas);
    if (rc != RC::SUCCESS) {
      delete index;
      LOG_ERROR("Failed to open index. table=%s, index=%s, file=%s, rc=%s",
                name(), index_meta->name(), index_file.c_str(), strrc(rc));
      // skip cleanup
      //  do all cleanup action in destructive Table function.
      return rc;
    }
    indexes_.push_back(index);
  }

  return rc;
}

RC Table::insert_record(Record &record)
{
  RC rc = RC::SUCCESS;
  rc    = record_handler_->insert_record(record.data(), table_meta_.record_size(), &record.rid(), &table_meta_);
  if (rc != RC::SUCCESS) {
    LOG_ERROR("Insert record failed. table name=%s, rc=%s", table_meta_.name(), strrc(rc));
    return rc;
  }

  rc = insert_entry_of_indexes(record.data(), record.rid());
  if (rc != RC::SUCCESS) { // 可能出现了键值重复,直接在insert_entry_of_indexes里面删除已插入索引,下面删掉
//    RC rc2 = delete_entry_of_indexes(record.data(), record.rid(), false/*error_on_not_exists*/);
//    if (rc2 != RC::SUCCESS) {
//      LOG_ERROR("Failed to rollback index data when insert index entries failed. table name=%s, rc=%d:%s",
//                name(), rc2, strrc(rc2));
//    }
    RC rc2 = record_handler_->delete_record(&record.rid());
    if (rc2 != RC::SUCCESS) {
      LOG_PANIC("Failed to rollback record data when insert index entries failed. table name=%s, rc=%d:%s",
                name(), rc2, strrc(rc2));
    }
  }
  return rc;
}
RC Table::insert_record_with_history(Record &record)
{
  RC rc = RC::SUCCESS;
  rc    = record_handler_->insert_record(record.data(), table_meta_.record_size(), &record.rid(), &table_meta_);
  if (rc != RC::SUCCESS) {
    LOG_ERROR("Insert record failed. table name=%s, rc=%s", table_meta_.name(), strrc(rc));
    return rc;
  }
  return rc;
}

RC Table::visit_record(const RID &rid, bool readonly, std::function<void(Record &)> visitor)
{
  return record_handler_->visit_record(rid, readonly, visitor);
}

RC Table::get_record(const RID &rid, Record &record)
{
  const int record_size = table_meta_.record_size();
  char *record_data = (char *)malloc(record_size);
  ASSERT(nullptr != record_data, "failed to malloc memory. record data size=%d", record_size);

  auto copier = [&record, record_data, record_size](Record &record_src) {
    memcpy(record_data, record_src.data(), record_size);
    record.set_rid(record_src.rid());
  };
  RC rc = record_handler_->visit_record(rid, true/*readonly*/, copier);
  if (rc != RC::SUCCESS) {
    free(record_data);
    LOG_WARN("failed to visit record. rid=%s, table=%s, rc=%s", rid.to_string().c_str(), name(), strrc(rc));
    return rc;
  }

  record.set_data_owner(record_data, record_size);
  return rc;
}

RC Table::recover_insert_record(Record &record)
{
  RC rc = RC::SUCCESS;
  rc = record_handler_->recover_insert_record(record.data(), table_meta_.record_size(), record.rid());
  if (rc != RC::SUCCESS) {
    LOG_ERROR("Insert record failed. table name=%s, rc=%s", table_meta_.name(), strrc(rc));
    return rc;
  }

  rc = insert_entry_of_indexes(record.data(), record.rid());
  if (rc != RC::SUCCESS) { // 可能出现了键值重复,直接在insert_entry_of_indexes里面删除已插入索引,下面删掉
//    RC rc2 = delete_entry_of_indexes(record.data(), record.rid(), false/*error_on_not_exists*/);
//    if (rc2 != RC::SUCCESS) {
//      LOG_ERROR("Failed to rollback index data when insert index entries failed. table name=%s, rc=%d:%s",
//                name(), rc2, strrc(rc2));
//    }
    RC rc2 = record_handler_->delete_record(&record.rid());
    if (rc2 != RC::SUCCESS) {
      LOG_PANIC("Failed to rollback record data when insert index entries failed. table name=%s, rc=%d:%s",
                name(), rc2, strrc(rc2));
    }
  }
  return rc;
}

const char *Table::name() const
{
  return table_meta_.name();
}

const TableMeta &Table::table_meta() const
{
  return table_meta_;
}

RC Table::value_cast_record(const Value &value, const FieldMeta *field, char *record_data, std::vector<char*> &text_mems)
{
  const FieldMeta *null_field = table_meta_.null_bitmap_field();
  common::Bitmap bitmap(record_data + null_field->offset(), null_field->len());

  int idx = field->id();
  if (AttrType::NULLS == value.attr_type()) {

    bitmap.set_bit(idx);
    // make sure data all zero bit
    memset(record_data + field->offset(), 0, field->len());
    return RC::SUCCESS;
  }
  bitmap.clear_bit(idx);

  const char *cast_data = value.data();
  if (field->type() != value.attr_type() &&
      !TextHelper::isInsertText(field->type(), value.attr_type())) {  // 进行type cast
    cast_data = common::type_cast_to[value.attr_type()][field->type()](value.data());
    if (cast_data == nullptr) {
      LOG_ERROR("Typecast error.");
      return RC::SCHEMA_FIELD_TYPE_MISMATCH;
    }
  }

  size_t copy_len = field->len();
  if (field->type() == CHARS) { // 字符串的len会小于field->len()
    const size_t data_len = strlen((const char *)cast_data);
    if (copy_len > data_len) {
      copy_len = data_len + 1;
    }
  }
  if (field->type() == TEXTS) {
    int text_length = value.text_length();
//    if (text_length > 4096) text_length = 4096;
    if (text_length > TEXT_MAX_LEN) {
      LOG_TRACE("Text too long.");
      return RC::TEXT_TOO_LONG;
    }
    copy_len = text_length + 1;
    char *text_mem = (char *)malloc(copy_len);
    memcpy(text_mem, cast_data, copy_len);
    *(char **)(record_data + field->offset()) = text_mem;
    *(text_mem + text_length) = '\0';
    text_mems.push_back(text_mem);
  } else {
    memcpy(record_data + field->offset(), cast_data, copy_len);
  }

  return RC::SUCCESS;
}

RC Table::make_record(int value_num, const Value *values, Record &record)
{
  // 检查字段类型是否一致
  if (value_num + table_meta_.sys_field_num() + table_meta_.extra_filed_num() != table_meta_.field_num()) {
    LOG_WARN("Input values don't match the table's schema, table name:%s", table_meta_.name());
    return RC::SCHEMA_FIELD_MISSING;
  }

  const int normal_field_start_index = table_meta_.sys_field_num();
  for (int i = 0; i < value_num; i++) {
    const FieldMeta *field = table_meta_.field(i + normal_field_start_index);
    const Value  &value = values[i];
    if (AttrType::NULLS == value.attr_type()) {
      if (!field->nullable()) {
        LOG_WARN("field type mismatch. can not be null. table=%s, field=%s, field type=%d, value_type=%d",
              table_meta_.name(),
              field->name(),
              field->type(),
              value.attr_type());
        return RC::SCHEMA_FIELD_TYPE_MISMATCH;
      }
      continue;
    }
    if (field->type() != value.attr_type() && !common::type_cast_check(value.attr_type(), field->type()) &&
        !TextHelper::isInsertText(field->type(), value.attr_type())) {
      LOG_ERROR("Invalid value type. table name =%s, field name=%s, type=%d, but given=%d",
                table_meta_.name(), field->name(), field->type(), value.attr_type());
      return RC::SCHEMA_FIELD_TYPE_MISMATCH;
    }
  }

  std::vector<char*> text_mems;
  // 复制所有字段的值
  int record_size = table_meta_.record_size();
  char *record_data = (char *)malloc(record_size);

  RC rc = RC::SUCCESS;
  for (int i = 0; i < value_num; i++) {
    const FieldMeta *field = table_meta_.field(i + normal_field_start_index);
    const Value &value = values[i];
    rc = value_cast_record(value, field, record_data, text_mems);
    if (rc != RC::SUCCESS) {
      LOG_ERROR("Value cast record error.");
      return rc;
    }
  }

  record.set_data_owner(record_data, record_size);
  if (!text_mems.empty()) {
    auto text_mems_to_delete = new TextMems;
    text_mems_to_delete->text_mems = std::move(text_mems);
    record.set_text_mems(text_mems_to_delete);
  }


  return RC::SUCCESS;
}


RC Table::init_record_handler(const char *base_dir)
{
  std::string data_file = table_data_file(base_dir, table_meta_.name());

  RC rc = BufferPoolManager::instance().open_file(data_file.c_str(), data_buffer_pool_);
  if (rc != RC::SUCCESS) {
    LOG_ERROR("Failed to open disk buffer pool for file:%s. rc=%d:%s", data_file.c_str(), rc, strrc(rc));
    return rc;
  }

  record_handler_ = new RecordFileHandler();
  rc = record_handler_->init(data_buffer_pool_);
  if (rc != RC::SUCCESS) {
    LOG_ERROR("Failed to init record handler. rc=%s", strrc(rc));
    data_buffer_pool_->close_file();
    data_buffer_pool_ = nullptr;
    delete record_handler_;
    record_handler_ = nullptr;
    return rc;
  }

  return rc;
}

RC Table::get_record_scanner(RecordFileScanner &scanner, Trx *trx, bool readonly)
{
  RC rc = scanner.open_scan(this, *data_buffer_pool_, trx, readonly, nullptr);
  if (rc != RC::SUCCESS) {
    LOG_ERROR("failed to open scanner. rc=%s", strrc(rc));
  }
  return rc;
}

RC Table::create_index(Trx *trx, bool is_unique, std::vector<const FieldMeta *> &field_metas, const char *index_name)
{
  if (common::is_blank(index_name) || field_metas.empty()) {
    LOG_INFO("Invalid input arguments, table name is %s, index_name is blank or attribute_name is blank", name());
    return RC::INVALID_ARGUMENT;
  }

  for (const auto &field: field_metas) {
    if (field->type() == TEXTS) {
      LOG_ERROR("Invalid input arguments, table name is %s, index field is text", name());
      return RC::INVALID_ARGUMENT;
    }
  }

  IndexMeta new_index_meta;
  RC rc = new_index_meta.init(index_name,is_unique,field_metas);
  if (rc != RC::SUCCESS) {
    LOG_INFO("Failed to init IndexMeta in table:%s, index_name:%s",
             name(), index_name);
    return rc;
  }

  std::vector<FieldMeta> field_metas_real;
  field_metas_real.push_back(*table_meta_.null_bitmap_field());
  field_metas_real.reserve(field_metas.size() + 1); //加上null的field
  for (auto & field_meta : field_metas) {
    field_metas_real.push_back(*field_meta);
  }
  // 创建索引相关数据
  BplusTreeIndex *index = new BplusTreeIndex();
  std::string index_file = table_index_file(base_dir_.c_str(), name(), index_name);
  rc = index->create(index_file.c_str(), new_index_meta, field_metas_real);
  if (rc != RC::SUCCESS) {
    delete index;
    LOG_ERROR("Failed to create bplus tree index. file name=%s, rc=%d:%s", index_file.c_str(), rc, strrc(rc));
    return rc;
  }

  // 遍历当前的所有数据，插入这个索引
  RecordFileScanner scanner;
  rc = get_record_scanner(scanner, trx, true/*readonly*/);
  if (rc != RC::SUCCESS) {
    LOG_WARN("failed to create scanner while creating index. table=%s, index=%s, rc=%s", 
             name(), index_name, strrc(rc));
    return rc;
  }

  Record record;
  while (scanner.has_next()) {
    rc = scanner.next(record);
    if (rc != RC::SUCCESS) {
      LOG_WARN("failed to scan records while creating index. table=%s, index=%s, rc=%s",
               name(), index_name, strrc(rc));
      return rc;
    }
    rc = index->insert_entry(record.data(), &record.rid());
    if (rc != RC::SUCCESS) {
      LOG_WARN("failed to insert record into index while creating index. table=%s, index=%s, rc=%s",
               name(), index_name, strrc(rc));
      return rc;         
    }
  }
  scanner.close_scan();
  LOG_INFO("inserted all records into new index. table=%s, index=%s", name(), index_name);
  
  indexes_.push_back(index);

  /// 接下来将这个索引放到表的元数据中
  TableMeta new_table_meta(table_meta_);
  rc = new_table_meta.add_index(new_index_meta);
  if (rc != RC::SUCCESS) {
    LOG_ERROR("Failed to add index (%s) on table (%s). error=%d:%s", index_name, name(), rc, strrc(rc));
    return rc;
  }

  /// 内存中有一份元数据，磁盘文件也有一份元数据。修改磁盘文件时，先创建一个临时文件，写入完成后再rename为正式文件
  /// 这样可以防止文件内容不完整
  // 创建元数据临时文件
  std::string tmp_file = table_meta_file(base_dir_.c_str(), name()) + ".tmp";
  std::fstream fs;
  fs.open(tmp_file, std::ios_base::out | std::ios_base::binary | std::ios_base::trunc);
  if (!fs.is_open()) {
    LOG_ERROR("Failed to open file for write. file name=%s, errmsg=%s", tmp_file.c_str(), strerror(errno));
    return RC::IOERR_OPEN;  // 创建索引中途出错，要做还原操作
  }
  if (new_table_meta.serialize(fs) < 0) {
    LOG_ERROR("Failed to dump new table meta to file: %s. sys err=%d:%s", tmp_file.c_str(), errno, strerror(errno));
    return RC::IOERR_WRITE;
  }
  fs.close();

  // 覆盖原始元数据文件
  std::string meta_file = table_meta_file(base_dir_.c_str(), name());
  int ret = rename(tmp_file.c_str(), meta_file.c_str());
  if (ret != 0) {
    LOG_ERROR("Failed to rename tmp meta file (%s) to normal meta file (%s) while creating index (%s) on table (%s). "
              "system error=%d:%s",
              tmp_file.c_str(), meta_file.c_str(), index_name, name(), errno, strerror(errno));
    return RC::IOERR_WRITE;
  }

  table_meta_.swap(new_table_meta);

  LOG_INFO("Successfully added a new index (%s) on the table (%s)", index_name, name());
  return rc;
}

RC Table::delete_record(const Record &record)
{
  RC rc = RC::SUCCESS;
  for (Index *index : indexes_) {
    rc = index->delete_entry(record.data(), &record.rid());
    ASSERT(RC::SUCCESS == rc,
        "failed to delete entry from index. table name=%s, index name=%s, rid=%s, rc=%s",
        name(),
        index->index_meta().name(),
        record.rid().to_string().c_str(),
        strrc(rc));
  }
  rc = record_handler_->delete_record(&record.rid(), &table_meta_);
  return rc;
}
bool Table::record_field_is_null(const char *record, int idx) const
{
  const FieldMeta *field = table_meta_.field(idx);
  if (!field->nullable()) {
    return false;
  }
  const FieldMeta *null_field = table_meta_.null_bitmap_field();
  common::Bitmap bitmap(const_cast<char *>(record) + null_field->offset(), null_field->len());
  return bitmap.get_bit(idx);
}
RC Table::make_record_from_old_record(
    vector<const FieldMeta *> &fields, vector<Value> &values, Record &old_record, Record &new_record)
{
  RC rc = RC::SUCCESS;
  bool duplicate = true;
  for (size_t i = 0; i < fields.size(); i++) {
    if (fields[i]->nullable()) {
      if (record_field_is_null(old_record.data(), fields[i]->id())) {
        if (AttrType::NULLS == values[i].attr_type())
          continue;
        else
          duplicate = false;
      } else {
        duplicate = false;
      }
    } else {
      duplicate = false;
    }
  }
  if (duplicate) {
    // remove this record;
    return RC::RECORD_DUPLICATE_KEY;
  }


  int record_size = table_meta_.record_size();

  std::vector<char*> text_mems;
  char *new_data = static_cast<char *>(malloc(record_size));
  memcpy(new_data, old_record.data(), record_size);

  for (size_t i = 0; i < fields.size(); i++) {
    const FieldMeta *field = fields[i];
    const Value value = values[i];
    if (field->type() == TEXTS) {
      auto &text_record = *(TextRecord*)(old_record.data() + field->offset());
      while (text_mems.size() != text_record.text_id) {
        text_mems.push_back(nullptr);
      }
    }
    rc = value_cast_record(value, field, new_data, text_mems);
    if (rc != RC::SUCCESS) {
      LOG_ERROR("Value cast record error.");
      return rc;
    }
  }


  new_record.set_rid(old_record.rid());
  new_record.set_data_owner(new_data, record_size);
  //  new_record.set_data(new_data, record_size);

  if (!text_mems.empty()) {
    auto text_mems_to_delete = new TextMems;
    text_mems_to_delete->text_mems = std::move(text_mems);
    new_record.set_text_mems(text_mems_to_delete);
  }

  return RC::SUCCESS;
}
RC Table::update_record_with_history(Record &old_record, Record &new_record, const FieldMeta * fields)
{
  RC rc = RC::SUCCESS;
  rc    = record_handler_->update_record_with_history(&new_record, table_meta_.record_size(), fields, &old_record.rid());
  if (rc != RC::SUCCESS) {
    LOG_ERROR("Update record failed. table name=%s, rc=%s", table_meta_.name(), strrc(rc));
    return rc;
  }
  return rc;
}
RC Table::update_record(const Record &old_record, Record &new_record, const vector<const FieldMeta*>& fields)
{
  RC rc = RC::SUCCESS;
  rc    = delete_entry_of_indexes(old_record.data(), old_record.rid(), false);
  if (rc != RC::SUCCESS) {
    LOG_ERROR("Failed to delete index data when update index. table name=%s, rc=%d:%s",
                name(), rc, strrc(rc));
  }
  rc = record_handler_->update_record(&new_record, fields);
  if (rc != RC::SUCCESS) {
    LOG_ERROR("Update record failed. table name=%s, rc=%s", table_meta_.name(), strrc(rc));
    return rc;
  }

  rc = insert_entry_of_indexes(new_record.data(), new_record.rid());
  if (rc != RC::SUCCESS) { // 可能出现了键值重复,直接在insert_entry_of_indexes里面删除已插入索引,下面删掉
//    // 索引中删除新的record
//    RC rc2 = delete_entry_of_indexes(new_record.data(), new_record.rid(), false/*error_on_not_exists*/);
//    if (rc2 != RC::SUCCESS) {
//      LOG_ERROR("Failed to rollback index data when update index entries failed. table name=%s, rc=%d:%s",
//                name(), rc2, strrc(rc2));
//    }
    // 索引中插入旧的record
    RC rc2 = insert_entry_of_indexes(old_record.data(), old_record.rid());
    if (rc2 != RC::SUCCESS) {
      LOG_ERROR("Failed to rollback index data when update index entries failed. table name=%s, rc=%d:%s",
                name(), rc2, strrc(rc2));
    }
    // 还原成旧的record
    rc2 = record_handler_->update_record(&old_record, fields);
    if (rc2 != RC::SUCCESS) {
      LOG_PANIC("Failed to rollback record data when insert index entries failed. table name=%s, rc=%d:%s",
                name(), rc2, strrc(rc2));
    }
  }

  return rc;
}

RC Table::insert_entry_of_indexes(const char *record, const RID &rid)
{
  RC rc = RC::SUCCESS;
  for (int i = 0; i < static_cast<int>(indexes_.size()); i ++ )
  {
    Index * index = indexes_[i];
    rc = index->insert_entry(record, &rid);
    if (rc != RC::SUCCESS) {
      for (int j = i - 1; j >= 0; j -- )
      {
         Index * index_to_delete = indexes_[j];
         RC rc2 = index_to_delete->delete_entry(record, &rid);
         if (rc2 != RC::SUCCESS) {
            LOG_ERROR("Failed to rollback index data when insert index entries failed. table name=%s, rc=%d:%s",
            name(), rc2, strrc(rc2));
         }
      }
      break;
    }
  }
  return rc;
}

RC Table::delete_entry_of_indexes(const char *record, const RID &rid, bool error_on_not_exists)
{
  RC rc = RC::SUCCESS;
  for (Index *index : indexes_) {
    rc = index->delete_entry(record, &rid);
    if (rc != RC::SUCCESS) {
      if (rc != RC::RECORD_INVALID_KEY || !error_on_not_exists) {
        break;
      }
    }
  }
  return rc;
}

Index *Table::find_index(const char *index_name) const
{
  for (Index *index : indexes_) {
    if (0 == strcmp(index->index_meta().name(), index_name)) {
      return index;
    }
  }
  return nullptr;
}
Index *Table::find_index_by_field(const char *field_name) const
{
  const TableMeta &table_meta = this->table_meta();
  const IndexMeta *index_meta = table_meta.find_index_by_field(field_name);
  if (index_meta != nullptr) {
    return this->find_index(index_meta->name());
  }
  return nullptr;
}

RC Table::sync()
{
  RC rc = RC::SUCCESS;
  for (Index *index : indexes_) {
    rc = index->sync();
    if (rc != RC::SUCCESS) {
      LOG_ERROR("Failed to flush index's pages. table=%s, index=%s, rc=%d:%s",
          name(),
          index->index_meta().name(),
          rc,
          strrc(rc));
      return rc;
    }
  }
  LOG_INFO("Sync table over. table=%s", name());
  return rc;
}
