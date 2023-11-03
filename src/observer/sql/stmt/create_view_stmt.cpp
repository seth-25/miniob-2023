#include "create_view_stmt.h"


RC CreateViewStmt::create(const CreateViewSqlNode &create_view, Stmt *&stmt)
{
  if (ViewMapHelper::get_instance()->get().find(create_view.relation_name) != ViewMapHelper::get_instance()->get().end()) {
    return RC::SCHEMA_TABLE_EXIST;
  }
  stmt = new CreateViewStmt(create_view.relation_name, create_view.selection);

  return RC::SUCCESS;
}

CreateViewStmt::CreateViewStmt(const string &view_name, const SelectSqlNode &select) {
  ViewMapHelper::get_instance()->get()[view_name] = select; // todo 存磁盘
}
