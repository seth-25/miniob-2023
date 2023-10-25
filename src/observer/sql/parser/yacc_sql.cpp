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
    HELP = 285,
    EXIT = 286,
    DOT = 287,
    INTO = 288,
    VALUES = 289,
    FROM = 290,
    WHERE = 291,
    AND = 292,
    SET = 293,
    ON = 294,
    LOAD = 295,
    DATA = 296,
    INFILE = 297,
    EXPLAIN = 298,
    NOT = 299,
    LIKE = 300,
    UNIQUE = 301,
    ORDER = 302,
    BY = 303,
    NULL_T = 304,
    AGGR_MAX = 305,
    AGGR_MIN = 306,
    AGGR_COUNT = 307,
    AGGR_AVG = 308,
    AGGR_SUM = 309,
    LENGTH = 310,
    ROUND = 311,
    DATE_FORMAT = 312,
    AS = 313,
    IS = 314,
    EQ = 315,
    LT = 316,
    GT = 317,
    LE = 318,
    GE = 319,
    NE = 320,
    NUMBER = 321,
    FLOAT = 322,
    ID = 323,
    SSS = 324,
    DATE_STR = 325,
    UMINUS = 326
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 124 "yacc_sql.y" /* yacc.c:355  */

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


#line 255 "yacc_sql.cpp" /* yacc.c:355  */
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

#line 285 "yacc_sql.cpp" /* yacc.c:358  */

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
#define YYFINAL  86
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   359

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  76
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  56
/* YYNRULES -- Number of rules.  */
#define YYNRULES  153
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  290

