
%{

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <algorithm>

#include "common/log/log.h"
#include "common/lang/string.h"
#include "sql/parser/parse_defs.h"
#include "sql/parser/yacc_sql.hpp"
#include "sql/parser/lex_sql.h"
#include "sql/expr/expression.h"
#include "sql/expr/arithmetic_expression.h"
#include "sql/expr/value_expression.h"

using namespace std;

string token_name(const char *sql_string, YYLTYPE *llocp)
{
  return string(sql_string + llocp->first_column, llocp->last_column - llocp->first_column + 1);
}

int yyerror(YYLTYPE *llocp, const char *sql_string, ParsedSqlResult *sql_result, yyscan_t scanner, const char *msg)
{
  std::unique_ptr<ParsedSqlNode> error_sql_node = std::make_unique<ParsedSqlNode>(SCF_ERROR);
  error_sql_node->error.error_msg = msg;
  error_sql_node->error.line = llocp->first_line;
  error_sql_node->error.column = llocp->first_column;
  sql_result->add_sql_node(std::move(error_sql_node));
  return 0;
}

ArithmeticExpr *create_arithmetic_expression(ArithmeticExpr::Type type,
                                             Expression *left,
                                             Expression *right,
                                             const char *sql_string,
                                             YYLTYPE *llocp)
{
  ArithmeticExpr *expr = new ArithmeticExpr(type, left, right);
  expr->set_name(token_name(sql_string, llocp));
  return expr;
}

%}

%define api.pure full
%define parse.error verbose
/** 启用位置标识 **/
%locations
%lex-param { yyscan_t scanner }
/** 这些定义了在yyparse函数中的参数 **/
%parse-param { const char * sql_string }
%parse-param { ParsedSqlResult * sql_result }
%parse-param { void * scanner }

//标识tokens
%token  SEMICOLON
        CREATE
        DROP
        TABLE
        TABLES
        INDEX
        INNER
        JOIN
        CALC
        SELECT
        DESC
        ASC
        SHOW
        SYNC
        INSERT
        DELETE
        UPDATE
        LBRACE
        RBRACE
        COMMA
        TRX_BEGIN
        TRX_COMMIT
        TRX_ROLLBACK
        INT_T
        STRING_T
        FLOAT_T
        DATE_T
        HELP
        EXIT
        DOT //QUOTE
        INTO
        VALUES
        FROM
        WHERE
        AND
        SET
        ON
        LOAD
        DATA
        INFILE
        EXPLAIN
        NOT
        LIKE
        UNIQUE
        ORDER
        BY
        AGGR_MAX
        AGGR_MIN
        AGGR_COUNT
        AGGR_AVG
        AGGR_SUM
        LENGTH
        ROUND
        DATE_FORMAT
        AS
        EQ
        LT
        GT
        LE
        GE
        NE

/** union 中定义各种数据类型，真实生成的代码也是union类型，所以不能有非POD类型的数据 **/
%union {
  ParsedSqlNode *                   sql_node;
  ConditionSqlNode *                condition;
  Value *                           value;
  enum CompOp                       comp;
  RelAttrSqlNode *                  rel_attr;
  OrderBySqlNode *                  order_attr;
  std::vector<AttrInfoSqlNode> *    attr_infos;
  AttrInfoSqlNode *                 attr_info;
  Expression *                      expression;
  std::vector<Expression *> *       expression_list;
  std::vector<Value> *              value_list;
  std::vector<std::vector<Value>> * row_value_list;
  std::vector<ConditionSqlNode> *   condition_list;
  std::vector<RelAttrSqlNode> *     rel_attr_list;
  std::vector<OrderBySqlNode> *     order_attr_list;
  RelationSqlNode *                 relation_list;
  std::vector<std::string> *        rel_index_attr_list;
  UpdateValueNode *                 update_value;
  std::vector<UpdateValueNode> *    update_value_list;
  char *                            string;
  int                               number;
  float                             floats;

  // 新加的表达式
  ExprSqlNode *                     expr;
  std::vector<ExprSqlNode *> *      expr_list;
  enum AggrFuncType                 aggr_func_type;

}

%token <number> NUMBER
%token <floats> FLOAT
%token <string> ID
%token <string> SSS
%token <string> DATE_STR
//非终结符

