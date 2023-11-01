#pragma once

#include <string>
#include <vector>

#include "sql/stmt/stmt.h"
class CreateViewStmt : public Stmt
{
public:
  CreateViewStmt(const std::string &view_name, const SelectSqlNode& select);

  virtual ~CreateViewStmt() = default;

  StmtType type() const override { return StmtType::CREATE_VIEW; }

  static RC create(const CreateViewSqlNode &create_view, Stmt *&stmt);

private:

};