/* YYTRANSLATE[YYX] -- Symbol number corresponding to YYX as returned
   by yylex, with out-of-bounds checking.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   326

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
       2,     2,    73,    71,     2,    72,     2,    74,     2,     2,
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
      65,    66,    67,    68,    69,    70,    75
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   231,   231,   239,   240,   241,   242,   243,   244,   245,
     246,   247,   248,   249,   250,   251,   252,   253,   254,   255,
     256,   257,   258,   259,   263,   269,   274,   280,   286,   292,
     298,   305,   310,   317,   325,   344,   366,   376,   395,   398,
     411,   420,   429,   438,   447,   456,   467,   470,   471,   472,
     473,   476,   492,   495,   509,   523,   526,   537,   541,   545,
     549,   553,   567,   572,   578,   605,   624,   634,   637,   648,
     655,   681,   691,   696,   707,   710,   713,   716,   719,   723,
     726,   737,   749,   761,   764,   767,   775,   787,   799,   811,
     823,   844,   850,   853,   863,   873,   886,   896,   906,   917,
     931,   941,   961,   964,   967,   970,   973,  1060,  1063,  1075,
    1092,  1100,  1110,  1123,  1133,  1144,  1158,  1163,  1191,  1194,
    1204,  1215,  1226,  1244,  1247,  1253,  1256,  1261,  1270,  1279,
    1290,  1293,  1299,  1308,  1311,  1319,  1322,  1327,  1334,  1341,
    1358,  1427,  1428,  1429,  1430,  1431,  1432,  1433,  1434,  1438,
    1451,  1459,  1469,  1470
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
  "FLOAT_T", "DATE_T", "HELP", "EXIT", "DOT", "INTO", "VALUES", "FROM",
  "WHERE", "AND", "SET", "ON", "LOAD", "DATA", "INFILE", "EXPLAIN", "NOT",
  "LIKE", "UNIQUE", "ORDER", "BY", "NULL_T", "AGGR_MAX", "AGGR_MIN",
  "AGGR_COUNT", "AGGR_AVG", "AGGR_SUM", "LENGTH", "ROUND", "DATE_FORMAT",
  "AS", "IS", "EQ", "LT", "GT", "LE", "GE", "NE", "NUMBER", "FLOAT", "ID",
  "SSS", "DATE_STR", "'+'", "'-'", "'*'", "'/'", "UMINUS", "$accept",
  "commands", "command_wrapper", "exit_stmt", "help_stmt", "sync_stmt",
  "begin_stmt", "commit_stmt", "rollback_stmt", "drop_table_stmt",
  "show_tables_stmt", "show_index_stmt", "desc_table_stmt",
  "create_index_stmt", "drop_index_stmt", "create_table_stmt",
  "attr_def_list", "attr_def", "number", "type", "insert_stmt",
  "row_value_list", "row_value", "value_list", "value", "delete_stmt",
  "update_stmt", "update_value", "update_value_list", "select_stmt",
  "calc_stmt", "expression_list", "expression", "unary_expr", "expr",
  "expr_list", "func_expr", "aggr_func_expr", "aggr_func_type",
  "index_attr_list", "select_attr", "select_from", "rel_attr", "rel_list",
  "inner_condition_list", "where", "sort_unit", "sort_list", "order_by",
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
     325,    43,    45,    42,    47,   326
};
# endif

#define YYPACT_NINF -237

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-237)))

#define YYTABLE_NINF -1

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     293,     2,    29,   127,    72,   -49,    98,  -237,    20,    11,
     -39,  -237,  -237,  -237,  -237,  -237,    -7,    22,   293,    68,
      70,  -237,  -237,  -237,  -237,  -237,  -237,  -237,  -237,  -237,
    -237,  -237,  -237,  -237,  -237,  -237,  -237,  -237,  -237,  -237,
    -237,  -237,    15,    23,    80,    26,    33,   127,  -237,  -237,
    -237,  -237,  -237,   211,  -237,  -237,    86,   160,  -237,  -237,
    -237,  -237,  -237,    89,    94,   123,   114,   198,  -237,  -237,
    -237,   201,  -237,  -237,   134,   121,  -237,  -237,  -237,   138,
     106,   107,   139,   119,   140,  -237,  -237,  -237,  -237,   161,
     156,   130,  -237,   167,     3,  -237,  -237,  -237,   127,   127,
     127,   127,   127,     7,   160,   160,   160,   132,  -237,   160,
     151,   200,   160,   160,   160,   160,  -237,   135,   152,   157,
     190,   197,   166,   -27,   168,   170,   171,   196,   173,  -237,
    -237,    57,    57,  -237,  -237,  -237,    13,   -15,   222,  -237,
     218,   200,  -237,    63,    63,  -237,  -237,   215,    45,    -6,
     197,  -237,   223,   160,  -237,   185,   224,    82,  -237,   225,
     141,   234,   237,   193,  -237,  -237,  -237,   160,   160,   194,
     200,  -237,  -237,  -237,  -237,   253,   203,   214,     5,  -237,
     232,   -27,   262,   281,  -237,   248,   -27,   166,   197,  -237,
    -237,   282,  -237,  -237,  -237,  -237,    -8,   170,   266,   231,
     280,    61,    79,   200,  -237,   233,    -4,     5,  -237,   254,
    -237,   285,   223,  -237,   258,  -237,   -29,  -237,  -237,  -237,
    -237,  -237,  -237,   160,   160,  -237,   224,  -237,   245,   249,
     265,  -237,   234,  -237,   297,   252,  -237,  -237,  -237,   283,
     259,     5,  -237,  -237,   260,   -27,   300,   262,  -237,   286,
    -237,    90,  -237,  -237,  -237,  -237,   308,  -237,  -237,   264,
     309,   297,   160,     5,     5,  -237,   158,   312,  -237,   285,
    -237,  -237,  -237,   -23,   297,  -237,   316,  -237,  -237,  -237,
    -237,  -237,   260,  -237,   289,  -237,  -237,  -237,  -237,  -237
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     0,     0,     0,     0,     0,     0,    26,     0,     0,
       0,    27,    28,    29,    25,    24,     0,     0,     0,     0,
     152,    23,    22,    15,    16,    17,    18,     9,    10,    11,
      12,    13,    14,     8,     5,     7,     6,     4,     3,    19,
      20,    21,     0,     0,     0,     0,     0,     0,    63,    57,
      59,    62,    61,     0,    80,    71,    72,     0,   102,   103,
     106,   105,   104,     0,     0,     0,   116,     0,   109,    81,
      91,    92,    83,    84,     0,    69,    82,    33,    31,     0,
       0,     0,     0,     0,     0,   150,     1,   153,     2,     0,
       0,     0,    30,     0,     0,    57,    59,    79,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    90,     0,
       0,    92,     0,     0,     0,     0,   110,     0,     0,     0,
       0,   125,     0,     0,     0,     0,     0,     0,     0,    78,
      73,    74,    75,    76,    77,    85,     0,     0,     0,   117,
      92,    92,   112,    86,    87,    88,    89,     0,     0,   118,
     125,    32,     0,   135,    64,     0,    67,     0,   151,     0,
       0,    38,     0,     0,    36,    96,    97,     0,     0,     0,
      92,    93,   111,   101,   100,     0,     0,     0,   118,   113,
     133,     0,    52,     0,   126,   136,     0,     0,   125,    58,
      60,     0,    47,    48,    49,    50,    41,     0,     0,     0,
       0,     0,     0,    92,    95,     0,   118,   118,   115,     0,
      70,    55,     0,    51,     0,   147,     0,   141,   142,   143,
     144,   145,   146,     0,   135,    66,    67,    65,     0,     0,
       0,    43,    38,    37,   107,     0,    98,    99,    94,   123,
       0,   118,   119,   114,   130,     0,     0,    52,   148,     0,
     139,   138,   137,    68,   149,    46,     0,    45,    39,     0,
       0,   107,   135,   118,   118,   121,   127,   131,   134,    55,
      54,    53,   140,    40,   107,    34,     0,   124,   122,   120,
     129,   128,   130,    56,     0,    42,   108,    35,   132,    44
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -237,  -237,   321,  -237,  -237,  -237,  -237,  -237,  -237,  -237,
    -237,  -237,  -237,  -237,  -237,  -237,   115,   153,  -237,  -237,
    -237,   101,   137,    87,    -3,  -237,  -237,   164,   131,  -237,
    -237,   261,   -30,  -237,    -2,  -110,  -237,  -237,  -237,  -236,
    -237,  -237,  -235,  -174,  -237,  -139,  -237,    76,  -237,  -211,
    -237,  -237,  -237,  -237,  -237,  -237
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,    19,    20,    21,    22,    23,    24,    25,    26,    27,
      28,    29,    30,    31,    32,    33,   198,   161,   256,   196,
      34,   213,   182,   246,    69,    35,    36,   156,   188,    37,
      38,    55,    56,    70,   183,   116,    72,    73,    74,   260,
      75,   150,    76,   179,   263,   154,   267,   268,   210,   184,
     185,   223,    39,    40,    41,    88
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_uint16 yytable[] =
{
      54,   142,    71,   175,   208,   175,   166,   167,    42,   266,
      43,   180,   229,   252,   175,   249,   176,    94,   176,    77,
     250,   284,    48,    97,   129,   276,   285,   176,   135,    82,
     171,   172,   242,   243,   165,    45,   230,    46,   286,    49,
      50,   231,    51,    52,    54,   157,    81,   266,    44,   227,
      54,   277,   177,    80,   240,   103,   112,   113,   114,   115,
     204,    83,   178,    84,   241,   108,   174,   265,    86,   131,
     132,   133,   134,    87,    99,   100,   101,   102,   112,   113,
     114,   115,   236,    89,   112,   113,   114,   115,    91,   278,
     279,    90,    57,   238,    92,    54,    54,    54,    54,    54,
     237,    93,   136,   137,   138,    78,    79,   140,    98,   104,
     143,   144,   145,   146,   105,   148,   112,   113,   114,   115,
     158,    48,    58,    59,    60,    61,    62,    63,    64,    65,
     101,   102,   112,   113,   114,   115,   114,   115,    49,    50,
      66,    51,    52,   106,    67,    68,   107,    47,   189,   190,
     112,   113,   114,   115,   117,    57,   118,    99,   100,   101,
     102,   112,   113,   114,   115,   201,   202,   192,   193,   194,
     195,   280,   281,   119,   120,   121,    48,   122,   211,   123,
      57,   125,   124,   225,    48,    58,    59,    60,    61,    62,
      63,    64,    65,    49,    50,   126,    51,    52,   127,    53,
     139,    49,    50,    66,    51,    52,   128,    67,   147,    48,
      58,    59,    60,    61,    62,    63,    64,    65,    57,   141,
     149,   251,   109,   109,   152,   151,    49,    50,    66,    51,
      52,    47,    67,   153,   155,   163,   173,   159,   160,   162,
     109,   164,   269,   181,   168,   186,   187,    48,    58,    59,
      60,    61,    62,    63,    64,    65,   197,   199,   191,   110,
      48,   200,   203,   205,    95,    96,    66,    51,    52,   111,
      67,   206,   112,   113,   114,   115,   169,    95,    96,   209,
      51,    52,   207,    53,   212,   224,   170,   233,   228,   112,
     113,   114,   115,   112,   113,   114,   115,     1,     2,   234,
     235,   239,   244,   248,     3,     4,     5,   245,     6,     7,
       8,     9,    10,   254,   257,   255,    11,    12,    13,   259,
     261,   270,   262,    14,    15,   214,   215,   264,    66,   273,
     275,    16,   274,    17,   282,   272,    18,   287,   289,    85,
     216,   217,   218,   219,   220,   221,   222,   258,   271,   247,
     232,   226,   112,   113,   114,   115,   283,   253,   288,   130
};

static const yytype_uint16 yycheck[] =
{
       3,   111,     4,     9,   178,     9,    21,    22,     6,   244,
       8,   150,    20,   224,     9,    44,    22,    47,    22,    68,
      49,    44,    49,    53,    21,   261,    49,    22,    21,    68,
     140,   141,   206,   207,    21,     6,    44,     8,   274,    66,
      67,    49,    69,    70,    47,    72,    35,   282,    46,   188,
      53,   262,    58,    33,    58,    57,    71,    72,    73,    74,
     170,    68,    68,    41,    68,    67,    21,   241,     0,    99,
     100,   101,   102,     3,    71,    72,    73,    74,    71,    72,
      73,    74,    21,    68,    71,    72,    73,    74,     8,   263,
     264,    68,    20,   203,    68,    98,    99,   100,   101,   102,
      21,    68,   104,   105,   106,     7,     8,   109,    22,    20,
     112,   113,   114,   115,    20,   117,    71,    72,    73,    74,
     123,    49,    50,    51,    52,    53,    54,    55,    56,    57,
      73,    74,    71,    72,    73,    74,    73,    74,    66,    67,
      68,    69,    70,    20,    72,    73,    32,    20,    66,    67,
      71,    72,    73,    74,    20,    20,    35,    71,    72,    73,
      74,    71,    72,    73,    74,   167,   168,    26,    27,    28,
      29,    13,    14,    35,    68,    68,    49,    38,   181,    60,
      20,    20,    42,   186,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    66,    67,    39,    69,    70,    68,    72,
      68,    66,    67,    68,    69,    70,    39,    72,    73,    49,
      50,    51,    52,    53,    54,    55,    56,    57,    20,    68,
      68,   223,    22,    22,    34,    68,    66,    67,    68,    69,
      70,    20,    72,    36,    68,    39,    21,    69,    68,    68,
      22,    68,   245,    20,    22,    60,    22,    49,    50,    51,
      52,    53,    54,    55,    56,    57,    22,    20,    33,    58,
      49,    68,    68,    10,    66,    67,    68,    69,    70,    68,
      72,    68,    71,    72,    73,    74,    58,    66,    67,    47,
      69,    70,    68,    72,    22,    37,    68,    21,     6,    71,
      72,    73,    74,    71,    72,    73,    74,     4,     5,    68,
      20,    68,    48,    45,    11,    12,    13,    22,    15,    16,
      17,    18,    19,    68,    49,    66,    23,    24,    25,    22,
      68,    21,    39,    30,    31,    44,    45,    68,    68,    21,
      21,    38,    68,    40,    22,    49,    43,    21,    49,    18,
      59,    60,    61,    62,    63,    64,    65,   232,   247,   212,
     197,   187,    71,    72,    73,    74,   269,   226,   282,    98
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     4,     5,    11,    12,    13,    15,    16,    17,    18,
      19,    23,    24,    25,    30,    31,    38,    40,    43,    77,
      78,    79,    80,    81,    82,    83,    84,    85,    86,    87,
      88,    89,    90,    91,    96,   101,   102,   105,   106,   128,
     129,   130,     6,     8,    46,     6,     8,    20,    49,    66,
      67,    69,    70,    72,   100,   107,   108,    20,    50,    51,
      52,    53,    54,    55,    56,    57,    68,    72,    73,   100,
     109,   110,   112,   113,   114,   116,   118,    68,     7,     8,
      33,    35,    68,    68,    41,    78,     0,     3,   131,    68,
      68,     8,    68,    68,   108,    66,    67,   108,    22,    71,
      72,    73,    74,   110,    20,    20,    20,    32,   110,    22,
      58,    68,    71,    72,    73,    74,   111,    20,    35,    35,
      68,    68,    38,    60,    42,    20,    39,    68,    39,    21,
     107,   108,   108,   108,   108,    21,   110,   110,   110,    68,
     110,    68,   111,   110,   110,   110,   110,    73,   110,    68,
     117,    68,    34,    36,   121,    68,   103,    72,   100,    69,
      68,    93,    68,    39,    68,    21,    21,    22,    22,    58,
      68,   111,   111,    21,    21,     9,    22,    58,    68,   119,
     121,    20,    98,   110,   125,   126,    60,    22,   104,    66,
      67,    33,    26,    27,    28,    29,    95,    22,    92,    20,
      68,   110,   110,    68,   111,    10,    68,    68,   119,    47,
     124,   100,    22,    97,    44,    45,    59,    60,    61,    62,
      63,    64,    65,   127,    37,   100,   103,   121,     6,    20,
      44,    49,    93,    21,    68,    20,    21,    21,   111,    68,
      58,    68,   119,   119,    48,    22,    99,    98,    45,    44,
      49,   110,   125,   104,    68,    66,    94,    49,    92,    22,
     115,    68,    39,   120,    68,   119,   118,   122,   123,   100,
      21,    97,    49,    21,    68,    21,   115,   125,   119,   119,
      13,    14,    22,    99,    44,    49,   115,    21,   123,    49
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    76,    77,    78,    78,    78,    78,    78,    78,    78,
      78,    78,    78,    78,    78,    78,    78,    78,    78,    78,
      78,    78,    78,    78,    79,    80,    81,    82,    83,    84,
      85,    86,    87,    88,    89,    89,    90,    91,    92,    92,
      93,    93,    93,    93,    93,    93,    94,    95,    95,    95,
      95,    96,    97,    97,    98,    99,    99,   100,   100,   100,
     100,   100,   100,   100,   101,   102,   103,   104,   104,   105,
     105,   106,   107,   107,   108,   108,   108,   108,   108,   108,
     108,   109,   109,   109,   109,   109,   110,   110,   110,   110,
     110,   110,   111,   111,   111,   111,   112,   112,   112,   112,
     113,   113,   114,   114,   114,   114,   114,   115,   115,   116,
     116,   116,   116,   117,   117,   117,   118,   118,   119,   119,
     119,   119,   119,   120,   120,   121,   121,   122,   122,   122,
     123,   123,   123,   124,   124,   125,   125,   125,   126,   126,
     126,   127,   127,   127,   127,   127,   127,   127,   127,   128,
     129,   130,   131,   131
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     2,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       3,     2,     4,     2,     9,    10,     5,     7,     0,     3,
       5,     2,     6,     3,     7,     4,     1,     1,     1,     1,
       1,     6,     0,     3,     4,     0,     3,     1,     2,     1,
       2,     1,     1,     1,     4,     6,     3,     0,     3,     2,
       6,     2,     1,     3,     3,     3,     3,     3,     3,     2,
       1,     1,     1,     1,     1,     3,     3,     3,     3,     3,
       2,     1,     0,     3,     5,     4,     4,     4,     6,     6,
       4,     4,     1,     1,     1,     1,     1,     0,     3,     1,
       2,     4,     3,     2,     4,     3,     1,     3,     0,     3,
       5,     4,     5,     0,     2,     0,     2,     1,     2,     2,
       0,     1,     3,     0,     3,     0,     1,     3,     3,     3,
       4,     1,     1,     1,     1,     1,     1,     1,     2,     7,
       2,     4,     0,     1
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
#line 232 "yacc_sql.y" /* yacc.c:1646  */
    {
    std::unique_ptr<ParsedSqlNode> sql_node = std::unique_ptr<ParsedSqlNode>((yyvsp[-1].sql_node));
    sql_result->add_sql_node(std::move(sql_node));
  }
