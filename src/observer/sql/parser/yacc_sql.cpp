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
    VIEW = 310,
    AGGR_MAX = 311,
    AGGR_MIN = 312,
    AGGR_COUNT = 313,
    AGGR_AVG = 314,
    AGGR_SUM = 315,
    LENGTH = 316,
    ROUND = 317,
    DATE_FORMAT = 318,
    AS = 319,
    IS = 320,
    EQ = 321,
    LT = 322,
    GT = 323,
    LE = 324,
    GE = 325,
    NE = 326,
    NUMBER = 327,
    FLOAT = 328,
    ID = 329,
    SSS = 330,
    DATE_STR = 331,
    UMINUS = 332
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 130 "yacc_sql.y" /* yacc.c:355  */

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


#line 261 "yacc_sql.cpp" /* yacc.c:355  */
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

#line 291 "yacc_sql.cpp" /* yacc.c:358  */

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
#define YYFINAL  89
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   390

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  82
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  61
/* YYNRULES -- Number of rules.  */
#define YYNRULES  170
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  320

/* YYTRANSLATE[YYX] -- Symbol number corresponding to YYX as returned
   by yylex, with out-of-bounds checking.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   332

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
       2,     2,    79,    77,     2,    78,     2,    80,     2,     2,
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
      75,    76,    81
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   242,   242,   250,   251,   252,   253,   254,   255,   256,
     257,   258,   259,   260,   261,   262,   263,   264,   265,   266,
     267,   268,   269,   270,   271,   272,   276,   282,   287,   293,
     299,   305,   311,   318,   323,   330,   338,   357,   379,   389,
     407,   417,   427,   447,   469,   479,   489,   509,   532,   535,
     548,   557,   565,   574,   583,   592,   601,   612,   615,   616,
     617,   618,   621,   637,   640,   654,   668,   671,   682,   686,
     690,   694,   698,   712,   717,   723,   750,   769,   779,   782,
     793,   800,   834,   844,   849,   860,   863,   866,   869,   872,
     876,   879,   890,   902,   914,   917,   920,   928,   940,   952,
     964,   976,   997,  1003,  1006,  1016,  1026,  1039,  1049,  1059,
    1070,  1084,  1094,  1122,  1125,  1128,  1131,  1134,  1221,  1224,
    1236,  1253,  1261,  1271,  1284,  1294,  1305,  1319,  1324,  1352,
    1355,  1365,  1376,  1387,  1405,  1408,  1414,  1417,  1424,  1427,
    1433,  1439,  1448,  1451,  1458,  1467,  1476,  1487,  1490,  1496,
    1505,  1508,  1517,  1520,  1525,  1532,  1539,  1556,  1625,  1626,
    1627,  1628,  1629,  1630,  1631,  1632,  1636,  1649,  1657,  1667,
    1668
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
  "IN", "NULL_T", "VIEW", "AGGR_MAX", "AGGR_MIN", "AGGR_COUNT", "AGGR_AVG",
  "AGGR_SUM", "LENGTH", "ROUND", "DATE_FORMAT", "AS", "IS", "EQ", "LT",
  "GT", "LE", "GE", "NE", "NUMBER", "FLOAT", "ID", "SSS", "DATE_STR",
  "'+'", "'-'", "'*'", "'/'", "UMINUS", "$accept", "commands",
  "command_wrapper", "exit_stmt", "help_stmt", "sync_stmt", "begin_stmt",
  "commit_stmt", "rollback_stmt", "drop_table_stmt", "show_tables_stmt",
  "show_index_stmt", "desc_table_stmt", "create_index_stmt",
  "drop_index_stmt", "create_table_stmt", "create_table_select_stmt",
  "create_view_stmt", "attr_def_list", "attr_def", "number", "type",
  "insert_stmt", "row_value_list", "row_value", "value_list", "value",
  "delete_stmt", "update_stmt", "update_value", "update_value_list",
  "select_stmt", "calc_stmt", "expression_list", "expression",
  "unary_expr", "expr", "expr_list", "func_expr", "aggr_func_expr",
  "aggr_func_type", "index_attr_list", "select_attr", "select_from",
  "rel_attr", "rel_list", "inner_condition_list", "where", "having",
  "group_list", "group_by", "sort_unit", "sort_list", "order_by",
  "condition_list", "condition", "comp_op", "load_data_stmt",
  "explain_stmt", "set_variable_stmt", "opt_semicolon", YY_NULLPTR
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
     325,   326,   327,   328,   329,   330,   331,    43,    45,    42,
      47,   332
};
# endif

#define YYPACT_NINF -268

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-268)))

#define YYTABLE_NINF -1

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     315,   133,    34,   200,    70,   -51,    47,  -268,    -5,     5,
     -40,  -268,  -268,  -268,  -268,  -268,   -28,    10,   315,    59,
      58,  -268,  -268,  -268,  -268,  -268,  -268,  -268,  -268,  -268,
    -268,  -268,  -268,  -268,  -268,  -268,  -268,  -268,  -268,  -268,
    -268,  -268,  -268,  -268,    31,    36,    61,    38,    49,    66,
     200,  -268,  -268,  -268,  -268,  -268,   211,  -268,  -268,   213,
     165,  -268,  -268,  -268,  -268,  -268,    78,   130,   140,    44,
     188,  -268,  -268,  -268,   230,  -268,  -268,   139,   128,  -268,
    -268,  -268,   136,    95,   103,   147,   109,   160,  -268,  -268,
    -268,  -268,    24,   176,   158,    25,  -268,   193,     7,  -268,
    -268,  -268,   200,   200,   200,   200,   200,    14,   165,   165,
     165,   162,  -268,   165,   179,   233,   165,   165,   165,   165,
    -268,   235,    41,   183,   194,   234,   240,   196,    98,   199,
     197,   267,  -268,   206,   241,   197,   267,  -268,   208,  -268,
    -268,    83,    83,  -268,  -268,  -268,    57,     3,   245,  -268,
     237,   233,  -268,   111,   111,  -268,  -268,  -268,  -268,    -1,
     240,  -268,   265,   165,  -268,   222,   273,   137,  -268,   262,
     -11,   275,  -268,   278,   225,   275,  -268,  -268,  -268,  -268,
     165,   165,   226,   233,  -268,  -268,   292,   229,   231,    11,
    -268,   257,    98,   290,   296,  -268,   280,    98,   196,   240,
    -268,  -268,   307,  -268,  -268,  -268,  -268,  -268,     6,   197,
     300,   255,   316,   314,    76,    88,   233,  -268,   263,     0,
      11,  -268,   293,   294,   322,   265,  -268,   302,  -268,    68,
    -268,  -268,  -268,  -268,  -268,  -268,   165,   165,  -268,   273,
    -268,   276,   277,   297,  -268,   275,     1,   330,   279,     2,
    -268,  -268,  -268,   317,   281,    11,  -268,  -268,   284,   165,
     312,    98,   347,   290,  -268,   318,  -268,   104,  -268,  -268,
    -268,  -268,   348,  -268,  -268,   267,  -268,   303,   349,   330,
     267,  -268,   165,    11,    11,  -268,   356,  -268,  -268,   321,
    -268,   322,  -268,  -268,  -268,    93,  -268,   330,  -268,   358,
    -268,  -268,  -268,  -268,   284,   284,  -268,   326,  -268,  -268,
    -268,  -268,   216,   359,  -268,  -268,  -268,  -268,   284,  -268
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     0,     0,     0,     0,     0,     0,    28,     0,     0,
       0,    29,    30,    31,    27,    26,     0,     0,     0,     0,
     169,    25,    24,    17,    18,    19,    20,    11,    12,    13,
      14,    15,    16,     8,    10,     9,     5,     7,     6,     4,
       3,    21,    22,    23,     0,     0,     0,     0,     0,     0,
       0,    74,    68,    70,    73,    72,     0,    91,    82,    83,
       0,   113,   114,   117,   116,   115,     0,     0,     0,   127,
       0,   120,    92,   102,   103,    94,    95,     0,    80,    93,
      35,    33,     0,     0,     0,     0,     0,     0,   167,     1,
     170,     2,     0,     0,     0,     0,    32,     0,     0,    68,
      70,    90,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   101,     0,     0,   103,     0,     0,     0,     0,
     121,     0,     0,     0,     0,     0,   136,     0,     0,     0,
       0,     0,    41,     0,     0,     0,     0,    45,     0,    89,
      84,    85,    86,    87,    88,    96,     0,     0,     0,   128,
     103,   103,   123,    97,    98,    99,   100,   112,   111,   129,
     136,    34,     0,   152,    75,     0,    78,     0,   168,     0,
       0,    48,    40,     0,     0,    48,    44,    38,   107,   108,
       0,     0,     0,   103,   104,   122,     0,     0,     0,   129,
     124,   142,     0,    63,     0,   137,   153,     0,     0,   136,
      69,    71,     0,    58,    59,    60,    61,    51,    52,     0,
       0,     0,     0,     0,     0,     0,   103,   106,     0,   129,
     129,   126,     0,   138,    66,     0,    62,     0,   164,     0,
     158,   159,   160,   161,   162,   163,     0,   152,    77,    78,
      76,     0,     0,     0,    54,    48,    39,   118,     0,     0,
     109,   110,   105,   134,     0,   129,   130,   125,     0,   152,
     150,     0,     0,    63,   165,     0,   156,   155,   154,    79,
     166,    57,     0,    56,    49,     0,    43,     0,     0,   118,
       0,    47,   152,   129,   129,   132,   140,   143,   139,     0,
      81,    66,    65,    64,   157,    50,    42,   118,    36,     0,
      46,   135,   133,   131,     0,   147,    67,     0,    53,   119,
      37,   141,   144,   148,   151,    55,   146,   145,   147,   149
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -268,  -268,   364,  -268,  -268,  -268,  -268,  -268,  -268,  -268,
    -268,  -268,  -268,  -268,  -268,  -268,  -268,  -268,  -169,  -130,
    -268,  -268,  -268,   120,   159,    94,    -3,  -268,  -268,   189,
     149,   -88,  -268,   287,   101,  -268,    -2,  -112,  -268,  -268,
    -268,  -267,  -268,  -268,  -248,  -188,  -268,  -149,  -268,    82,
    -268,  -268,    72,  -268,  -210,  -268,  -268,  -268,  -268,  -268,
    -268
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,    19,    20,    21,    22,    23,    24,    25,    26,    27,
      28,    29,    30,    31,    32,    33,    34,    35,   210,   171,
     272,   208,    36,   226,   193,   262,    72,    37,    38,   166,
     199,    39,    40,    58,    59,    73,   194,   120,    75,    76,
      77,   278,    78,   160,    79,   190,   283,   164,   260,   287,
     223,   313,   314,   290,   195,   196,   236,    41,    42,    43,
      91
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_uint16 yytable[] =
{
      57,   221,    74,   152,   132,   175,   213,   137,   186,   186,
     286,   191,   299,     4,     4,   203,   204,   205,   206,   207,
     186,   187,   187,    80,   179,   180,   242,   268,   139,    83,
     309,   256,   257,   187,    85,   145,     4,     4,   184,   185,
      48,    84,    49,   172,   130,   135,    86,    57,   176,   288,
     240,   243,    87,    57,    81,    82,   286,   312,   107,    89,
     244,    90,   158,   188,   254,   275,   280,   285,   112,    94,
     312,   217,   301,   189,   255,   122,   274,   111,   178,   245,
     116,   117,   118,   119,   103,   104,   105,   106,   131,   136,
      60,   116,   117,   118,   119,   302,   303,   250,   108,    57,
      57,    57,    57,    57,   252,    92,   146,   147,   148,   251,
      93,   150,    95,   265,   153,   154,   155,   156,   116,   117,
     118,   119,   266,    96,    51,   168,    61,    62,    63,    64,
      65,    66,    67,    68,   116,   117,   118,   119,   307,    44,
      97,    45,    52,    53,    69,    54,    55,   308,    70,    71,
     109,    98,    51,   116,   117,   118,   119,   101,   276,    60,
     110,   281,   105,   106,   123,   116,   117,   118,   119,   125,
      52,    53,   124,    54,    55,   128,   167,   126,   214,   215,
      46,   116,   117,   118,   119,    60,   127,   296,    47,   224,
     118,   119,   300,    51,   238,    61,    62,    63,    64,    65,
      66,    67,    68,   129,   141,   142,   143,   144,    60,   200,
     201,    52,    53,    69,    54,    55,   133,    70,   121,    51,
      50,    61,    62,    63,    64,    65,    66,    67,    68,   316,
     317,    50,   134,   138,   267,   102,   149,    52,    53,    69,
      54,    55,    51,    70,    61,    62,    63,    64,    65,    66,
      67,    68,   113,   151,    51,   113,   157,   159,   291,   113,
      99,   100,    69,    54,    55,    51,    70,   181,   161,   162,
     165,   170,    52,    53,   169,    54,    55,   163,    56,     4,
     173,   174,   177,    99,   100,   192,    54,    55,   197,    56,
     103,   104,   105,   106,   114,   198,   202,   209,   211,   212,
     216,   182,   218,   219,   115,   220,   222,   116,   117,   118,
     119,   183,   225,   241,   116,   117,   118,   119,   237,     1,
       2,   246,   116,   117,   118,   119,     3,     4,     5,   247,
       6,     7,     8,     9,    10,   249,   248,   253,    11,    12,
      13,   227,   228,   258,   261,   259,    14,    15,   264,   271,
     270,   273,   277,   279,    16,   284,    17,   282,    69,    18,
     289,   229,   230,   231,   232,   233,   234,   235,   292,   295,
     298,   305,   294,   116,   117,   118,   119,   297,   304,   310,
     315,   318,    88,   293,   263,   306,   311,   239,   269,   140,
     319
};

static const yytype_uint16 yycheck[] =
{
       3,   189,     4,   115,    92,   135,   175,    95,     9,     9,
     258,   160,   279,    12,    12,    26,    27,    28,    29,    30,
       9,    22,    22,    74,    21,    22,    20,   237,    21,    34,
     297,   219,   220,    22,    74,    21,    12,    12,   150,   151,
       6,    36,     8,   131,    20,    20,    74,    50,   136,   259,
     199,    45,    42,    56,     7,     8,   304,   305,    60,     0,
      54,     3,    21,    64,    64,    64,    64,   255,    70,     8,
     318,   183,   282,    74,    74,    77,   245,    33,    21,   209,
      77,    78,    79,    80,    77,    78,    79,    80,    64,    64,
      20,    77,    78,    79,    80,   283,   284,    21,    20,   102,
     103,   104,   105,   106,   216,    74,   108,   109,   110,    21,
      74,   113,    74,    45,   116,   117,   118,   119,    77,    78,
      79,    80,    54,    74,    54,   128,    56,    57,    58,    59,
      60,    61,    62,    63,    77,    78,    79,    80,    45,     6,
      74,     8,    72,    73,    74,    75,    76,    54,    78,    79,
      20,    50,    54,    77,    78,    79,    80,    56,   246,    20,
      20,   249,    79,    80,    36,    77,    78,    79,    80,    74,
      72,    73,    36,    75,    76,    66,    78,    74,   180,   181,
      47,    77,    78,    79,    80,    20,    39,   275,    55,   192,
      79,    80,   280,    54,   197,    56,    57,    58,    59,    60,
      61,    62,    63,    43,   103,   104,   105,   106,    20,    72,
      73,    72,    73,    74,    75,    76,    40,    78,    79,    54,
      20,    56,    57,    58,    59,    60,    61,    62,    63,    13,
      14,    20,    74,    40,   236,    22,    74,    72,    73,    74,
      75,    76,    54,    78,    56,    57,    58,    59,    60,    61,
      62,    63,    22,    74,    54,    22,    21,    74,   261,    22,
      72,    73,    74,    75,    76,    54,    78,    22,    74,    35,
      74,    74,    72,    73,    75,    75,    76,    37,    78,    12,
      74,    40,    74,    72,    73,    20,    75,    76,    66,    78,
      77,    78,    79,    80,    64,    22,    34,    22,    20,    74,
      74,    64,    10,    74,    74,    74,    49,    77,    78,    79,
      80,    74,    22,     6,    77,    78,    79,    80,    38,     4,
       5,    21,    77,    78,    79,    80,    11,    12,    13,    74,
      15,    16,    17,    18,    19,    21,    20,    74,    23,    24,
      25,    45,    46,    50,    22,    51,    31,    32,    46,    72,
      74,    54,    22,    74,    39,    74,    41,    40,    74,    44,
      48,    65,    66,    67,    68,    69,    70,    71,    21,    21,
      21,    50,    54,    77,    78,    79,    80,    74,    22,    21,
      54,    22,    18,   263,   225,   291,   304,   198,   239,   102,
     318
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     4,     5,    11,    12,    13,    15,    16,    17,    18,
      19,    23,    24,    25,    31,    32,    39,    41,    44,    83,
      84,    85,    86,    87,    88,    89,    90,    91,    92,    93,
      94,    95,    96,    97,    98,    99,   104,   109,   110,   113,
     114,   139,   140,   141,     6,     8,    47,    55,     6,     8,
      20,    54,    72,    73,    75,    76,    78,   108,   115,   116,
      20,    56,    57,    58,    59,    60,    61,    62,    63,    74,
      78,    79,   108,   117,   118,   120,   121,   122,   124,   126,
      74,     7,     8,    34,    36,    74,    74,    42,    84,     0,
       3,   142,    74,    74,     8,    74,    74,    74,   116,    72,
      73,   116,    22,    77,    78,    79,    80,   118,    20,    20,
      20,    33,   118,    22,    64,    74,    77,    78,    79,    80,
     119,    79,   118,    36,    36,    74,    74,    39,    66,    43,
      20,    64,   113,    40,    74,    20,    64,   113,    40,    21,
     115,   116,   116,   116,   116,    21,   118,   118,   118,    74,
     118,    74,   119,   118,   118,   118,   118,    21,    21,    74,
     125,    74,    35,    37,   129,    74,   111,    78,   108,    75,
      74,   101,   113,    74,    40,   101,   113,    74,    21,    21,
      22,    22,    64,    74,   119,   119,     9,    22,    64,    74,
     127,   129,    20,   106,   118,   136,   137,    66,    22,   112,
      72,    73,    34,    26,    27,    28,    29,    30,   103,    22,
     100,    20,    74,   100,   118,   118,    74,   119,    10,    74,
      74,   127,    49,   132,   108,    22,   105,    45,    46,    65,
      66,    67,    68,    69,    70,    71,   138,    38,   108,   111,
     129,     6,    20,    45,    54,   101,    21,    74,    20,    21,
      21,    21,   119,    74,    64,    74,   127,   127,    50,    51,
     130,    22,   107,   106,    46,    45,    54,   118,   136,   112,
      74,    72,   102,    54,   100,    64,   113,    22,   123,    74,
      64,   113,    40,   128,    74,   127,   126,   131,   136,    48,
     135,   108,    21,   105,    54,    21,   113,    74,    21,   123,
     113,   136,   127,   127,    22,    50,   107,    45,    54,   123,
      21,   131,   126,   133,   134,    54,    13,    14,    22,   134
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    82,    83,    84,    84,    84,    84,    84,    84,    84,
      84,    84,    84,    84,    84,    84,    84,    84,    84,    84,
      84,    84,    84,    84,    84,    84,    85,    86,    87,    88,
      89,    90,    91,    92,    93,    94,    95,    95,    96,    97,
      98,    98,    98,    98,    99,    99,    99,    99,   100,   100,
     101,   101,   101,   101,   101,   101,   101,   102,   103,   103,
     103,   103,   104,   105,   105,   106,   107,   107,   108,   108,
     108,   108,   108,   108,   108,   109,   110,   111,   112,   112,
     113,   113,   114,   115,   115,   116,   116,   116,   116,   116,
     116,   116,   117,   117,   117,   117,   117,   118,   118,   118,
     118,   118,   118,   119,   119,   119,   119,   120,   120,   120,
     120,   121,   121,   122,   122,   122,   122,   122,   123,   123,
     124,   124,   124,   124,   125,   125,   125,   126,   126,   127,
     127,   127,   127,   127,   128,   128,   129,   129,   130,   130,
     131,   131,   132,   132,   133,   133,   133,   134,   134,   134,
     135,   135,   136,   136,   136,   137,   137,   137,   138,   138,
     138,   138,   138,   138,   138,   138,   139,   140,   141,   142,
     142
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     2,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     3,     2,     4,     2,     9,    10,     5,     7,
       5,     4,     9,     8,     5,     4,     9,     8,     0,     3,
       5,     2,     2,     6,     3,     7,     4,     1,     1,     1,
       1,     1,     6,     0,     3,     4,     0,     3,     1,     2,
       1,     2,     1,     1,     1,     4,     6,     3,     0,     3,
       2,     8,     2,     1,     3,     3,     3,     3,     3,     3,
       2,     1,     1,     1,     1,     1,     3,     3,     3,     3,
       3,     2,     1,     0,     3,     5,     4,     4,     4,     6,
       6,     3,     3,     1,     1,     1,     1,     1,     0,     3,
       1,     2,     4,     3,     2,     4,     3,     1,     3,     0,
       3,     5,     4,     5,     0,     2,     0,     2,     0,     2,
       1,     3,     0,     3,     1,     2,     2,     0,     1,     3,
       0,     3,     0,     1,     3,     3,     3,     4,     1,     1,
       1,     1,     1,     1,     1,     2,     7,     2,     4,     0,
       1
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
#line 243 "yacc_sql.y" /* yacc.c:1646  */
    {
    std::unique_ptr<ParsedSqlNode> sql_node = std::unique_ptr<ParsedSqlNode>((yyvsp[-1].sql_node));
    sql_result->add_sql_node(std::move(sql_node));
  }
