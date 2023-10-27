/* A Bison parser, made by GNU Bison 3.0.4.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015 Free Software Foundation, Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "3.0.4"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 2

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* Copy the first part of user declarations.  */
#line 2 "yacc_sql.y" /* yacc.c:339  */


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


#line 112 "yacc_sql.cpp" /* yacc.c:339  */

# ifndef YY_NULLPTR
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULLPTR nullptr
#  else
#   define YY_NULLPTR 0
#  endif
# endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 1
#endif

/* In a future release of Bison, this section will be replaced
   by #include "yacc_sql.hpp".  */
#ifndef YY_YY_YACC_SQL_HPP_INCLUDED
# define YY_YY_YACC_SQL_HPP_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    SEMICOLON = 258,
    CREATE = 259,
    DROP = 260,
    TABLE = 261,
    TABLES = 262,
    INDEX = 263,
    INNER = 264,
    JOIN = 265,
    CALC = 266,
    SELECT = 267,
    DESC = 268,
    ASC = 269,
    SHOW = 270,
    SYNC = 271,
    INSERT = 272,
    DELETE = 273,
    UPDATE = 274,
    LBRACE = 275,
    RBRACE = 276,
    COMMA = 277,
    TRX_BEGIN = 278,
    TRX_COMMIT = 279,
    TRX_ROLLBACK = 280,
    INT_T = 281,
    STRING_T = 282,
    FLOAT_T = 283,
    DATE_T = 284,
    TEXT_T = 285,
    HELP = 286,
    EXIT = 287,
    DOT = 288,
    INTO = 289,
    VALUES = 290,
    FROM = 291,
    WHERE = 292,
    AND = 293,
    SET = 294,
    ON = 295,
    LOAD = 296,
    DATA = 297,
    INFILE = 298,
    EXPLAIN = 299,
    NOT = 300,
    LIKE = 301,
    UNIQUE = 302,
    ORDER = 303,
    GROUP = 304,
    BY = 305,
    HAVING = 306,
    EXISTS = 307,
    IN = 308,
    NULL_T = 309,
    AGGR_MAX = 310,
    AGGR_MIN = 311,
    AGGR_COUNT = 312,
    AGGR_AVG = 313,
    AGGR_SUM = 314,
    LENGTH = 315,
    ROUND = 316,
    DATE_FORMAT = 317,
    AS = 318,
    IS = 319,
    EQ = 320,
    LT = 321,
    GT = 322,
    LE = 323,
    GE = 324,
    NE = 325,
    NUMBER = 326,
    FLOAT = 327,
    ID = 328,
    SSS = 329,
    DATE_STR = 330,
    UMINUS = 331
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 129 "yacc_sql.y" /* yacc.c:355  */

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


#line 260 "yacc_sql.cpp" /* yacc.c:355  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif

/* Location type.  */
#if ! defined YYLTYPE && ! defined YYLTYPE_IS_DECLARED
typedef struct YYLTYPE YYLTYPE;
struct YYLTYPE
{
  int first_line;
  int first_column;
  int last_line;
  int last_column;
};
# define YYLTYPE_IS_DECLARED 1
# define YYLTYPE_IS_TRIVIAL 1
#endif



int yyparse (const char * sql_string, ParsedSqlResult * sql_result, void * scanner);

#endif /* !YY_YY_YACC_SQL_HPP_INCLUDED  */

/* Copy the second part of user declarations.  */

#line 290 "yacc_sql.cpp" /* yacc.c:358  */

#ifdef short
# undef short
#endif

#ifdef YYTYPE_UINT8
typedef YYTYPE_UINT8 yytype_uint8;
#else
typedef unsigned char yytype_uint8;
#endif

#ifdef YYTYPE_INT8
typedef YYTYPE_INT8 yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short int yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short int yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif

#ifndef YY_ATTRIBUTE
# if (defined __GNUC__                                               \
      && (2 < __GNUC__ || (__GNUC__ == 2 && 96 <= __GNUC_MINOR__)))  \
     || defined __SUNPRO_C && 0x5110 <= __SUNPRO_C
#  define YY_ATTRIBUTE(Spec) __attribute__(Spec)
# else
#  define YY_ATTRIBUTE(Spec) /* empty */
# endif
#endif

#ifndef YY_ATTRIBUTE_PURE
# define YY_ATTRIBUTE_PURE   YY_ATTRIBUTE ((__pure__))
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# define YY_ATTRIBUTE_UNUSED YY_ATTRIBUTE ((__unused__))
#endif

#if !defined _Noreturn \
     && (!defined __STDC_VERSION__ || __STDC_VERSION__ < 201112)
# if defined _MSC_VER && 1200 <= _MSC_VER
#  define _Noreturn __declspec (noreturn)
# else
#  define _Noreturn YY_ATTRIBUTE ((__noreturn__))
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN \
    _Pragma ("GCC diagnostic push") \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")\
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# define YY_IGNORE_MAYBE_UNINITIALIZED_END \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif


#if ! defined yyoverflow || YYERROR_VERBOSE

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
             && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL \
             && defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
  YYLTYPE yyls_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE) + sizeof (YYLTYPE)) \
      + 2 * YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYSIZE_T yynewbytes;                                            \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / sizeof (*yyptr);                          \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, (Count) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYSIZE_T yyi;                         \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  87
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   376

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  81
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  60
/* YYNRULES -- Number of rules.  */
#define YYNRULES  165
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  307