/** type 定义了各种解析后的结果输出的是什么类型。类型对应了 union 中的定义的成员变量名称 **/
%type <number>              type
%type <condition>           condition
%type <value>               value
%type <number>              number
%type <comp>                comp_op
%type <rel_attr>            rel_attr
%type <order_attr>          sort_unit
%type <attr_infos>          attr_def_list
%type <attr_info>           attr_def
%type <value_list>          value_list
%type <value_list>          row_value
%type <row_value_list>      row_value_list
%type <condition_list>      where
%type <condition_list>      condition_list
%type <condition_list>      inner_condition_list
%type <relation_list>       select_from
%type <relation_list>       rel_list
%type <rel_attr_list>       attr_list
%type <order_attr_list>     order_by
%type <order_attr_list>     sort_list
%type <rel_index_attr_list> index_attr_list
%type <expression>          expression
%type <expression_list>     expression_list
%type <sql_node>            calc_stmt
%type <sql_node>            select_stmt
%type <sql_node>            insert_stmt
%type <sql_node>            update_stmt
%type <sql_node>            delete_stmt
%type <sql_node>            create_table_stmt
%type <sql_node>            drop_table_stmt
%type <sql_node>            show_tables_stmt
%type <sql_node>            show_index_stmt
%type <sql_node>            desc_table_stmt
%type <sql_node>            create_index_stmt
%type <sql_node>            drop_index_stmt
%type <sql_node>            sync_stmt
%type <sql_node>            begin_stmt
%type <sql_node>            commit_stmt
%type <sql_node>            rollback_stmt
%type <sql_node>            load_data_stmt
%type <sql_node>            explain_stmt
%type <sql_node>            set_variable_stmt
%type <sql_node>            help_stmt
%type <sql_node>            exit_stmt
%type <sql_node>            command_wrapper
%type <update_value>        update_value;
%type <update_value_list>   update_value_list;

// 新加的表达式
%type <expr>                unary_expr
%type <expr>                expr
%type <expr>                add_expr
%type <expr>                mul_expr
%type <expr>                func_expr
%type <expr>                aggr_func_expr;
%type <aggr_func_type>      aggr_func_type;
%type <expr_list>           expr_list
%type <expr_list>           select_attr


// commands should be a list but I use a single command instead
%type <sql_node>            commands

%left '+' '-'
%left '*' '/'
%nonassoc UMINUS
%%

commands: command_wrapper opt_semicolon  //commands or sqls. parser starts here.
  {
    std::unique_ptr<ParsedSqlNode> sql_node = std::unique_ptr<ParsedSqlNode>($1);
    sql_result->add_sql_node(std::move(sql_node));
  }
  ;

command_wrapper:
    calc_stmt
  | select_stmt
  | insert_stmt
  | update_stmt
  | delete_stmt
  | create_table_stmt
  | drop_table_stmt
  | show_tables_stmt
  | show_index_stmt
  | desc_table_stmt
  | create_index_stmt
  | drop_index_stmt
  | sync_stmt
  | begin_stmt
  | commit_stmt
  | rollback_stmt
  | load_data_stmt
  | explain_stmt
  | set_variable_stmt
  | help_stmt
  | exit_stmt
    ;

exit_stmt:
    EXIT {
      (void)yynerrs;  // 这么写为了消除yynerrs未使用的告警。如果你有更好的方法欢迎提PR
      $$ = new ParsedSqlNode(SCF_EXIT);
    };

help_stmt:
    HELP {
      $$ = new ParsedSqlNode(SCF_HELP);
    };

sync_stmt:
    SYNC {
      $$ = new ParsedSqlNode(SCF_SYNC);
    }
    ;

begin_stmt:
    TRX_BEGIN  {
      $$ = new ParsedSqlNode(SCF_BEGIN);
    }
    ;

commit_stmt:
    TRX_COMMIT {
      $$ = new ParsedSqlNode(SCF_COMMIT);
    }
    ;

rollback_stmt:
    TRX_ROLLBACK  {
      $$ = new ParsedSqlNode(SCF_ROLLBACK);
    }
    ;

drop_table_stmt:    /*drop table 语句的语法解析树*/
    DROP TABLE ID {
      $$ = new ParsedSqlNode(SCF_DROP_TABLE);
      $$->drop_table.relation_name = $3;
      free($3);
    };

show_tables_stmt:
    SHOW TABLES {
      $$ = new ParsedSqlNode(SCF_SHOW_TABLES);
    }
    ;
show_index_stmt:
    SHOW INDEX FROM ID  {
      $$ = new ParsedSqlNode(SCF_SHOW_INDEX);
      $$->show_index.relation_name = $4;
      free($4);
    }
    ;
desc_table_stmt:
    DESC ID  {
      $$ = new ParsedSqlNode(SCF_DESC_TABLE);
      $$->desc_table.relation_name = $2;
      free($2);
    }
    ;

create_index_stmt:    /*create index 语句的语法解析树*/
    CREATE INDEX ID ON ID LBRACE ID index_attr_list RBRACE
    {
      $$ = new ParsedSqlNode(SCF_CREATE_INDEX);
      CreateIndexSqlNode &create_index = $$->create_index;

      create_index.index_name = $3;
      create_index.relation_name = $5;
      if ($8 != nullptr) {
         create_index.attribute_names.swap(*$8);
         delete $8;
      }
      create_index.attribute_names.push_back($7);
      std::reverse(create_index.attribute_names.begin(), create_index.attribute_names.end());
      create_index.is_unique = false;

      free($3);
      free($5);
      free($7);
    }
    | CREATE UNIQUE INDEX ID ON ID LBRACE ID index_attr_list RBRACE
    {
        $$ = new ParsedSqlNode(SCF_CREATE_INDEX);
        CreateIndexSqlNode &create_index = $$->create_index;

        create_index.index_name = $4;
        create_index.relation_name = $6;
        if ($9 != nullptr) {
           create_index.attribute_names.swap(*$9);
           delete $9;
        }
        create_index.attribute_names.push_back($8);
        std::reverse(create_index.attribute_names.begin(), create_index.attribute_names.end());
        create_index.is_unique = true;

        free($4);
        free($6);
        free($8);
    }
    ;