#line 1739 "yacc_sql.cpp" /* yacc.c:1646  */
    break;

  case 26:
#line 276 "yacc_sql.y" /* yacc.c:1646  */
    {
      (void)yynerrs;  // 这么写为了消除yynerrs未使用的告警。如果你有更好的方法欢迎提PR
      (yyval.sql_node) = new ParsedSqlNode(SCF_EXIT);
    }
#line 1748 "yacc_sql.cpp" /* yacc.c:1646  */
    break;

  case 27:
#line 282 "yacc_sql.y" /* yacc.c:1646  */
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_HELP);
    }
#line 1756 "yacc_sql.cpp" /* yacc.c:1646  */
    break;

  case 28:
#line 287 "yacc_sql.y" /* yacc.c:1646  */
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_SYNC);
    }
#line 1764 "yacc_sql.cpp" /* yacc.c:1646  */
    break;

  case 29:
#line 293 "yacc_sql.y" /* yacc.c:1646  */
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_BEGIN);
    }
#line 1772 "yacc_sql.cpp" /* yacc.c:1646  */
    break;

  case 30:
#line 299 "yacc_sql.y" /* yacc.c:1646  */
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_COMMIT);
    }
#line 1780 "yacc_sql.cpp" /* yacc.c:1646  */
    break;

  case 31:
#line 305 "yacc_sql.y" /* yacc.c:1646  */
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_ROLLBACK);
    }
#line 1788 "yacc_sql.cpp" /* yacc.c:1646  */
    break;

  case 32:
#line 311 "yacc_sql.y" /* yacc.c:1646  */
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_DROP_TABLE);
      (yyval.sql_node)->drop_table.relation_name = (yyvsp[0].string);
      free((yyvsp[0].string));
    }
#line 1798 "yacc_sql.cpp" /* yacc.c:1646  */
    break;

  case 33:
#line 318 "yacc_sql.y" /* yacc.c:1646  */
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_SHOW_TABLES);
    }
#line 1806 "yacc_sql.cpp" /* yacc.c:1646  */
    break;

  case 34:
#line 323 "yacc_sql.y" /* yacc.c:1646  */
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_SHOW_INDEX);
      (yyval.sql_node)->show_index.relation_name = (yyvsp[0].string);
      free((yyvsp[0].string));
    }
#line 1816 "yacc_sql.cpp" /* yacc.c:1646  */
    break;

  case 35:
#line 330 "yacc_sql.y" /* yacc.c:1646  */
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_DESC_TABLE);
      (yyval.sql_node)->desc_table.relation_name = (yyvsp[0].string);
      free((yyvsp[0].string));
    }
#line 1826 "yacc_sql.cpp" /* yacc.c:1646  */
    break;

  case 36:
#line 339 "yacc_sql.y" /* yacc.c:1646  */
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
#line 1849 "yacc_sql.cpp" /* yacc.c:1646  */
    break;

  case 37:
#line 358 "yacc_sql.y" /* yacc.c:1646  */
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
#line 1872 "yacc_sql.cpp" /* yacc.c:1646  */
    break;

  case 38:
#line 380 "yacc_sql.y" /* yacc.c:1646  */
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_DROP_INDEX);
      (yyval.sql_node)->drop_index.index_name = (yyvsp[-2].string);
      (yyval.sql_node)->drop_index.relation_name = (yyvsp[0].string);
      free((yyvsp[-2].string));
      free((yyvsp[0].string));
    }
#line 1884 "yacc_sql.cpp" /* yacc.c:1646  */
    break;

  case 39:
#line 390 "yacc_sql.y" /* yacc.c:1646  */
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
#line 1904 "yacc_sql.cpp" /* yacc.c:1646  */
    break;

  case 40:
#line 408 "yacc_sql.y" /* yacc.c:1646  */
    {
        (yyval.sql_node) = new ParsedSqlNode(SCF_CREATE_TABLE_SELECT);
        CreateTableSelectSqlNode &create_table_select = (yyval.sql_node)->create_table_select;
        create_table_select.relation_name = (yyvsp[-2].string);
        free((yyvsp[-2].string));

        create_table_select.selection = (yyvsp[0].sql_node)->selection;
        delete (yyvsp[0].sql_node);
     }
#line 1918 "yacc_sql.cpp" /* yacc.c:1646  */
    break;

  case 41:
#line 418 "yacc_sql.y" /* yacc.c:1646  */
    {
          (yyval.sql_node) = new ParsedSqlNode(SCF_CREATE_TABLE_SELECT);
          CreateTableSelectSqlNode &create_table_select = (yyval.sql_node)->create_table_select;
          create_table_select.relation_name = (yyvsp[-1].string);
          free((yyvsp[-1].string));

          create_table_select.selection = (yyvsp[0].sql_node)->selection;
          delete (yyvsp[0].sql_node);
       }
#line 1932 "yacc_sql.cpp" /* yacc.c:1646  */
    break;

  case 42:
#line 428 "yacc_sql.y" /* yacc.c:1646  */
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
#line 1956 "yacc_sql.cpp" /* yacc.c:1646  */
    break;

  case 43:
#line 448 "yacc_sql.y" /* yacc.c:1646  */
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
#line 1980 "yacc_sql.cpp" /* yacc.c:1646  */
    break;

  case 44:
#line 470 "yacc_sql.y" /* yacc.c:1646  */
    {
        (yyval.sql_node) = new ParsedSqlNode(SCF_CREATE_TABLE_SELECT);
        CreateTableSelectSqlNode &create_table_select = (yyval.sql_node)->create_table_select;
        create_table_select.relation_name = (yyvsp[-2].string);
        free((yyvsp[-2].string));

        create_table_select.selection = (yyvsp[0].sql_node)->selection;
        delete (yyvsp[0].sql_node);
     }
#line 1994 "yacc_sql.cpp" /* yacc.c:1646  */
    break;

  case 45:
#line 480 "yacc_sql.y" /* yacc.c:1646  */
    {
          (yyval.sql_node) = new ParsedSqlNode(SCF_CREATE_TABLE_SELECT);
          CreateTableSelectSqlNode &create_table_select = (yyval.sql_node)->create_table_select;
          create_table_select.relation_name = (yyvsp[-1].string);
          free((yyvsp[-1].string));

          create_table_select.selection = (yyvsp[0].sql_node)->selection;
          delete (yyvsp[0].sql_node);
       }
#line 2008 "yacc_sql.cpp" /* yacc.c:1646  */
    break;

  case 46:
#line 490 "yacc_sql.y" /* yacc.c:1646  */
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
#line 2032 "yacc_sql.cpp" /* yacc.c:1646  */
    break;

  case 47:
#line 510 "yacc_sql.y" /* yacc.c:1646  */
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
#line 2056 "yacc_sql.cpp" /* yacc.c:1646  */
    break;

  case 48:
#line 532 "yacc_sql.y" /* yacc.c:1646  */
    {
      (yyval.attr_infos) = nullptr;
    }
#line 2064 "yacc_sql.cpp" /* yacc.c:1646  */
    break;

  case 49:
#line 536 "yacc_sql.y" /* yacc.c:1646  */
    {
      if ((yyvsp[0].attr_infos) != nullptr) {
        (yyval.attr_infos) = (yyvsp[0].attr_infos);
      } else {
        (yyval.attr_infos) = new std::vector<AttrInfoSqlNode>;
      }
      (yyval.attr_infos)->emplace_back(*(yyvsp[-1].attr_info));
      delete (yyvsp[-1].attr_info);
    }
#line 2078 "yacc_sql.cpp" /* yacc.c:1646  */
    break;

  case 50:
#line 549 "yacc_sql.y" /* yacc.c:1646  */
    {
      (yyval.attr_info) = new AttrInfoSqlNode;
      (yyval.attr_info)->type = (AttrType)(yyvsp[-3].number);
      (yyval.attr_info)->name = (yyvsp[-4].string);
      (yyval.attr_info)->length = (yyvsp[-1].number);
      (yyval.attr_info)->nullable = true;
      free((yyvsp[-4].string));
    }
#line 2091 "yacc_sql.cpp" /* yacc.c:1646  */
    break;

  case 51:
#line 558 "yacc_sql.y" /* yacc.c:1646  */
    {
      (yyval.attr_info) = new AttrInfoSqlNode;
      (yyval.attr_info)->type = (AttrType)TEXTS;
      (yyval.attr_info)->name = (yyvsp[-1].string);
      (yyval.attr_info)->length = 12;
      free((yyvsp[-1].string));
    }
#line 2103 "yacc_sql.cpp" /* yacc.c:1646  */
    break;

  case 52:
#line 566 "yacc_sql.y" /* yacc.c:1646  */
    {
      (yyval.attr_info) = new AttrInfoSqlNode;
      (yyval.attr_info)->type = (AttrType)(yyvsp[0].number);
      (yyval.attr_info)->name = (yyvsp[-1].string);
      (yyval.attr_info)->length = 4;
      (yyval.attr_info)->nullable = true;
      free((yyvsp[-1].string));
    }
#line 2116 "yacc_sql.cpp" /* yacc.c:1646  */
    break;

  case 53:
#line 575 "yacc_sql.y" /* yacc.c:1646  */
    {
        (yyval.attr_info) = new AttrInfoSqlNode;
        (yyval.attr_info)->type = (AttrType)(yyvsp[-4].number);
        (yyval.attr_info)->name = (yyvsp[-5].string);
        (yyval.attr_info)->length = (yyvsp[-2].number);
        (yyval.attr_info)->nullable = true;
        free((yyvsp[-5].string));
    }
#line 2129 "yacc_sql.cpp" /* yacc.c:1646  */
    break;

  case 54:
#line 584 "yacc_sql.y" /* yacc.c:1646  */
    {
        (yyval.attr_info) = new AttrInfoSqlNode;
        (yyval.attr_info)->type = (AttrType)(yyvsp[-1].number);
        (yyval.attr_info)->name = (yyvsp[-2].string);
        (yyval.attr_info)->length = 4;
        (yyval.attr_info)->nullable = true;
        free((yyvsp[-2].string));
    }
#line 2142 "yacc_sql.cpp" /* yacc.c:1646  */
    break;

  case 55:
#line 593 "yacc_sql.y" /* yacc.c:1646  */
    {
      (yyval.attr_info) = new AttrInfoSqlNode;
      (yyval.attr_info)->type = (AttrType)(yyvsp[-5].number);
      (yyval.attr_info)->name = (yyvsp[-6].string);
      (yyval.attr_info)->length = (yyvsp[-3].number);
      (yyval.attr_info)->nullable = false;
      free((yyvsp[-6].string));
    }
#line 2155 "yacc_sql.cpp" /* yacc.c:1646  */
    break;

  case 56:
#line 602 "yacc_sql.y" /* yacc.c:1646  */
    {
      (yyval.attr_info) = new AttrInfoSqlNode;
      (yyval.attr_info)->type = (AttrType)(yyvsp[-2].number);
      (yyval.attr_info)->name = (yyvsp[-3].string);
      (yyval.attr_info)->length = 4;
      (yyval.attr_info)->nullable = false;
      free((yyvsp[-3].string));
    }