/* YYTRANSLATE[YYX] -- Symbol number corresponding to YYX as returned
   by yylex, with out-of-bounds checking.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   331

#define YYTRANSLATE(YYX)                                                \
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, without out-of-bounds checking.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,    78,    76,     2,    77,     2,    79,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    66,    67,    68,    69,    70,    71,    72,    73,    74,
      75,    80
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   240,   240,   248,   249,   250,   251,   252,   253,   254,
     255,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   273,   279,   284,   290,   296,
     302,   308,   315,   320,   327,   335,   354,   376,   386,   404,
     414,   424,   444,   467,   470,   483,   492,   500,   509,   518,
     527,   536,   547,   550,   551,   552,   553,   556,   572,   575,
     589,   603,   606,   617,   621,   625,   629,   633,   647,   652,
     658,   685,   704,   714,   717,   728,   735,   769,   779,   784,
     795,   798,   801,   804,   807,   811,   814,   825,   837,   849,
     852,   855,   863,   875,   887,   899,   911,   932,   938,   941,
     951,   961,   974,   984,   994,  1005,  1019,  1029,  1057,  1060,
    1063,  1066,  1069,  1156,  1159,  1171,  1188,  1196,  1206,  1219,
    1229,  1240,  1254,  1259,  1287,  1290,  1300,  1311,  1322,  1340,
    1343,  1349,  1352,  1359,  1362,  1368,  1374,  1383,  1386,  1393,
    1402,  1411,  1422,  1425,  1431,  1440,  1443,  1452,  1455,  1460,
    1467,  1474,  1491,  1560,  1561,  1562,  1563,  1564,  1565,  1566,
    1567,  1571,  1584,  1592,  1602,  1603
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 1
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "SEMICOLON", "CREATE", "DROP", "TABLE",
  "TABLES", "INDEX", "INNER", "JOIN", "CALC", "SELECT", "DESC", "ASC",
  "SHOW", "SYNC", "INSERT", "DELETE", "UPDATE", "LBRACE", "RBRACE",
  "COMMA", "TRX_BEGIN", "TRX_COMMIT", "TRX_ROLLBACK", "INT_T", "STRING_T",
  "FLOAT_T", "DATE_T", "TEXT_T", "HELP", "EXIT", "DOT", "INTO", "VALUES",
  "FROM", "WHERE", "AND", "SET", "ON", "LOAD", "DATA", "INFILE", "EXPLAIN",
  "NOT", "LIKE", "UNIQUE", "ORDER", "GROUP", "BY", "HAVING", "EXISTS",
  "IN", "NULL_T", "AGGR_MAX", "AGGR_MIN", "AGGR_COUNT", "AGGR_AVG",
  "AGGR_SUM", "LENGTH", "ROUND", "DATE_FORMAT", "AS", "IS", "EQ", "LT",
  "GT", "LE", "GE", "NE", "NUMBER", "FLOAT", "ID", "SSS", "DATE_STR",
  "'+'", "'-'", "'*'", "'/'", "UMINUS", "$accept", "commands",
  "command_wrapper", "exit_stmt", "help_stmt", "sync_stmt", "begin_stmt",
  "commit_stmt", "rollback_stmt", "drop_table_stmt", "show_tables_stmt",
  "show_index_stmt", "desc_table_stmt", "create_index_stmt",
  "drop_index_stmt", "create_table_stmt", "create_table_select_stmt",
  "attr_def_list", "attr_def", "number", "type", "insert_stmt",
  "row_value_list", "row_value", "value_list", "value", "delete_stmt",
  "update_stmt", "update_value", "update_value_list", "select_stmt",
  "calc_stmt", "expression_list", "expression", "unary_expr", "expr",
  "expr_list", "func_expr", "aggr_func_expr", "aggr_func_type",
  "index_attr_list", "select_attr", "select_from", "rel_attr", "rel_list",
  "inner_condition_list", "where", "having", "group_list", "group_by",
  "sort_unit", "sort_list", "order_by", "condition_list", "condition",
  "comp_op", "load_data_stmt", "explain_stmt", "set_variable_stmt",
  "opt_semicolon", YY_NULLPTR
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301,   302,   303,   304,
     305,   306,   307,   308,   309,   310,   311,   312,   313,   314,
     315,   316,   317,   318,   319,   320,   321,   322,   323,   324,
     325,   326,   327,   328,   329,   330,    43,    45,    42,    47,
     331
};
# endif

#define YYPACT_NINF -261

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-261)))

#define YYTABLE_NINF -1

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     306,    40,    29,   204,    69,   -61,     8,  -261,   -11,   -17,
     -43,  -261,  -261,  -261,  -261,  -261,   -39,    15,   306,    38,
      46,  -261,  -261,  -261,  -261,  -261,  -261,  -261,  -261,  -261,
    -261,  -261,  -261,  -261,  -261,  -261,  -261,  -261,  -261,  -261,
    -261,  -261,  -261,    48,    64,    84,    65,    82,   204,  -261,
    -261,  -261,  -261,  -261,   214,  -261,  -261,    73,   158,  -261,
    -261,  -261,  -261,  -261,    68,    99,   140,   128,   182,  -261,
    -261,  -261,   187,  -261,  -261,   133,    66,  -261,  -261,  -261,
     130,    94,    95,   134,   104,   129,  -261,  -261,  -261,  -261,
       2,   135,   101,  -261,   137,    -1,  -261,  -261,  -261,   204,
     204,   204,   204,   204,     3,   158,   158,   158,   111,  -261,
     158,   112,   157,   158,   158,   158,   158,  -261,   178,     7,
     148,   149,   188,   189,   154,   126,   171,   155,   235,  -261,
     176,   212,   196,  -261,  -261,   -37,   -37,  -261,  -261,  -261,
      39,   -15,   229,  -261,   224,   157,  -261,    -8,    -8,  -261,
    -261,  -261,  -261,    -5,   189,  -261,   242,   158,  -261,   205,
     249,    19,  -261,   238,   106,   251,  -261,   254,   207,  -261,
    -261,  -261,   158,   158,   209,   157,  -261,  -261,   267,   210,
     211,     4,  -261,   241,   126,   270,   287,  -261,   255,   126,
     154,   189,  -261,  -261,   288,  -261,  -261,  -261,  -261,  -261,
     100,   155,   274,   223,   278,    80,    86,   157,  -261,   226,
      -4,     4,  -261,   259,   253,   290,   242,  -261,   280,  -261,
     -18,  -261,  -261,  -261,  -261,  -261,  -261,   158,   158,  -261,
     249,  -261,   247,   256,   281,  -261,   251,     9,   312,   263,
    -261,  -261,  -261,   299,   268,     4,  -261,  -261,   269,   158,
     292,   126,   307,   270,  -261,   289,  -261,   -24,  -261,  -261,
    -261,  -261,   323,  -261,  -261,   235,  -261,   273,   327,   312,
     158,     4,     4,  -261,   336,  -261,  -261,   309,  -261,   290,
    -261,  -261,  -261,   -14,  -261,   312,  -261,   328,  -261,  -261,
    -261,   269,   269,  -261,   308,  -261,  -261,  -261,  -261,    96,
     338,  -261,  -261,  -261,  -261,   269,  -261
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     0,     0,     0,     0,     0,     0,    27,     0,     0,
       0,    28,    29,    30,    26,    25,     0,     0,     0,     0,
     164,    24,    23,    16,    17,    18,    19,    10,    11,    12,
      13,    14,    15,     8,     9,     5,     7,     6,     4,     3,
      20,    21,    22,     0,     0,     0,     0,     0,     0,    69,
      63,    65,    68,    67,     0,    86,    77,    78,     0,   108,
     109,   112,   111,   110,     0,     0,     0,   122,     0,   115,
      87,    97,    98,    89,    90,     0,    75,    88,    34,    32,
       0,     0,     0,     0,     0,     0,   162,     1,   165,     2,
       0,     0,     0,    31,     0,     0,    63,    65,    85,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    96,
       0,     0,    98,     0,     0,     0,     0,   116,     0,     0,
       0,     0,     0,   131,     0,     0,     0,     0,     0,    40,
       0,     0,     0,    84,    79,    80,    81,    82,    83,    91,
       0,     0,     0,   123,    98,    98,   118,    92,    93,    94,
      95,   107,   106,   124,   131,    33,     0,   147,    70,     0,
      73,     0,   163,     0,     0,    43,    39,     0,     0,    37,
     102,   103,     0,     0,     0,    98,    99,   117,     0,     0,
       0,   124,   119,   137,     0,    58,     0,   132,   148,     0,
       0,   131,    64,    66,     0,    53,    54,    55,    56,    46,
      47,     0,     0,     0,     0,     0,     0,    98,   101,     0,
     124,   124,   121,     0,   133,    61,     0,    57,     0,   159,
       0,   153,   154,   155,   156,   157,   158,     0,   147,    72,
      73,    71,     0,     0,     0,    49,    43,    38,   113,     0,
     104,   105,   100,   129,     0,   124,   125,   120,     0,   147,
     145,     0,     0,    58,   160,     0,   151,   150,   149,    74,
     161,    52,     0,    51,    44,     0,    42,     0,     0,   113,
     147,   124,   124,   127,   135,   138,   134,     0,    76,    61,
      60,    59,   152,    45,    41,   113,    35,     0,   130,   128,
     126,     0,   142,    62,     0,    48,   114,    36,   136,   139,
     143,   146,    50,   141,   140,   142,   144
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -261,  -261,   343,  -261,  -261,  -261,  -261,  -261,  -261,  -261,
    -261,  -261,  -261,  -261,  -261,  -261,  -261,   131,   167,  -261,
    -261,  -261,   116,   156,    91,    -3,  -261,  -261,   181,   143,
     -89,  -261,   275,   213,  -261,    -2,  -101,  -261,  -261,  -261,
    -260,  -261,  -261,  -109,  -178,  -261,  -144,  -261,    85,  -261,
    -261,    70,  -261,  -220,  -261,  -261,  -261,  -261,  -261,  -261
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,    19,    20,    21,    22,    23,    24,    25,    26,    27,
      28,    29,    30,    31,    32,    33,    34,   202,   165,   262,
     200,    35,   217,   185,   252,    70,    36,    37,   160,   191,
      38,    39,    56,    57,    71,   186,   117,    73,    74,    75,
     268,    76,   154,    77,   182,   271,   158,   250,   275,   214,
     300,   301,   278,   187,   188,   227,    40,    41,    42,    89
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_uint16 yytable[] =
{
      55,   129,    72,   212,   178,   178,   171,   172,   258,   287,
     183,   146,    78,   178,     4,    79,    80,   179,   179,    82,
     133,     4,   127,    81,   139,   296,   179,   255,   152,   276,
      83,   294,   246,   247,    84,    46,   256,    47,    87,   166,
     295,   102,   103,   176,   177,    55,    43,   231,    44,    88,
     288,    55,   113,   114,   115,   116,   104,    85,   180,   244,
     170,   113,   114,   115,   116,   128,   109,   273,   181,   245,
     115,   116,   265,   119,   208,   100,   101,   102,   103,   113,
     114,   115,   116,   113,   114,   115,   116,    45,   105,    58,
     192,   193,    92,   289,   290,    99,    55,    55,    55,    55,
      55,   240,   120,   140,   141,   142,   242,   241,   144,   303,
     304,   147,   148,   149,   150,   113,   114,   115,   116,   106,
     233,    90,   162,    49,    59,    60,    61,    62,    63,    64,
      65,    66,   195,   196,   197,   198,   199,    91,    93,   274,
      50,    51,    67,    52,    53,   234,    68,    69,   266,   100,
     101,   102,   103,    58,   235,    94,   113,   114,   115,   116,
     107,   108,   113,   114,   115,   116,   121,   122,   123,   125,
     205,   206,   126,   124,   131,   130,   284,   132,    58,   110,
      49,   215,   274,   299,   143,   145,   229,    49,    59,    60,
      61,    62,    63,    64,    65,    66,   299,    50,    51,   151,
      52,    53,    58,   161,    50,    51,    67,    52,    53,   110,
      68,   118,    49,    59,    60,    61,    62,    63,    64,    65,
      66,   153,   155,   156,    48,   257,   157,   159,   164,    50,
      51,    67,    52,    53,    48,    68,    49,    59,    60,    61,
      62,    63,    64,    65,    66,   163,   110,     4,   279,   167,
     111,   173,   168,    96,    97,    67,    52,    53,    49,    68,
     112,    95,   184,   113,   114,   115,   116,    98,    49,   169,
     189,   190,   194,   201,   203,    50,    51,   209,    52,    53,
     204,    54,   207,   210,   211,    96,    97,   174,    52,    53,
     213,    54,   216,   228,   232,   237,   238,   175,   239,   243,
     113,   114,   115,   116,   249,   113,   114,   115,   116,   248,
       1,     2,   251,   135,   136,   137,   138,     3,     4,     5,
     260,     6,     7,     8,     9,    10,   254,   261,   280,    11,
      12,    13,   218,   219,   267,   263,   269,    14,    15,   270,
     277,   272,    67,   282,   283,    16,   285,    17,   286,   297,
      18,   220,   221,   222,   223,   224,   225,   226,   291,   292,
     305,    86,   302,   113,   114,   115,   116,   264,   236,   281,
     293,   230,   253,   259,   134,   306,   298
};

static const yytype_uint16 yycheck[] =
{
       3,    90,     4,   181,     9,     9,    21,    22,   228,   269,
     154,   112,    73,     9,    12,     7,     8,    22,    22,    36,
      21,    12,    20,    34,    21,   285,    22,    45,    21,   249,
      73,    45,   210,   211,    73,     6,    54,     8,     0,   128,
      54,    78,    79,   144,   145,    48,     6,   191,     8,     3,
     270,    54,    76,    77,    78,    79,    58,    42,    63,    63,
      21,    76,    77,    78,    79,    63,    68,   245,    73,    73,
      78,    79,    63,    75,   175,    76,    77,    78,    79,    76,
      77,    78,    79,    76,    77,    78,    79,    47,    20,    20,
      71,    72,     8,   271,   272,    22,    99,   100,   101,   102,
     103,    21,    36,   105,   106,   107,   207,    21,   110,    13,
      14,   113,   114,   115,   116,    76,    77,    78,    79,    20,
      20,    73,   125,    54,    55,    56,    57,    58,    59,    60,
      61,    62,    26,    27,    28,    29,    30,    73,    73,   248,
      71,    72,    73,    74,    75,    45,    77,    78,   237,    76,
      77,    78,    79,    20,    54,    73,    76,    77,    78,    79,
      20,    33,    76,    77,    78,    79,    36,    73,    73,    65,
     172,   173,    43,    39,    73,    40,   265,    40,    20,    22,
      54,   184,   291,   292,    73,    73,   189,    54,    55,    56,
      57,    58,    59,    60,    61,    62,   305,    71,    72,    21,
      74,    75,    20,    77,    71,    72,    73,    74,    75,    22,
      77,    78,    54,    55,    56,    57,    58,    59,    60,    61,
      62,    73,    73,    35,    20,   227,    37,    73,    73,    71,
      72,    73,    74,    75,    20,    77,    54,    55,    56,    57,
      58,    59,    60,    61,    62,    74,    22,    12,   251,    73,
      63,    22,    40,    71,    72,    73,    74,    75,    54,    77,
      73,    48,    20,    76,    77,    78,    79,    54,    54,    73,
      65,    22,    34,    22,    20,    71,    72,    10,    74,    75,
      73,    77,    73,    73,    73,    71,    72,    63,    74,    75,
      49,    77,    22,    38,     6,    21,    73,    73,    20,    73,
      76,    77,    78,    79,    51,    76,    77,    78,    79,    50,
       4,     5,    22,   100,   101,   102,   103,    11,    12,    13,
      73,    15,    16,    17,    18,    19,    46,    71,    21,    23,
      24,    25,    45,    46,    22,    54,    73,    31,    32,    40,
      48,    73,    73,    54,    21,    39,    73,    41,    21,    21,
      44,    64,    65,    66,    67,    68,    69,    70,    22,    50,
      22,    18,    54,    76,    77,    78,    79,   236,   201,   253,
     279,   190,   216,   230,    99,   305,   291
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     4,     5,    11,    12,    13,    15,    16,    17,    18,
      19,    23,    24,    25,    31,    32,    39,    41,    44,    82,
      83,    84,    85,    86,    87,    88,    89,    90,    91,    92,
      93,    94,    95,    96,    97,   102,   107,   108,   111,   112,
     137,   138,   139,     6,     8,    47,     6,     8,    20,    54,
      71,    72,    74,    75,    77,   106,   113,   114,    20,    55,
      56,    57,    58,    59,    60,    61,    62,    73,    77,    78,
     106,   115,   116,   118,   119,   120,   122,   124,    73,     7,
       8,    34,    36,    73,    73,    42,    83,     0,     3,   140,
      73,    73,     8,    73,    73,   114,    71,    72,   114,    22,
      76,    77,    78,    79,   116,    20,    20,    20,    33,   116,
      22,    63,    73,    76,    77,    78,    79,   117,    78,   116,
      36,    36,    73,    73,    39,    65,    43,    20,    63,   111,
      40,    73,    40,    21,   113,   114,   114,   114,   114,    21,
     116,   116,   116,    73,   116,    73,   117,   116,   116,   116,
     116,    21,    21,    73,   123,    73,    35,    37,   127,    73,
     109,    77,   106,    74,    73,    99,   111,    73,    40,    73,
      21,    21,    22,    22,    63,    73,   117,   117,     9,    22,
      63,    73,   125,   127,    20,   104,   116,   134,   135,    65,
      22,   110,    71,    72,    34,    26,    27,    28,    29,    30,
     101,    22,    98,    20,    73,   116,   116,    73,   117,    10,
      73,    73,   125,    49,   130,   106,    22,   103,    45,    46,
      64,    65,    66,    67,    68,    69,    70,   136,    38,   106,
     109,   127,     6,    20,    45,    54,    99,    21,    73,    20,
      21,    21,   117,    73,    63,    73,   125,   125,    50,    51,
     128,    22,   105,   104,    46,    45,    54,   116,   134,   110,
      73,    71,   100,    54,    98,    63,   111,    22,   121,    73,
      40,   126,    73,   125,   124,   129,   134,    48,   133,   106,
      21,   103,    54,    21,   111,    73,    21,   121,   134,   125,
     125,    22,    50,   105,    45,    54,   121,    21,   129,   124,
     131,   132,    54,    13,    14,    22,   132
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    81,    82,    83,    83,    83,    83,    83,    83,    83,
      83,    83,    83,    83,    83,    83,    83,    83,    83,    83,
      83,    83,    83,    83,    83,    84,    85,    86,    87,    88,
      89,    90,    91,    92,    93,    94,    94,    95,    96,    97,
      97,    97,    97,    98,    98,    99,    99,    99,    99,    99,
      99,    99,   100,   101,   101,   101,   101,   102,   103,   103,
     104,   105,   105,   106,   106,   106,   106,   106,   106,   106,
     107,   108,   109,   110,   110,   111,   111,   112,   113,   113,
     114,   114,   114,   114,   114,   114,   114,   115,   115,   115,
     115,   115,   116,   116,   116,   116,   116,   116,   117,   117,
     117,   117,   118,   118,   118,   118,   119,   119,   120,   120,
     120,   120,   120,   121,   121,   122,   122,   122,   122,   123,
     123,   123,   124,   124,   125,   125,   125,   125,   125,   126,
     126,   127,   127,   128,   128,   129,   129,   130,   130,   131,
     131,   131,   132,   132,   132,   133,   133,   134,   134,   134,
     135,   135,   135,   136,   136,   136,   136,   136,   136,   136,
     136,   137,   138,   139,   140,   140
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     2,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     3,     2,     4,     2,     9,    10,     5,     7,     5,
       4,     9,     8,     0,     3,     5,     2,     2,     6,     3,
       7,     4,     1,     1,     1,     1,     1,     6,     0,     3,
       4,     0,     3,     1,     2,     1,     2,     1,     1,     1,
       4,     6,     3,     0,     3,     2,     8,     2,     1,     3,
       3,     3,     3,     3,     3,     2,     1,     1,     1,     1,
       1,     3,     3,     3,     3,     3,     2,     1,     0,     3,
       5,     4,     4,     4,     6,     6,     3,     3,     1,     1,
       1,     1,     1,     0,     3,     1,     2,     4,     3,     2,
       4,     3,     1,     3,     0,     3,     5,     4,     5,     0,
       2,     0,     2,     0,     2,     1,     3,     0,     3,     1,
       2,     2,     0,     1,     3,     0,     3,     0,     1,     3,
       3,     3,     4,     1,     1,     1,     1,     1,     1,     1,
       2,     7,     2,     4,     0,     1
};


#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)
#define YYEMPTY         (-2)
#define YYEOF           0

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                  \
do                                                              \
  if (yychar == YYEMPTY)                                        \
    {                                                           \
      yychar = (Token);                                         \
      yylval = (Value);                                         \
      YYPOPSTACK (yylen);                                       \
      yystate = *yyssp;                                         \
      goto yybackup;                                            \
    }                                                           \
  else                                                          \
    {                                                           \
      yyerror (&yylloc, sql_string, sql_result, scanner, YY_("syntax error: cannot back up")); \
      YYERROR;                                                  \
    }                                                           \
while (0)

/* Error token number */
#define YYTERROR        1
#define YYERRCODE       256