drop_index_stmt:      /*drop index 语句的语法解析树*/
    DROP INDEX ID ON ID
    {
      $$ = new ParsedSqlNode(SCF_DROP_INDEX);
      $$->drop_index.index_name = $3;
      $$->drop_index.relation_name = $5;
      free($3);
      free($5);
    }
    ;
create_table_stmt:    /*create table 语句的语法解析树*/
    CREATE TABLE ID LBRACE attr_def attr_def_list RBRACE
    {
      $$ = new ParsedSqlNode(SCF_CREATE_TABLE);
      CreateTableSqlNode &create_table = $$->create_table;
      create_table.relation_name = $3;
      free($3);

      std::vector<AttrInfoSqlNode> *src_attrs = $6;

      if (src_attrs != nullptr) {
        create_table.attr_infos.swap(*src_attrs);
      }
      create_table.attr_infos.emplace_back(*$5);
      std::reverse(create_table.attr_infos.begin(), create_table.attr_infos.end());
      delete $5;
    }
    ;
attr_def_list:
    /* empty */
    {
      $$ = nullptr;
    }
    | COMMA attr_def attr_def_list
    {
      if ($3 != nullptr) {
        $$ = $3;
      } else {
        $$ = new std::vector<AttrInfoSqlNode>;
      }
      $$->emplace_back(*$2);
      delete $2;
    }
    ;

attr_def:
    ID type LBRACE number RBRACE
    {
      $$ = new AttrInfoSqlNode;
      $$->type = (AttrType)$2;
      $$->name = $1;
      $$->length = $4;
      free($1);
    }
    | ID type
    {
      $$ = new AttrInfoSqlNode;
      $$->type = (AttrType)$2;
      $$->name = $1;
      $$->length = 4;
      free($1);
    }
    ;
number:
    NUMBER {$$ = $1;}
    ;
type:
    INT_T      { $$=INTS; }
    | STRING_T { $$=CHARS; }
    | FLOAT_T  { $$=FLOATS; }
    | DATE_T   { $$=DATES; }
    ;
insert_stmt:        /*insert   语句的语法解析树*/
    INSERT INTO ID VALUES row_value row_value_list
    {
      $$ = new ParsedSqlNode(SCF_INSERT);
      $$->insertion.relation_name = $3;
      if ($6 != nullptr) {
        $$->insertion.values.swap(*$6);
        delete $6;
      }
      $$->insertion.values.emplace_back(*$5);
      std::reverse($$->insertion.values.begin(), $$->insertion.values.end());
      delete $5;
      free($3);
    }
    ;
row_value_list:
		/* EMPTY */
	{
	    $$ = nullptr;
	}
    | COMMA row_value row_value_list {
        if ($3 == nullptr)
        {
            $$ = new std::vector<std::vector<Value>>;
        }else
        {
            $$ = $3;
        }

        $$->emplace_back(*$2);
        delete $2;
    }
    ;
row_value:
    LBRACE value value_list RBRACE
    {
         $$ = new std::vector<Value>;
         if ($3 != nullptr) {
           $$->swap(*$3);
           delete $3;
         }
         $$->emplace_back(*$2);
         std::reverse($$->begin(), $$->end());
         delete $2;
    }
    ;
value_list:
    /* empty */
    {
      $$ = nullptr;
    }
    | COMMA value value_list  {
      if ($3 != nullptr) {
        $$ = $3;
      } else {
        $$ = new std::vector<Value>;
      }
      $$->emplace_back(*$2);
      delete $2;
    }
    ;
value:
    NUMBER {
      $$ = new Value((int)$1);
      @$ = @1;
    }
    | '-' NUMBER {
      $$ = new Value(-(int)$2);
      @$ = @1;
    }
    | FLOAT {
      $$ = new Value((float)$1);
      @$ = @1;
    }
    | '-' FLOAT {
      $$ = new Value(-(float)$2);
      @$ = @1;
    }
    | DATE_STR {
        int p1 = common::find_ch((yyvsp[0].string),1,'-');
        int p2 = common::find_ch((yyvsp[0].string),p1+1,'-');
        char *y = common::substr((yyvsp[0].string),1,p1-1);            // year
        char *m = common::substr((yyvsp[0].string),p1+1,p2-1);         // month
        char *d = common::substr((yyvsp[0].string),p2+1,strlen((yyvsp[0].string))-2); // day
        $$ = new Value(y,m,d);
        if ($$->attr_type() == 0) { // date is illegal
            yyerror (&yylloc, sql_string, sql_result, scanner, YY_("date is illegal"));
        }
        free(y);
        free(m);
        free(d);
    }
    | SSS {
      char *tmp = common::substr($1,1,strlen($1)-2);
      $$ = new Value(tmp);
      free(tmp);
    }
    ;

