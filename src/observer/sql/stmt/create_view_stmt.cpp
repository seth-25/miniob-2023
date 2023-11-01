#include "create_view_stmt.h"


RC CreateViewStmt::create(const CreateViewSqlNode &create_view, Stmt *&stmt)
{
  if (view_map.find(create_view.relation_name) != view_map.end()) {
    return RC::SCHEMA_TABLE_EXIST;
  }
  stmt = new CreateViewStmt(create_view.relation_name, create_view.selection);

  return RC::SUCCESS;
}

CreateViewStmt::CreateViewStmt(const string &view_name, const SelectSqlNode &select) {
  view_map[view_name] = select; // todo 存磁盘
}