/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)                                \
    do                                                                  \
      if (N)                                                            \
        {                                                               \
          (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;        \
          (Current).first_column = YYRHSLOC (Rhs, 1).first_column;      \
          (Current).last_line    = YYRHSLOC (Rhs, N).last_line;         \
          (Current).last_column  = YYRHSLOC (Rhs, N).last_column;       \
        }                                                               \
      else                                                              \
        {                                                               \
          (Current).first_line   = (Current).last_line   =              \
            YYRHSLOC (Rhs, 0).last_line;                                \
          (Current).first_column = (Current).last_column =              \
            YYRHSLOC (Rhs, 0).last_column;                              \
        }                                                               \
    while (0)
#endif

#define YYRHSLOC(Rhs, K) ((Rhs)[K])


/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)


/* YY_LOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

#ifndef YY_LOCATION_PRINT
# if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL

/* Print *YYLOCP on YYO.  Private, do not rely on its existence. */

YY_ATTRIBUTE_UNUSED
static unsigned
yy_location_print_ (FILE *yyo, YYLTYPE const * const yylocp)
{
  unsigned res = 0;
  int end_col = 0 != yylocp->last_column ? yylocp->last_column - 1 : 0;
  if (0 <= yylocp->first_line)
    {
      res += YYFPRINTF (yyo, "%d", yylocp->first_line);
      if (0 <= yylocp->first_column)
        res += YYFPRINTF (yyo, ".%d", yylocp->first_column);
    }
  if (0 <= yylocp->last_line)
    {
      if (yylocp->first_line < yylocp->last_line)
        {
          res += YYFPRINTF (yyo, "-%d", yylocp->last_line);
          if (0 <= end_col)
            res += YYFPRINTF (yyo, ".%d", end_col);
        }
      else if (0 <= end_col && yylocp->first_column < end_col)
        res += YYFPRINTF (yyo, "-%d", end_col);
    }
  return res;
 }

#  define YY_LOCATION_PRINT(File, Loc)          \
  yy_location_print_ (File, &(Loc))

# else
#  define YY_LOCATION_PRINT(File, Loc) ((void) 0)
# endif
#endif


# define YY_SYMBOL_PRINT(Title, Type, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Type, Value, Location, sql_string, sql_result, scanner); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*----------------------------------------.
| Print this symbol's value on YYOUTPUT.  |
`----------------------------------------*/

static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp, const char * sql_string, ParsedSqlResult * sql_result, void * scanner)
{
  FILE *yyo = yyoutput;
  YYUSE (yyo);
  YYUSE (yylocationp);
  YYUSE (sql_string);
  YYUSE (sql_result);
  YYUSE (scanner);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# endif
  YYUSE (yytype);
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp, const char * sql_string, ParsedSqlResult * sql_result, void * scanner)
{
  YYFPRINTF (yyoutput, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  YY_LOCATION_PRINT (yyoutput, *yylocationp);
  YYFPRINTF (yyoutput, ": ");
  yy_symbol_value_print (yyoutput, yytype, yyvaluep, yylocationp, sql_string, sql_result, scanner);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yytype_int16 *yyssp, YYSTYPE *yyvsp, YYLTYPE *yylsp, int yyrule, const char * sql_string, ParsedSqlResult * sql_result, void * scanner)
{
  unsigned long int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       yystos[yyssp[yyi + 1 - yynrhs]],
                       &(yyvsp[(yyi + 1) - (yynrhs)])
                       , &(yylsp[(yyi + 1) - (yynrhs)])                       , sql_string, sql_result, scanner);
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, yylsp, Rule, sql_string, sql_result, scanner); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif


#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
static YYSIZE_T
yystrlen (const char *yystr)
{
  YYSIZE_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
static char *
yystpcpy (char *yydest, const char *yysrc)
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYSIZE_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYSIZE_T yyn = 0;
      char const *yyp = yystr;

      for (;;)
        switch (*++yyp)
          {
          case '\'':
          case ',':
            goto do_not_strip_quotes;

          case '\\':
            if (*++yyp != '\\')
              goto do_not_strip_quotes;
            /* Fall through.  */
          default:
            if (yyres)
              yyres[yyn] = *yyp;
            yyn++;
            break;

          case '"':
            if (yyres)
              yyres[yyn] = '\0';
            return yyn;
          }
    do_not_strip_quotes: ;
    }

  if (! yyres)
    return yystrlen (yystr);

  return yystpcpy (yyres, yystr) - yyres;
}
# endif

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return 1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return 2 if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYSIZE_T *yymsg_alloc, char **yymsg,
                yytype_int16 *yyssp, int yytoken)
{
  YYSIZE_T yysize0 = yytnamerr (YY_NULLPTR, yytname[yytoken]);
  YYSIZE_T yysize = yysize0;
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat. */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Number of reported tokens (one for the "unexpected", one per
     "expected"). */
  int yycount = 0;

  /* There are many possibilities here to consider:
     - If this state is a consistent state with a default action, then
       the only way this function was invoked is if the default action
       is an error action.  In that case, don't check for expected
       tokens because there are none.
     - The only way there can be no lookahead present (in yychar) is if
       this state is a consistent state with a default action.  Thus,
       detecting the absence of a lookahead is sufficient to determine
       that there is no unexpected or expected token to report.  In that
       case, just report a simple "syntax error".
     - Don't assume there isn't a lookahead just because this state is a
       consistent state with a default action.  There might have been a
       previous inconsistent state, consistent state with a non-default
       action, or user semantic action that manipulated yychar.
     - Of course, the expected token list depends on states to have
       correct lookahead information, and it depends on the parser not
       to perform extra reductions after fetching a lookahead from the
       scanner and before detecting a syntax error.  Thus, state merging
       (from LALR or IELR) and default reductions corrupt the expected
       token list.  However, the list is correct for canonical LR with
       one exception: it will still contain any token that will not be
       accepted due to an error action in a later state.
  */
  if (yytoken != YYEMPTY)
    {
      int yyn = yypact[*yyssp];
      yyarg[yycount++] = yytname[yytoken];
      if (!yypact_value_is_default (yyn))
        {
          /* Start YYX at -YYN if negative to avoid negative indexes in
             YYCHECK.  In other words, skip the first -YYN actions for
             this state because they are default actions.  */
          int yyxbegin = yyn < 0 ? -yyn : 0;
          /* Stay within bounds of both yycheck and yytname.  */
          int yychecklim = YYLAST - yyn + 1;
          int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
          int yyx;

          for (yyx = yyxbegin; yyx < yyxend; ++yyx)
            if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR
                && !yytable_value_is_error (yytable[yyx + yyn]))
              {
                if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                  {
                    yycount = 1;
                    yysize = yysize0;
                    break;
                  }
                yyarg[yycount++] = yytname[yyx];
                {
                  YYSIZE_T yysize1 = yysize + yytnamerr (YY_NULLPTR, yytname[yyx]);
                  if (! (yysize <= yysize1
                         && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
                    return 2;
                  yysize = yysize1;
                }
              }
        }
    }

  switch (yycount)
    {
# define YYCASE_(N, S)                      \
      case N:                               \
        yyformat = S;                       \
      break
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
# undef YYCASE_
    }

  {
    YYSIZE_T yysize1 = yysize + yystrlen (yyformat);
    if (! (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
      return 2;
    yysize = yysize1;
  }

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return 1;
    }

  /* Avoid sprintf, as that infringes on the user's name space.
     Don't have undefined behavior even if the translation
     produced a string with the wrong number of "%s"s.  */
  {
    char *yyp = *yymsg;
    int yyi = 0;
    while ((*yyp = *yyformat) != '\0')
      if (*yyp == '%' && yyformat[1] == 's' && yyi < yycount)
        {
          yyp += yytnamerr (yyp, yyarg[yyi++]);
          yyformat += 2;
        }
      else
        {
          yyp++;
          yyformat++;
        }
  }
  return 0;
}
#endif /* YYERROR_VERBOSE */

/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep, YYLTYPE *yylocationp, const char * sql_string, ParsedSqlResult * sql_result, void * scanner)
{
  YYUSE (yyvaluep);
  YYUSE (yylocationp);
  YYUSE (sql_string);
  YYUSE (sql_result);
  YYUSE (scanner);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}




/*----------.
| yyparse.  |
`----------*/

int
yyparse (const char * sql_string, ParsedSqlResult * sql_result, void * scanner)
{
/* The lookahead symbol.  */
int yychar;


/* The semantic value of the lookahead symbol.  */
/* Default value used for initialization, for pacifying older GCCs
   or non-GCC compilers.  */
YY_INITIAL_VALUE (static YYSTYPE yyval_default;)
YYSTYPE yylval YY_INITIAL_VALUE (= yyval_default);

/* Location data for the lookahead symbol.  */
static YYLTYPE yyloc_default
# if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL
  = { 1, 1, 1, 1 }
# endif
;
YYLTYPE yylloc = yyloc_default;

    /* Number of syntax errors so far.  */
    int yynerrs;

    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       'yyss': related to states.
       'yyvs': related to semantic values.
       'yyls': related to locations.

       Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yytype_int16 yyssa[YYINITDEPTH];
    yytype_int16 *yyss;
    yytype_int16 *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    /* The location stack.  */
    YYLTYPE yylsa[YYINITDEPTH];
    YYLTYPE *yyls;
    YYLTYPE *yylsp;

    /* The locations where the error started and ended.  */
    YYLTYPE yyerror_range[3];

    YYSIZE_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken = 0;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;
  YYLTYPE yyloc;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N), yylsp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yyssp = yyss = yyssa;
  yyvsp = yyvs = yyvsa;
  yylsp = yyls = yylsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */
  yylsp[0] = yylloc;
  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        YYSTYPE *yyvs1 = yyvs;
        yytype_int16 *yyss1 = yyss;
        YYLTYPE *yyls1 = yyls;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * sizeof (*yyssp),
                    &yyvs1, yysize * sizeof (*yyvsp),
                    &yyls1, yysize * sizeof (*yylsp),
                    &yystacksize);

        yyls = yyls1;
        yyss = yyss1;
        yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyexhaustedlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yytype_int16 *yyss1 = yyss;
        union yyalloc *yyptr =
          (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
        if (! yyptr)
          goto yyexhaustedlab;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
        YYSTACK_RELOCATE (yyls_alloc, yyls);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;
      yylsp = yyls + yysize - 1;

      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
                  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;

/*-----------.
| yybackup.  |
`-----------*/
yybackup:

  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = yylex (&yylval, &yylloc, scanner);
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

  /* Discard the shifted token.  */
  yychar = YYEMPTY;

  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END
  *++yylsp = yylloc;
  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- Do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];

  /* Default location.  */
  YYLLOC_DEFAULT (yyloc, (yylsp - yylen), yylen);
  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 2:
#line 241 "yacc_sql.y" /* yacc.c:1646  */
    {
    std::unique_ptr<ParsedSqlNode> sql_node = std::unique_ptr<ParsedSqlNode>((yyvsp[-1].sql_node));
    sql_result->add_sql_node(std::move(sql_node));
  }
#line 1726 "yacc_sql.cpp" /* yacc.c:1646  */
    break;

  case 25:
#line 273 "yacc_sql.y" /* yacc.c:1646  */
    {
      (void)yynerrs;  // 这么写为了消除yynerrs未使用的告警。如果你有更好的方法欢迎提PR
      (yyval.sql_node) = new ParsedSqlNode(SCF_EXIT);
    }
#line 1735 "yacc_sql.cpp" /* yacc.c:1646  */
    break;

  case 26:
#line 279 "yacc_sql.y" /* yacc.c:1646  */
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_HELP);
    }
#line 1743 "yacc_sql.cpp" /* yacc.c:1646  */
    break;

  case 27:
#line 284 "yacc_sql.y" /* yacc.c:1646  */
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_SYNC);
    }
#line 1751 "yacc_sql.cpp" /* yacc.c:1646  */
    break;

  case 28:
#line 290 "yacc_sql.y" /* yacc.c:1646  */
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_BEGIN);
    }
#line 1759 "yacc_sql.cpp" /* yacc.c:1646  */
    break;

  case 29:
#line 296 "yacc_sql.y" /* yacc.c:1646  */
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_COMMIT);
    }
#line 1767 "yacc_sql.cpp" /* yacc.c:1646  */
    break;

  case 30:
#line 302 "yacc_sql.y" /* yacc.c:1646  */
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_ROLLBACK);
    }
#line 1775 "yacc_sql.cpp" /* yacc.c:1646  */
    break;

  case 31:
#line 308 "yacc_sql.y" /* yacc.c:1646  */
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_DROP_TABLE);
      (yyval.sql_node)->drop_table.relation_name = (yyvsp[0].string);
      free((yyvsp[0].string));
    }
#line 1785 "yacc_sql.cpp" /* yacc.c:1646  */
    break;

  case 32:
#line 315 "yacc_sql.y" /* yacc.c:1646  */
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_SHOW_TABLES);
    }
#line 1793 "yacc_sql.cpp" /* yacc.c:1646  */
    break;

  case 33:
#line 320 "yacc_sql.y" /* yacc.c:1646  */
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_SHOW_INDEX);
      (yyval.sql_node)->show_index.relation_name = (yyvsp[0].string);
      free((yyvsp[0].string));
    }
#line 1803 "yacc_sql.cpp" /* yacc.c:1646  */
    break;

  case 34:
#line 327 "yacc_sql.y" /* yacc.c:1646  */
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_DESC_TABLE);
      (yyval.sql_node)->desc_table.relation_name = (yyvsp[0].string);
      free((yyvsp[0].string));
    }
#line 1813 "yacc_sql.cpp" /* yacc.c:1646  */
    break;

  case 35:
#line 336 "yacc_sql.y" /* yacc.c:1646  */
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_CREATE_INDEX);
      CreateIndexSqlNode &create_index = (yyval.sql_node)->create_index;

      create_index.index_name = (yyvsp[-6].string);
      create_index.relation_name = (yyvsp[-4].string);
      if ((yyvsp[-1].rel_index_attr_list) != nullptr) {
         create_index.attribute_names.swap(*(yyvsp[-1].rel_index_attr_list));
         delete (yyvsp[-1].rel_index_attr_list);
      }
      create_index.attribute_names.push_back((yyvsp[-2].string));
      std::reverse(create_index.attribute_names.begin(), create_index.attribute_names.end());
      create_index.is_unique = false;

      free((yyvsp[-6].string));
      free((yyvsp[-4].string));
      free((yyvsp[-2].string));
    }
#line 1836 "yacc_sql.cpp" /* yacc.c:1646  */
    break;

  case 36:
#line 355 "yacc_sql.y" /* yacc.c:1646  */
    {
        (yyval.sql_node) = new ParsedSqlNode(SCF_CREATE_INDEX);
        CreateIndexSqlNode &create_index = (yyval.sql_node)->create_index;

        create_index.index_name = (yyvsp[-6].string);
        create_index.relation_name = (yyvsp[-4].string);
        if ((yyvsp[-1].rel_index_attr_list) != nullptr) {
           create_index.attribute_names.swap(*(yyvsp[-1].rel_index_attr_list));
           delete (yyvsp[-1].rel_index_attr_list);
        }
        create_index.attribute_names.push_back((yyvsp[-2].string));
        std::reverse(create_index.attribute_names.begin(), create_index.attribute_names.end());
        create_index.is_unique = true;

        free((yyvsp[-6].string));
        free((yyvsp[-4].string));
        free((yyvsp[-2].string));
    }
#line 1859 "yacc_sql.cpp" /* yacc.c:1646  */
    break;

  case 37:
#line 377 "yacc_sql.y" /* yacc.c:1646  */
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_DROP_INDEX);
      (yyval.sql_node)->drop_index.index_name = (yyvsp[-2].string);
      (yyval.sql_node)->drop_index.relation_name = (yyvsp[0].string);
      free((yyvsp[-2].string));
      free((yyvsp[0].string));
    }
#line 1871 "yacc_sql.cpp" /* yacc.c:1646  */
    break;

  case 38:
#line 387 "yacc_sql.y" /* yacc.c:1646  */
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_CREATE_TABLE);
      CreateTableSqlNode &create_table = (yyval.sql_node)->create_table;
      create_table.relation_name = (yyvsp[-4].string);
      free((yyvsp[-4].string));

      std::vector<AttrInfoSqlNode> *src_attrs = (yyvsp[-1].attr_infos);

      if (src_attrs != nullptr) {
        create_table.attr_infos.swap(*src_attrs);
      }
      create_table.attr_infos.emplace_back(*(yyvsp[-2].attr_info));
      std::reverse(create_table.attr_infos.begin(), create_table.attr_infos.end());
      delete (yyvsp[-2].attr_info);
    }
#line 1891 "yacc_sql.cpp" /* yacc.c:1646  */
    break;

  case 39:
#line 405 "yacc_sql.y" /* yacc.c:1646  */
    {
        (yyval.sql_node) = new ParsedSqlNode(SCF_CREATE_TABLE_SELECT);
        CreateTableSelectSqlNode &create_table_select = (yyval.sql_node)->create_table_select;
        create_table_select.relation_name = (yyvsp[-2].string);
        free((yyvsp[-2].string));

        create_table_select.selection = (yyvsp[0].sql_node)->selection;
        delete (yyvsp[0].sql_node);
     }
#line 1905 "yacc_sql.cpp" /* yacc.c:1646  */
    break;

  case 40:
#line 415 "yacc_sql.y" /* yacc.c:1646  */
    {
          (yyval.sql_node) = new ParsedSqlNode(SCF_CREATE_TABLE_SELECT);
          CreateTableSelectSqlNode &create_table_select = (yyval.sql_node)->create_table_select;
          create_table_select.relation_name = (yyvsp[-1].string);
          free((yyvsp[-1].string));

          create_table_select.selection = (yyvsp[0].sql_node)->selection;
          delete (yyvsp[0].sql_node);
       }
#line 1919 "yacc_sql.cpp" /* yacc.c:1646  */
    break;

  case 41:
#line 425 "yacc_sql.y" /* yacc.c:1646  */
    {
        (yyval.sql_node) = new ParsedSqlNode(SCF_CREATE_TABLE_SELECT);
        CreateTableSelectSqlNode &create_table_select = (yyval.sql_node)->create_table_select;
        create_table_select.relation_name = (yyvsp[-6].string);
        free((yyvsp[-6].string));

        std::vector<AttrInfoSqlNode> *src_attrs = (yyvsp[-3].attr_infos);

        if (src_attrs != nullptr) {
          create_table_select.attr_infos.swap(*src_attrs);
        }
        create_table_select.attr_infos.emplace_back(*(yyvsp[-4].attr_info));
        std::reverse(create_table_select.attr_infos.begin(), create_table_select.attr_infos.end());
        delete (yyvsp[-4].attr_info);


        create_table_select.selection = (yyvsp[0].sql_node)->selection;
        delete (yyvsp[0].sql_node);
     }
#line 1943 "yacc_sql.cpp" /* yacc.c:1646  */
    break;

  case 42:
#line 445 "yacc_sql.y" /* yacc.c:1646  */
    {
        (yyval.sql_node) = new ParsedSqlNode(SCF_CREATE_TABLE_SELECT);
        CreateTableSelectSqlNode &create_table_select = (yyval.sql_node)->create_table_select;
        create_table_select.relation_name = (yyvsp[-5].string);
        free((yyvsp[-5].string));

        std::vector<AttrInfoSqlNode> *src_attrs = (yyvsp[-2].attr_infos);

        if (src_attrs != nullptr) {
          create_table_select.attr_infos.swap(*src_attrs);
        }
        create_table_select.attr_infos.emplace_back(*(yyvsp[-3].attr_info));
        std::reverse(create_table_select.attr_infos.begin(), create_table_select.attr_infos.end());
        delete (yyvsp[-3].attr_info);


        create_table_select.selection = (yyvsp[0].sql_node)->selection;
        delete (yyvsp[0].sql_node);
     }
#line 1967 "yacc_sql.cpp" /* yacc.c:1646  */
    break;

  case 43:
#line 467 "yacc_sql.y" /* yacc.c:1646  */
    {
      (yyval.attr_infos) = nullptr;
    }
#line 1975 "yacc_sql.cpp" /* yacc.c:1646  */
    break;

  case 44:
#line 471 "yacc_sql.y" /* yacc.c:1646  */
    {
      if ((yyvsp[0].attr_infos) != nullptr) {
        (yyval.attr_infos) = (yyvsp[0].attr_infos);
      } else {
        (yyval.attr_infos) = new std::vector<AttrInfoSqlNode>;
      }
      (yyval.attr_infos)->emplace_back(*(yyvsp[-1].attr_info));
      delete (yyvsp[-1].attr_info);
    }
#line 1989 "yacc_sql.cpp" /* yacc.c:1646  */
    break;

  case 45:
#line 484 "yacc_sql.y" /* yacc.c:1646  */
    {
      (yyval.attr_info) = new AttrInfoSqlNode;
      (yyval.attr_info)->type = (AttrType)(yyvsp[-3].number);
      (yyval.attr_info)->name = (yyvsp[-4].string);
      (yyval.attr_info)->length = (yyvsp[-1].number);
      (yyval.attr_info)->nullable = true;
      free((yyvsp[-4].string));
    }
#line 2002 "yacc_sql.cpp" /* yacc.c:1646  */
    break;

  case 46:
#line 493 "yacc_sql.y" /* yacc.c:1646  */
    {
      (yyval.attr_info) = new AttrInfoSqlNode;
      (yyval.attr_info)->type = (AttrType)TEXTS;
      (yyval.attr_info)->name = (yyvsp[-1].string);
      (yyval.attr_info)->length = 12;
      free((yyvsp[-1].string));
    }
#line 2014 "yacc_sql.cpp" /* yacc.c:1646  */
    break;

  case 47:
#line 501 "yacc_sql.y" /* yacc.c:1646  */
    {
      (yyval.attr_info) = new AttrInfoSqlNode;
      (yyval.attr_info)->type = (AttrType)(yyvsp[0].number);
      (yyval.attr_info)->name = (yyvsp[-1].string);
      (yyval.attr_info)->length = 4;
      (yyval.attr_info)->nullable = true;
      free((yyvsp[-1].string));
    }
#line 2027 "yacc_sql.cpp" /* yacc.c:1646  */
    break;

  case 48:
#line 510 "yacc_sql.y" /* yacc.c:1646  */
    {
        (yyval.attr_info) = new AttrInfoSqlNode;
        (yyval.attr_info)->type = (AttrType)(yyvsp[-4].number);
        (yyval.attr_info)->name = (yyvsp[-5].string);
        (yyval.attr_info)->length = (yyvsp[-2].number);
        (yyval.attr_info)->nullable = true;
        free((yyvsp[-5].string));
    }
#line 2040 "yacc_sql.cpp" /* yacc.c:1646  */
    break;

  case 49:
#line 519 "yacc_sql.y" /* yacc.c:1646  */
    {
        (yyval.attr_info) = new AttrInfoSqlNode;
        (yyval.attr_info)->type = (AttrType)(yyvsp[-1].number);
        (yyval.attr_info)->name = (yyvsp[-2].string);
        (yyval.attr_info)->length = 4;
        (yyval.attr_info)->nullable = true;
        free((yyvsp[-2].string));
    }
#line 2053 "yacc_sql.cpp" /* yacc.c:1646  */
    break;

  case 50:
#line 528 "yacc_sql.y" /* yacc.c:1646  */
    {
      (yyval.attr_info) = new AttrInfoSqlNode;
      (yyval.attr_info)->type = (AttrType)(yyvsp[-5].number);
      (yyval.attr_info)->name = (yyvsp[-6].string);
      (yyval.attr_info)->length = (yyvsp[-3].number);
      (yyval.attr_info)->nullable = false;
      free((yyvsp[-6].string));
    }
#line 2066 "yacc_sql.cpp" /* yacc.c:1646  */
    break;

  case 51:
#line 537 "yacc_sql.y" /* yacc.c:1646  */
    {
      (yyval.attr_info) = new AttrInfoSqlNode;
      (yyval.attr_info)->type = (AttrType)(yyvsp[-2].number);
      (yyval.attr_info)->name = (yyvsp[-3].string);
      (yyval.attr_info)->length = 4;
      (yyval.attr_info)->nullable = false;
      free((yyvsp[-3].string));
    }