delete_stmt:    /*  delete 语句的语法解析树*/
    DELETE FROM ID where
    {
      $$ = new ParsedSqlNode(SCF_DELETE);
      $$->deletion.relation_name = $3;
      if ($4 != nullptr) {
        $$->deletion.conditions.swap(*$4);
        delete $4;
      }
      free($3);
    }
    ;
update_stmt:      /*  update 语句的语法解析树*/
/*
    UPDATE ID SET ID EQ value where
    {
      $$ = new ParsedSqlNode(SCF_UPDATE);
      $$->update.relation_name = $2;
      $$->update.attribute_name = $4;
      $$->update.value = *$6;
      if ($7 != nullptr) {
        $$->update.conditions.swap(*$7);
        delete $7;
      }
      free($2);
      free($4);
    }
    |*/
    UPDATE ID SET update_value update_value_list where
    {
      $$ = new ParsedSqlNode(SCF_UPDATE);
      $$->update.relation_name = $2;
      if ($5 != nullptr) {
        $$->update.update_values.swap(*$5);
        delete $5;
      }
      $$->update.update_values.emplace_back(*$4);
      delete $4;
      if ($6 != nullptr) {
        $$->update.conditions.swap(*$6);
        delete $6;
      }
      free($2);
    }
    ;

update_value:
    ID EQ value {
      $$ = new UpdateValueNode;
      $$->attribute_name = $1;
      $$->value = *$3;
      free($1);
      delete($3);
    }

update_value_list:
    /* empty */
    {
      $$ = nullptr;
    }
    | COMMA update_value update_value_list {
      if ($3 != nullptr) {
        $$ = $3;
      } else {
        $$ = new std::vector<UpdateValueNode>;
      }
      $$->emplace_back(*$2);
      delete $2;
    }

select_stmt:        /*  select 语句的语法解析树*/
    SELECT select_attr {  // function 可能出现
      $$ = new ParsedSqlNode(SCF_SELECT);
      if ($2 != nullptr) {
        $$->selection.project_exprs.swap(*$2);
        delete $2;
      }
    }
    | SELECT select_attr FROM select_from where order_by
    {
      $$ = new ParsedSqlNode(SCF_SELECT);
      if ($2 != nullptr) {
        $$->selection.project_exprs.swap(*$2);
        delete $2;
      }
      if ($4 != nullptr) {
        $$->selection.relation_names.swap($4->relation_names);
        $$->selection.alias_names.swap($4->alias_names);
        $$->selection.inner_join_conditions.swap($4->conditions);
        delete $4;
      }
      std::reverse($$->selection.relation_names.begin(), $$->selection.relation_names.end());
      std::reverse($$->selection.alias_names.begin(), $$->selection.alias_names.end());
      if ($5 != nullptr) {
        $$->selection.conditions.swap(*$5);
        delete $5;
      }
      if ($6 != nullptr) {
        $$->selection.order_by_cols.swap(*$6);
        delete $6;
      }
    }
    ;
calc_stmt:
    CALC expression_list
    {
      $$ = new ParsedSqlNode(SCF_CALC);
      std::reverse($2->begin(), $2->end());
      $$->calc.expressions.swap(*$2);
      delete $2;
    }
    ;

expression_list:
    expression
    {
      $$ = new std::vector<Expression*>;
      $$->emplace_back($1);
    }
    | expression COMMA expression_list
    {
      if ($3 != nullptr) {
        $$ = $3;
      } else {
        $$ = new std::vector<Expression *>;
      }
      $$->emplace_back($1);
    }
    ;
expression: // 普通的算术表达式
    expression '+' expression {
      $$ = create_arithmetic_expression(ArithmeticExpr::Type::ADD, $1, $3, sql_string, &@$);
    }
    | expression '-' expression {
      $$ = create_arithmetic_expression(ArithmeticExpr::Type::SUB, $1, $3, sql_string, &@$);
    }
    | expression '*' expression {
      $$ = create_arithmetic_expression(ArithmeticExpr::Type::MUL, $1, $3, sql_string, &@$);
    }
    | expression '/' expression {
      $$ = create_arithmetic_expression(ArithmeticExpr::Type::DIV, $1, $3, sql_string, &@$);
    }
    | LBRACE expression RBRACE {
      $$ = $2;
      $$->set_name(token_name(sql_string, &@$));
    }
    | '-' expression %prec UMINUS {
      $$ = create_arithmetic_expression(ArithmeticExpr::Type::NEGATIVE, $2, nullptr, sql_string, &@$);
    }
    | value {
      $$ = new ValueExpr(*$1);
      $$->set_name(token_name(sql_string, &@$));
      delete $1;
    }
    ;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//表达式

