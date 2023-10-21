/* Copyright (c) 2021 OceanBase and/or its affiliates. All rights reserved.
miniob is licensed under Mulan PSL v2.
You can use this software according to the terms and conditions of the Mulan PSL v2.
You may obtain a copy of Mulan PSL v2 at:
         http://license.coscl.org.cn/MulanPSL2
THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND,
EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT,
MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
See the Mulan PSL v2 for more details. */

//
// Created by Wangyunlai on 2023/6/14.
//

#include <memory>

#include "sql/executor/show_index_executor.h"

#include "session/session.h"
#include "event/sql_event.h"
#include "event/session_event.h"
#include "common/log/log.h"
#include "storage/table/table.h"
#include "sql/stmt/show_index_stmt.h"
#include "storage/db/db.h"
#include "sql/operator/string_list_physical_operator.h"

using namespace std;

RC ShowIndexExecutor::execute(SQLStageEvent *sql_event)
{
  RC rc = RC::SUCCESS;
  Stmt *stmt = sql_event->stmt();
  SessionEvent *session_event = sql_event->session_event();
  Session *session = session_event->session();
  ASSERT(stmt->type() == StmtType::SHOW_INDEX,
         "show index executor can not run this command: %d", static_cast<int>(stmt->type()));

  ShowIndexStmt *show_index_stmt = static_cast<ShowIndexStmt *>(stmt);

  SqlResult *sql_result = session_event->sql_result();

  const char *table_name = show_index_stmt->table_name().c_str();

  Db *db = session->get_current_db();
  Table *table = db->find_table(table_name);
  if (table != nullptr) {
    TupleSchema* tuple_schema = new TupleSchema;
    tuple_schema->append_cell(new TupleCellSpec("Table"));
    tuple_schema->append_cell(new TupleCellSpec("Unique"));
    tuple_schema->append_cell(new TupleCellSpec("Key_name"));
    tuple_schema->append_cell(new TupleCellSpec("Seq_in_fields"));
    tuple_schema->append_cell(new TupleCellSpec("Column_name"));

    sql_result->set_tuple_schema(tuple_schema);

    auto show_index_opera = new StringListPhysicalOperator;
    const TableMeta &table_meta = table->table_meta();
    const int index_num = table_meta.index_num();
    for (int i = 0; i < index_num; i ++ )
    {
      const IndexMeta *index_meta = table_meta.index(i);
      std::vector<std::string> fields = *index_meta->field();
      for (size_t j = 0; j < fields.size(); j ++ ) {
        show_index_opera->append({table_meta.name(), to_string(index_meta->is_unique()), index_meta->name(), to_string(j + 1), fields[j]});
      }
    }
    sql_result->set_operator(unique_ptr<PhysicalOperator>(show_index_opera));
  } else {

    sql_result->set_return_code(RC::SCHEMA_TABLE_NOT_EXIST);
    sql_result->set_state_string("Table not exists");
  }
  return rc;
}