#line 2079 "yacc_sql.cpp" /* yacc.c:1646  */
    break;

  case 52:
#line 547 "yacc_sql.y" /* yacc.c:1646  */
    {(yyval.number) = (yyvsp[0].number);}
#line 2085 "yacc_sql.cpp" /* yacc.c:1646  */
    break;

  case 53:
#line 550 "yacc_sql.y" /* yacc.c:1646  */
    { (yyval.number)=INTS; }
#line 2091 "yacc_sql.cpp" /* yacc.c:1646  */
    break;

  case 54:
#line 551 "yacc_sql.y" /* yacc.c:1646  */
    { (yyval.number)=CHARS; }
#line 2097 "yacc_sql.cpp" /* yacc.c:1646  */
    break;

  case 55:
#line 552 "yacc_sql.y" /* yacc.c:1646  */
    { (yyval.number)=FLOATS; }
#line 2103 "yacc_sql.cpp" /* yacc.c:1646  */
    break;

  case 56:
#line 553 "yacc_sql.y" /* yacc.c:1646  */
    { (yyval.number)=DATES; }
#line 2109 "yacc_sql.cpp" /* yacc.c:1646  */
    break;

  case 57:
#line 557 "yacc_sql.y" /* yacc.c:1646  */
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_INSERT);
      (yyval.sql_node)->insertion.relation_name = (yyvsp[-3].string);
      if ((yyvsp[0].row_value_list) != nullptr) {
        (yyval.sql_node)->insertion.values.swap(*(yyvsp[0].row_value_list));
        delete (yyvsp[0].row_value_list);
      }
      (yyval.sql_node)->insertion.values.emplace_back(*(yyvsp[-1].value_list));
      std::reverse((yyval.sql_node)->insertion.values.begin(), (yyval.sql_node)->insertion.values.end());
      delete (yyvsp[-1].value_list);
      free((yyvsp[-3].string));
    }
#line 2126 "yacc_sql.cpp" /* yacc.c:1646  */
    break;

  case 58:
#line 572 "yacc_sql.y" /* yacc.c:1646  */
    {
	    (yyval.row_value_list) = nullptr;
	}
#line 2134 "yacc_sql.cpp" /* yacc.c:1646  */
    break;

  case 59:
#line 575 "yacc_sql.y" /* yacc.c:1646  */
    {
        if ((yyvsp[0].row_value_list) == nullptr)
        {
            (yyval.row_value_list) = new std::vector<std::vector<Value>>;
        }else
        {
            (yyval.row_value_list) = (yyvsp[0].row_value_list);
        }

        (yyval.row_value_list)->emplace_back(*(yyvsp[-1].value_list));
        delete (yyvsp[-1].value_list);
    }
#line 2151 "yacc_sql.cpp" /* yacc.c:1646  */
    break;

  case 60:
#line 590 "yacc_sql.y" /* yacc.c:1646  */
    {
         (yyval.value_list) = new std::vector<Value>;
         if ((yyvsp[-1].value_list) != nullptr) {
           (yyval.value_list)->swap(*(yyvsp[-1].value_list));
           delete (yyvsp[-1].value_list);
         }
         (yyval.value_list)->emplace_back(*(yyvsp[-2].value));
         std::reverse((yyval.value_list)->begin(), (yyval.value_list)->end());
         delete (yyvsp[-2].value);
    }
#line 2166 "yacc_sql.cpp" /* yacc.c:1646  */
    break;

  case 61:
#line 603 "yacc_sql.y" /* yacc.c:1646  */
    {
      (yyval.value_list) = nullptr;
    }
#line 2174 "yacc_sql.cpp" /* yacc.c:1646  */
    break;

  case 62:
#line 606 "yacc_sql.y" /* yacc.c:1646  */
    {
      if ((yyvsp[0].value_list) != nullptr) {
        (yyval.value_list) = (yyvsp[0].value_list);
      } else {
        (yyval.value_list) = new std::vector<Value>;
      }
      (yyval.value_list)->emplace_back(*(yyvsp[-1].value));
      delete (yyvsp[-1].value);
    }
#line 2188 "yacc_sql.cpp" /* yacc.c:1646  */
    break;

  case 63:
#line 617 "yacc_sql.y" /* yacc.c:1646  */
    {
      (yyval.value) = new Value((int)(yyvsp[0].number));
      (yyloc) = (yylsp[0]);
    }
#line 2197 "yacc_sql.cpp" /* yacc.c:1646  */
    break;

  case 64:
#line 621 "yacc_sql.y" /* yacc.c:1646  */
    {
      (yyval.value) = new Value(-(int)(yyvsp[0].number));
      (yyloc) = (yylsp[-1]);
    }
#line 2206 "yacc_sql.cpp" /* yacc.c:1646  */
    break;

  case 65:
#line 625 "yacc_sql.y" /* yacc.c:1646  */
    {
      (yyval.value) = new Value((float)(yyvsp[0].floats));
      (yyloc) = (yylsp[0]);
    }
#line 2215 "yacc_sql.cpp" /* yacc.c:1646  */
    break;

  case 66:
#line 629 "yacc_sql.y" /* yacc.c:1646  */
    {
      (yyval.value) = new Value(-(float)(yyvsp[0].floats));
      (yyloc) = (yylsp[-1]);
    }
#line 2224 "yacc_sql.cpp" /* yacc.c:1646  */
    break;

  case 67:
#line 633 "yacc_sql.y" /* yacc.c:1646  */
    {
        int p1 = common::find_ch((yyvsp[0].string),1,'-');
        int p2 = common::find_ch((yyvsp[0].string),p1+1,'-');
        char *y = common::substr((yyvsp[0].string),1,p1-1);            // year
        char *m = common::substr((yyvsp[0].string),p1+1,p2-1);         // month
        char *d = common::substr((yyvsp[0].string),p2+1,strlen((yyvsp[0].string))-2); // day
        (yyval.value) = new Value(y,m,d);
        if ((yyval.value)->attr_type() == 0) { // date is illegal
            yyerror (&yylloc, sql_string, sql_result, scanner, YY_("date is illegal"));
        }
        free(y);
        free(m);
        free(d);
    }
#line 2243 "yacc_sql.cpp" /* yacc.c:1646  */
    break;

  case 68:
#line 647 "yacc_sql.y" /* yacc.c:1646  */
    {
      char *tmp = common::substr((yyvsp[0].string),1,strlen((yyvsp[0].string))-2);
      (yyval.value) = new Value(tmp);
      free(tmp);
    }
#line 2253 "yacc_sql.cpp" /* yacc.c:1646  */
    break;

  case 69:
#line 652 "yacc_sql.y" /* yacc.c:1646  */
    {
        (yyval.value) = new Value();
    }
#line 2261 "yacc_sql.cpp" /* yacc.c:1646  */
    break;

  case 70:
#line 659 "yacc_sql.y" /* yacc.c:1646  */
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_DELETE);
      (yyval.sql_node)->deletion.relation_name = (yyvsp[-1].string);
      if ((yyvsp[0].condition_list) != nullptr) {
        (yyval.sql_node)->deletion.conditions.swap(*(yyvsp[0].condition_list));
        delete (yyvsp[0].condition_list);
      }
      free((yyvsp[-1].string));
    }
#line 2275 "yacc_sql.cpp" /* yacc.c:1646  */
    break;

  case 71:
#line 686 "yacc_sql.y" /* yacc.c:1646  */
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_UPDATE);
      (yyval.sql_node)->update.relation_name = (yyvsp[-4].string);
      if ((yyvsp[-1].update_value_list) != nullptr) {
        (yyval.sql_node)->update.update_values.swap(*(yyvsp[-1].update_value_list));
        delete (yyvsp[-1].update_value_list);
      }
      (yyval.sql_node)->update.update_values.emplace_back(*(yyvsp[-2].update_value));
      delete (yyvsp[-2].update_value);
      if ((yyvsp[0].condition_list) != nullptr) {
        (yyval.sql_node)->update.conditions.swap(*(yyvsp[0].condition_list));
        delete (yyvsp[0].condition_list);
      }
      free((yyvsp[-4].string));
    }
#line 2295 "yacc_sql.cpp" /* yacc.c:1646  */
    break;

  case 72:
#line 704 "yacc_sql.y" /* yacc.c:1646  */
    {
      (yyval.update_value) = new UpdateValueNode;
      (yyval.update_value)->attribute_name = (yyvsp[-2].string);
      (yyval.update_value)->value = *(yyvsp[0].value);
      free((yyvsp[-2].string));
      delete((yyvsp[0].value));
    }
#line 2307 "yacc_sql.cpp" /* yacc.c:1646  */
    break;

  case 73:
#line 714 "yacc_sql.y" /* yacc.c:1646  */
    {
      (yyval.update_value_list) = nullptr;
    }
#line 2315 "yacc_sql.cpp" /* yacc.c:1646  */
    break;

  case 74:
#line 717 "yacc_sql.y" /* yacc.c:1646  */
    {
      if ((yyvsp[0].update_value_list) != nullptr) {
        (yyval.update_value_list) = (yyvsp[0].update_value_list);
      } else {
        (yyval.update_value_list) = new std::vector<UpdateValueNode>;
      }
      (yyval.update_value_list)->emplace_back(*(yyvsp[-1].update_value));
      delete (yyvsp[-1].update_value);
    }
#line 2329 "yacc_sql.cpp" /* yacc.c:1646  */
    break;

  case 75:
#line 728 "yacc_sql.y" /* yacc.c:1646  */
    {  // function 可能出现
      (yyval.sql_node) = new ParsedSqlNode(SCF_SELECT);
      if ((yyvsp[0].expr_list) != nullptr) {
        (yyval.sql_node)->selection.project_exprs.swap(*(yyvsp[0].expr_list));
        delete (yyvsp[0].expr_list);
      }
    }
#line 2341 "yacc_sql.cpp" /* yacc.c:1646  */
    break;

  case 76:
#line 736 "yacc_sql.y" /* yacc.c:1646  */
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_SELECT);
      if ((yyvsp[-6].expr_list) != nullptr) {
        (yyval.sql_node)->selection.project_exprs.swap(*(yyvsp[-6].expr_list));
        delete (yyvsp[-6].expr_list);
      }
      if ((yyvsp[-4].relation_list) != nullptr) {
        (yyval.sql_node)->selection.relation_names.swap((yyvsp[-4].relation_list)->relation_names);
        (yyval.sql_node)->selection.alias_names.swap((yyvsp[-4].relation_list)->alias_names);
        (yyval.sql_node)->selection.inner_join_conditions.swap((yyvsp[-4].relation_list)->conditions);
        delete (yyvsp[-4].relation_list);
      }
      std::reverse((yyval.sql_node)->selection.relation_names.begin(), (yyval.sql_node)->selection.relation_names.end());
      std::reverse((yyval.sql_node)->selection.alias_names.begin(), (yyval.sql_node)->selection.alias_names.end());
      if ((yyvsp[-3].condition_list) != nullptr) {
        (yyval.sql_node)->selection.conditions.swap(*(yyvsp[-3].condition_list));
        delete (yyvsp[-3].condition_list);
      }
      if ((yyvsp[-2].rel_attr_list) != nullptr) {
        (yyval.sql_node)->selection.group_by_cols.swap(*(yyvsp[-2].rel_attr_list));
        delete (yyvsp[-2].rel_attr_list);
      }
      if ((yyvsp[-1].condition_list) != nullptr) {
        (yyval.sql_node)->selection.having_conditions.swap(*(yyvsp[-1].condition_list));
        delete (yyvsp[-1].condition_list);
      }
      if ((yyvsp[0].order_attr_list) != nullptr) {
        (yyval.sql_node)->selection.order_by_cols.swap(*(yyvsp[0].order_attr_list));
        delete (yyvsp[0].order_attr_list);
      }
    }
#line 2377 "yacc_sql.cpp" /* yacc.c:1646  */
    break;

  case 77:
#line 770 "yacc_sql.y" /* yacc.c:1646  */
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_CALC);
      std::reverse((yyvsp[0].expression_list)->begin(), (yyvsp[0].expression_list)->end());
      (yyval.sql_node)->calc.expressions.swap(*(yyvsp[0].expression_list));
      delete (yyvsp[0].expression_list);
    }
#line 2388 "yacc_sql.cpp" /* yacc.c:1646  */
    break;

  case 78:
#line 780 "yacc_sql.y" /* yacc.c:1646  */
    {
      (yyval.expression_list) = new std::vector<Expression*>;
      (yyval.expression_list)->emplace_back((yyvsp[0].expression));
    }
#line 2397 "yacc_sql.cpp" /* yacc.c:1646  */
    break;

  case 79:
#line 785 "yacc_sql.y" /* yacc.c:1646  */
    {
      if ((yyvsp[0].expression_list) != nullptr) {
        (yyval.expression_list) = (yyvsp[0].expression_list);
      } else {
        (yyval.expression_list) = new std::vector<Expression *>;
      }
      (yyval.expression_list)->emplace_back((yyvsp[-2].expression));
    }
#line 2410 "yacc_sql.cpp" /* yacc.c:1646  */
    break;

  case 80:
#line 795 "yacc_sql.y" /* yacc.c:1646  */
    {
      (yyval.expression) = create_arithmetic_expression(ArithmeticExpr::Type::ADD, (yyvsp[-2].expression), (yyvsp[0].expression), sql_string, &(yyloc));
    }
#line 2418 "yacc_sql.cpp" /* yacc.c:1646  */
    break;

  case 81:
#line 798 "yacc_sql.y" /* yacc.c:1646  */
    {
      (yyval.expression) = create_arithmetic_expression(ArithmeticExpr::Type::SUB, (yyvsp[-2].expression), (yyvsp[0].expression), sql_string, &(yyloc));
    }
#line 2426 "yacc_sql.cpp" /* yacc.c:1646  */
    break;

  case 82:
#line 801 "yacc_sql.y" /* yacc.c:1646  */
    {
      (yyval.expression) = create_arithmetic_expression(ArithmeticExpr::Type::MUL, (yyvsp[-2].expression), (yyvsp[0].expression), sql_string, &(yyloc));
    }
#line 2434 "yacc_sql.cpp" /* yacc.c:1646  */
    break;

  case 83:
#line 804 "yacc_sql.y" /* yacc.c:1646  */
    {
      (yyval.expression) = create_arithmetic_expression(ArithmeticExpr::Type::DIV, (yyvsp[-2].expression), (yyvsp[0].expression), sql_string, &(yyloc));
    }
#line 2442 "yacc_sql.cpp" /* yacc.c:1646  */
    break;

  case 84:
#line 807 "yacc_sql.y" /* yacc.c:1646  */
    {
      (yyval.expression) = (yyvsp[-1].expression);
      (yyval.expression)->set_name(token_name(sql_string, &(yyloc)));
    }
#line 2451 "yacc_sql.cpp" /* yacc.c:1646  */
    break;

  case 85:
#line 811 "yacc_sql.y" /* yacc.c:1646  */
    {
      (yyval.expression) = create_arithmetic_expression(ArithmeticExpr::Type::NEGATIVE, (yyvsp[0].expression), nullptr, sql_string, &(yyloc));
    }
#line 2459 "yacc_sql.cpp" /* yacc.c:1646  */
    break;

  case 86:
#line 814 "yacc_sql.y" /* yacc.c:1646  */
    {
      (yyval.expression) = new ValueExpr(*(yyvsp[0].value));
      (yyval.expression)->set_name(token_name(sql_string, &(yyloc)));
      delete (yyvsp[0].value);
    }
#line 2469 "yacc_sql.cpp" /* yacc.c:1646  */
    break;

  case 87:
#line 825 "yacc_sql.y" /* yacc.c:1646  */
    {
      UnaryExprSqlNode* unary = new UnaryExprSqlNode;
      unary->is_attr = false;
      unary->value = *(yyvsp[0].value);
      delete (yyvsp[0].value);

      ExprSqlNode* expr = new ExprSqlNode;
      expr->type = ExprSqlNodeType::UNARY;
      expr->unary_expr = unary;

      (yyval.expr) = expr;
    }
#line 2486 "yacc_sql.cpp" /* yacc.c:1646  */
    break;

  case 88:
#line 837 "yacc_sql.y" /* yacc.c:1646  */
    {
      UnaryExprSqlNode* unary = new UnaryExprSqlNode;
      unary->is_attr = true;
      unary->attr = *(yyvsp[0].rel_attr);
      delete (yyvsp[0].rel_attr);

      ExprSqlNode* expr = new ExprSqlNode;
      expr->type = ExprSqlNodeType::UNARY;
      expr->unary_expr = unary;

      (yyval.expr) = expr;
    }
#line 2503 "yacc_sql.cpp" /* yacc.c:1646  */
    break;

  case 89:
#line 849 "yacc_sql.y" /* yacc.c:1646  */
    {
      (yyval.expr) = (yyvsp[0].expr);
    }
#line 2511 "yacc_sql.cpp" /* yacc.c:1646  */
    break;

  case 90:
#line 852 "yacc_sql.y" /* yacc.c:1646  */
    {
      (yyval.expr) = (yyvsp[0].expr);
    }
#line 2519 "yacc_sql.cpp" /* yacc.c:1646  */
    break;

  case 91:
#line 855 "yacc_sql.y" /* yacc.c:1646  */
    {
      (yyvsp[-1].expr)->with_brace = true;
      (yyval.expr) = (yyvsp[-1].expr);
    }
#line 2528 "yacc_sql.cpp" /* yacc.c:1646  */
    break;

  case 92:
#line 863 "yacc_sql.y" /* yacc.c:1646  */
    {
      BinaryExprSqlNode* binary = new BinaryExprSqlNode;
      binary->op = ExprOp::ADD_OP;
      binary->left = (yyvsp[-2].expr);
      binary->right = (yyvsp[0].expr);

      ExprSqlNode* expr = new ExprSqlNode;
      expr->type = ExprSqlNodeType::BINARY;
      expr->binary_expr = binary;

      (yyval.expr) = expr;
    }
#line 2545 "yacc_sql.cpp" /* yacc.c:1646  */
    break;

  case 93:
#line 875 "yacc_sql.y" /* yacc.c:1646  */
    {
      BinaryExprSqlNode* binary = new BinaryExprSqlNode;
      binary->op = ExprOp::SUB_OP;
      binary->left = (yyvsp[-2].expr);
      binary->right = (yyvsp[0].expr);

      ExprSqlNode* expr = new ExprSqlNode;
      expr->type = ExprSqlNodeType::BINARY;
      expr->binary_expr = binary;

      (yyval.expr) = expr;
    }
#line 2562 "yacc_sql.cpp" /* yacc.c:1646  */
    break;

  case 94:
#line 887 "yacc_sql.y" /* yacc.c:1646  */
    {
      BinaryExprSqlNode* binary = new BinaryExprSqlNode;
      binary->op = ExprOp::MUL_OP;
      binary->left = (yyvsp[-2].expr);
      binary->right = (yyvsp[0].expr);

      ExprSqlNode* expr = new ExprSqlNode;
      expr->type = ExprSqlNodeType::BINARY;
      expr->binary_expr = binary;

      (yyval.expr) = expr;
    }
#line 2579 "yacc_sql.cpp" /* yacc.c:1646  */
    break;

  case 95:
#line 899 "yacc_sql.y" /* yacc.c:1646  */
    {
      BinaryExprSqlNode* binary = new BinaryExprSqlNode;
      binary->op = ExprOp::DIV_OP;
      binary->left = (yyvsp[-2].expr);
      binary->right = (yyvsp[0].expr);

      ExprSqlNode* expr = new ExprSqlNode;
      expr->type = ExprSqlNodeType::BINARY;
      expr->binary_expr = binary;

      (yyval.expr) = expr;
    }
#line 2596 "yacc_sql.cpp" /* yacc.c:1646  */
    break;

  case 96:
#line 911 "yacc_sql.y" /* yacc.c:1646  */
    {  // 负号
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
      binary->right = (yyvsp[0].expr);
      binary->is_minus = true;

      ExprSqlNode* expr = new ExprSqlNode;
      expr->type = ExprSqlNodeType::BINARY;
      expr->binary_expr = binary;

      (yyval.expr) = expr;
    }
#line 2622 "yacc_sql.cpp" /* yacc.c:1646  */
    break;

  case 97:
#line 932 "yacc_sql.y" /* yacc.c:1646  */
    { (yyval.expr) = (yyvsp[0].expr); }
#line 2628 "yacc_sql.cpp" /* yacc.c:1646  */
    break;

  case 98:
#line 938 "yacc_sql.y" /* yacc.c:1646  */
    {
      (yyval.expr_list) = nullptr;
    }
#line 2636 "yacc_sql.cpp" /* yacc.c:1646  */
    break;

  case 99:
#line 941 "yacc_sql.y" /* yacc.c:1646  */
    {
      if ((yyvsp[0].expr_list) != nullptr) {
        (yyval.expr_list) = (yyvsp[0].expr_list);
      } else {
        (yyval.expr_list) = new std::vector<ExprSqlNode *>;
      }

      (yyval.expr_list)->emplace_back((yyvsp[-1].expr));
      // delete $2;     在stmt阶段删除
    }
#line 2651 "yacc_sql.cpp" /* yacc.c:1646  */
    break;

  case 100:
#line 951 "yacc_sql.y" /* yacc.c:1646  */
    {  // 别名
      if ((yyvsp[0].expr_list) != nullptr) {
        (yyval.expr_list) = (yyvsp[0].expr_list);
      } else {
        (yyval.expr_list) = new std::vector<ExprSqlNode *>;
      }
      (yyvsp[-3].expr)->alias_name = (yyvsp[-1].string);
      free((yyvsp[-1].string));
      (yyval.expr_list)->emplace_back((yyvsp[-3].expr));
    }
#line 2666 "yacc_sql.cpp" /* yacc.c:1646  */
    break;

  case 101:
#line 961 "yacc_sql.y" /* yacc.c:1646  */
    {  // 别名
      if ((yyvsp[0].expr_list) != nullptr) {
        (yyval.expr_list) = (yyvsp[0].expr_list);
      } else {
        (yyval.expr_list) = new std::vector<ExprSqlNode *>;
      }
      (yyvsp[-2].expr)->alias_name = (yyvsp[-1].string);
      free((yyvsp[-1].string));
      (yyval.expr_list)->emplace_back((yyvsp[-2].expr));
    }
#line 2681 "yacc_sql.cpp" /* yacc.c:1646  */
    break;

  case 102:
#line 974 "yacc_sql.y" /* yacc.c:1646  */
    {
      FuncExprSqlNode* func = new FuncExprSqlNode;
      func->type = FuncType::FUNC_LENGTH;
      func->exprs.emplace_back((yyvsp[-1].expr));

      ExprSqlNode* expr = new ExprSqlNode;
      expr->type = ExprSqlNodeType::FUNCTION;
      expr->func_expr = func;
      (yyval.expr) = expr;
    }
#line 2696 "yacc_sql.cpp" /* yacc.c:1646  */
    break;

  case 103:
#line 984 "yacc_sql.y" /* yacc.c:1646  */
    {
      FuncExprSqlNode* func = new FuncExprSqlNode;
      func->type = FuncType::FUNC_ROUND;
      func->exprs.emplace_back((yyvsp[-1].expr));

      ExprSqlNode* expr = new ExprSqlNode;
      expr->type = ExprSqlNodeType::FUNCTION;
      expr->func_expr = func;
      (yyval.expr) = expr;
    }
#line 2711 "yacc_sql.cpp" /* yacc.c:1646  */
    break;

  case 104:
#line 994 "yacc_sql.y" /* yacc.c:1646  */
    {
      FuncExprSqlNode* func = new FuncExprSqlNode;
      func->type = FuncType::FUNC_ROUND;
      func->exprs.emplace_back((yyvsp[-3].expr));
      func->exprs.emplace_back((yyvsp[-1].expr));

      ExprSqlNode* expr = new ExprSqlNode;
      expr->type = ExprSqlNodeType::FUNCTION;
      expr->func_expr = func;
      (yyval.expr) = expr;
    }
#line 2727 "yacc_sql.cpp" /* yacc.c:1646  */
    break;

  case 105:
#line 1005 "yacc_sql.y" /* yacc.c:1646  */
    {
      FuncExprSqlNode* func = new FuncExprSqlNode;
      func->type = FuncType::FUNC_DATE_FORMAT;
      func->exprs.emplace_back((yyvsp[-3].expr));
      func->exprs.emplace_back((yyvsp[-1].expr));

      ExprSqlNode* expr = new ExprSqlNode;
      expr->type = ExprSqlNodeType::FUNCTION;
      expr->func_expr = func;
      (yyval.expr) = expr;
    }
#line 2743 "yacc_sql.cpp" /* yacc.c:1646  */
    break;

  case 106:
#line 1019 "yacc_sql.y" /* yacc.c:1646  */
    {
      AggrExprSqlNode* aggr = new AggrExprSqlNode;
      aggr->type = (yyvsp[-2].aggr_func_type);
      aggr->expr = (yyvsp[-1].expr);

      ExprSqlNode* expr = new ExprSqlNode;
      expr->type = ExprSqlNodeType::AGGREGATION;
      expr->aggr_expr = aggr;
      (yyval.expr) = expr;
    }
#line 2758 "yacc_sql.cpp" /* yacc.c:1646  */
    break;

  case 107:
#line 1029 "yacc_sql.y" /* yacc.c:1646  */
    {
      if ((yyvsp[-2].aggr_func_type) != AggrFuncType::AGGR_COUNT) {
        yyerror (&yylloc, sql_string, sql_result, scanner, YY_("aggr func is illegal"));
      }

      std::string star = "*";
      Value star_val(star.c_str());    // val = *
      UnaryExprSqlNode* star_unary = new UnaryExprSqlNode;
      star_unary->value = star_val;
      star_unary->is_attr = false;

      ExprSqlNode* star_expr = new ExprSqlNode;
      star_expr->type = ExprSqlNodeType::UNARY;
      star_expr->unary_expr = star_unary;

      AggrExprSqlNode* aggr = new AggrExprSqlNode;
      aggr->type = (yyvsp[-2].aggr_func_type);
      aggr->is_star = true;
      aggr->expr = star_expr;

      ExprSqlNode* expr = new ExprSqlNode;
      expr->type = ExprSqlNodeType::AGGREGATION;
      expr->aggr_expr = aggr;
      (yyval.expr) = expr;
    }
#line 2788 "yacc_sql.cpp" /* yacc.c:1646  */
    break;

  case 108:
#line 1057 "yacc_sql.y" /* yacc.c:1646  */
    {
      (yyval.aggr_func_type) = AggrFuncType::AGGR_MAX;
    }
#line 2796 "yacc_sql.cpp" /* yacc.c:1646  */
    break;

  case 109:
#line 1060 "yacc_sql.y" /* yacc.c:1646  */
    {
      (yyval.aggr_func_type) = AggrFuncType::AGGR_MIN;
    }
#line 2804 "yacc_sql.cpp" /* yacc.c:1646  */
    break;

  case 110:
#line 1063 "yacc_sql.y" /* yacc.c:1646  */
    {
      (yyval.aggr_func_type) = AggrFuncType::AGGR_SUM;
    }
#line 2812 "yacc_sql.cpp" /* yacc.c:1646  */
    break;

  case 111:
#line 1066 "yacc_sql.y" /* yacc.c:1646  */
    {
      (yyval.aggr_func_type) = AggrFuncType::AGGR_AVG;
    }
#line 2820 "yacc_sql.cpp" /* yacc.c:1646  */
    break;

  case 112:
#line 1069 "yacc_sql.y" /* yacc.c:1646  */
    {
      (yyval.aggr_func_type) = AggrFuncType::AGGR_COUNT;
    }
#line 2828 "yacc_sql.cpp" /* yacc.c:1646  */
    break;

  case 113:
#line 1156 "yacc_sql.y" /* yacc.c:1646  */
    {
      (yyval.rel_index_attr_list) = nullptr;
    }
#line 2836 "yacc_sql.cpp" /* yacc.c:1646  */
    break;

  case 114:
#line 1159 "yacc_sql.y" /* yacc.c:1646  */
    {
      if ((yyvsp[0].rel_index_attr_list) != nullptr) {
        (yyval.rel_index_attr_list) = (yyvsp[0].rel_index_attr_list);
      } else {
        (yyval.rel_index_attr_list) = new std::vector<string>;
      }

      (yyval.rel_index_attr_list)->emplace_back((yyvsp[-1].string));
      free((yyvsp[-1].string));
    }
#line 2851 "yacc_sql.cpp" /* yacc.c:1646  */
    break;

  case 115:
#line 1171 "yacc_sql.y" /* yacc.c:1646  */
    {
      RelAttrSqlNode attr;
      attr.relation_name  = "";
      attr.attribute_name = "*";

      UnaryExprSqlNode* unary = new UnaryExprSqlNode;
      unary->is_attr = true;
      unary->attr = attr;

      ExprSqlNode* expr = new ExprSqlNode;
      expr->type = ExprSqlNodeType::UNARY;
      expr->unary_expr = unary;

      (yyval.expr_list) = new std::vector<ExprSqlNode*>;
      (yyval.expr_list)->emplace_back(expr);
    }
#line 2872 "yacc_sql.cpp" /* yacc.c:1646  */
    break;

  case 116:
#line 1188 "yacc_sql.y" /* yacc.c:1646  */
    {
      if ((yyvsp[0].expr_list) != nullptr) {
        (yyval.expr_list) = (yyvsp[0].expr_list);
      } else {
        (yyval.expr_list) = new std::vector<ExprSqlNode*>;
      }
      (yyval.expr_list)->emplace_back((yyvsp[-1].expr));
    }
#line 2885 "yacc_sql.cpp" /* yacc.c:1646  */
    break;

  case 117:
#line 1196 "yacc_sql.y" /* yacc.c:1646  */
    {    // 别名
      if ((yyvsp[0].expr_list) != nullptr) {
        (yyval.expr_list) = (yyvsp[0].expr_list);
      } else {
        (yyval.expr_list) = new std::vector<ExprSqlNode*>;
      }
      (yyvsp[-3].expr)->alias_name = (yyvsp[-1].string);
      free((yyvsp[-1].string));
      (yyval.expr_list)->emplace_back((yyvsp[-3].expr));
    }
#line 2900 "yacc_sql.cpp" /* yacc.c:1646  */
    break;

  case 118:
#line 1206 "yacc_sql.y" /* yacc.c:1646  */
    {    // 别名
      if ((yyvsp[0].expr_list) != nullptr) {
        (yyval.expr_list) = (yyvsp[0].expr_list);
      } else {
        (yyval.expr_list) = new std::vector<ExprSqlNode*>;
      }
      (yyvsp[-2].expr)->alias_name = (yyvsp[-1].string);
      free((yyvsp[-1].string));
      (yyval.expr_list)->emplace_back((yyvsp[-2].expr));
    }
#line 2915 "yacc_sql.cpp" /* yacc.c:1646  */
    break;

  case 119:
#line 1219 "yacc_sql.y" /* yacc.c:1646  */
    {
      if ((yyvsp[0].relation_list) != nullptr) {
        (yyval.relation_list) = (yyvsp[0].relation_list);
      } else {
        (yyval.relation_list) = new RelationSqlNode;
      }
      (yyval.relation_list)->relation_names.push_back((yyvsp[-1].string));
      (yyval.relation_list)->alias_names.push_back("");
      free((yyvsp[-1].string));
    }
#line 2930 "yacc_sql.cpp" /* yacc.c:1646  */
    break;

  case 120:
#line 1229 "yacc_sql.y" /* yacc.c:1646  */
    {   // 包含别名
      if ((yyvsp[0].relation_list) != nullptr) {
        (yyval.relation_list) = (yyvsp[0].relation_list);
      } else {
        (yyval.relation_list) = new RelationSqlNode;
      }
      (yyval.relation_list)->relation_names.push_back((yyvsp[-3].string));
      (yyval.relation_list)->alias_names.push_back((yyvsp[-1].string));
      free((yyvsp[-3].string));
      free((yyvsp[-1].string));
    }
#line 2946 "yacc_sql.cpp" /* yacc.c:1646  */
    break;

  case 121:
#line 1240 "yacc_sql.y" /* yacc.c:1646  */
    {   // 包含别名
      if ((yyvsp[0].relation_list) != nullptr) {
        (yyval.relation_list) = (yyvsp[0].relation_list);
      } else {
        (yyval.relation_list) = new RelationSqlNode;
      }
      (yyval.relation_list)->relation_names.push_back((yyvsp[-2].string));
      (yyval.relation_list)->alias_names.push_back((yyvsp[-1].string));
      free((yyvsp[-2].string));
      free((yyvsp[-1].string));
    }
#line 2962 "yacc_sql.cpp" /* yacc.c:1646  */
    break;

  case 122:
#line 1254 "yacc_sql.y" /* yacc.c:1646  */
    {
      (yyval.rel_attr) = new RelAttrSqlNode;
      (yyval.rel_attr)->attribute_name = (yyvsp[0].string);
      free((yyvsp[0].string));
    }
#line 2972 "yacc_sql.cpp" /* yacc.c:1646  */
    break;

  case 123:
#line 1259 "yacc_sql.y" /* yacc.c:1646  */
    {
      (yyval.rel_attr) = new RelAttrSqlNode;
      (yyval.rel_attr)->relation_name  = (yyvsp[-2].string);
      (yyval.rel_attr)->attribute_name = (yyvsp[0].string);
      free((yyvsp[-2].string));
      free((yyvsp[0].string));
    }
#line 2984 "yacc_sql.cpp" /* yacc.c:1646  */
    break;

  case 124:
#line 1287 "yacc_sql.y" /* yacc.c:1646  */
    {
      (yyval.relation_list) = nullptr;
    }
#line 2992 "yacc_sql.cpp" /* yacc.c:1646  */
    break;

  case 125:
#line 1290 "yacc_sql.y" /* yacc.c:1646  */
    {
      if ((yyvsp[0].relation_list) != nullptr) {
        (yyval.relation_list) = (yyvsp[0].relation_list);
      } else {
        (yyval.relation_list) = new RelationSqlNode;
      }
      (yyval.relation_list)->relation_names.push_back((yyvsp[-1].string));
      (yyval.relation_list)->alias_names.push_back("");
      free((yyvsp[-1].string));
    }
#line 3007 "yacc_sql.cpp" /* yacc.c:1646  */
    break;

  case 126:
#line 1300 "yacc_sql.y" /* yacc.c:1646  */
    { // 别名
      if ((yyvsp[0].relation_list) != nullptr) {
        (yyval.relation_list) = (yyvsp[0].relation_list);
      } else {
        (yyval.relation_list) = new RelationSqlNode;
      }
      (yyval.relation_list)->relation_names.push_back((yyvsp[-3].string));
      (yyval.relation_list)->alias_names.push_back((yyvsp[-1].string));
      free((yyvsp[-3].string));
      free((yyvsp[-1].string));
    }
#line 3023 "yacc_sql.cpp" /* yacc.c:1646  */
    break;

  case 127:
#line 1311 "yacc_sql.y" /* yacc.c:1646  */
    { // 别名
      if ((yyvsp[0].relation_list) != nullptr) {
        (yyval.relation_list) = (yyvsp[0].relation_list);
      } else {
        (yyval.relation_list) = new RelationSqlNode;
      }
      (yyval.relation_list)->relation_names.push_back((yyvsp[-2].string));
      (yyval.relation_list)->alias_names.push_back((yyvsp[-1].string));
      free((yyvsp[-2].string));
      free((yyvsp[-1].string));
    }
#line 3039 "yacc_sql.cpp" /* yacc.c:1646  */
    break;

  case 128:
#line 1322 "yacc_sql.y" /* yacc.c:1646  */
    {  // todo INNER JOIN ID AS ID
      if ((yyvsp[0].relation_list) != nullptr) {
         (yyval.relation_list) = (yyvsp[0].relation_list);
      } else {
         (yyval.relation_list) = new RelationSqlNode;
      }
      std::vector<ConditionSqlNode> &conditions = (yyval.relation_list)->conditions;
      if ((yyvsp[-1].condition_list) != nullptr)
      {
         conditions.insert(conditions.end(), (yyvsp[-1].condition_list)->begin(), (yyvsp[-1].condition_list)->end());
         delete (yyvsp[-1].condition_list);
      }
      (yyval.relation_list)->relation_names.push_back((yyvsp[-2].string));
      (yyval.relation_list)->alias_names.push_back("");
      free((yyvsp[-2].string));
    }
#line 3060 "yacc_sql.cpp" /* yacc.c:1646  */
    break;

  case 129:
#line 1340 "yacc_sql.y" /* yacc.c:1646  */
    {
       (yyval.condition_list) = nullptr;
    }
#line 3068 "yacc_sql.cpp" /* yacc.c:1646  */
    break;

  case 130:
#line 1343 "yacc_sql.y" /* yacc.c:1646  */
    {
       (yyval.condition_list) = (yyvsp[0].condition_list);
	}
#line 3076 "yacc_sql.cpp" /* yacc.c:1646  */
    break;

  case 131:
#line 1349 "yacc_sql.y" /* yacc.c:1646  */
    {
      (yyval.condition_list) = nullptr;
    }
#line 3084 "yacc_sql.cpp" /* yacc.c:1646  */
    break;

  case 132:
#line 1352 "yacc_sql.y" /* yacc.c:1646  */
    {
      (yyval.condition_list) = (yyvsp[0].condition_list);  
    }
#line 3092 "yacc_sql.cpp" /* yacc.c:1646  */
    break;

  case 133:
#line 1359 "yacc_sql.y" /* yacc.c:1646  */
    {
      (yyval.condition_list) = nullptr;
    }
#line 3100 "yacc_sql.cpp" /* yacc.c:1646  */
    break;

  case 134:
#line 1362 "yacc_sql.y" /* yacc.c:1646  */
    {
      (yyval.condition_list) = (yyvsp[0].condition_list);
    }