unary_expr: // 一元表达式
    value {
      UnaryExprSqlNode* unary = new UnaryExprSqlNode;
      unary->is_attr = false;
      unary->value = *$1;
      delete $1;

      ExprSqlNode* expr = new ExprSqlNode;
      expr->type = ExprSqlNodeType::UNARY;
      expr->unary_expr = unary;

      $$ = expr;
    }
    | rel_attr {
      UnaryExprSqlNode* unary = new UnaryExprSqlNode;
      unary->is_attr = true;
      unary->attr = *$1;
      delete $1;

      ExprSqlNode* expr = new ExprSqlNode;
      expr->type = ExprSqlNodeType::UNARY;
      expr->unary_expr = unary;

      $$ = expr;
    }
    | func_expr {
      $$ = $1;
    }
    | aggr_func_expr {
      $$ = $1;
    }
    | LBRACE expr RBRACE {
      $2->with_brace = true;
      $$ = $2;
    }
    ;


expr: // 二元表达式
    expr '+' expr {
      BinaryExprSqlNode* binary = new BinaryExprSqlNode;
      binary->op = ExprOp::ADD_OP;
      binary->left = $1;
      binary->right = $3;

      ExprSqlNode* expr = new ExprSqlNode;
      expr->type = ExprSqlNodeType::BINARY;
      expr->binary_expr = binary;

      $$ = expr;
    }
    | expr '-' expr {
      BinaryExprSqlNode* binary = new BinaryExprSqlNode;
      binary->op = ExprOp::SUB_OP;
      binary->left = $1;
      binary->right = $3;

      ExprSqlNode* expr = new ExprSqlNode;
      expr->type = ExprSqlNodeType::BINARY;
      expr->binary_expr = binary;

      $$ = expr;
    }
    | expr '*' expr {
      BinaryExprSqlNode* binary = new BinaryExprSqlNode;
      binary->op = ExprOp::MUL_OP;
      binary->left = $1;
      binary->right = $3;

      ExprSqlNode* expr = new ExprSqlNode;
      expr->type = ExprSqlNodeType::BINARY;
      expr->binary_expr = binary;

      $$ = expr;
    }
    | expr '/' expr {
      BinaryExprSqlNode* binary = new BinaryExprSqlNode;
      binary->op = ExprOp::DIV_OP;
      binary->left = $1;
      binary->right = $3;

      ExprSqlNode* expr = new ExprSqlNode;
      expr->type = ExprSqlNodeType::BINARY;
      expr->binary_expr = binary;

      $$ = expr;
    }
    | '-' expr %prec UMINUS {  // 负号
      Value left_val((int)-1);    // val = -1
      UnaryExprSqlNode* left_unary = new UnaryExprSqlNode;
      left_unary->is_attr = false;
      left_unary->value = left_val;
      ExprSqlNode* left_expr = new ExprSqlNode;
      left_expr->type = ExprSqlNodeType::UNARY;
      left_expr->unary_expr = left_unary;

      BinaryExprSqlNode* binary = new BinaryExprSqlNode;
      binary->op = ExprOp::MUL_OP;
      binary->left = left_expr;
      binary->right = $2;
      binary->is_minus = true;

      ExprSqlNode* expr = new ExprSqlNode;
      expr->type = ExprSqlNodeType::BINARY;
      expr->binary_expr = binary;

      $$ = expr;
    }
    | unary_expr { $$ = $1; }
    ;


expr_list:
    /* empty */
    {
      $$ = nullptr;
    }
    | COMMA expr expr_list {
      if ($3 != nullptr) {
        $$ = $3;
      } else {
        $$ = new std::vector<ExprSqlNode *>;
      }

      $$->emplace_back($2);
      // delete $2;     在stmt阶段删除
    }
    | COMMA expr AS ID expr_list {  // 别名
      if ($5 != nullptr) {
        $$ = $5;
      } else {
        $$ = new std::vector<ExprSqlNode *>;
      }
      $2->alias_name = $4;
      free($4);
      $$->emplace_back($2);
    }
    | COMMA expr ID expr_list {  // 别名
      if ($4 != nullptr) {
        $$ = $4;
      } else {
        $$ = new std::vector<ExprSqlNode *>;
      }
      $2->alias_name = $3;
      free($3);
      $$->emplace_back($2);
    }
    ;