#line 2168 "yacc_sql.cpp" /* yacc.c:1646  */
    break;

  case 57:
#line 612 "yacc_sql.y" /* yacc.c:1646  */
    {(yyval.number) = (yyvsp[0].number);}
#line 2174 "yacc_sql.cpp" /* yacc.c:1646  */
    break;

  case 58:
#line 615 "yacc_sql.y" /* yacc.c:1646  */
    { (yyval.number)=INTS; }
#line 2180 "yacc_sql.cpp" /* yacc.c:1646  */
    break;

  case 59:
#line 616 "yacc_sql.y" /* yacc.c:1646  */
    { (yyval.number)=CHARS; }
#line 2186 "yacc_sql.cpp" /* yacc.c:1646  */
    break;

  case 60:
#line 617 "yacc_sql.y" /* yacc.c:1646  */
    { (yyval.number)=FLOATS; }
#line 2192 "yacc_sql.cpp" /* yacc.c:1646  */
    break;

  case 61:
#line 618 "yacc_sql.y" /* yacc.c:1646  */
    { (yyval.number)=DATES; }
#line 2198 "yacc_sql.cpp" /* yacc.c:1646  */
    break;

  case 62:
#line 622 "yacc_sql.y" /* yacc.c:1646  */
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
#line 2215 "yacc_sql.cpp" /* yacc.c:1646  */
    break;

  case 63:
#line 637 "yacc_sql.y" /* yacc.c:1646  */
    {
	    (yyval.row_value_list) = nullptr;
	}
#line 2223 "yacc_sql.cpp" /* yacc.c:1646  */
    break;

  case 64:
#line 640 "yacc_sql.y" /* yacc.c:1646  */
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
#line 2240 "yacc_sql.cpp" /* yacc.c:1646  */
    break;

  case 65:
#line 655 "yacc_sql.y" /* yacc.c:1646  */
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
#line 2255 "yacc_sql.cpp" /* yacc.c:1646  */
    break;

  case 66:
#line 668 "yacc_sql.y" /* yacc.c:1646  */
    {
      (yyval.value_list) = nullptr;
    }
#line 2263 "yacc_sql.cpp" /* yacc.c:1646  */
    break;

  case 67:
#line 671 "yacc_sql.y" /* yacc.c:1646  */
    {
      if ((yyvsp[0].value_list) != nullptr) {
        (yyval.value_list) = (yyvsp[0].value_list);
      } else {
        (yyval.value_list) = new std::vector<Value>;
      }
      (yyval.value_list)->emplace_back(*(yyvsp[-1].value));
      delete (yyvsp[-1].value);
    }
#line 2277 "yacc_sql.cpp" /* yacc.c:1646  */
    break;

  case 68:
#line 682 "yacc_sql.y" /* yacc.c:1646  */
    {
      (yyval.value) = new Value((int)(yyvsp[0].number));
      (yyloc) = (yylsp[0]);
    }
#line 2286 "yacc_sql.cpp" /* yacc.c:1646  */
    break;

  case 69:
#line 686 "yacc_sql.y" /* yacc.c:1646  */
    {
      (yyval.value) = new Value(-(int)(yyvsp[0].number));
      (yyloc) = (yylsp[-1]);
    }
#line 2295 "yacc_sql.cpp" /* yacc.c:1646  */
    break;

  case 70:
#line 690 "yacc_sql.y" /* yacc.c:1646  */
    {
      (yyval.value) = new Value((float)(yyvsp[0].floats));
      (yyloc) = (yylsp[0]);
    }
#line 2304 "yacc_sql.cpp" /* yacc.c:1646  */
    break;

  case 71:
#line 694 "yacc_sql.y" /* yacc.c:1646  */
    {
      (yyval.value) = new Value(-(float)(yyvsp[0].floats));
      (yyloc) = (yylsp[-1]);
    }
#line 2313 "yacc_sql.cpp" /* yacc.c:1646  */
    break;

  case 72:
#line 698 "yacc_sql.y" /* yacc.c:1646  */
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
#line 2332 "yacc_sql.cpp" /* yacc.c:1646  */
    break;

  case 73:
#line 712 "yacc_sql.y" /* yacc.c:1646  */
    {
      char *tmp = common::substr((yyvsp[0].string),1,strlen((yyvsp[0].string))-2);
      (yyval.value) = new Value(tmp);
      free(tmp);
    }
#line 2342 "yacc_sql.cpp" /* yacc.c:1646  */
    break;

  case 74:
#line 717 "yacc_sql.y" /* yacc.c:1646  */
    {
        (yyval.value) = new Value();
    }
#line 2350 "yacc_sql.cpp" /* yacc.c:1646  */
    break;

  case 75:
#line 724 "yacc_sql.y" /* yacc.c:1646  */
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_DELETE);
      (yyval.sql_node)->deletion.relation_name = (yyvsp[-1].string);
      if ((yyvsp[0].condition_list) != nullptr) {
        (yyval.sql_node)->deletion.conditions.swap(*(yyvsp[0].condition_list));
        delete (yyvsp[0].condition_list);
      }
      free((yyvsp[-1].string));
    }
#line 2364 "yacc_sql.cpp" /* yacc.c:1646  */
    break;

  case 76:
#line 751 "yacc_sql.y" /* yacc.c:1646  */
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
#line 2384 "yacc_sql.cpp" /* yacc.c:1646  */
    break;

  case 77:
#line 769 "yacc_sql.y" /* yacc.c:1646  */
    {
      (yyval.update_value) = new UpdateValueNode;
      (yyval.update_value)->attribute_name = (yyvsp[-2].string);
      (yyval.update_value)->value = *(yyvsp[0].value);
      free((yyvsp[-2].string));
      delete((yyvsp[0].value));
    }
#line 2396 "yacc_sql.cpp" /* yacc.c:1646  */
    break;

  case 78:
#line 779 "yacc_sql.y" /* yacc.c:1646  */
    {
      (yyval.update_value_list) = nullptr;
    }
#line 2404 "yacc_sql.cpp" /* yacc.c:1646  */
    break;

  case 79:
#line 782 "yacc_sql.y" /* yacc.c:1646  */
    {
      if ((yyvsp[0].update_value_list) != nullptr) {
        (yyval.update_value_list) = (yyvsp[0].update_value_list);
      } else {
        (yyval.update_value_list) = new std::vector<UpdateValueNode>;
      }
      (yyval.update_value_list)->emplace_back(*(yyvsp[-1].update_value));
      delete (yyvsp[-1].update_value);
    }
#line 2418 "yacc_sql.cpp" /* yacc.c:1646  */
    break;

  case 80:
#line 793 "yacc_sql.y" /* yacc.c:1646  */
    {  // function 可能出现
      (yyval.sql_node) = new ParsedSqlNode(SCF_SELECT);
      if ((yyvsp[0].expr_list) != nullptr) {
        (yyval.sql_node)->selection.project_exprs.swap(*(yyvsp[0].expr_list));
        delete (yyvsp[0].expr_list);
      }
    }
#line 2430 "yacc_sql.cpp" /* yacc.c:1646  */
    break;

  case 81:
#line 801 "yacc_sql.y" /* yacc.c:1646  */
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
#line 2466 "yacc_sql.cpp" /* yacc.c:1646  */
    break;

  case 82:
#line 835 "yacc_sql.y" /* yacc.c:1646  */
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_CALC);
      std::reverse((yyvsp[0].expression_list)->begin(), (yyvsp[0].expression_list)->end());
      (yyval.sql_node)->calc.expressions.swap(*(yyvsp[0].expression_list));
      delete (yyvsp[0].expression_list);
    }
#line 2477 "yacc_sql.cpp" /* yacc.c:1646  */
    break;

  case 83:
#line 845 "yacc_sql.y" /* yacc.c:1646  */
    {
      (yyval.expression_list) = new std::vector<Expression*>;
      (yyval.expression_list)->emplace_back((yyvsp[0].expression));
    }
#line 2486 "yacc_sql.cpp" /* yacc.c:1646  */
    break;

  case 84:
#line 850 "yacc_sql.y" /* yacc.c:1646  */
    {
      if ((yyvsp[0].expression_list) != nullptr) {
        (yyval.expression_list) = (yyvsp[0].expression_list);
      } else {
        (yyval.expression_list) = new std::vector<Expression *>;
      }
      (yyval.expression_list)->emplace_back((yyvsp[-2].expression));
    }