#line 3108 "yacc_sql.cpp" /* yacc.c:1646  */
    break;

  case 135:
#line 1369 "yacc_sql.y" /* yacc.c:1646  */
    {
        (yyval.rel_attr_list) = new std::vector<RelAttrSqlNode>;
        (yyval.rel_attr_list)->emplace_back(*(yyvsp[0].rel_attr));
        delete (yyvsp[0].rel_attr);
    }
#line 3118 "yacc_sql.cpp" /* yacc.c:1646  */
    break;

  case 136:
#line 1375 "yacc_sql.y" /* yacc.c:1646  */
    {
        (yyval.rel_attr_list) = (yyvsp[0].rel_attr_list);
        (yyval.rel_attr_list)->emplace_back(*(yyvsp[-2].rel_attr));
        delete (yyvsp[-2].rel_attr);
	}
#line 3128 "yacc_sql.cpp" /* yacc.c:1646  */
    break;

  case 137:
#line 1383 "yacc_sql.y" /* yacc.c:1646  */
    {
      (yyval.rel_attr_list) = nullptr;
    }
#line 3136 "yacc_sql.cpp" /* yacc.c:1646  */
    break;

  case 138:
#line 1386 "yacc_sql.y" /* yacc.c:1646  */
    {
      (yyval.rel_attr_list) = (yyvsp[0].rel_attr_list);
      std::reverse((yyval.rel_attr_list)->begin(), (yyval.rel_attr_list)->end());
    }
#line 3145 "yacc_sql.cpp" /* yacc.c:1646  */
    break;

  case 139:
#line 1394 "yacc_sql.y" /* yacc.c:1646  */
    {
		(yyval.order_attr) = new OrderBySqlNode;
		(yyval.order_attr)->attribute = *(yyvsp[0].rel_attr);
		(yyval.order_attr)->is_asc = true;

		delete (yyvsp[0].rel_attr);
	}
#line 3157 "yacc_sql.cpp" /* yacc.c:1646  */
    break;

  case 140:
#line 1403 "yacc_sql.y" /* yacc.c:1646  */
    {
		(yyval.order_attr) = new OrderBySqlNode;
        (yyval.order_attr)->attribute = *(yyvsp[-1].rel_attr);
      	(yyval.order_attr)->is_asc = true;

      	delete (yyvsp[-1].rel_attr);
	}
#line 3169 "yacc_sql.cpp" /* yacc.c:1646  */
    break;

  case 141:
#line 1412 "yacc_sql.y" /* yacc.c:1646  */
    {
		(yyval.order_attr) = new OrderBySqlNode;
        (yyval.order_attr)->attribute = *(yyvsp[-1].rel_attr);
      	(yyval.order_attr)->is_asc = false;

      	delete (yyvsp[-1].rel_attr);
	}
#line 3181 "yacc_sql.cpp" /* yacc.c:1646  */
    break;

  case 142:
#line 1422 "yacc_sql.y" /* yacc.c:1646  */
    {
        (yyval.order_attr_list) = nullptr;
	}
#line 3189 "yacc_sql.cpp" /* yacc.c:1646  */
    break;

  case 143:
#line 1426 "yacc_sql.y" /* yacc.c:1646  */
    {
        (yyval.order_attr_list) = new std::vector<OrderBySqlNode>;
        (yyval.order_attr_list)->emplace_back(*(yyvsp[0].order_attr));
        delete (yyvsp[0].order_attr);
    }
#line 3199 "yacc_sql.cpp" /* yacc.c:1646  */
    break;

  case 144:
#line 1432 "yacc_sql.y" /* yacc.c:1646  */
    {
        (yyval.order_attr_list) = (yyvsp[0].order_attr_list);
        (yyval.order_attr_list)->emplace_back(*(yyvsp[-2].order_attr));
        delete (yyvsp[-2].order_attr);
	}
#line 3209 "yacc_sql.cpp" /* yacc.c:1646  */
    break;

  case 145:
#line 1440 "yacc_sql.y" /* yacc.c:1646  */
    {
      (yyval.order_attr_list) = nullptr;
    }
#line 3217 "yacc_sql.cpp" /* yacc.c:1646  */
    break;

  case 146:
#line 1443 "yacc_sql.y" /* yacc.c:1646  */
    {
      (yyval.order_attr_list) = (yyvsp[0].order_attr_list);
      std::reverse((yyval.order_attr_list)->begin(), (yyval.order_attr_list)->end());
    }
#line 3226 "yacc_sql.cpp" /* yacc.c:1646  */
    break;

  case 147:
#line 1452 "yacc_sql.y" /* yacc.c:1646  */
    {
      (yyval.condition_list) = nullptr;
    }
#line 3234 "yacc_sql.cpp" /* yacc.c:1646  */
    break;

  case 148:
#line 1455 "yacc_sql.y" /* yacc.c:1646  */
    {
      (yyval.condition_list) = new std::vector<ConditionSqlNode>;
      (yyval.condition_list)->emplace_back(*(yyvsp[0].condition));
      delete (yyvsp[0].condition);
    }
#line 3244 "yacc_sql.cpp" /* yacc.c:1646  */
    break;

  case 149:
#line 1460 "yacc_sql.y" /* yacc.c:1646  */
    {
      (yyval.condition_list) = (yyvsp[0].condition_list);
      (yyval.condition_list)->emplace_back(*(yyvsp[-2].condition));
      delete (yyvsp[-2].condition);
    }
#line 3254 "yacc_sql.cpp" /* yacc.c:1646  */
    break;

  case 150:
#line 1468 "yacc_sql.y" /* yacc.c:1646  */
    {
      (yyval.condition) = new ConditionSqlNode;
      (yyval.condition)->left = (yyvsp[-2].expr);
      (yyval.condition)->comp = (yyvsp[-1].comp);
      (yyval.condition)->right = (yyvsp[0].expr);
    }
#line 3265 "yacc_sql.cpp" /* yacc.c:1646  */
    break;

  case 151:
#line 1475 "yacc_sql.y" /* yacc.c:1646  */
    {
      (yyval.condition) = new ConditionSqlNode;
      (yyval.condition)->left = (yyvsp[-2].expr);
      (yyval.condition)->comp = IS_NULL;

      Value value;
      UnaryExprSqlNode* unary = new UnaryExprSqlNode;
      unary->is_attr = false;
      unary->value = value;

      ExprSqlNode* expr = new ExprSqlNode;
      expr->type = ExprSqlNodeType::UNARY;
      expr->unary_expr = unary;

      (yyval.condition)->right = expr;
    }
#line 3286 "yacc_sql.cpp" /* yacc.c:1646  */
    break;

  case 152:
#line 1492 "yacc_sql.y" /* yacc.c:1646  */
    {
      (yyval.condition) = new ConditionSqlNode;
      (yyval.condition)->left = (yyvsp[-3].expr);
      (yyval.condition)->comp = IS_NOT_NULL;

      Value value;
      UnaryExprSqlNode* unary = new UnaryExprSqlNode;
      unary->is_attr = false;
      unary->value = value;

      ExprSqlNode* expr = new ExprSqlNode;
      expr->type = ExprSqlNodeType::UNARY;
      expr->unary_expr = unary;

      (yyval.condition)->right = expr;
    }
#line 3307 "yacc_sql.cpp" /* yacc.c:1646  */
    break;

  case 153:
#line 1560 "yacc_sql.y" /* yacc.c:1646  */
    { (yyval.comp) = EQUAL_TO; }
#line 3313 "yacc_sql.cpp" /* yacc.c:1646  */
    break;

  case 154:
#line 1561 "yacc_sql.y" /* yacc.c:1646  */
    { (yyval.comp) = LESS_THAN; }
#line 3319 "yacc_sql.cpp" /* yacc.c:1646  */
    break;

  case 155:
#line 1562 "yacc_sql.y" /* yacc.c:1646  */
    { (yyval.comp) = GREAT_THAN; }
#line 3325 "yacc_sql.cpp" /* yacc.c:1646  */
    break;

  case 156:
#line 1563 "yacc_sql.y" /* yacc.c:1646  */
    { (yyval.comp) = LESS_EQUAL; }
#line 3331 "yacc_sql.cpp" /* yacc.c:1646  */
    break;

  case 157:
#line 1564 "yacc_sql.y" /* yacc.c:1646  */
    { (yyval.comp) = GREAT_EQUAL; }
#line 3337 "yacc_sql.cpp" /* yacc.c:1646  */
    break;

  case 158:
#line 1565 "yacc_sql.y" /* yacc.c:1646  */
    { (yyval.comp) = NOT_EQUAL; }
#line 3343 "yacc_sql.cpp" /* yacc.c:1646  */
    break;

  case 159:
#line 1566 "yacc_sql.y" /* yacc.c:1646  */
    { (yyval.comp) = LIKE_OP; }
#line 3349 "yacc_sql.cpp" /* yacc.c:1646  */
    break;

  case 160:
#line 1567 "yacc_sql.y" /* yacc.c:1646  */
    { (yyval.comp) = NOT_LIKE_OP; }
#line 3355 "yacc_sql.cpp" /* yacc.c:1646  */
    break;

  case 161:
#line 1572 "yacc_sql.y" /* yacc.c:1646  */
    {
      char *tmp_file_name = common::substr((yyvsp[-3].string), 1, strlen((yyvsp[-3].string)) - 2);
      
      (yyval.sql_node) = new ParsedSqlNode(SCF_LOAD_DATA);
      (yyval.sql_node)->load_data.relation_name = (yyvsp[0].string);
      (yyval.sql_node)->load_data.file_name = tmp_file_name;
      free((yyvsp[0].string));
      free(tmp_file_name);
    }
#line 3369 "yacc_sql.cpp" /* yacc.c:1646  */
    break;

  case 162:
#line 1585 "yacc_sql.y" /* yacc.c:1646  */
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_EXPLAIN);
      (yyval.sql_node)->explain.sql_node = std::unique_ptr<ParsedSqlNode>((yyvsp[0].sql_node));
    }
#line 3378 "yacc_sql.cpp" /* yacc.c:1646  */
    break;

  case 163:
#line 1593 "yacc_sql.y" /* yacc.c:1646  */
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_SET_VARIABLE);
      (yyval.sql_node)->set_variable.name  = (yyvsp[-2].string);
      (yyval.sql_node)->set_variable.value = *(yyvsp[0].value);
      free((yyvsp[-2].string));
      delete (yyvsp[0].value);
    }
#line 3390 "yacc_sql.cpp" /* yacc.c:1646  */
    break;


#line 3394 "yacc_sql.cpp" /* yacc.c:1646  */
      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;
  *++yylsp = yyloc;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYEMPTY : YYTRANSLATE (yychar);

  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (&yylloc, sql_string, sql_result, scanner, YY_("syntax error"));
#else
# define YYSYNTAX_ERROR yysyntax_error (&yymsg_alloc, &yymsg, \
                                        yyssp, yytoken)
      {
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = YYSYNTAX_ERROR;
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == 1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = (char *) YYSTACK_ALLOC (yymsg_alloc);
            if (!yymsg)
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = 2;
              }
            else
              {
                yysyntax_error_status = YYSYNTAX_ERROR;
                yymsgp = yymsg;
              }
          }
        yyerror (&yylloc, sql_string, sql_result, scanner, yymsgp);
        if (yysyntax_error_status == 2)
          goto yyexhaustedlab;
      }
# undef YYSYNTAX_ERROR
#endif
    }

  yyerror_range[1] = yylloc;

  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
         error, discard it.  */

      if (yychar <= YYEOF)
        {
          /* Return failure if at end of input.  */
          if (yychar == YYEOF)
            YYABORT;
        }
      else
        {
          yydestruct ("Error: discarding",
                      yytoken, &yylval, &yylloc, sql_string, sql_result, scanner);
          yychar = YYEMPTY;
        }
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

  yyerror_range[1] = yylsp[1-yylen];
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYTERROR;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
            {
              yyn = yytable[yyn];
              if (0 < yyn)
                break;
            }
        }

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
        YYABORT;

      yyerror_range[1] = *yylsp;
      yydestruct ("Error: popping",
                  yystos[yystate], yyvsp, yylsp, sql_string, sql_result, scanner);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  yyerror_range[2] = yylloc;
  /* Using YYLLOC is tempting, but would change the location of
     the lookahead.  YYLOC is available though.  */
  YYLLOC_DEFAULT (yyloc, yyerror_range, 2);
  *++yylsp = yyloc;

  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;

/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;

#if !defined yyoverflow || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (&yylloc, sql_string, sql_result, scanner, YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval, &yylloc, sql_string, sql_result, scanner);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  yystos[*yyssp], yyvsp, yylsp, sql_string, sql_result, scanner);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  return yyresult;
}
#line 1605 "yacc_sql.y" /* yacc.c:1906  */

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