func_expr:
    LENGTH LBRACE expr RBRACE {
      FuncExprSqlNode* func = new FuncExprSqlNode;
      func->type = FuncType::FUNC_LENGTH;
      func->exprs.emplace_back($3);

      ExprSqlNode* expr = new ExprSqlNode;
      expr->type = ExprSqlNodeType::FUNCTION;
      expr->func_expr = func;
      $$ = expr;
    }
    | ROUND LBRACE expr RBRACE {
      FuncExprSqlNode* func = new FuncExprSqlNode;
      func->type = FuncType::FUNC_ROUND;
      func->exprs.emplace_back($3);

      ExprSqlNode* expr = new ExprSqlNode;
      expr->type = ExprSqlNodeType::FUNCTION;
      expr->func_expr = func;
      $$ = expr;
    }
    | ROUND LBRACE expr COMMA expr RBRACE {
      FuncExprSqlNode* func = new FuncExprSqlNode;
      func->type = FuncType::FUNC_ROUND;
      func->exprs.emplace_back($3);
      func->exprs.emplace_back($5);

      ExprSqlNode* expr = new ExprSqlNode;
      expr->type = ExprSqlNodeType::FUNCTION;
      expr->func_expr = func;
      $$ = expr;
    }
    | DATE_FORMAT LBRACE expr COMMA expr RBRACE {
      FuncExprSqlNode* func = new FuncExprSqlNode;
      func->type = FuncType::FUNC_DATE_FORMAT;
      func->exprs.emplace_back($3);
      func->exprs.emplace_back($5);

      ExprSqlNode* expr = new ExprSqlNode;
      expr->type = ExprSqlNodeType::FUNCTION;
      expr->func_expr = func;
      $$ = expr;
    }
    ;

aggr_func_expr:
    aggr_func_type LBRACE expr RBRACE {
      AggrExprSqlNode* aggr = new AggrExprSqlNode;
      aggr->type = $1;
      aggr->expr = $3;

      ExprSqlNode* expr = new ExprSqlNode;
      expr->type = ExprSqlNodeType::AGGREGATION;
      expr->aggr_expr = aggr;
      $$ = expr;
    }
    | aggr_func_type LBRACE '*' RBRACE {
      if ($1 != AggrFuncType::AGGR_COUNT) {
        yyerror (&yylloc, sql_string, sql_result, scanner, YY_("aggr func is illegal"));
      }
      AggrExprSqlNode* aggr = new AggrExprSqlNode;
      aggr->type = $1;
      aggr->is_star = true;
      std::string star = "*";
      Value star_val(star.c_str());    // val = *
      UnaryExprSqlNode* star_unary = new UnaryExprSqlNode;
      star_unary->value = star_val;

      ExprSqlNode* expr = new ExprSqlNode;
      expr->type = ExprSqlNodeType::AGGREGATION;
      expr->aggr_expr = aggr;
      $$ = expr;
    }
    ;

aggr_func_type:
    AGGR_MAX {
      $$ = AggrFuncType::AGGR_MAX;
    }
    | AGGR_MIN {
      $$ = AggrFuncType::AGGR_MIN;
    }
    | AGGR_SUM {
      $$ = AggrFuncType::AGGR_SUM;
    }
    | AGGR_AVG {
      $$ = AggrFuncType::AGGR_AVG;
    }
    | AGGR_COUNT {
      $$ = AggrFuncType::AGGR_COUNT;
    }
    ;

add_expr:   // 二元表达式 低优先级
    mul_expr { $$ = $1; }
    | add_expr '+' mul_expr {
      BinaryExprSqlNode* binary = new BinaryExprSqlNode;
      binary->op = ExprOp::ADD_OP;
      binary->left = $1;
      binary->right = $3;

      ExprSqlNode* expr = new ExprSqlNode;
      expr->type = ExprSqlNodeType::BINARY;
      expr->binary_expr = binary;

      $$ = expr;
    }
    | add_expr '-' mul_expr {
      BinaryExprSqlNode* binary = new BinaryExprSqlNode;
      binary->op = ExprOp::SUB_OP;
      binary->left = $1;
      binary->right = $3;

      ExprSqlNode* expr = new ExprSqlNode;
      expr->type = ExprSqlNodeType::BINARY;
      expr->binary_expr = binary;

      $$ = expr;
    }
    ;


mul_expr:   // 二元表达式 高优先级
    unary_expr {
      $$ = $1;
    }
    | '-' unary_expr {
      Value left_val((int)-1);    // val = -1
      UnaryExprSqlNode* left_unary = new UnaryExprSqlNode;
      left_unary->is_attr = false;
      left_unary->value = left_val;
      ExprSqlNode* left_expr = new ExprSqlNode;
      left_expr->type = ExprSqlNodeType::UNARY;
      left_expr->unary_expr = left_unary;

      BinaryExprSqlNode* binary = new BinaryExprSqlNode;
      binary->op = ExprOp::MUL_OP;
      binary->left = left_expr;
      binary->right = $2;
      binary->is_minus = true;

      ExprSqlNode* expr = new ExprSqlNode;
      expr->type = ExprSqlNodeType::BINARY;
      expr->binary_expr = binary;

      $$ = expr;
    }
    | mul_expr '*' unary_expr {
      BinaryExprSqlNode* binary = new BinaryExprSqlNode;
      binary->op = ExprOp::MUL_OP;
      binary->left = $1;
      binary->right = $3;

      ExprSqlNode* expr = new ExprSqlNode;
      expr->type = ExprSqlNodeType::BINARY;
      expr->binary_expr = binary;

      $$ = expr;
    }
    | mul_expr '/' unary_expr {
      BinaryExprSqlNode* binary = new BinaryExprSqlNode;
      binary->op = ExprOp::DIV_OP;
      binary->left = $1;
      binary->right = $3;

      ExprSqlNode* expr = new ExprSqlNode;
      expr->type = ExprSqlNodeType::BINARY;
      expr->binary_expr = binary;

      $$ = expr;
    }
    ;
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
index_attr_list:
    /* empty */
    {
      $$ = nullptr;
    }
    | COMMA ID index_attr_list {
      if ($3 != nullptr) {
        $$ = $3;
      } else {
        $$ = new std::vector<string>;
      }

      $$->emplace_back($2);
      free($2);
    }
    ;