#line 2499 "yacc_sql.cpp" /* yacc.c:1646  */
    break;

  case 85:
#line 860 "yacc_sql.y" /* yacc.c:1646  */
    {
      (yyval.expression) = create_arithmetic_expression(ArithmeticExpr::Type::ADD, (yyvsp[-2].expression), (yyvsp[0].expression), sql_string, &(yyloc));
    }
#line 2507 "yacc_sql.cpp" /* yacc.c:1646  */
    break;

  case 86:
#line 863 "yacc_sql.y" /* yacc.c:1646  */
    {
      (yyval.expression) = create_arithmetic_expression(ArithmeticExpr::Type::SUB, (yyvsp[-2].expression), (yyvsp[0].expression), sql_string, &(yyloc));
    }
#line 2515 "yacc_sql.cpp" /* yacc.c:1646  */
    break;

  case 87:
#line 866 "yacc_sql.y" /* yacc.c:1646  */
    {
      (yyval.expression) = create_arithmetic_expression(ArithmeticExpr::Type::MUL, (yyvsp[-2].expression), (yyvsp[0].expression), sql_string, &(yyloc));
    }
#line 2523 "yacc_sql.cpp" /* yacc.c:1646  */
    break;

  case 88:
#line 869 "yacc_sql.y" /* yacc.c:1646  */
    {
      (yyval.expression) = create_arithmetic_expression(ArithmeticExpr::Type::DIV, (yyvsp[-2].expression), (yyvsp[0].expression), sql_string, &(yyloc));
    }
#line 2531 "yacc_sql.cpp" /* yacc.c:1646  */
    break;

  case 89:
#line 872 "yacc_sql.y" /* yacc.c:1646  */
    {
      (yyval.expression) = (yyvsp[-1].expression);
      (yyval.expression)->set_name(token_name(sql_string, &(yyloc)));
    }
#line 2540 "yacc_sql.cpp" /* yacc.c:1646  */
    break;

  case 90:
#line 876 "yacc_sql.y" /* yacc.c:1646  */
    {
      (yyval.expression) = create_arithmetic_expression(ArithmeticExpr::Type::NEGATIVE, (yyvsp[0].expression), nullptr, sql_string, &(yyloc));
    }
#line 2548 "yacc_sql.cpp" /* yacc.c:1646  */
    break;

  case 91:
#line 879 "yacc_sql.y" /* yacc.c:1646  */
    {
      (yyval.expression) = new ValueExpr(*(yyvsp[0].value));
      (yyval.expression)->set_name(token_name(sql_string, &(yyloc)));
      delete (yyvsp[0].value);
    }
#line 2558 "yacc_sql.cpp" /* yacc.c:1646  */
    break;

  case 92:
#line 890 "yacc_sql.y" /* yacc.c:1646  */
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
#line 2575 "yacc_sql.cpp" /* yacc.c:1646  */
    break;

  case 93:
#line 902 "yacc_sql.y" /* yacc.c:1646  */
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
#line 2592 "yacc_sql.cpp" /* yacc.c:1646  */
    break;

  case 94:
#line 914 "yacc_sql.y" /* yacc.c:1646  */
    {
      (yyval.expr) = (yyvsp[0].expr);
    }
#line 2600 "yacc_sql.cpp" /* yacc.c:1646  */
    break;

  case 95:
#line 917 "yacc_sql.y" /* yacc.c:1646  */
    {
      (yyval.expr) = (yyvsp[0].expr);
    }
#line 2608 "yacc_sql.cpp" /* yacc.c:1646  */
    break;

  case 96:
#line 920 "yacc_sql.y" /* yacc.c:1646  */
    {
      (yyvsp[-1].expr)->with_brace = true;
      (yyval.expr) = (yyvsp[-1].expr);
    }
#line 2617 "yacc_sql.cpp" /* yacc.c:1646  */
    break;

  case 97:
#line 928 "yacc_sql.y" /* yacc.c:1646  */
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
#line 2634 "yacc_sql.cpp" /* yacc.c:1646  */
    break;

  case 98:
#line 940 "yacc_sql.y" /* yacc.c:1646  */
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
#line 2651 "yacc_sql.cpp" /* yacc.c:1646  */
    break;

  case 99:
#line 952 "yacc_sql.y" /* yacc.c:1646  */
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
#line 2668 "yacc_sql.cpp" /* yacc.c:1646  */
    break;

  case 100:
#line 964 "yacc_sql.y" /* yacc.c:1646  */
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
#line 2685 "yacc_sql.cpp" /* yacc.c:1646  */
    break;

  case 101:
#line 976 "yacc_sql.y" /* yacc.c:1646  */
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
#line 2711 "yacc_sql.cpp" /* yacc.c:1646  */
    break;

  case 102:
#line 997 "yacc_sql.y" /* yacc.c:1646  */
    { (yyval.expr) = (yyvsp[0].expr); }
#line 2717 "yacc_sql.cpp" /* yacc.c:1646  */
    break;

  case 103:
#line 1003 "yacc_sql.y" /* yacc.c:1646  */
    {
      (yyval.expr_list) = nullptr;
    }
#line 2725 "yacc_sql.cpp" /* yacc.c:1646  */
    break;

  case 104:
#line 1006 "yacc_sql.y" /* yacc.c:1646  */
    {
      if ((yyvsp[0].expr_list) != nullptr) {
        (yyval.expr_list) = (yyvsp[0].expr_list);
      } else {
        (yyval.expr_list) = new std::vector<ExprSqlNode *>;
      }

      (yyval.expr_list)->emplace_back((yyvsp[-1].expr));
      // delete $2;     在stmt阶段删除
    }
#line 2740 "yacc_sql.cpp" /* yacc.c:1646  */
    break;

  case 105:
#line 1016 "yacc_sql.y" /* yacc.c:1646  */
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
#line 2755 "yacc_sql.cpp" /* yacc.c:1646  */
    break;

  case 106:
#line 1026 "yacc_sql.y" /* yacc.c:1646  */
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
#line 2770 "yacc_sql.cpp" /* yacc.c:1646  */
    break;

  case 107:
#line 1039 "yacc_sql.y" /* yacc.c:1646  */
    {
      FuncExprSqlNode* func = new FuncExprSqlNode;
      func->type = FuncType::FUNC_LENGTH;
      func->exprs.emplace_back((yyvsp[-1].expr));

      ExprSqlNode* expr = new ExprSqlNode;
      expr->type = ExprSqlNodeType::FUNCTION;
      expr->func_expr = func;
      (yyval.expr) = expr;
    }
#line 2785 "yacc_sql.cpp" /* yacc.c:1646  */
    break;

  case 108:
#line 1049 "yacc_sql.y" /* yacc.c:1646  */
    {
      FuncExprSqlNode* func = new FuncExprSqlNode;
      func->type = FuncType::FUNC_ROUND;
      func->exprs.emplace_back((yyvsp[-1].expr));

      ExprSqlNode* expr = new ExprSqlNode;
      expr->type = ExprSqlNodeType::FUNCTION;
      expr->func_expr = func;
      (yyval.expr) = expr;
    }
#line 2800 "yacc_sql.cpp" /* yacc.c:1646  */
    break;

  case 109:
#line 1059 "yacc_sql.y" /* yacc.c:1646  */
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
#line 2816 "yacc_sql.cpp" /* yacc.c:1646  */
    break;

  case 110:
#line 1070 "yacc_sql.y" /* yacc.c:1646  */
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
#line 2832 "yacc_sql.cpp" /* yacc.c:1646  */
    break;

  case 111:
#line 1084 "yacc_sql.y" /* yacc.c:1646  */
    {
      AggrExprSqlNode* aggr = new AggrExprSqlNode;
      aggr->type = (yyvsp[-2].aggr_func_type);
      aggr->expr = (yyvsp[-1].expr);

      ExprSqlNode* expr = new ExprSqlNode;
      expr->type = ExprSqlNodeType::AGGREGATION;
      expr->aggr_expr = aggr;
      (yyval.expr) = expr;
    }
#line 2847 "yacc_sql.cpp" /* yacc.c:1646  */
    break;

  case 112:
#line 1094 "yacc_sql.y" /* yacc.c:1646  */
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
#line 2877 "yacc_sql.cpp" /* yacc.c:1646  */
    break;

  case 113:
#line 1122 "yacc_sql.y" /* yacc.c:1646  */
    {
      (yyval.aggr_func_type) = AggrFuncType::AGGR_MAX;
    }
#line 2885 "yacc_sql.cpp" /* yacc.c:1646  */
    break;

  case 114:
#line 1125 "yacc_sql.y" /* yacc.c:1646  */
    {
      (yyval.aggr_func_type) = AggrFuncType::AGGR_MIN;
    }
#line 2893 "yacc_sql.cpp" /* yacc.c:1646  */
    break;

  case 115:
#line 1128 "yacc_sql.y" /* yacc.c:1646  */
    {
      (yyval.aggr_func_type) = AggrFuncType::AGGR_SUM;
    }
#line 2901 "yacc_sql.cpp" /* yacc.c:1646  */
    break;

  case 116:
#line 1131 "yacc_sql.y" /* yacc.c:1646  */
    {
      (yyval.aggr_func_type) = AggrFuncType::AGGR_AVG;
    }
#line 2909 "yacc_sql.cpp" /* yacc.c:1646  */
    break;

  case 117:
#line 1134 "yacc_sql.y" /* yacc.c:1646  */
    {
      (yyval.aggr_func_type) = AggrFuncType::AGGR_COUNT;
    }
#line 2917 "yacc_sql.cpp" /* yacc.c:1646  */
    break;

  case 118:
#line 1221 "yacc_sql.y" /* yacc.c:1646  */
    {
      (yyval.rel_index_attr_list) = nullptr;
    }
#line 2925 "yacc_sql.cpp" /* yacc.c:1646  */
    break;

  case 119:
#line 1224 "yacc_sql.y" /* yacc.c:1646  */
    {
      if ((yyvsp[0].rel_index_attr_list) != nullptr) {
        (yyval.rel_index_attr_list) = (yyvsp[0].rel_index_attr_list);
      } else {
        (yyval.rel_index_attr_list) = new std::vector<string>;
      }

      (yyval.rel_index_attr_list)->emplace_back((yyvsp[-1].string));
      free((yyvsp[-1].string));
    }
#line 2940 "yacc_sql.cpp" /* yacc.c:1646  */
    break;

  case 120:
#line 1236 "yacc_sql.y" /* yacc.c:1646  */
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
#line 2961 "yacc_sql.cpp" /* yacc.c:1646  */
    break;

  case 121:
#line 1253 "yacc_sql.y" /* yacc.c:1646  */
    {
      if ((yyvsp[0].expr_list) != nullptr) {
        (yyval.expr_list) = (yyvsp[0].expr_list);
      } else {
        (yyval.expr_list) = new std::vector<ExprSqlNode*>;
      }
      (yyval.expr_list)->emplace_back((yyvsp[-1].expr));
    }
#line 2974 "yacc_sql.cpp" /* yacc.c:1646  */
    break;

  case 122:
#line 1261 "yacc_sql.y" /* yacc.c:1646  */
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
#line 2989 "yacc_sql.cpp" /* yacc.c:1646  */
    break;

  case 123:
#line 1271 "yacc_sql.y" /* yacc.c:1646  */
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
#line 3004 "yacc_sql.cpp" /* yacc.c:1646  */
    break;

  case 124:
#line 1284 "yacc_sql.y" /* yacc.c:1646  */
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
#line 3019 "yacc_sql.cpp" /* yacc.c:1646  */
    break;

  case 125:
#line 1294 "yacc_sql.y" /* yacc.c:1646  */
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
#line 3035 "yacc_sql.cpp" /* yacc.c:1646  */
    break;

  case 126:
#line 1305 "yacc_sql.y" /* yacc.c:1646  */
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
#line 3051 "yacc_sql.cpp" /* yacc.c:1646  */
    break;

  case 127:
#line 1319 "yacc_sql.y" /* yacc.c:1646  */
    {
      (yyval.rel_attr) = new RelAttrSqlNode;
      (yyval.rel_attr)->attribute_name = (yyvsp[0].string);
      free((yyvsp[0].string));
    }
#line 3061 "yacc_sql.cpp" /* yacc.c:1646  */
    break;

  case 128:
#line 1324 "yacc_sql.y" /* yacc.c:1646  */
    {
      (yyval.rel_attr) = new RelAttrSqlNode;
      (yyval.rel_attr)->relation_name  = (yyvsp[-2].string);
      (yyval.rel_attr)->attribute_name = (yyvsp[0].string);
      free((yyvsp[-2].string));
      free((yyvsp[0].string));
    }
#line 3073 "yacc_sql.cpp" /* yacc.c:1646  */
    break;

  case 129:
#line 1352 "yacc_sql.y" /* yacc.c:1646  */
    {
      (yyval.relation_list) = nullptr;
    }
#line 3081 "yacc_sql.cpp" /* yacc.c:1646  */
    break;

  case 130:
#line 1355 "yacc_sql.y" /* yacc.c:1646  */
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
#line 3096 "yacc_sql.cpp" /* yacc.c:1646  */
    break;

  case 131:
#line 1365 "yacc_sql.y" /* yacc.c:1646  */
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
#line 3112 "yacc_sql.cpp" /* yacc.c:1646  */
    break;

  case 132:
#line 1376 "yacc_sql.y" /* yacc.c:1646  */
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
#line 3128 "yacc_sql.cpp" /* yacc.c:1646  */
    break;

  case 133:
#line 1387 "yacc_sql.y" /* yacc.c:1646  */
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
#line 3149 "yacc_sql.cpp" /* yacc.c:1646  */
    break;

  case 134:
#line 1405 "yacc_sql.y" /* yacc.c:1646  */
    {
       (yyval.condition_list) = nullptr;
    }
#line 3157 "yacc_sql.cpp" /* yacc.c:1646  */
    break;

  case 135:
#line 1408 "yacc_sql.y" /* yacc.c:1646  */
    {
       (yyval.condition_list) = (yyvsp[0].condition_list);
	}
#line 3165 "yacc_sql.cpp" /* yacc.c:1646  */
    break;

  case 136:
#line 1414 "yacc_sql.y" /* yacc.c:1646  */
    {
      (yyval.condition_list) = nullptr;
    }
#line 3173 "yacc_sql.cpp" /* yacc.c:1646  */
    break;

  case 137:
#line 1417 "yacc_sql.y" /* yacc.c:1646  */
    {
      (yyval.condition_list) = (yyvsp[0].condition_list);  
    }
#line 3181 "yacc_sql.cpp" /* yacc.c:1646  */
    break;

  case 138:
#line 1424 "yacc_sql.y" /* yacc.c:1646  */
    {
      (yyval.condition_list) = nullptr;
    }
#line 3189 "yacc_sql.cpp" /* yacc.c:1646  */
    break;

  case 139:
#line 1427 "yacc_sql.y" /* yacc.c:1646  */
    {
      (yyval.condition_list) = (yyvsp[0].condition_list);
    }
#line 3197 "yacc_sql.cpp" /* yacc.c:1646  */
    break;

  case 140:
#line 1434 "yacc_sql.y" /* yacc.c:1646  */
    {
        (yyval.rel_attr_list) = new std::vector<RelAttrSqlNode>;
        (yyval.rel_attr_list)->emplace_back(*(yyvsp[0].rel_attr));
        delete (yyvsp[0].rel_attr);
    }
#line 3207 "yacc_sql.cpp" /* yacc.c:1646  */
    break;

  case 141:
#line 1440 "yacc_sql.y" /* yacc.c:1646  */
    {
        (yyval.rel_attr_list) = (yyvsp[0].rel_attr_list);
        (yyval.rel_attr_list)->emplace_back(*(yyvsp[-2].rel_attr));
        delete (yyvsp[-2].rel_attr);
	}
#line 3217 "yacc_sql.cpp" /* yacc.c:1646  */
    break;

  case 142:
#line 1448 "yacc_sql.y" /* yacc.c:1646  */
    {
      (yyval.rel_attr_list) = nullptr;
    }
#line 3225 "yacc_sql.cpp" /* yacc.c:1646  */
    break;

  case 143:
#line 1451 "yacc_sql.y" /* yacc.c:1646  */
    {
      (yyval.rel_attr_list) = (yyvsp[0].rel_attr_list);
      std::reverse((yyval.rel_attr_list)->begin(), (yyval.rel_attr_list)->end());
    }