#line 1704 "yacc_sql.cpp" /* yacc.c:1646  */
    break;

  case 24:
#line 263 "yacc_sql.y" /* yacc.c:1646  */
    {
      (void)yynerrs;  // 这么写为了消除yynerrs未使用的告警。如果你有更好的方法欢迎提PR
      (yyval.sql_node) = new ParsedSqlNode(SCF_EXIT);
    }
#line 1713 "yacc_sql.cpp" /* yacc.c:1646  */
    break;

  case 25:
#line 269 "yacc_sql.y" /* yacc.c:1646  */
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_HELP);
    }
#line 1721 "yacc_sql.cpp" /* yacc.c:1646  */
    break;

  case 26:
#line 274 "yacc_sql.y" /* yacc.c:1646  */
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_SYNC);
    }
#line 1729 "yacc_sql.cpp" /* yacc.c:1646  */
    break;

  case 27:
#line 280 "yacc_sql.y" /* yacc.c:1646  */
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_BEGIN);
    }
#line 1737 "yacc_sql.cpp" /* yacc.c:1646  */
    break;

  case 28:
#line 286 "yacc_sql.y" /* yacc.c:1646  */
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_COMMIT);
    }
#line 1745 "yacc_sql.cpp" /* yacc.c:1646  */
    break;

  case 29:
#line 292 "yacc_sql.y" /* yacc.c:1646  */
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_ROLLBACK);
    }
#line 1753 "yacc_sql.cpp" /* yacc.c:1646  */
    break;

  case 30:
#line 298 "yacc_sql.y" /* yacc.c:1646  */
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_DROP_TABLE);
      (yyval.sql_node)->drop_table.relation_name = (yyvsp[0].string);
      free((yyvsp[0].string));
    }
#line 1763 "yacc_sql.cpp" /* yacc.c:1646  */
    break;

  case 31:
#line 305 "yacc_sql.y" /* yacc.c:1646  */
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_SHOW_TABLES);
    }
#line 1771 "yacc_sql.cpp" /* yacc.c:1646  */
    break;

  case 32:
#line 310 "yacc_sql.y" /* yacc.c:1646  */
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_SHOW_INDEX);
      (yyval.sql_node)->show_index.relation_name = (yyvsp[0].string);
      free((yyvsp[0].string));
    }
#line 1781 "yacc_sql.cpp" /* yacc.c:1646  */
    break;

  case 33:
#line 317 "yacc_sql.y" /* yacc.c:1646  */
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_DESC_TABLE);
      (yyval.sql_node)->desc_table.relation_name = (yyvsp[0].string);
      free((yyvsp[0].string));
    }
#line 1791 "yacc_sql.cpp" /* yacc.c:1646  */
    break;

  case 34:
#line 326 "yacc_sql.y" /* yacc.c:1646  */
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
#line 1814 "yacc_sql.cpp" /* yacc.c:1646  */
    break;

  case 35:
#line 345 "yacc_sql.y" /* yacc.c:1646  */
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
#line 1837 "yacc_sql.cpp" /* yacc.c:1646  */
    break;

  case 36:
#line 367 "yacc_sql.y" /* yacc.c:1646  */
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_DROP_INDEX);
      (yyval.sql_node)->drop_index.index_name = (yyvsp[-2].string);
      (yyval.sql_node)->drop_index.relation_name = (yyvsp[0].string);
      free((yyvsp[-2].string));
      free((yyvsp[0].string));
    }
#line 1849 "yacc_sql.cpp" /* yacc.c:1646  */
    break;

  case 37:
#line 377 "yacc_sql.y" /* yacc.c:1646  */
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
#line 1869 "yacc_sql.cpp" /* yacc.c:1646  */
    break;

  case 38:
#line 395 "yacc_sql.y" /* yacc.c:1646  */
    {
      (yyval.attr_infos) = nullptr;
    }
#line 1877 "yacc_sql.cpp" /* yacc.c:1646  */
    break;

  case 39:
#line 399 "yacc_sql.y" /* yacc.c:1646  */
    {
      if ((yyvsp[0].attr_infos) != nullptr) {
        (yyval.attr_infos) = (yyvsp[0].attr_infos);
      } else {
        (yyval.attr_infos) = new std::vector<AttrInfoSqlNode>;
      }
      (yyval.attr_infos)->emplace_back(*(yyvsp[-1].attr_info));
      delete (yyvsp[-1].attr_info);
    }
#line 1891 "yacc_sql.cpp" /* yacc.c:1646  */
    break;

  case 40:
#line 412 "yacc_sql.y" /* yacc.c:1646  */
    {
      (yyval.attr_info) = new AttrInfoSqlNode;
      (yyval.attr_info)->type = (AttrType)(yyvsp[-3].number);
      (yyval.attr_info)->name = (yyvsp[-4].string);
      (yyval.attr_info)->length = (yyvsp[-1].number);
      (yyval.attr_info)->nullable = true;
      free((yyvsp[-4].string));
    }
#line 1904 "yacc_sql.cpp" /* yacc.c:1646  */
    break;

  case 41:
#line 421 "yacc_sql.y" /* yacc.c:1646  */
    {
      (yyval.attr_info) = new AttrInfoSqlNode;
      (yyval.attr_info)->type = (AttrType)(yyvsp[0].number);
      (yyval.attr_info)->name = (yyvsp[-1].string);
      (yyval.attr_info)->length = 4;
      (yyval.attr_info)->nullable = true;
      free((yyvsp[-1].string));
    }
#line 1917 "yacc_sql.cpp" /* yacc.c:1646  */
    break;

  case 42:
#line 430 "yacc_sql.y" /* yacc.c:1646  */
    {
        (yyval.attr_info) = new AttrInfoSqlNode;
        (yyval.attr_info)->type = (AttrType)(yyvsp[-4].number);
        (yyval.attr_info)->name = (yyvsp[-5].string);
        (yyval.attr_info)->length = (yyvsp[-2].number);
        (yyval.attr_info)->nullable = true;
        free((yyvsp[-5].string));
    }
#line 1930 "yacc_sql.cpp" /* yacc.c:1646  */
    break;

  case 43:
#line 439 "yacc_sql.y" /* yacc.c:1646  */
    {
        (yyval.attr_info) = new AttrInfoSqlNode;
        (yyval.attr_info)->type = (AttrType)(yyvsp[-1].number);
        (yyval.attr_info)->name = (yyvsp[-2].string);
        (yyval.attr_info)->length = 4;
        (yyval.attr_info)->nullable = true;
        free((yyvsp[-2].string));
    }
#line 1943 "yacc_sql.cpp" /* yacc.c:1646  */
    break;

  case 44:
#line 448 "yacc_sql.y" /* yacc.c:1646  */
    {
      (yyval.attr_info) = new AttrInfoSqlNode;
      (yyval.attr_info)->type = (AttrType)(yyvsp[-5].number);
      (yyval.attr_info)->name = (yyvsp[-6].string);
      (yyval.attr_info)->length = (yyvsp[-3].number);
      (yyval.attr_info)->nullable = false;
      free((yyvsp[-6].string));
    }
#line 1956 "yacc_sql.cpp" /* yacc.c:1646  */
    break;

  case 45:
#line 457 "yacc_sql.y" /* yacc.c:1646  */
    {
      (yyval.attr_info) = new AttrInfoSqlNode;
      (yyval.attr_info)->type = (AttrType)(yyvsp[-2].number);
      (yyval.attr_info)->name = (yyvsp[-3].string);
      (yyval.attr_info)->length = 4;
      (yyval.attr_info)->nullable = false;
      free((yyvsp[-3].string));
    }
#line 1969 "yacc_sql.cpp" /* yacc.c:1646  */
    break;

  case 46:
#line 467 "yacc_sql.y" /* yacc.c:1646  */
    {(yyval.number) = (yyvsp[0].number);}
#line 1975 "yacc_sql.cpp" /* yacc.c:1646  */
    break;

  case 47:
#line 470 "yacc_sql.y" /* yacc.c:1646  */
    { (yyval.number)=INTS; }
#line 1981 "yacc_sql.cpp" /* yacc.c:1646  */
    break;

  case 48:
#line 471 "yacc_sql.y" /* yacc.c:1646  */
    { (yyval.number)=CHARS; }
#line 1987 "yacc_sql.cpp" /* yacc.c:1646  */
    break;

  case 49:
#line 472 "yacc_sql.y" /* yacc.c:1646  */
    { (yyval.number)=FLOATS; }
#line 1993 "yacc_sql.cpp" /* yacc.c:1646  */
    break;

  case 50:
#line 473 "yacc_sql.y" /* yacc.c:1646  */
    { (yyval.number)=DATES; }
#line 1999 "yacc_sql.cpp" /* yacc.c:1646  */
    break;

  case 51:
#line 477 "yacc_sql.y" /* yacc.c:1646  */
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
#line 2016 "yacc_sql.cpp" /* yacc.c:1646  */
    break;

  case 52:
#line 492 "yacc_sql.y" /* yacc.c:1646  */
    {
	    (yyval.row_value_list) = nullptr;
	}
#line 2024 "yacc_sql.cpp" /* yacc.c:1646  */
    break;

  case 53:
#line 495 "yacc_sql.y" /* yacc.c:1646  */
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
#line 2041 "yacc_sql.cpp" /* yacc.c:1646  */
    break;

  case 54:
#line 510 "yacc_sql.y" /* yacc.c:1646  */
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
#line 2056 "yacc_sql.cpp" /* yacc.c:1646  */
    break;

  case 55:
#line 523 "yacc_sql.y" /* yacc.c:1646  */
    {
      (yyval.value_list) = nullptr;
    }
#line 2064 "yacc_sql.cpp" /* yacc.c:1646  */
    break;

  case 56:
#line 526 "yacc_sql.y" /* yacc.c:1646  */
    {
      if ((yyvsp[0].value_list) != nullptr) {
        (yyval.value_list) = (yyvsp[0].value_list);
      } else {
        (yyval.value_list) = new std::vector<Value>;
      }
      (yyval.value_list)->emplace_back(*(yyvsp[-1].value));
      delete (yyvsp[-1].value);
    }