select_attr:
    '*' {
      RelAttrSqlNode attr;
      attr.relation_name  = "";
      attr.attribute_name = "*";

      UnaryExprSqlNode* unary = new UnaryExprSqlNode;
      unary->is_attr = true;
      unary->attr = attr;

      ExprSqlNode* expr = new ExprSqlNode;
      expr->type = ExprSqlNodeType::UNARY;
      expr->unary_expr = unary;

      $$ = new std::vector<ExprSqlNode*>;
      $$->emplace_back(expr);
    }
    // todo ID DOT '*' attr_list {}
    | expr expr_list {
      if ($2 != nullptr) {
        $$ = $2;
      } else {
        $$ = new std::vector<ExprSqlNode*>;
      }
      $$->emplace_back($1);
    }
    | expr AS ID expr_list {    // 别名
      if ($4 != nullptr) {
        $$ = $4;
      } else {
        $$ = new std::vector<ExprSqlNode*>;
      }
      $1->alias_name = $3;
      free($3);
      $$->emplace_back($1);
    }
    | expr ID expr_list {    // 别名
      if ($3 != nullptr) {
        $$ = $3;
      } else {
        $$ = new std::vector<ExprSqlNode*>;
      }
      $1->alias_name = $2;
      free($2);
      $$->emplace_back($1);
    }
    ;

select_from:
    ID rel_list {
      if ($2 != nullptr) {
        $$ = $2;
      } else {
        $$ = new RelationSqlNode;
      }
      $$->relation_names.push_back($1);
      $$->alias_names.push_back("");
      free($1);
    }
    | ID AS ID rel_list {   // 包含别名
      if ($4 != nullptr) {
        $$ = $4;
      } else {
        $$ = new RelationSqlNode;
      }
      $$->relation_names.push_back($1);
      $$->alias_names.push_back($3);
      free($1);
      free($3);
    }
    | ID ID rel_list {   // 包含别名
      if ($3 != nullptr) {
        $$ = $3;
      } else {
        $$ = new RelationSqlNode;
      }
      $$->relation_names.push_back($1);
      $$->alias_names.push_back($2);
      free($1);
      free($2);
    }
    ;

rel_attr:
    ID {
      $$ = new RelAttrSqlNode;
      $$->attribute_name = $1;
      free($1);
    }
    | ID DOT ID {
      $$ = new RelAttrSqlNode;
      $$->relation_name  = $1;
      $$->attribute_name = $3;
      free($1);
      free($3);
    }
    ;

attr_list:
    /* empty */
    {
      $$ = nullptr;
    }
    | COMMA rel_attr attr_list {
      if ($3 != nullptr) {
        $$ = $3;
      } else {
        $$ = new std::vector<RelAttrSqlNode>;
      }

      $$->emplace_back(*$2);
      delete $2;
    }
    ;

rel_list:
    /* empty */
    {
      $$ = nullptr;
    }
    | COMMA ID rel_list {
      if ($3 != nullptr) {
        $$ = $3;
      } else {
        $$ = new RelationSqlNode;
      }
      $$->relation_names.push_back($2);
      $$->alias_names.push_back("");
      free($2);
    }
    | COMMA ID AS ID rel_list { // 别名
      if ($5 != nullptr) {
        $$ = $5;
      } else {
        $$ = new RelationSqlNode;
      }
      $$->relation_names.push_back($2);
      $$->alias_names.push_back($4);
      free($2);
      free($4);
    }
    | COMMA ID ID rel_list { // 别名
      if ($4 != nullptr) {
        $$ = $4;
      } else {
        $$ = new RelationSqlNode;
      }
      $$->relation_names.push_back($2);
      $$->alias_names.push_back($3);
      free($2);
      free($3);
    }
    | INNER JOIN ID inner_condition_list rel_list{  // todo INNER JOIN ID AS ID
      if ($5 != nullptr) {
         $$ = $5;
      } else {
         $$ = new RelationSqlNode;
      }
      std::vector<ConditionSqlNode> &conditions = $$->conditions;
      if ($4 != nullptr)
      {
         conditions.insert(conditions.end(), $4->begin(), $4->end());
         delete $4;
      }
      $$->relation_names.push_back($3);
      $$->alias_names.push_back("");
      free($3);
    }
    ;