#line 3234 "yacc_sql.cpp" /* yacc.c:1646  */
    break;

  case 144:
#line 1459 "yacc_sql.y" /* yacc.c:1646  */
    {
		(yyval.order_attr) = new OrderBySqlNode;
		(yyval.order_attr)->attribute = *(yyvsp[0].rel_attr);
		(yyval.order_attr)->is_asc = true;

		delete (yyvsp[0].rel_attr);
	}
#line 3246 "yacc_sql.cpp" /* yacc.c:1646  */
    break;

  case 145:
#line 1468 "yacc_sql.y" /* yacc.c:1646  */
    {
		(yyval.order_attr) = new OrderBySqlNode;
        (yyval.order_attr)->attribute = *(yyvsp[-1].rel_attr);
      	(yyval.order_attr)->is_asc = true;

      	delete (yyvsp[-1].rel_attr);
	}
#line 3258 "yacc_sql.cpp" /* yacc.c:1646  */
    break;

  case 146:
#line 1477 "yacc_sql.y" /* yacc.c:1646  */
    {
		(yyval.order_attr) = new OrderBySqlNode;
        (yyval.order_attr)->attribute = *(yyvsp[-1].rel_attr);
      	(yyval.order_attr)->is_asc = false;

      	delete (yyvsp[-1].rel_attr);
	}
#line 3270 "yacc_sql.cpp" /* yacc.c:1646  */
    break;

  case 147:
#line 1487 "yacc_sql.y" /* yacc.c:1646  */
    {
        (yyval.order_attr_list) = nullptr;
	}
#line 3278 "yacc_sql.cpp" /* yacc.c:1646  */
    break;

  case 148:
#line 1491 "yacc_sql.y" /* yacc.c:1646  */
    {
        (yyval.order_attr_list) = new std::vector<OrderBySqlNode>;
        (yyval.order_attr_list)->emplace_back(*(yyvsp[0].order_attr));
        delete (yyvsp[0].order_attr);
    }
#line 3288 "yacc_sql.cpp" /* yacc.c:1646  */
    break;

  case 149:
#line 1497 "yacc_sql.y" /* yacc.c:1646  */
    {
        (yyval.order_attr_list) = (yyvsp[0].order_attr_list);
        (yyval.order_attr_list)->emplace_back(*(yyvsp[-2].order_attr));
        delete (yyvsp[-2].order_attr);
	}
#line 3298 "yacc_sql.cpp" /* yacc.c:1646  */
    break;

  case 150:
#line 1505 "yacc_sql.y" /* yacc.c:1646  */
    {
      (yyval.order_attr_list) = nullptr;
    }
#line 3306 "yacc_sql.cpp" /* yacc.c:1646  */
    break;

  case 151:
#line 1508 "yacc_sql.y" /* yacc.c:1646  */
    {
      (yyval.order_attr_list) = (yyvsp[0].order_attr_list);
      std::reverse((yyval.order_attr_list)->begin(), (yyval.order_attr_list)->end());
    }
#line 3315 "yacc_sql.cpp" /* yacc.c:1646  */
    break;

  case 152:
#line 1517 "yacc_sql.y" /* yacc.c:1646  */
    {
      (yyval.condition_list) = nullptr;
    }
#line 3323 "yacc_sql.cpp" /* yacc.c:1646  */
    break;

  case 153:
#line 1520 "yacc_sql.y" /* yacc.c:1646  */
    {
      (yyval.condition_list) = new std::vector<ConditionSqlNode>;
      (yyval.condition_list)->emplace_back(*(yyvsp[0].condition));
      delete (yyvsp[0].condition);
    }
#line 3333 "yacc_sql.cpp" /* yacc.c:1646  */
    break;

  case 154:
#line 1525 "yacc_sql.y" /* yacc.c:1646  */
    {
      (yyval.condition_list) = (yyvsp[0].condition_list);
      (yyval.condition_list)->emplace_back(*(yyvsp[-2].condition));
      delete (yyvsp[-2].condition);
    }
#line 3343 "yacc_sql.cpp" /* yacc.c:1646  */
    break;

  case 155:
#line 1533 "yacc_sql.y" /* yacc.c:1646  */
    {
      (yyval.condition) = new ConditionSqlNode;
      (yyval.condition)->left = (yyvsp[-2].expr);
      (yyval.condition)->comp = (yyvsp[-1].comp);
      (yyval.condition)->right = (yyvsp[0].expr);
    }
#line 3354 "yacc_sql.cpp" /* yacc.c:1646  */
    break;

  case 156:
#line 1540 "yacc_sql.y" /* yacc.c:1646  */
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
#line 3375 "yacc_sql.cpp" /* yacc.c:1646  */
    break;

  case 157:
#line 1557 "yacc_sql.y" /* yacc.c:1646  */
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
#line 3396 "yacc_sql.cpp" /* yacc.c:1646  */
    break;

  case 158:
#line 1625 "yacc_sql.y" /* yacc.c:1646  */
    { (yyval.comp) = EQUAL_TO; }
#line 3402 "yacc_sql.cpp" /* yacc.c:1646  */
    break;

  case 159:
#line 1626 "yacc_sql.y" /* yacc.c:1646  */
    { (yyval.comp) = LESS_THAN; }
#line 3408 "yacc_sql.cpp" /* yacc.c:1646  */
    break;

  case 160:
#line 1627 "yacc_sql.y" /* yacc.c:1646  */
    { (yyval.comp) = GREAT_THAN; }
#line 3414 "yacc_sql.cpp" /* yacc.c:1646  */
    break;

  case 161:
#line 1628 "yacc_sql.y" /* yacc.c:1646  */
    { (yyval.comp) = LESS_EQUAL; }
#line 3420 "yacc_sql.cpp" /* yacc.c:1646  */
    break;

  case 162:
#line 1629 "yacc_sql.y" /* yacc.c:1646  */
    { (yyval.comp) = GREAT_EQUAL; }
#line 3426 "yacc_sql.cpp" /* yacc.c:1646  */
    break;

  case 163:
#line 1630 "yacc_sql.y" /* yacc.c:1646  */
    { (yyval.comp) = NOT_EQUAL; }
#line 3432 "yacc_sql.cpp" /* yacc.c:1646  */
    break;

  case 164:
#line 1631 "yacc_sql.y" /* yacc.c:1646  */
    { (yyval.comp) = LIKE_OP; }
#line 3438 "yacc_sql.cpp" /* yacc.c:1646  */
    break;

  case 165:
#line 1632 "yacc_sql.y" /* yacc.c:1646  */
    { (yyval.comp) = NOT_LIKE_OP; }
#line 3444 "yacc_sql.cpp" /* yacc.c:1646  */
    break;

  case 166:
#line 1637 "yacc_sql.y" /* yacc.c:1646  */
    {
      char *tmp_file_name = common::substr((yyvsp[-3].string), 1, strlen((yyvsp[-3].string)) - 2);
      
      (yyval.sql_node) = new ParsedSqlNode(SCF_LOAD_DATA);
      (yyval.sql_node)->load_data.relation_name = (yyvsp[0].string);
      (yyval.sql_node)->load_data.file_name = tmp_file_name;
      free((yyvsp[0].string));
      free(tmp_file_name);
    }
#line 3458 "yacc_sql.cpp" /* yacc.c:1646  */
    break;

  case 167:
#line 1650 "yacc_sql.y" /* yacc.c:1646  */
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_EXPLAIN);
      (yyval.sql_node)->explain.sql_node = std::unique_ptr<ParsedSqlNode>((yyvsp[0].sql_node));
    }
#line 3467 "yacc_sql.cpp" /* yacc.c:1646  */
    break;

  case 168:
#line 1658 "yacc_sql.y" /* yacc.c:1646  */
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_SET_VARIABLE);
      (yyval.sql_node)->set_variable.name  = (yyvsp[-2].string);
      (yyval.sql_node)->set_variable.value = *(yyvsp[0].value);
      free((yyvsp[-2].string));
      delete (yyvsp[0].value);
    }
#line 3479 "yacc_sql.cpp" /* yacc.c:1646  */
    break;


#line 3483 "yacc_sql.cpp" /* yacc.c:1646  */
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
#line 1670 "yacc_sql.y" /* yacc.c:1906  */

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