#line 2078 "yacc_sql.cpp" /* yacc.c:1646  */
    break;

  case 57:
#line 537 "yacc_sql.y" /* yacc.c:1646  */
    {
      (yyval.value) = new Value((int)(yyvsp[0].number));
      (yyloc) = (yylsp[0]);
    }
#line 2087 "yacc_sql.cpp" /* yacc.c:1646  */
    break;

  case 58:
#line 541 "yacc_sql.y" /* yacc.c:1646  */
    {
      (yyval.value) = new Value(-(int)(yyvsp[0].number));
      (yyloc) = (yylsp[-1]);
    }
#line 2096 "yacc_sql.cpp" /* yacc.c:1646  */
    break;

  case 59:
#line 545 "yacc_sql.y" /* yacc.c:1646  */
    {
      (yyval.value) = new Value((float)(yyvsp[0].floats));
      (yyloc) = (yylsp[0]);
    }
#line 2105 "yacc_sql.cpp" /* yacc.c:1646  */
    break;

  case 60:
#line 549 "yacc_sql.y" /* yacc.c:1646  */
    {
      (yyval.value) = new Value(-(float)(yyvsp[0].floats));
      (yyloc) = (yylsp[-1]);
    }
#line 2114 "yacc_sql.cpp" /* yacc.c:1646  */
    break;

  case 61:
#line 553 "yacc_sql.y" /* yacc.c:1646  */
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
#line 2133 "yacc_sql.cpp" /* yacc.c:1646  */
    break;

  case 62:
#line 567 "yacc_sql.y" /* yacc.c:1646  */
    {
      char *tmp = common::substr((yyvsp[0].string),1,strlen((yyvsp[0].string))-2);
      (yyval.value) = new Value(tmp);
      free(tmp);
    }
#line 2143 "yacc_sql.cpp" /* yacc.c:1646  */
    break;

  case 63:
#line 572 "yacc_sql.y" /* yacc.c:1646  */
    {
        (yyval.value) = new Value();
    }
#line 2151 "yacc_sql.cpp" /* yacc.c:1646  */
    break;

  case 64:
#line 579 "yacc_sql.y" /* yacc.c:1646  */
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_DELETE);
      (yyval.sql_node)->deletion.relation_name = (yyvsp[-1].string);
      if ((yyvsp[0].condition_list) != nullptr) {
        (yyval.sql_node)->deletion.conditions.swap(*(yyvsp[0].condition_list));
        delete (yyvsp[0].condition_list);
      }
      free((yyvsp[-1].string));
    }
#line 2165 "yacc_sql.cpp" /* yacc.c:1646  */
    break;

  case 65:
#line 606 "yacc_sql.y" /* yacc.c:1646  */
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
#line 2185 "yacc_sql.cpp" /* yacc.c:1646  */
    break;

  case 66:
#line 624 "yacc_sql.y" /* yacc.c:1646  */
    {
      (yyval.update_value) = new UpdateValueNode;
      (yyval.update_value)->attribute_name = (yyvsp[-2].string);
      (yyval.update_value)->value = *(yyvsp[0].value);
      free((yyvsp[-2].string));
      delete((yyvsp[0].value));
    }
#line 2197 "yacc_sql.cpp" /* yacc.c:1646  */
    break;

  case 67:
#line 634 "yacc_sql.y" /* yacc.c:1646  */
    {
      (yyval.update_value_list) = nullptr;
    }
#line 2205 "yacc_sql.cpp" /* yacc.c:1646  */
    break;

  case 68:
#line 637 "yacc_sql.y" /* yacc.c:1646  */
    {
      if ((yyvsp[0].update_value_list) != nullptr) {
        (yyval.update_value_list) = (yyvsp[0].update_value_list);
      } else {
        (yyval.update_value_list) = new std::vector<UpdateValueNode>;
      }
      (yyval.update_value_list)->emplace_back(*(yyvsp[-1].update_value));
      delete (yyvsp[-1].update_value);
    }
#line 2219 "yacc_sql.cpp" /* yacc.c:1646  */
    break;

  case 69:
#line 648 "yacc_sql.y" /* yacc.c:1646  */
    {  // function 可能出现
      (yyval.sql_node) = new ParsedSqlNode(SCF_SELECT);
      if ((yyvsp[0].expr_list) != nullptr) {
        (yyval.sql_node)->selection.project_exprs.swap(*(yyvsp[0].expr_list));
        delete (yyvsp[0].expr_list);
      }
    }
#line 2231 "yacc_sql.cpp" /* yacc.c:1646  */
    break;

  case 70:
#line 656 "yacc_sql.y" /* yacc.c:1646  */
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_SELECT);
      if ((yyvsp[-4].expr_list) != nullptr) {
        (yyval.sql_node)->selection.project_exprs.swap(*(yyvsp[-4].expr_list));
        delete (yyvsp[-4].expr_list);
      }
      if ((yyvsp[-2].relation_list) != nullptr) {
        (yyval.sql_node)->selection.relation_names.swap((yyvsp[-2].relation_list)->relation_names);
        (yyval.sql_node)->selection.alias_names.swap((yyvsp[-2].relation_list)->alias_names);
        (yyval.sql_node)->selection.inner_join_conditions.swap((yyvsp[-2].relation_list)->conditions);
        delete (yyvsp[-2].relation_list);
      }
      std::reverse((yyval.sql_node)->selection.relation_names.begin(), (yyval.sql_node)->selection.relation_names.end());
      std::reverse((yyval.sql_node)->selection.alias_names.begin(), (yyval.sql_node)->selection.alias_names.end());
      if ((yyvsp[-1].condition_list) != nullptr) {
        (yyval.sql_node)->selection.conditions.swap(*(yyvsp[-1].condition_list));
        delete (yyvsp[-1].condition_list);
      }
      if ((yyvsp[0].order_attr_list) != nullptr) {
        (yyval.sql_node)->selection.order_by_cols.swap(*(yyvsp[0].order_attr_list));
        delete (yyvsp[0].order_attr_list);
      }
    }
#line 2259 "yacc_sql.cpp" /* yacc.c:1646  */
    break;

  case 71:
#line 682 "yacc_sql.y" /* yacc.c:1646  */
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_CALC);
      std::reverse((yyvsp[0].expression_list)->begin(), (yyvsp[0].expression_list)->end());
      (yyval.sql_node)->calc.expressions.swap(*(yyvsp[0].expression_list));
      delete (yyvsp[0].expression_list);
    }
#line 2270 "yacc_sql.cpp" /* yacc.c:1646  */
    break;

  case 72:
#line 692 "yacc_sql.y" /* yacc.c:1646  */
    {
      (yyval.expression_list) = new std::vector<Expression*>;
      (yyval.expression_list)->emplace_back((yyvsp[0].expression));
    }
#line 2279 "yacc_sql.cpp" /* yacc.c:1646  */
    break;

  case 73:
#line 697 "yacc_sql.y" /* yacc.c:1646  */
    {
      if ((yyvsp[0].expression_list) != nullptr) {
        (yyval.expression_list) = (yyvsp[0].expression_list);
      } else {
        (yyval.expression_list) = new std::vector<Expression *>;
      }
      (yyval.expression_list)->emplace_back((yyvsp[-2].expression));
    }
#line 2292 "yacc_sql.cpp" /* yacc.c:1646  */
    break;

  case 74:
#line 707 "yacc_sql.y" /* yacc.c:1646  */
    {
      (yyval.expression) = create_arithmetic_expression(ArithmeticExpr::Type::ADD, (yyvsp[-2].expression), (yyvsp[0].expression), sql_string, &(yyloc));
    }
#line 2300 "yacc_sql.cpp" /* yacc.c:1646  */
    break;

  case 75:
#line 710 "yacc_sql.y" /* yacc.c:1646  */
    {
      (yyval.expression) = create_arithmetic_expression(ArithmeticExpr::Type::SUB, (yyvsp[-2].expression), (yyvsp[0].expression), sql_string, &(yyloc));
    }
#line 2308 "yacc_sql.cpp" /* yacc.c:1646  */
    break;

  case 76:
#line 713 "yacc_sql.y" /* yacc.c:1646  */
    {
      (yyval.expression) = create_arithmetic_expression(ArithmeticExpr::Type::MUL, (yyvsp[-2].expression), (yyvsp[0].expression), sql_string, &(yyloc));
    }
#line 2316 "yacc_sql.cpp" /* yacc.c:1646  */
    break;

  case 77:
#line 716 "yacc_sql.y" /* yacc.c:1646  */
    {
      (yyval.expression) = create_arithmetic_expression(ArithmeticExpr::Type::DIV, (yyvsp[-2].expression), (yyvsp[0].expression), sql_string, &(yyloc));
    }
#line 2324 "yacc_sql.cpp" /* yacc.c:1646  */
    break;

  case 78:
#line 719 "yacc_sql.y" /* yacc.c:1646  */
    {
      (yyval.expression) = (yyvsp[-1].expression);
      (yyval.expression)->set_name(token_name(sql_string, &(yyloc)));
    }
#line 2333 "yacc_sql.cpp" /* yacc.c:1646  */
    break;

  case 79:
#line 723 "yacc_sql.y" /* yacc.c:1646  */
    {
      (yyval.expression) = create_arithmetic_expression(ArithmeticExpr::Type::NEGATIVE, (yyvsp[0].expression), nullptr, sql_string, &(yyloc));
    }
#line 2341 "yacc_sql.cpp" /* yacc.c:1646  */
    break;

  case 80:
#line 726 "yacc_sql.y" /* yacc.c:1646  */
    {
      (yyval.expression) = new ValueExpr(*(yyvsp[0].value));
      (yyval.expression)->set_name(token_name(sql_string, &(yyloc)));
      delete (yyvsp[0].value);
    }
#line 2351 "yacc_sql.cpp" /* yacc.c:1646  */
    break;

  case 81:
#line 737 "yacc_sql.y" /* yacc.c:1646  */
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
#line 2368 "yacc_sql.cpp" /* yacc.c:1646  */
    break;

  case 82:
#line 749 "yacc_sql.y" /* yacc.c:1646  */
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
#line 2385 "yacc_sql.cpp" /* yacc.c:1646  */
    break;

  case 83:
#line 761 "yacc_sql.y" /* yacc.c:1646  */
    {
      (yyval.expr) = (yyvsp[0].expr);
    }
#line 2393 "yacc_sql.cpp" /* yacc.c:1646  */
    break;

  case 84:
#line 764 "yacc_sql.y" /* yacc.c:1646  */
    {
      (yyval.expr) = (yyvsp[0].expr);
    }
#line 2401 "yacc_sql.cpp" /* yacc.c:1646  */
    break;

  case 85:
#line 767 "yacc_sql.y" /* yacc.c:1646  */
    {
      (yyvsp[-1].expr)->with_brace = true;
      (yyval.expr) = (yyvsp[-1].expr);
    }
#line 2410 "yacc_sql.cpp" /* yacc.c:1646  */
    break;

  case 86:
#line 775 "yacc_sql.y" /* yacc.c:1646  */
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
#line 2427 "yacc_sql.cpp" /* yacc.c:1646  */
    break;

  case 87:
#line 787 "yacc_sql.y" /* yacc.c:1646  */
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
#line 2444 "yacc_sql.cpp" /* yacc.c:1646  */
    break;

  case 88:
#line 799 "yacc_sql.y" /* yacc.c:1646  */
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
#line 2461 "yacc_sql.cpp" /* yacc.c:1646  */
    break;

  case 89:
#line 811 "yacc_sql.y" /* yacc.c:1646  */
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
#line 2478 "yacc_sql.cpp" /* yacc.c:1646  */
    break;

  case 90:
#line 823 "yacc_sql.y" /* yacc.c:1646  */
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
#line 2504 "yacc_sql.cpp" /* yacc.c:1646  */
    break;

  case 91:
#line 844 "yacc_sql.y" /* yacc.c:1646  */
    { (yyval.expr) = (yyvsp[0].expr); }
#line 2510 "yacc_sql.cpp" /* yacc.c:1646  */
    break;

  case 92:
#line 850 "yacc_sql.y" /* yacc.c:1646  */
    {
      (yyval.expr_list) = nullptr;
    }
#line 2518 "yacc_sql.cpp" /* yacc.c:1646  */
    break;

  case 93:
#line 853 "yacc_sql.y" /* yacc.c:1646  */
    {
      if ((yyvsp[0].expr_list) != nullptr) {
        (yyval.expr_list) = (yyvsp[0].expr_list);
      } else {
        (yyval.expr_list) = new std::vector<ExprSqlNode *>;
      }

      (yyval.expr_list)->emplace_back((yyvsp[-1].expr));
      // delete $2;     在stmt阶段删除
    }
#line 2533 "yacc_sql.cpp" /* yacc.c:1646  */
    break;

  case 94:
#line 863 "yacc_sql.y" /* yacc.c:1646  */
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
#line 2548 "yacc_sql.cpp" /* yacc.c:1646  */
    break;

  case 95:
#line 873 "yacc_sql.y" /* yacc.c:1646  */
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
#line 2563 "yacc_sql.cpp" /* yacc.c:1646  */
    break;

  case 96:
#line 886 "yacc_sql.y" /* yacc.c:1646  */
    {
      FuncExprSqlNode* func = new FuncExprSqlNode;
      func->type = FuncType::FUNC_LENGTH;
      func->exprs.emplace_back((yyvsp[-1].expr));

      ExprSqlNode* expr = new ExprSqlNode;
      expr->type = ExprSqlNodeType::FUNCTION;
      expr->func_expr = func;
      (yyval.expr) = expr;
    }
#line 2578 "yacc_sql.cpp" /* yacc.c:1646  */
    break;

  case 97:
#line 896 "yacc_sql.y" /* yacc.c:1646  */
    {
      FuncExprSqlNode* func = new FuncExprSqlNode;
      func->type = FuncType::FUNC_ROUND;
      func->exprs.emplace_back((yyvsp[-1].expr));

      ExprSqlNode* expr = new ExprSqlNode;
      expr->type = ExprSqlNodeType::FUNCTION;
      expr->func_expr = func;
      (yyval.expr) = expr;
    }
#line 2593 "yacc_sql.cpp" /* yacc.c:1646  */
    break;

  case 98:
#line 906 "yacc_sql.y" /* yacc.c:1646  */
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
#line 2609 "yacc_sql.cpp" /* yacc.c:1646  */
    break;

  case 99:
#line 917 "yacc_sql.y" /* yacc.c:1646  */
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
#line 2625 "yacc_sql.cpp" /* yacc.c:1646  */
    break;

  case 100:
#line 931 "yacc_sql.y" /* yacc.c:1646  */
    {
      AggrExprSqlNode* aggr = new AggrExprSqlNode;
      aggr->type = (yyvsp[-3].aggr_func_type);
      aggr->expr = (yyvsp[-1].expr);

      ExprSqlNode* expr = new ExprSqlNode;
      expr->type = ExprSqlNodeType::AGGREGATION;
      expr->aggr_expr = aggr;
      (yyval.expr) = expr;
    }
#line 2640 "yacc_sql.cpp" /* yacc.c:1646  */
    break;

  case 101:
#line 941 "yacc_sql.y" /* yacc.c:1646  */
    {
      if ((yyvsp[-3].aggr_func_type) != AggrFuncType::AGGR_COUNT) {
        yyerror (&yylloc, sql_string, sql_result, scanner, YY_("aggr func is illegal"));
      }
      AggrExprSqlNode* aggr = new AggrExprSqlNode;
      aggr->type = (yyvsp[-3].aggr_func_type);
      aggr->is_star = true;
      std::string star = "*";
      Value star_val(star.c_str());    // val = *
      UnaryExprSqlNode* star_unary = new UnaryExprSqlNode;
      star_unary->value = star_val;

      ExprSqlNode* expr = new ExprSqlNode;
      expr->type = ExprSqlNodeType::AGGREGATION;
      expr->aggr_expr = aggr;
      (yyval.expr) = expr;
    }
#line 2662 "yacc_sql.cpp" /* yacc.c:1646  */
    break;

  case 102:
#line 961 "yacc_sql.y" /* yacc.c:1646  */
    {
      (yyval.aggr_func_type) = AggrFuncType::AGGR_MAX;
    }
#line 2670 "yacc_sql.cpp" /* yacc.c:1646  */
    break;

  case 103:
#line 964 "yacc_sql.y" /* yacc.c:1646  */
    {
      (yyval.aggr_func_type) = AggrFuncType::AGGR_MIN;
    }
#line 2678 "yacc_sql.cpp" /* yacc.c:1646  */
    break;

  case 104:
#line 967 "yacc_sql.y" /* yacc.c:1646  */
    {
      (yyval.aggr_func_type) = AggrFuncType::AGGR_SUM;
    }
#line 2686 "yacc_sql.cpp" /* yacc.c:1646  */
    break;

  case 105:
#line 970 "yacc_sql.y" /* yacc.c:1646  */
    {
      (yyval.aggr_func_type) = AggrFuncType::AGGR_AVG;
    }
#line 2694 "yacc_sql.cpp" /* yacc.c:1646  */
    break;

  case 106:
#line 973 "yacc_sql.y" /* yacc.c:1646  */
    {
      (yyval.aggr_func_type) = AggrFuncType::AGGR_COUNT;
    }
#line 2702 "yacc_sql.cpp" /* yacc.c:1646  */
    break;

  case 107:
#line 1060 "yacc_sql.y" /* yacc.c:1646  */
    {
      (yyval.rel_index_attr_list) = nullptr;
    }
#line 2710 "yacc_sql.cpp" /* yacc.c:1646  */
    break;

  case 108:
#line 1063 "yacc_sql.y" /* yacc.c:1646  */
    {
      if ((yyvsp[0].rel_index_attr_list) != nullptr) {
        (yyval.rel_index_attr_list) = (yyvsp[0].rel_index_attr_list);
      } else {
        (yyval.rel_index_attr_list) = new std::vector<string>;
      }

      (yyval.rel_index_attr_list)->emplace_back((yyvsp[-1].string));
      free((yyvsp[-1].string));
    }
#line 2725 "yacc_sql.cpp" /* yacc.c:1646  */
    break;

  case 109:
#line 1075 "yacc_sql.y" /* yacc.c:1646  */
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
#line 2746 "yacc_sql.cpp" /* yacc.c:1646  */
    break;

  case 110:
#line 1092 "yacc_sql.y" /* yacc.c:1646  */
    {
      if ((yyvsp[0].expr_list) != nullptr) {
        (yyval.expr_list) = (yyvsp[0].expr_list);
      } else {
        (yyval.expr_list) = new std::vector<ExprSqlNode*>;
      }
      (yyval.expr_list)->emplace_back((yyvsp[-1].expr));
    }
#line 2759 "yacc_sql.cpp" /* yacc.c:1646  */
    break;

  case 111:
#line 1100 "yacc_sql.y" /* yacc.c:1646  */
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
#line 2774 "yacc_sql.cpp" /* yacc.c:1646  */
    break;

  case 112:
#line 1110 "yacc_sql.y" /* yacc.c:1646  */
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
#line 2789 "yacc_sql.cpp" /* yacc.c:1646  */
    break;

  case 113:
#line 1123 "yacc_sql.y" /* yacc.c:1646  */
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
#line 2804 "yacc_sql.cpp" /* yacc.c:1646  */
    break;

  case 114:
#line 1133 "yacc_sql.y" /* yacc.c:1646  */
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
#line 2820 "yacc_sql.cpp" /* yacc.c:1646  */
    break;

  case 115:
#line 1144 "yacc_sql.y" /* yacc.c:1646  */
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
#line 2836 "yacc_sql.cpp" /* yacc.c:1646  */
    break;

  case 116:
#line 1158 "yacc_sql.y" /* yacc.c:1646  */
    {
      (yyval.rel_attr) = new RelAttrSqlNode;
      (yyval.rel_attr)->attribute_name = (yyvsp[0].string);
      free((yyvsp[0].string));
    }
#line 2846 "yacc_sql.cpp" /* yacc.c:1646  */
    break;

  case 117:
#line 1163 "yacc_sql.y" /* yacc.c:1646  */
    {
      (yyval.rel_attr) = new RelAttrSqlNode;
      (yyval.rel_attr)->relation_name  = (yyvsp[-2].string);
      (yyval.rel_attr)->attribute_name = (yyvsp[0].string);
      free((yyvsp[-2].string));
      free((yyvsp[0].string));
    }
#line 2858 "yacc_sql.cpp" /* yacc.c:1646  */
    break;

  case 118:
#line 1191 "yacc_sql.y" /* yacc.c:1646  */
    {
      (yyval.relation_list) = nullptr;
    }
#line 2866 "yacc_sql.cpp" /* yacc.c:1646  */
    break;

  case 119:
#line 1194 "yacc_sql.y" /* yacc.c:1646  */
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
#line 2881 "yacc_sql.cpp" /* yacc.c:1646  */
    break;

  case 120:
#line 1204 "yacc_sql.y" /* yacc.c:1646  */
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
#line 2897 "yacc_sql.cpp" /* yacc.c:1646  */
    break;

  case 121:
#line 1215 "yacc_sql.y" /* yacc.c:1646  */
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
#line 2913 "yacc_sql.cpp" /* yacc.c:1646  */
    break;

  case 122:
#line 1226 "yacc_sql.y" /* yacc.c:1646  */
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
#line 2934 "yacc_sql.cpp" /* yacc.c:1646  */
    break;

  case 123:
#line 1244 "yacc_sql.y" /* yacc.c:1646  */
    {
       (yyval.condition_list) = nullptr;
    }
#line 2942 "yacc_sql.cpp" /* yacc.c:1646  */
    break;

  case 124:
#line 1247 "yacc_sql.y" /* yacc.c:1646  */
    {
       (yyval.condition_list) = (yyvsp[0].condition_list);
	}
#line 2950 "yacc_sql.cpp" /* yacc.c:1646  */
    break;

  case 125:
#line 1253 "yacc_sql.y" /* yacc.c:1646  */
    {
      (yyval.condition_list) = nullptr;
    }
#line 2958 "yacc_sql.cpp" /* yacc.c:1646  */
    break;

  case 126:
#line 1256 "yacc_sql.y" /* yacc.c:1646  */
    {
      (yyval.condition_list) = (yyvsp[0].condition_list);  
    }
#line 2966 "yacc_sql.cpp" /* yacc.c:1646  */
    break;

  case 127:
#line 1262 "yacc_sql.y" /* yacc.c:1646  */
    {
		(yyval.order_attr) = new OrderBySqlNode;
		(yyval.order_attr)->attribute = *(yyvsp[0].rel_attr);
		(yyval.order_attr)->is_asc = true;

		delete (yyvsp[0].rel_attr);
	}
#line 2978 "yacc_sql.cpp" /* yacc.c:1646  */
    break;

  case 128:
#line 1271 "yacc_sql.y" /* yacc.c:1646  */
    {
		(yyval.order_attr) = new OrderBySqlNode;
        (yyval.order_attr)->attribute = *(yyvsp[-1].rel_attr);
      	(yyval.order_attr)->is_asc = true;

      	delete (yyvsp[-1].rel_attr);
	}
#line 2990 "yacc_sql.cpp" /* yacc.c:1646  */
    break;

  case 129:
#line 1280 "yacc_sql.y" /* yacc.c:1646  */
    {
		(yyval.order_attr) = new OrderBySqlNode;
        (yyval.order_attr)->attribute = *(yyvsp[-1].rel_attr);
      	(yyval.order_attr)->is_asc = false;

      	delete (yyvsp[-1].rel_attr);
	}
#line 3002 "yacc_sql.cpp" /* yacc.c:1646  */
    break;

  case 130:
#line 1290 "yacc_sql.y" /* yacc.c:1646  */
    {
        (yyval.order_attr_list) = nullptr;
	}
#line 3010 "yacc_sql.cpp" /* yacc.c:1646  */
    break;

  case 131:
#line 1294 "yacc_sql.y" /* yacc.c:1646  */
    {
        (yyval.order_attr_list) = new std::vector<OrderBySqlNode>;
        (yyval.order_attr_list)->emplace_back(*(yyvsp[0].order_attr));
        delete (yyvsp[0].order_attr);
    }
#line 3020 "yacc_sql.cpp" /* yacc.c:1646  */
    break;

  case 132:
#line 1300 "yacc_sql.y" /* yacc.c:1646  */
    {
        (yyval.order_attr_list) = (yyvsp[0].order_attr_list);
        (yyval.order_attr_list)->emplace_back(*(yyvsp[-2].order_attr));
        delete (yyvsp[-2].order_attr);
	}
#line 3030 "yacc_sql.cpp" /* yacc.c:1646  */
    break;

  case 133:
#line 1308 "yacc_sql.y" /* yacc.c:1646  */
    {
      (yyval.order_attr_list) = nullptr;
    }
#line 3038 "yacc_sql.cpp" /* yacc.c:1646  */
    break;

  case 134:
#line 1311 "yacc_sql.y" /* yacc.c:1646  */
    {
      (yyval.order_attr_list) = (yyvsp[0].order_attr_list);
      std::reverse((yyval.order_attr_list)->begin(), (yyval.order_attr_list)->end());
    }
#line 3047 "yacc_sql.cpp" /* yacc.c:1646  */
    break;

  case 135:
#line 1319 "yacc_sql.y" /* yacc.c:1646  */
    {
      (yyval.condition_list) = nullptr;
    }
#line 3055 "yacc_sql.cpp" /* yacc.c:1646  */
    break;

  case 136:
#line 1322 "yacc_sql.y" /* yacc.c:1646  */
    {
      (yyval.condition_list) = new std::vector<ConditionSqlNode>;
      (yyval.condition_list)->emplace_back(*(yyvsp[0].condition));
      delete (yyvsp[0].condition);
    }
#line 3065 "yacc_sql.cpp" /* yacc.c:1646  */
    break;

  case 137:
#line 1327 "yacc_sql.y" /* yacc.c:1646  */
    {
      (yyval.condition_list) = (yyvsp[0].condition_list);
      (yyval.condition_list)->emplace_back(*(yyvsp[-2].condition));
      delete (yyvsp[-2].condition);
    }
#line 3075 "yacc_sql.cpp" /* yacc.c:1646  */
    break;

  case 138:
#line 1335 "yacc_sql.y" /* yacc.c:1646  */
    {
      (yyval.condition) = new ConditionSqlNode;
      (yyval.condition)->left = (yyvsp[-2].expr);
      (yyval.condition)->comp = (yyvsp[-1].comp);
      (yyval.condition)->right = (yyvsp[0].expr);
    }
#line 3086 "yacc_sql.cpp" /* yacc.c:1646  */
    break;

  case 139:
#line 1342 "yacc_sql.y" /* yacc.c:1646  */
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
#line 3107 "yacc_sql.cpp" /* yacc.c:1646  */
    break;

  case 140:
#line 1359 "yacc_sql.y" /* yacc.c:1646  */
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
#line 3128 "yacc_sql.cpp" /* yacc.c:1646  */
    break;

  case 141:
#line 1427 "yacc_sql.y" /* yacc.c:1646  */
    { (yyval.comp) = EQUAL_TO; }
#line 3134 "yacc_sql.cpp" /* yacc.c:1646  */
    break;

  case 142:
#line 1428 "yacc_sql.y" /* yacc.c:1646  */
    { (yyval.comp) = LESS_THAN; }
#line 3140 "yacc_sql.cpp" /* yacc.c:1646  */
    break;

  case 143:
#line 1429 "yacc_sql.y" /* yacc.c:1646  */
    { (yyval.comp) = GREAT_THAN; }
#line 3146 "yacc_sql.cpp" /* yacc.c:1646  */
    break;

  case 144:
#line 1430 "yacc_sql.y" /* yacc.c:1646  */
    { (yyval.comp) = LESS_EQUAL; }
#line 3152 "yacc_sql.cpp" /* yacc.c:1646  */
    break;

  case 145:
#line 1431 "yacc_sql.y" /* yacc.c:1646  */
    { (yyval.comp) = GREAT_EQUAL; }
#line 3158 "yacc_sql.cpp" /* yacc.c:1646  */
    break;

  case 146:
#line 1432 "yacc_sql.y" /* yacc.c:1646  */
    { (yyval.comp) = NOT_EQUAL; }
#line 3164 "yacc_sql.cpp" /* yacc.c:1646  */
    break;

  case 147:
#line 1433 "yacc_sql.y" /* yacc.c:1646  */
    { (yyval.comp) = LIKE_OP; }
#line 3170 "yacc_sql.cpp" /* yacc.c:1646  */
    break;

  case 148:
#line 1434 "yacc_sql.y" /* yacc.c:1646  */
    { (yyval.comp) = NOT_LIKE_OP; }
#line 3176 "yacc_sql.cpp" /* yacc.c:1646  */
    break;

  case 149:
#line 1439 "yacc_sql.y" /* yacc.c:1646  */
    {
      char *tmp_file_name = common::substr((yyvsp[-3].string), 1, strlen((yyvsp[-3].string)) - 2);
      
      (yyval.sql_node) = new ParsedSqlNode(SCF_LOAD_DATA);
      (yyval.sql_node)->load_data.relation_name = (yyvsp[0].string);
      (yyval.sql_node)->load_data.file_name = tmp_file_name;
      free((yyvsp[0].string));
      free(tmp_file_name);
    }
#line 3190 "yacc_sql.cpp" /* yacc.c:1646  */
    break;

  case 150:
#line 1452 "yacc_sql.y" /* yacc.c:1646  */
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_EXPLAIN);
      (yyval.sql_node)->explain.sql_node = std::unique_ptr<ParsedSqlNode>((yyvsp[0].sql_node));
    }
#line 3199 "yacc_sql.cpp" /* yacc.c:1646  */
    break;

  case 151:
#line 1460 "yacc_sql.y" /* yacc.c:1646  */
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_SET_VARIABLE);
      (yyval.sql_node)->set_variable.name  = (yyvsp[-2].string);
      (yyval.sql_node)->set_variable.value = *(yyvsp[0].value);
      free((yyvsp[-2].string));
      delete (yyvsp[0].value);
    }
#line 3211 "yacc_sql.cpp" /* yacc.c:1646  */
    break;


#line 3215 "yacc_sql.cpp" /* yacc.c:1646  */
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
#line 1472 "yacc_sql.y" /* yacc.c:1906  */

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