inner_condition_list:
	/* empty */ {
       $$ = nullptr;
    }
	| ON condition_list {
       $$ = $2;
	}
	;
where:
    /* empty */
    {
      $$ = nullptr;
    }
    | WHERE condition_list {
      $$ = $2;  
    }
    ;
sort_unit:
	rel_attr
	{
		$$ = new OrderBySqlNode;
		$$->attribute = *$1;
		$$->is_asc = true;

		delete $1;
	}
	|
	rel_attr ASC
	{
		$$ = new OrderBySqlNode;
        $$->attribute = *$1;
      	$$->is_asc = true;

      	delete $1;
	}
	|
	rel_attr DESC
	{
		$$ = new OrderBySqlNode;
        $$->attribute = *$1;
      	$$->is_asc = false;

      	delete $1;
	}
	;
sort_list:
	/* empty */
	{
        $$ = nullptr;
	}
	| sort_unit
    {
        $$ = new std::vector<OrderBySqlNode>;
        $$->emplace_back(*$1);
        delete $1;
    }
	| sort_unit COMMA sort_list
	{
        $$ = $3;
        $$->emplace_back(*$1);
        delete $1;
	}
	;
order_by:
    /* empty */
    {
      $$ = nullptr;
    }
    | ORDER BY sort_list {
      $$ = $3;
      std::reverse($$->begin(), $$->end());
    }
    ;

condition_list:
    /* empty */
    {
      $$ = nullptr;
    }
    | condition {
      $$ = new std::vector<ConditionSqlNode>;
      $$->emplace_back(*$1);
      delete $1;
    }
    | condition AND condition_list {
      $$ = $3;
      $$->emplace_back(*$1);
      delete $1;
    }
    ;
condition:
    expr comp_op expr
    {
      $$ = new ConditionSqlNode;
      $$->left = $1;
      $$->comp = $2;
      $$->right = $3;
    }
    // todo IS NULL, IS NOT NULL
    /*rel_attr comp_op value
    {
      $$ = new ConditionSqlNode;
      $$->left_is_attr = 1;
      $$->left_attr = *$1;
      $$->right_is_attr = 0;
      $$->right_value = *$3;
      $$->comp = $2;

      delete $1;
      delete $3;
    }
    | value comp_op value 
    {
      $$ = new ConditionSqlNode;
      $$->left_is_attr = 0;
      $$->left_value = *$1;
      $$->right_is_attr = 0;
      $$->right_value = *$3;
      $$->comp = $2;

      delete $1;
      delete $3;
    }
    | rel_attr comp_op rel_attr
    {
      $$ = new ConditionSqlNode;
      $$->left_is_attr = 1;
      $$->left_attr = *$1;
      $$->right_is_attr = 1;
      $$->right_attr = *$3;
      $$->comp = $2;

      delete $1;
      delete $3;
    }
    | value comp_op rel_attr
    {
      $$ = new ConditionSqlNode;
      $$->left_is_attr = 0;
      $$->left_value = *$1;
      $$->right_is_attr = 1;
      $$->right_attr = *$3;
      $$->comp = $2;

      delete $1;
      delete $3;
    }*/
    ;

comp_op:
      EQ { $$ = EQUAL_TO; }
    | LT { $$ = LESS_THAN; }
    | GT { $$ = GREAT_THAN; }
    | LE { $$ = LESS_EQUAL; }
    | GE { $$ = GREAT_EQUAL; }
    | NE { $$ = NOT_EQUAL; }
    | LIKE { $$ = LIKE_OP; }
    | NOT LIKE { $$ = NOT_LIKE_OP; }
    ;

load_data_stmt:
    LOAD DATA INFILE SSS INTO TABLE ID 
    {
      char *tmp_file_name = common::substr($4, 1, strlen($4) - 2);
      
      $$ = new ParsedSqlNode(SCF_LOAD_DATA);
      $$->load_data.relation_name = $7;
      $$->load_data.file_name = tmp_file_name;
      free($7);
      free(tmp_file_name);
    }
    ;

explain_stmt:
    EXPLAIN command_wrapper
    {
      $$ = new ParsedSqlNode(SCF_EXPLAIN);
      $$->explain.sql_node = std::unique_ptr<ParsedSqlNode>($2);
    }
    ;

set_variable_stmt:
    SET ID EQ value
    {
      $$ = new ParsedSqlNode(SCF_SET_VARIABLE);
      $$->set_variable.name  = $2;
      $$->set_variable.value = *$4;
      free($2);
      delete $4;
    }
    ;

opt_semicolon: /*empty*/
    | SEMICOLON
    ;
%%
//_____________________________________________________________________
extern void scan_string(const char *str, yyscan_t scanner);

int sql_parse(const char *s, ParsedSqlResult *sql_result) {
  yyscan_t scanner;
  yylex_init(&scanner);
  scan_string(s, scanner);
  int result = yyparse(s, sql_result, scanner);
  yylex_destroy(scanner);
  return result;
}
