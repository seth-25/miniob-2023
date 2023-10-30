/* A Bison parser, made by GNU Bison 3.5.1.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2020 Free Software Foundation,
   Inc.

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

/* Undocumented macros, especially those whose name start with YY_,
   are private implementation details.  Do not rely on them.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "3.5.1"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 2

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 2 "yacc_sql.y"


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


#line 116 "yacc_sql.cpp"

# ifndef YY_CAST
#  ifdef __cplusplus
#   define YY_CAST(Type, Val) static_cast<Type> (Val)
#   define YY_REINTERPRET_CAST(Type, Val) reinterpret_cast<Type> (Val)
#  else
#   define YY_CAST(Type, Val) ((Type) (Val))
#   define YY_REINTERPRET_CAST(Type, Val) ((Type) (Val))
#  endif
# endif
# ifndef YY_NULLPTR
#  if defined __cplusplus
#   if 201103L <= __cplusplus
#    define YY_NULLPTR nullptr
#   else
#    define YY_NULLPTR 0
#   endif
#  else
#   define YY_NULLPTR ((void*)0)
#  endif
# endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 1
#endif

/* Use api.header.include to #include this header
   instead of duplicating it here.  */
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
    OR = 294,
    SET = 295,
    ON = 296,
    LOAD = 297,
    DATA = 298,
    INFILE = 299,
    EXPLAIN = 300,
    NOT = 301,
    LIKE = 302,
    UNIQUE = 303,
    ORDER = 304,
    GROUP = 305,
    BY = 306,
    HAVING = 307,
    EXISTS = 308,
    IN = 309,
    NULL_T = 310,
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
#line 130 "yacc_sql.y"

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


#line 277 "yacc_sql.cpp"

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



#ifdef short
# undef short
#endif

/* On compilers that do not define __PTRDIFF_MAX__ etc., make sure
   <limits.h> and (if available) <stdint.h> are included
   so that the code can choose integer types of a good width.  */

#ifndef __PTRDIFF_MAX__
# include <limits.h> /* INFRINGES ON USER NAME SPACE */
# if defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stdint.h> /* INFRINGES ON USER NAME SPACE */
#  define YY_STDINT_H
# endif
#endif

/* Narrow types that promote to a signed type and that can represent a
   signed or unsigned integer of at least N bits.  In tables they can
   save space and decrease cache pressure.  Promoting to a signed type
   helps avoid bugs in integer arithmetic.  */

#ifdef __INT_LEAST8_MAX__
typedef __INT_LEAST8_TYPE__ yytype_int8;
#elif defined YY_STDINT_H
typedef int_least8_t yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef __INT_LEAST16_MAX__
typedef __INT_LEAST16_TYPE__ yytype_int16;
#elif defined YY_STDINT_H
typedef int_least16_t yytype_int16;
#else
typedef short yytype_int16;
#endif

#if defined __UINT_LEAST8_MAX__ && __UINT_LEAST8_MAX__ <= __INT_MAX__
typedef __UINT_LEAST8_TYPE__ yytype_uint8;
#elif (!defined __UINT_LEAST8_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST8_MAX <= INT_MAX)
typedef uint_least8_t yytype_uint8;
#elif !defined __UINT_LEAST8_MAX__ && UCHAR_MAX <= INT_MAX
typedef unsigned char yytype_uint8;
#else
typedef short yytype_uint8;
#endif

#if defined __UINT_LEAST16_MAX__ && __UINT_LEAST16_MAX__ <= __INT_MAX__
typedef __UINT_LEAST16_TYPE__ yytype_uint16;
#elif (!defined __UINT_LEAST16_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST16_MAX <= INT_MAX)
typedef uint_least16_t yytype_uint16;
#elif !defined __UINT_LEAST16_MAX__ && USHRT_MAX <= INT_MAX
typedef unsigned short yytype_uint16;
#else
typedef int yytype_uint16;
#endif

#ifndef YYPTRDIFF_T
# if defined __PTRDIFF_TYPE__ && defined __PTRDIFF_MAX__
#  define YYPTRDIFF_T __PTRDIFF_TYPE__
#  define YYPTRDIFF_MAXIMUM __PTRDIFF_MAX__
# elif defined PTRDIFF_MAX
#  ifndef ptrdiff_t
#   include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  endif
#  define YYPTRDIFF_T ptrdiff_t
#  define YYPTRDIFF_MAXIMUM PTRDIFF_MAX
# else
#  define YYPTRDIFF_T long
#  define YYPTRDIFF_MAXIMUM LONG_MAX
# endif
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned
# endif
#endif

#define YYSIZE_MAXIMUM                                  \
  YY_CAST (YYPTRDIFF_T,                                 \
           (YYPTRDIFF_MAXIMUM < YY_CAST (YYSIZE_T, -1)  \
            ? YYPTRDIFF_MAXIMUM                         \
            : YY_CAST (YYSIZE_T, -1)))

#define YYSIZEOF(X) YY_CAST (YYPTRDIFF_T, sizeof (X))

/* Stored state numbers (used for stacks). */
typedef yytype_int16 yy_state_t;

/* State numbers in computations.  */
typedef int yy_state_fast_t;

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

#ifndef YY_ATTRIBUTE_PURE
# if defined __GNUC__ && 2 < __GNUC__ + (96 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_PURE __attribute__ ((__pure__))
# else
#  define YY_ATTRIBUTE_PURE
# endif
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# if defined __GNUC__ && 2 < __GNUC__ + (7 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_UNUSED __attribute__ ((__unused__))
# else
#  define YY_ATTRIBUTE_UNUSED
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && ! defined __ICC && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                            \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# define YY_IGNORE_MAYBE_UNINITIALIZED_END      \
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

#if defined __cplusplus && defined __GNUC__ && ! defined __ICC && 6 <= __GNUC__
# define YY_IGNORE_USELESS_CAST_BEGIN                          \
    _Pragma ("GCC diagnostic push")                            \
    _Pragma ("GCC diagnostic ignored \"-Wuseless-cast\"")
# define YY_IGNORE_USELESS_CAST_END            \
    _Pragma ("GCC diagnostic pop")
#endif
#ifndef YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_END
#endif


#define YY_ASSERT(E) ((void) (0 && (E)))

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
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
  YYLTYPE yyls_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE) \
             + YYSIZEOF (YYLTYPE)) \
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
        YYPTRDIFF_T yynewbytes;                                         \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * YYSIZEOF (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / YYSIZEOF (*yyptr);                        \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, YY_CAST (YYSIZE_T, (Count)) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYPTRDIFF_T yyi;                      \
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
#define YYLAST   440

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  82
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  65
/* YYNRULES -- Number of rules.  */
#define YYNRULES  179
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  338

#define YYUNDEFTOK  2
#define YYMAXUTOK   332


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_int8 yytranslate[] =
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
static const yytype_int16 yyrline[] =
{
       0,   244,   244,   252,   253,   254,   255,   256,   257,   258,
     259,   260,   261,   262,   263,   264,   265,   266,   267,   268,
     269,   270,   271,   272,   273,   277,   283,   288,   294,   300,
     306,   312,   319,   324,   331,   339,   358,   380,   390,   408,
     418,   428,   448,   471,   474,   487,   496,   504,   513,   522,
     531,   540,   551,   554,   555,   556,   557,   560,   576,   579,
     593,   607,   610,   621,   625,   629,   633,   637,   651,   656,
     662,   674,   693,   703,   706,   717,   724,   759,   769,   774,
     785,   788,   791,   794,   797,   801,   804,   815,   827,   839,
     842,   845,   853,   865,   877,   889,   901,   922,   923,   924,
     930,   933,   942,   952,   965,   975,   985,   996,  1010,  1020,
    1048,  1051,  1054,  1057,  1060,  1067,  1086,  1130,  1133,  1145,
    1162,  1170,  1180,  1193,  1203,  1214,  1228,  1233,  1261,  1264,
    1274,  1285,  1296,  1314,  1317,  1323,  1326,  1333,  1336,  1342,
    1348,  1357,  1360,  1367,  1376,  1385,  1396,  1399,  1405,  1414,
    1417,  1425,  1428,  1434,  1438,  1452,  1459,  1478,  1481,  1486,
    1494,  1501,  1518,  1535,  1542,  1549,  1567,  1588,  1589,  1590,
    1591,  1592,  1593,  1594,  1595,  1599,  1612,  1620,  1630,  1631
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
  "FROM", "WHERE", "AND", "OR", "SET", "ON", "LOAD", "DATA", "INFILE",
  "EXPLAIN", "NOT", "LIKE", "UNIQUE", "ORDER", "GROUP", "BY", "HAVING",
  "EXISTS", "IN", "NULL_T", "AGGR_MAX", "AGGR_MIN", "AGGR_COUNT",
  "AGGR_AVG", "AGGR_SUM", "LENGTH", "ROUND", "DATE_FORMAT", "AS", "IS",
  "EQ", "LT", "GT", "LE", "GE", "NE", "NUMBER", "FLOAT", "ID", "SSS",
  "DATE_STR", "'+'", "'-'", "'*'", "'/'", "UMINUS", "$accept", "commands",
  "command_wrapper", "exit_stmt", "help_stmt", "sync_stmt", "begin_stmt",
  "commit_stmt", "rollback_stmt", "drop_table_stmt", "show_tables_stmt",
  "show_index_stmt", "desc_table_stmt", "create_index_stmt",
  "drop_index_stmt", "create_table_stmt", "create_table_select_stmt",
  "attr_def_list", "attr_def", "number", "type", "insert_stmt",
  "row_value_list", "row_value", "value_list", "value", "delete_stmt",
  "update_stmt", "update_value", "update_value_list", "select_stmt",
  "calc_stmt", "expression_list", "expression", "unary_expr", "expr",
  "expr_list", "func_expr", "aggr_func_expr", "aggr_func_type",
  "in_value_list", "sub_select", "index_attr_list", "select_attr",
  "select_from", "rel_attr", "rel_list", "inner_condition_list", "where",
  "having", "group_list", "group_by", "sort_unit", "sort_list", "order_by",
  "select_where", "condition_or", "condition_and", "condition_list",
  "condition", "comp_op", "load_data_stmt", "explain_stmt",
  "set_variable_stmt", "opt_semicolon", YY_NULLPTR
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_int16 yytoknum[] =
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

#define YYPACT_NINF (-272)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-62)

#define yytable_value_is_error(Yyn) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     373,     2,    14,    88,   149,   -55,    38,  -272,    25,    16,
     -34,  -272,  -272,  -272,  -272,  -272,    -9,    34,   373,    93,
      94,  -272,  -272,  -272,  -272,  -272,  -272,  -272,  -272,  -272,
    -272,  -272,  -272,  -272,  -272,  -272,  -272,  -272,  -272,  -272,
    -272,  -272,  -272,    35,    56,   136,    71,    72,    88,  -272,
    -272,  -272,  -272,  -272,   298,  -272,  -272,   118,    76,  -272,
    -272,  -272,  -272,  -272,   133,   145,   148,   137,   254,  -272,
    -272,  -272,   215,  -272,  -272,   194,  -272,  -272,   135,  -272,
    -272,  -272,   141,    98,   119,   159,   150,   157,  -272,  -272,
    -272,  -272,    -3,   161,   143,  -272,   174,    12,  -272,  -272,
    -272,    88,    88,    88,    88,    88,   149,    53,    21,   282,
     282,   282,   144,  -272,   282,   152,   181,   282,   282,   282,
     282,  -272,   198,    48,   155,   156,   196,   197,   164,   -41,
     158,   169,   223,  -272,   172,   206,   184,  -272,  -272,    15,
      15,  -272,  -272,   212,   -41,   238,  -272,    96,     7,   162,
    -272,   285,   181,  -272,    24,    24,  -272,  -272,  -272,  -272,
      -7,   224,  -272,   240,   225,  -272,   199,   241,     6,  -272,
     228,   129,   242,  -272,   256,   203,  -272,   155,   268,  -272,
    -272,  -272,   282,   282,   217,   181,  -272,  -272,   286,   230,
     231,     4,  -272,   225,   258,   -41,   284,   266,   282,   354,
    -272,   283,   -41,   164,   197,  -272,  -272,   314,  -272,  -272,
    -272,  -272,  -272,    -2,   169,   301,   249,   304,   224,  -272,
     103,   108,   181,  -272,   259,    -6,     4,  -272,   295,   297,
    -272,   296,   294,   268,   240,  -272,   282,   112,   -24,  -272,
     282,   -19,  -272,  -272,  -272,  -272,  -272,  -272,   282,   225,
    -272,   241,  -272,   262,   276,   306,  -272,   242,    -1,   328,
     278,   258,  -272,  -272,  -272,   310,   292,     4,  -272,  -272,
     225,   225,   293,   225,   319,   348,   284,   112,  -272,   282,
     112,   317,  -272,   112,  -272,  -272,  -272,  -272,   362,  -272,
    -272,   223,  -272,   313,   372,   328,   294,   225,     4,     4,
    -272,   297,  -272,   353,  -272,  -272,   343,  -272,  -272,  -272,
     112,  -272,     5,  -272,   328,  -272,   374,   319,  -272,  -272,
    -272,   293,   293,   344,  -272,  -272,  -272,   381,  -272,   128,
     384,  -272,  -272,  -272,  -272,  -272,   293,  -272
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     0,     0,     0,     0,     0,     0,    27,     0,     0,
       0,    28,    29,    30,    26,    25,     0,     0,     0,     0,
     178,    24,    23,    16,    17,    18,    19,    10,    11,    12,
      13,    14,    15,     8,     9,     5,     7,     6,     4,     3,
      20,    21,    22,     0,     0,     0,     0,     0,     0,    69,
      63,    65,    68,    67,     0,    86,    77,    78,     0,   110,
     111,   114,   113,   112,     0,     0,     0,   126,     0,   119,
      87,    97,   100,    89,    90,     0,    99,    98,    75,    88,
      34,    32,     0,     0,     0,     0,     0,     0,   176,     1,
     179,     2,     0,     0,     0,    31,     0,     0,    63,    65,
      85,     0,     0,     0,     0,     0,     0,    87,     0,     0,
       0,     0,     0,    96,     0,     0,   100,     0,     0,     0,
       0,   120,     0,     0,     0,     0,     0,   135,     0,     0,
       0,     0,     0,    40,     0,     0,     0,    84,    79,    80,
      81,    82,    83,     0,     0,     0,    91,     0,     0,     0,
     127,   100,   100,   122,    92,    93,    94,    95,   109,   108,
     128,   151,    33,     0,   157,    70,     0,    73,     0,   177,
       0,     0,    43,    39,     0,     0,    37,     0,    61,   115,
     104,   105,     0,     0,     0,   100,   101,   121,     0,     0,
       0,   128,   123,     0,   141,     0,    58,     0,     0,     0,
     136,   158,     0,     0,   135,    64,    66,     0,    53,    54,
      55,    56,    46,    47,     0,     0,     0,     0,   151,    62,
       0,     0,   100,   103,     0,   128,   128,   125,   152,   153,
     155,     0,   137,    61,     0,    57,     0,   165,     0,   173,
       0,     0,   167,   168,   169,   170,   171,   172,     0,   157,
      72,    73,    71,     0,     0,     0,    49,    43,    38,   117,
       0,   141,   106,   107,   102,   133,     0,   128,   129,   124,
       0,     0,     0,   157,   149,     0,    58,   166,   174,     0,
     163,     0,   161,   160,   159,    74,   175,    52,     0,    51,
      44,     0,    42,     0,     0,   117,   137,   157,   128,   128,
     131,   154,   156,   139,   142,   138,     0,    76,    60,    59,
     164,   162,    45,    41,   117,    35,     0,   149,   134,   132,
     130,     0,   146,     0,    48,   118,    36,     0,   140,   143,
     147,   150,    50,   116,   145,   144,   146,   148
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -272,  -272,   385,  -272,  -272,  -272,  -272,  -272,  -272,  -272,
    -272,  -272,  -272,  -272,  -272,  -272,  -272,   153,   193,  -272,
    -272,  -272,   138,   175,  -171,    18,  -272,  -272,   208,   165,
     -91,  -272,   311,   277,  -272,    -4,  -104,  -272,  -272,  -272,
    -272,  -272,  -271,   320,   250,  -266,  -187,  -272,   213,   132,
     109,   168,  -272,    99,   120,   218,  -272,   170,  -224,  -188,
    -272,  -272,  -272,  -272,  -272
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,    19,    20,    21,    22,    23,    24,    25,    26,    27,
      28,    29,    30,    31,    32,    33,    34,   215,   172,   288,
     213,    35,   235,   196,   145,    70,    36,    37,   167,   204,
      38,    39,    56,    57,    71,   199,   121,    73,    74,    75,
      76,    77,   294,    78,   161,    79,   192,   298,   165,   274,
     304,   232,   330,   331,   307,   194,   228,   229,   200,   201,
     248,    40,    41,    42,    91
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      72,   133,   188,   188,   227,   230,   303,   219,    43,     4,
      44,     4,   153,   188,    49,   189,   189,   131,   254,    80,
      46,    55,    47,   278,   316,   284,   189,   281,   181,   182,
     279,    50,    51,   137,    52,    53,   282,   168,   268,   269,
      85,   173,   146,   325,   255,    81,    82,   186,   187,   305,
      45,   323,    84,   256,   108,   303,   329,   190,   266,    83,
     324,   132,   275,   291,   113,    86,    55,   191,   267,   159,
     329,   123,    55,   318,   -61,   144,   107,    87,   205,   206,
     300,   223,   230,   302,   117,   118,   119,   120,   106,   102,
     103,   104,   105,    89,   104,   105,    58,    90,   117,   118,
     119,   120,    72,   119,   120,   147,   148,   149,    48,    92,
     151,   319,   320,   154,   155,   156,   157,   180,   264,    55,
      55,    55,    55,    55,   262,   117,   118,   119,   120,   263,
      93,    49,    59,    60,    61,    62,    63,    64,    65,    66,
     101,   334,   335,    49,    94,    95,    96,   169,    50,    51,
      67,    52,    53,   109,    68,   208,   209,   210,   211,   212,
      50,    51,   178,    52,    53,   110,    54,   292,   111,    58,
     112,   124,   126,   117,   118,   119,   120,   125,   220,   221,
     117,   118,   119,   120,   183,   117,   118,   119,   120,   117,
     118,   119,   120,   127,   237,   102,   103,   104,   105,   128,
     313,   130,   134,   114,    49,    59,    60,    61,    62,    63,
      64,    65,    66,   233,    58,   136,   129,   135,   150,   158,
     250,    50,    51,    67,    52,    53,   152,    68,    69,   160,
     162,   163,   277,   170,   164,     4,   280,   114,   166,   117,
     118,   119,   120,   171,   283,    58,   174,   175,   177,    49,
      59,    60,    61,    62,    63,    64,    65,    66,   176,   179,
     195,   193,   207,   203,   214,   202,    50,    51,    67,    52,
      53,   197,    68,   122,    58,   310,   216,   217,   198,   115,
      49,    59,    60,    61,    62,    63,    64,    65,    66,   116,
     144,   222,   117,   118,   119,   120,   224,    50,    51,    67,
      52,    53,    58,    68,   225,   226,   234,   114,   231,    49,
      59,    60,    61,    62,    63,    64,    65,    66,    48,   236,
     253,   249,   258,   259,   260,    97,    98,    99,    67,    52,
      53,   100,    68,   265,   270,   271,   286,    49,    59,    60,
      61,    62,    63,    64,    65,    66,   273,   272,   287,   184,
     293,   297,   295,    49,    50,    51,    67,    52,    53,   185,
      68,   289,   117,   118,   119,   120,   299,    67,   306,   308,
      98,    99,   311,    52,    53,   321,    54,     1,     2,   139,
     140,   141,   142,   312,     3,     4,     5,   314,     6,     7,
       8,     9,    10,   315,   322,   326,    11,    12,    13,   332,
     238,   239,   333,    88,    14,    15,   336,   257,   240,   276,
     290,   251,   138,    16,   309,    17,   285,   252,    18,   241,
     242,   243,   244,   245,   246,   247,   143,   218,   317,   296,
     328,   117,   118,   119,   120,   337,   261,   327,     0,     0,
     301
};

static const yytype_int16 yycheck[] =
{
       4,    92,     9,     9,   191,   193,   272,   178,     6,    12,
       8,    12,   116,     9,    55,    22,    22,    20,    20,    74,
       6,     3,     8,    47,   295,   249,    22,    46,    21,    22,
      54,    72,    73,    21,    75,    76,    55,    78,   225,   226,
      74,   132,    21,   314,    46,     7,     8,   151,   152,   273,
      48,    46,    36,    55,    58,   321,   322,    64,    64,    34,
      55,    64,   233,    64,    68,    74,    48,    74,    74,    21,
     336,    75,    54,   297,    21,    22,    58,    43,    72,    73,
     267,   185,   270,   271,    77,    78,    79,    80,    12,    77,
      78,    79,    80,     0,    79,    80,    20,     3,    77,    78,
      79,    80,   106,    79,    80,   109,   110,   111,    20,    74,
     114,   298,   299,   117,   118,   119,   120,    21,   222,   101,
     102,   103,   104,   105,    21,    77,    78,    79,    80,    21,
      74,    55,    56,    57,    58,    59,    60,    61,    62,    63,
      22,    13,    14,    55,     8,    74,    74,   129,    72,    73,
      74,    75,    76,    20,    78,    26,    27,    28,    29,    30,
      72,    73,   144,    75,    76,    20,    78,   258,    20,    20,
      33,    36,    74,    77,    78,    79,    80,    36,   182,   183,
      77,    78,    79,    80,    22,    77,    78,    79,    80,    77,
      78,    79,    80,    74,   198,    77,    78,    79,    80,    40,
     291,    44,    41,    22,    55,    56,    57,    58,    59,    60,
      61,    62,    63,   195,    20,    41,    66,    74,    74,    21,
     202,    72,    73,    74,    75,    76,    74,    78,    79,    74,
      74,    35,   236,    75,    37,    12,   240,    22,    74,    77,
      78,    79,    80,    74,   248,    20,    74,    41,    36,    55,
      56,    57,    58,    59,    60,    61,    62,    63,    74,    21,
      20,    37,    34,    22,    22,    66,    72,    73,    74,    75,
      76,    46,    78,    79,    20,   279,    20,    74,    53,    64,
      55,    56,    57,    58,    59,    60,    61,    62,    63,    74,
      22,    74,    77,    78,    79,    80,    10,    72,    73,    74,
      75,    76,    20,    78,    74,    74,    22,    22,    50,    55,
      56,    57,    58,    59,    60,    61,    62,    63,    20,    53,
       6,    38,    21,    74,    20,    48,    72,    73,    74,    75,
      76,    54,    78,    74,    39,    38,    74,    55,    56,    57,
      58,    59,    60,    61,    62,    63,    52,    51,    72,    64,
      22,    41,    74,    55,    72,    73,    74,    75,    76,    74,
      78,    55,    77,    78,    79,    80,    74,    74,    49,    21,
      72,    73,    55,    75,    76,    22,    78,     4,     5,   102,
     103,   104,   105,    21,    11,    12,    13,    74,    15,    16,
      17,    18,    19,    21,    51,    21,    23,    24,    25,    55,
      46,    47,    21,    18,    31,    32,    22,   214,    54,   234,
     257,   203,   101,    40,   276,    42,   251,   204,    45,    65,
      66,    67,    68,    69,    70,    71,   106,   177,   296,   261,
     321,    77,    78,    79,    80,   336,   218,   317,    -1,    -1,
     270
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     4,     5,    11,    12,    13,    15,    16,    17,    18,
      19,    23,    24,    25,    31,    32,    40,    42,    45,    83,
      84,    85,    86,    87,    88,    89,    90,    91,    92,    93,
      94,    95,    96,    97,    98,   103,   108,   109,   112,   113,
     143,   144,   145,     6,     8,    48,     6,     8,    20,    55,
      72,    73,    75,    76,    78,   107,   114,   115,    20,    56,
      57,    58,    59,    60,    61,    62,    63,    74,    78,    79,
     107,   116,   117,   119,   120,   121,   122,   123,   125,   127,
      74,     7,     8,    34,    36,    74,    74,    43,    84,     0,
       3,   146,    74,    74,     8,    74,    74,   115,    72,    73,
     115,    22,    77,    78,    79,    80,    12,   107,   117,    20,
      20,    20,    33,   117,    22,    64,    74,    77,    78,    79,
      80,   118,    79,   117,    36,    36,    74,    74,    40,    66,
      44,    20,    64,   112,    41,    74,    41,    21,   114,   115,
     115,   115,   115,   125,    22,   106,    21,   117,   117,   117,
      74,   117,    74,   118,   117,   117,   117,   117,    21,    21,
      74,   126,    74,    35,    37,   130,    74,   110,    78,   107,
      75,    74,   100,   112,    74,    41,    74,    36,   107,    21,
      21,    21,    22,    22,    64,    74,   118,   118,     9,    22,
      64,    74,   128,    37,   137,    20,   105,    46,    53,   117,
     140,   141,    66,    22,   111,    72,    73,    34,    26,    27,
      28,    29,    30,   102,    22,    99,    20,    74,   126,   106,
     117,   117,    74,   118,    10,    74,    74,   128,   138,   139,
     141,    50,   133,   107,    22,   104,    53,   117,    46,    47,
      54,    65,    66,    67,    68,    69,    70,    71,   142,    38,
     107,   110,   130,     6,    20,    46,    55,   100,    21,    74,
      20,   137,    21,    21,   118,    74,    64,    74,   128,   128,
      39,    38,    51,    52,   131,   106,   105,   117,    47,    54,
     117,    46,    55,   117,   140,   111,    74,    72,   101,    55,
      99,    64,   112,    22,   124,    74,   133,    41,   129,    74,
     128,   139,   141,   127,   132,   140,    49,   136,    21,   104,
     117,    55,    21,   112,    74,    21,   124,   131,   140,   128,
     128,    22,    51,    46,    55,   124,    21,   136,   132,   127,
     134,   135,    55,    21,    13,    14,    22,   135
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    82,    83,    84,    84,    84,    84,    84,    84,    84,
      84,    84,    84,    84,    84,    84,    84,    84,    84,    84,
      84,    84,    84,    84,    84,    85,    86,    87,    88,    89,
      90,    91,    92,    93,    94,    95,    95,    96,    97,    98,
      98,    98,    98,    99,    99,   100,   100,   100,   100,   100,
     100,   100,   101,   102,   102,   102,   102,   103,   104,   104,
     105,   106,   106,   107,   107,   107,   107,   107,   107,   107,
     108,   109,   110,   111,   111,   112,   112,   113,   114,   114,
     115,   115,   115,   115,   115,   115,   115,   116,   116,   116,
     116,   116,   117,   117,   117,   117,   117,   117,   117,   117,
     118,   118,   118,   118,   119,   119,   119,   119,   120,   120,
     121,   121,   121,   121,   121,   122,   123,   124,   124,   125,
     125,   125,   125,   126,   126,   126,   127,   127,   128,   128,
     128,   128,   128,   129,   129,   130,   130,   131,   131,   132,
     132,   133,   133,   134,   134,   134,   135,   135,   135,   136,
     136,   137,   137,   138,   138,   139,   139,   140,   140,   140,
     141,   141,   141,   141,   141,   141,   141,   142,   142,   142,
     142,   142,   142,   142,   142,   143,   144,   145,   146,   146
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_int8 yyr2[] =
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
       1,     3,     3,     3,     3,     3,     2,     1,     1,     1,
       0,     3,     5,     4,     4,     4,     6,     6,     3,     3,
       1,     1,     1,     1,     1,     4,    10,     0,     3,     1,
       2,     4,     3,     2,     4,     3,     1,     3,     0,     3,
       5,     4,     5,     0,     2,     0,     2,     0,     2,     1,
       3,     0,     3,     1,     2,     2,     0,     1,     3,     0,
       3,     0,     2,     1,     3,     1,     3,     0,     1,     3,
       3,     3,     4,     3,     4,     2,     3,     1,     1,     1,
       1,     1,     1,     1,     2,     7,     2,     4,     0,     1
};


#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)
#define YYEMPTY         (-2)
#define YYEOF           0

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                    \
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
static int
yy_location_print_ (FILE *yyo, YYLTYPE const * const yylocp)
{
  int res = 0;
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


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo, int yytype, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp, const char * sql_string, ParsedSqlResult * sql_result, void * scanner)
{
  FILE *yyoutput = yyo;
  YYUSE (yyoutput);
  YYUSE (yylocationp);
  YYUSE (sql_string);
  YYUSE (sql_result);
  YYUSE (scanner);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyo, yytoknum[yytype], *yyvaluep);
# endif
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo, int yytype, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp, const char * sql_string, ParsedSqlResult * sql_result, void * scanner)
{
  YYFPRINTF (yyo, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  YY_LOCATION_PRINT (yyo, *yylocationp);
  YYFPRINTF (yyo, ": ");
  yy_symbol_value_print (yyo, yytype, yyvaluep, yylocationp, sql_string, sql_result, scanner);
  YYFPRINTF (yyo, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yy_state_t *yybottom, yy_state_t *yytop)
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
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp, YYLTYPE *yylsp, int yyrule, const char * sql_string, ParsedSqlResult * sql_result, void * scanner)
{
  int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %d):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       yystos[+yyssp[yyi + 1 - yynrhs]],
                       &yyvsp[(yyi + 1) - (yynrhs)]
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
#   define yystrlen(S) (YY_CAST (YYPTRDIFF_T, strlen (S)))
#  else
/* Return the length of YYSTR.  */
static YYPTRDIFF_T
yystrlen (const char *yystr)
{
  YYPTRDIFF_T yylen;
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
static YYPTRDIFF_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYPTRDIFF_T yyn = 0;
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
            else
              goto append;

          append:
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

  if (yyres)
    return yystpcpy (yyres, yystr) - yyres;
  else
    return yystrlen (yystr);
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
yysyntax_error (YYPTRDIFF_T *yymsg_alloc, char **yymsg,
                yy_state_t *yyssp, int yytoken)
{
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat: reported tokens (one for the "unexpected",
     one per "expected"). */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Actual size of YYARG. */
  int yycount = 0;
  /* Cumulated lengths of YYARG.  */
  YYPTRDIFF_T yysize = 0;

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
      int yyn = yypact[+*yyssp];
      YYPTRDIFF_T yysize0 = yytnamerr (YY_NULLPTR, yytname[yytoken]);
      yysize = yysize0;
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
                  YYPTRDIFF_T yysize1
                    = yysize + yytnamerr (YY_NULLPTR, yytname[yyx]);
                  if (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM)
                    yysize = yysize1;
                  else
                    return 2;
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
    default: /* Avoid compiler warnings. */
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
# undef YYCASE_
    }

  {
    /* Don't count the "%s"s in the final size, but reserve room for
       the terminator.  */
    YYPTRDIFF_T yysize1 = yysize + (yystrlen (yyformat) - 2 * yycount) + 1;
    if (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM)
      yysize = yysize1;
    else
      return 2;
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
          ++yyp;
          ++yyformat;
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

    yy_state_fast_t yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       'yyss': related to states.
       'yyvs': related to semantic values.
       'yyls': related to locations.

       Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss;
    yy_state_t *yyssp;

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

    YYPTRDIFF_T yystacksize;

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
  YYPTRDIFF_T yymsg_alloc = sizeof yymsgbuf;
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
| yynewstate -- push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;


/*--------------------------------------------------------------------.
| yysetstate -- set current state (the top of the stack) to yystate.  |
`--------------------------------------------------------------------*/
yysetstate:
  YYDPRINTF ((stderr, "Entering state %d\n", yystate));
  YY_ASSERT (0 <= yystate && yystate < YYNSTATES);
  YY_IGNORE_USELESS_CAST_BEGIN
  *yyssp = YY_CAST (yy_state_t, yystate);
  YY_IGNORE_USELESS_CAST_END

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    goto yyexhaustedlab;
#else
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYPTRDIFF_T yysize = yyssp - yyss + 1;

# if defined yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        yy_state_t *yyss1 = yyss;
        YYSTYPE *yyvs1 = yyvs;
        YYLTYPE *yyls1 = yyls;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
                    &yyls1, yysize * YYSIZEOF (*yylsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
        yyls = yyls1;
      }
# else /* defined YYSTACK_RELOCATE */
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          goto yyexhaustedlab;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
        YYSTACK_RELOCATE (yyls_alloc, yyls);
# undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;
      yylsp = yyls + yysize - 1;

      YY_IGNORE_USELESS_CAST_BEGIN
      YYDPRINTF ((stderr, "Stack size increased to %ld\n",
                  YY_CAST (long, yystacksize)));
      YY_IGNORE_USELESS_CAST_END

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }
#endif /* !defined yyoverflow && !defined YYSTACK_RELOCATE */

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
  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END
  *++yylsp = yylloc;

  /* Discard the shifted token.  */
  yychar = YYEMPTY;
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
| yyreduce -- do a reduction.  |
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

  /* Default location. */
  YYLLOC_DEFAULT (yyloc, (yylsp - yylen), yylen);
  yyerror_range[1] = yyloc;
  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
  case 2:
#line 245 "yacc_sql.y"
  {
    std::unique_ptr<ParsedSqlNode> sql_node = std::unique_ptr<ParsedSqlNode>((yyvsp[-1].sql_node));
    sql_result->add_sql_node(std::move(sql_node));
  }
#line 1855 "yacc_sql.cpp"
    break;

  case 25:
#line 277 "yacc_sql.y"
         {
      (void)yynerrs;  // 这么写为了消除yynerrs未使用的告警。如果你有更好的方法欢迎提PR
      (yyval.sql_node) = new ParsedSqlNode(SCF_EXIT);
    }
#line 1864 "yacc_sql.cpp"
    break;

  case 26:
#line 283 "yacc_sql.y"
         {
      (yyval.sql_node) = new ParsedSqlNode(SCF_HELP);
    }
#line 1872 "yacc_sql.cpp"
    break;

  case 27:
#line 288 "yacc_sql.y"
         {
      (yyval.sql_node) = new ParsedSqlNode(SCF_SYNC);
    }
#line 1880 "yacc_sql.cpp"
    break;

  case 28:
#line 294 "yacc_sql.y"
               {
      (yyval.sql_node) = new ParsedSqlNode(SCF_BEGIN);
    }
#line 1888 "yacc_sql.cpp"
    break;

  case 29:
#line 300 "yacc_sql.y"
               {
      (yyval.sql_node) = new ParsedSqlNode(SCF_COMMIT);
    }
#line 1896 "yacc_sql.cpp"
    break;

  case 30:
#line 306 "yacc_sql.y"
                  {
      (yyval.sql_node) = new ParsedSqlNode(SCF_ROLLBACK);
    }
#line 1904 "yacc_sql.cpp"
    break;

  case 31:
#line 312 "yacc_sql.y"
                  {
      (yyval.sql_node) = new ParsedSqlNode(SCF_DROP_TABLE);
      (yyval.sql_node)->drop_table.relation_name = (yyvsp[0].string);
      free((yyvsp[0].string));
    }
#line 1914 "yacc_sql.cpp"
    break;

  case 32:
#line 319 "yacc_sql.y"
                {
      (yyval.sql_node) = new ParsedSqlNode(SCF_SHOW_TABLES);
    }
#line 1922 "yacc_sql.cpp"
    break;

  case 33:
#line 324 "yacc_sql.y"
                        {
      (yyval.sql_node) = new ParsedSqlNode(SCF_SHOW_INDEX);
      (yyval.sql_node)->show_index.relation_name = (yyvsp[0].string);
      free((yyvsp[0].string));
    }
#line 1932 "yacc_sql.cpp"
    break;

  case 34:
#line 331 "yacc_sql.y"
             {
      (yyval.sql_node) = new ParsedSqlNode(SCF_DESC_TABLE);
      (yyval.sql_node)->desc_table.relation_name = (yyvsp[0].string);
      free((yyvsp[0].string));
    }
#line 1942 "yacc_sql.cpp"
    break;

  case 35:
#line 340 "yacc_sql.y"
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
#line 1965 "yacc_sql.cpp"
    break;

  case 36:
#line 359 "yacc_sql.y"
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
#line 1988 "yacc_sql.cpp"
    break;

  case 37:
#line 381 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_DROP_INDEX);
      (yyval.sql_node)->drop_index.index_name = (yyvsp[-2].string);
      (yyval.sql_node)->drop_index.relation_name = (yyvsp[0].string);
      free((yyvsp[-2].string));
      free((yyvsp[0].string));
    }
#line 2000 "yacc_sql.cpp"
    break;

  case 38:
#line 391 "yacc_sql.y"
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
#line 2020 "yacc_sql.cpp"
    break;

  case 39:
#line 409 "yacc_sql.y"
     {
        (yyval.sql_node) = new ParsedSqlNode(SCF_CREATE_TABLE_SELECT);
        CreateTableSelectSqlNode &create_table_select = (yyval.sql_node)->create_table_select;
        create_table_select.relation_name = (yyvsp[-2].string);
        free((yyvsp[-2].string));

        create_table_select.selection = (yyvsp[0].sql_node)->selection;
        delete (yyvsp[0].sql_node);
     }
#line 2034 "yacc_sql.cpp"
    break;

  case 40:
#line 419 "yacc_sql.y"
       {
          (yyval.sql_node) = new ParsedSqlNode(SCF_CREATE_TABLE_SELECT);
          CreateTableSelectSqlNode &create_table_select = (yyval.sql_node)->create_table_select;
          create_table_select.relation_name = (yyvsp[-1].string);
          free((yyvsp[-1].string));

          create_table_select.selection = (yyvsp[0].sql_node)->selection;
          delete (yyvsp[0].sql_node);
       }
#line 2048 "yacc_sql.cpp"
    break;

  case 41:
#line 429 "yacc_sql.y"
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
#line 2072 "yacc_sql.cpp"
    break;

  case 42:
#line 449 "yacc_sql.y"
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
#line 2096 "yacc_sql.cpp"
    break;

  case 43:
#line 471 "yacc_sql.y"
    {
      (yyval.attr_infos) = nullptr;
    }
#line 2104 "yacc_sql.cpp"
    break;

  case 44:
#line 475 "yacc_sql.y"
    {
      if ((yyvsp[0].attr_infos) != nullptr) {
        (yyval.attr_infos) = (yyvsp[0].attr_infos);
      } else {
        (yyval.attr_infos) = new std::vector<AttrInfoSqlNode>;
      }
      (yyval.attr_infos)->emplace_back(*(yyvsp[-1].attr_info));
      delete (yyvsp[-1].attr_info);
    }
#line 2118 "yacc_sql.cpp"
    break;

  case 45:
#line 488 "yacc_sql.y"
    {
      (yyval.attr_info) = new AttrInfoSqlNode;
      (yyval.attr_info)->type = (AttrType)(yyvsp[-3].number);
      (yyval.attr_info)->name = (yyvsp[-4].string);
      (yyval.attr_info)->length = (yyvsp[-1].number);
      (yyval.attr_info)->nullable = true;
      free((yyvsp[-4].string));
    }
#line 2131 "yacc_sql.cpp"
    break;

  case 46:
#line 497 "yacc_sql.y"
    {
      (yyval.attr_info) = new AttrInfoSqlNode;
      (yyval.attr_info)->type = (AttrType)TEXTS;
      (yyval.attr_info)->name = (yyvsp[-1].string);
      (yyval.attr_info)->length = 12;
      free((yyvsp[-1].string));
    }
#line 2143 "yacc_sql.cpp"
    break;

  case 47:
#line 505 "yacc_sql.y"
    {
      (yyval.attr_info) = new AttrInfoSqlNode;
      (yyval.attr_info)->type = (AttrType)(yyvsp[0].number);
      (yyval.attr_info)->name = (yyvsp[-1].string);
      (yyval.attr_info)->length = 4;
      (yyval.attr_info)->nullable = true;
      free((yyvsp[-1].string));
    }
#line 2156 "yacc_sql.cpp"
    break;

  case 48:
#line 514 "yacc_sql.y"
    {
        (yyval.attr_info) = new AttrInfoSqlNode;
        (yyval.attr_info)->type = (AttrType)(yyvsp[-4].number);
        (yyval.attr_info)->name = (yyvsp[-5].string);
        (yyval.attr_info)->length = (yyvsp[-2].number);
        (yyval.attr_info)->nullable = true;
        free((yyvsp[-5].string));
    }
#line 2169 "yacc_sql.cpp"
    break;

  case 49:
#line 523 "yacc_sql.y"
    {
        (yyval.attr_info) = new AttrInfoSqlNode;
        (yyval.attr_info)->type = (AttrType)(yyvsp[-1].number);
        (yyval.attr_info)->name = (yyvsp[-2].string);
        (yyval.attr_info)->length = 4;
        (yyval.attr_info)->nullable = true;
        free((yyvsp[-2].string));
    }
#line 2182 "yacc_sql.cpp"
    break;

  case 50:
#line 532 "yacc_sql.y"
    {
      (yyval.attr_info) = new AttrInfoSqlNode;
      (yyval.attr_info)->type = (AttrType)(yyvsp[-5].number);
      (yyval.attr_info)->name = (yyvsp[-6].string);
      (yyval.attr_info)->length = (yyvsp[-3].number);
      (yyval.attr_info)->nullable = false;
      free((yyvsp[-6].string));
    }
#line 2195 "yacc_sql.cpp"
    break;

  case 51:
#line 541 "yacc_sql.y"
    {
      (yyval.attr_info) = new AttrInfoSqlNode;
      (yyval.attr_info)->type = (AttrType)(yyvsp[-2].number);
      (yyval.attr_info)->name = (yyvsp[-3].string);
      (yyval.attr_info)->length = 4;
      (yyval.attr_info)->nullable = false;
      free((yyvsp[-3].string));
    }
#line 2208 "yacc_sql.cpp"
    break;

  case 52:
#line 551 "yacc_sql.y"
           {(yyval.number) = (yyvsp[0].number);}
#line 2214 "yacc_sql.cpp"
    break;

  case 53:
#line 554 "yacc_sql.y"
               { (yyval.number)=INTS; }
#line 2220 "yacc_sql.cpp"
    break;

  case 54:
#line 555 "yacc_sql.y"
               { (yyval.number)=CHARS; }
#line 2226 "yacc_sql.cpp"
    break;

  case 55:
#line 556 "yacc_sql.y"
               { (yyval.number)=FLOATS; }
#line 2232 "yacc_sql.cpp"
    break;

  case 56:
#line 557 "yacc_sql.y"
               { (yyval.number)=DATES; }
#line 2238 "yacc_sql.cpp"
    break;

  case 57:
#line 561 "yacc_sql.y"
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
#line 2255 "yacc_sql.cpp"
    break;

  case 58:
#line 576 "yacc_sql.y"
        {
	    (yyval.row_value_list) = nullptr;
	}
#line 2263 "yacc_sql.cpp"
    break;

  case 59:
#line 579 "yacc_sql.y"
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
#line 2280 "yacc_sql.cpp"
    break;

  case 60:
#line 594 "yacc_sql.y"
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
#line 2295 "yacc_sql.cpp"
    break;

  case 61:
#line 607 "yacc_sql.y"
    {
      (yyval.value_list) = nullptr;
    }
#line 2303 "yacc_sql.cpp"
    break;

  case 62:
#line 610 "yacc_sql.y"
                              {
      if ((yyvsp[0].value_list) != nullptr) {
        (yyval.value_list) = (yyvsp[0].value_list);
      } else {
        (yyval.value_list) = new std::vector<Value>;
      }
      (yyval.value_list)->emplace_back(*(yyvsp[-1].value));
      delete (yyvsp[-1].value);
    }
#line 2317 "yacc_sql.cpp"
    break;

  case 63:
#line 621 "yacc_sql.y"
           {
      (yyval.value) = new Value((int)(yyvsp[0].number));
      (yyloc) = (yylsp[0]);
    }
#line 2326 "yacc_sql.cpp"
    break;

  case 64:
#line 625 "yacc_sql.y"
                 {
      (yyval.value) = new Value(-(int)(yyvsp[0].number));
      (yyloc) = (yylsp[-1]);
    }
#line 2335 "yacc_sql.cpp"
    break;

  case 65:
#line 629 "yacc_sql.y"
            {
      (yyval.value) = new Value((float)(yyvsp[0].floats));
      (yyloc) = (yylsp[0]);
    }
#line 2344 "yacc_sql.cpp"
    break;

  case 66:
#line 633 "yacc_sql.y"
                {
      (yyval.value) = new Value(-(float)(yyvsp[0].floats));
      (yyloc) = (yylsp[-1]);
    }
#line 2353 "yacc_sql.cpp"
    break;

  case 67:
#line 637 "yacc_sql.y"
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
#line 2372 "yacc_sql.cpp"
    break;

  case 68:
#line 651 "yacc_sql.y"
          {
      char *tmp = common::substr((yyvsp[0].string),1,strlen((yyvsp[0].string))-2);
      (yyval.value) = new Value(tmp);
      free(tmp);
    }
#line 2382 "yacc_sql.cpp"
    break;

  case 69:
#line 656 "yacc_sql.y"
             {
        (yyval.value) = new Value();
    }
#line 2390 "yacc_sql.cpp"
    break;

  case 70:
#line 663 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_DELETE);
      (yyval.sql_node)->deletion.relation_name = (yyvsp[-1].string);
      if ((yyvsp[0].condition_list) != nullptr) {
        (yyval.sql_node)->deletion.conditions.swap(*(yyvsp[0].condition_list));
        delete (yyvsp[0].condition_list);
      }
      free((yyvsp[-1].string));
    }
#line 2404 "yacc_sql.cpp"
    break;

  case 71:
#line 675 "yacc_sql.y"
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
#line 2424 "yacc_sql.cpp"
    break;

  case 72:
#line 693 "yacc_sql.y"
                {
      (yyval.update_value) = new UpdateValueNode;
      (yyval.update_value)->attribute_name = (yyvsp[-2].string);
      (yyval.update_value)->value = *(yyvsp[0].value);
      free((yyvsp[-2].string));
      delete((yyvsp[0].value));
    }
#line 2436 "yacc_sql.cpp"
    break;

  case 73:
#line 703 "yacc_sql.y"
    {
      (yyval.update_value_list) = nullptr;
    }
#line 2444 "yacc_sql.cpp"
    break;

  case 74:
#line 706 "yacc_sql.y"
                                           {
      if ((yyvsp[0].update_value_list) != nullptr) {
        (yyval.update_value_list) = (yyvsp[0].update_value_list);
      } else {
        (yyval.update_value_list) = new std::vector<UpdateValueNode>;
      }
      (yyval.update_value_list)->emplace_back(*(yyvsp[-1].update_value));
      delete (yyvsp[-1].update_value);
    }
#line 2458 "yacc_sql.cpp"
    break;

  case 75:
#line 717 "yacc_sql.y"
                       {  // function 可能出现
      (yyval.sql_node) = new ParsedSqlNode(SCF_SELECT);
      if ((yyvsp[0].expr_list) != nullptr) {
        (yyval.sql_node)->selection.project_exprs.swap(*(yyvsp[0].expr_list));
        delete (yyvsp[0].expr_list);
      }
    }
#line 2470 "yacc_sql.cpp"
    break;

  case 76:
#line 725 "yacc_sql.y"
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
      if ((yyvsp[-3].expr) != nullptr) {
        (yyval.sql_node)->selection.condition = *((yyvsp[-3].expr)->condition_expr);
        delete (yyvsp[-3].expr);
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
#line 2506 "yacc_sql.cpp"
    break;

  case 77:
#line 760 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_CALC);
      std::reverse((yyvsp[0].expression_list)->begin(), (yyvsp[0].expression_list)->end());
      (yyval.sql_node)->calc.expressions.swap(*(yyvsp[0].expression_list));
      delete (yyvsp[0].expression_list);
    }
#line 2517 "yacc_sql.cpp"
    break;

  case 78:
#line 770 "yacc_sql.y"
    {
      (yyval.expression_list) = new std::vector<Expression*>;
      (yyval.expression_list)->emplace_back((yyvsp[0].expression));
    }
#line 2526 "yacc_sql.cpp"
    break;

  case 79:
#line 775 "yacc_sql.y"
    {
      if ((yyvsp[0].expression_list) != nullptr) {
        (yyval.expression_list) = (yyvsp[0].expression_list);
      } else {
        (yyval.expression_list) = new std::vector<Expression *>;
      }
      (yyval.expression_list)->emplace_back((yyvsp[-2].expression));
    }
#line 2539 "yacc_sql.cpp"
    break;

  case 80:
#line 785 "yacc_sql.y"
                              {
      (yyval.expression) = create_arithmetic_expression(ArithmeticExpr::Type::ADD, (yyvsp[-2].expression), (yyvsp[0].expression), sql_string, &(yyloc));
    }
#line 2547 "yacc_sql.cpp"
    break;

  case 81:
#line 788 "yacc_sql.y"
                                {
      (yyval.expression) = create_arithmetic_expression(ArithmeticExpr::Type::SUB, (yyvsp[-2].expression), (yyvsp[0].expression), sql_string, &(yyloc));
    }
#line 2555 "yacc_sql.cpp"
    break;

  case 82:
#line 791 "yacc_sql.y"
                                {
      (yyval.expression) = create_arithmetic_expression(ArithmeticExpr::Type::MUL, (yyvsp[-2].expression), (yyvsp[0].expression), sql_string, &(yyloc));
    }
#line 2563 "yacc_sql.cpp"
    break;

  case 83:
#line 794 "yacc_sql.y"
                                {
      (yyval.expression) = create_arithmetic_expression(ArithmeticExpr::Type::DIV, (yyvsp[-2].expression), (yyvsp[0].expression), sql_string, &(yyloc));
    }
#line 2571 "yacc_sql.cpp"
    break;

  case 84:
#line 797 "yacc_sql.y"
                               {
      (yyval.expression) = (yyvsp[-1].expression);
      (yyval.expression)->set_name(token_name(sql_string, &(yyloc)));
    }
#line 2580 "yacc_sql.cpp"
    break;

  case 85:
#line 801 "yacc_sql.y"
                                  {
      (yyval.expression) = create_arithmetic_expression(ArithmeticExpr::Type::NEGATIVE, (yyvsp[0].expression), nullptr, sql_string, &(yyloc));
    }
#line 2588 "yacc_sql.cpp"
    break;

  case 86:
#line 804 "yacc_sql.y"
            {
      (yyval.expression) = new ValueExpr(*(yyvsp[0].value));
      (yyval.expression)->set_name(token_name(sql_string, &(yyloc)));
      delete (yyvsp[0].value);
    }
#line 2598 "yacc_sql.cpp"
    break;

  case 87:
#line 815 "yacc_sql.y"
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
#line 2615 "yacc_sql.cpp"
    break;

  case 88:
#line 827 "yacc_sql.y"
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
#line 2632 "yacc_sql.cpp"
    break;

  case 89:
#line 839 "yacc_sql.y"
                {
      (yyval.expr) = (yyvsp[0].expr);
    }
#line 2640 "yacc_sql.cpp"
    break;

  case 90:
#line 842 "yacc_sql.y"
                     {
      (yyval.expr) = (yyvsp[0].expr);
    }
#line 2648 "yacc_sql.cpp"
    break;

  case 91:
#line 845 "yacc_sql.y"
                         {
      (yyvsp[-1].expr)->with_brace = true;
      (yyval.expr) = (yyvsp[-1].expr);
    }
#line 2657 "yacc_sql.cpp"
    break;

  case 92:
#line 853 "yacc_sql.y"
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
#line 2674 "yacc_sql.cpp"
    break;

  case 93:
#line 865 "yacc_sql.y"
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
#line 2691 "yacc_sql.cpp"
    break;

  case 94:
#line 877 "yacc_sql.y"
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
#line 2708 "yacc_sql.cpp"
    break;

  case 95:
#line 889 "yacc_sql.y"
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
#line 2725 "yacc_sql.cpp"
    break;

  case 96:
#line 901 "yacc_sql.y"
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
#line 2751 "yacc_sql.cpp"
    break;

  case 97:
#line 922 "yacc_sql.y"
                 { (yyval.expr) = (yyvsp[0].expr); }
#line 2757 "yacc_sql.cpp"
    break;

  case 98:
#line 923 "yacc_sql.y"
                 { (yyval.expr) = (yyvsp[0].expr); }
#line 2763 "yacc_sql.cpp"
    break;

  case 99:
#line 924 "yacc_sql.y"
                    { (yyval.expr) = (yyvsp[0].expr); }
#line 2769 "yacc_sql.cpp"
    break;

  case 100:
#line 930 "yacc_sql.y"
    {
      (yyval.expr_list) = nullptr;
    }
#line 2777 "yacc_sql.cpp"
    break;

  case 101:
#line 933 "yacc_sql.y"
                           {
      if ((yyvsp[0].expr_list) != nullptr) {
        (yyval.expr_list) = (yyvsp[0].expr_list);
      } else {
        (yyval.expr_list) = new std::vector<ExprSqlNode *>;
      }

      (yyval.expr_list)->emplace_back((yyvsp[-1].expr));
    }
#line 2791 "yacc_sql.cpp"
    break;

  case 102:
#line 942 "yacc_sql.y"
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
#line 2806 "yacc_sql.cpp"
    break;

  case 103:
#line 952 "yacc_sql.y"
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
#line 2821 "yacc_sql.cpp"
    break;

  case 104:
#line 965 "yacc_sql.y"
                              {
      FuncExprSqlNode* func = new FuncExprSqlNode;
      func->type = FuncType::FUNC_LENGTH;
      func->exprs.emplace_back((yyvsp[-1].expr));

      ExprSqlNode* expr = new ExprSqlNode;
      expr->type = ExprSqlNodeType::FUNCTION;
      expr->func_expr = func;
      (yyval.expr) = expr;
    }
#line 2836 "yacc_sql.cpp"
    break;

  case 105:
#line 975 "yacc_sql.y"
                               {
      FuncExprSqlNode* func = new FuncExprSqlNode;
      func->type = FuncType::FUNC_ROUND;
      func->exprs.emplace_back((yyvsp[-1].expr));

      ExprSqlNode* expr = new ExprSqlNode;
      expr->type = ExprSqlNodeType::FUNCTION;
      expr->func_expr = func;
      (yyval.expr) = expr;
    }
#line 2851 "yacc_sql.cpp"
    break;

  case 106:
#line 985 "yacc_sql.y"
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
#line 2867 "yacc_sql.cpp"
    break;

  case 107:
#line 996 "yacc_sql.y"
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
#line 2883 "yacc_sql.cpp"
    break;

  case 108:
#line 1010 "yacc_sql.y"
                               {
      AggrExprSqlNode* aggr = new AggrExprSqlNode;
      aggr->type = (yyvsp[-2].aggr_func_type);
      aggr->expr = (yyvsp[-1].expr);

      ExprSqlNode* expr = new ExprSqlNode;
      expr->type = ExprSqlNodeType::AGGREGATION;
      expr->aggr_expr = aggr;
      (yyval.expr) = expr;
    }
#line 2898 "yacc_sql.cpp"
    break;

  case 109:
#line 1020 "yacc_sql.y"
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
#line 2928 "yacc_sql.cpp"
    break;

  case 110:
#line 1048 "yacc_sql.y"
             {
      (yyval.aggr_func_type) = AggrFuncType::AGGR_MAX;
    }
#line 2936 "yacc_sql.cpp"
    break;

  case 111:
#line 1051 "yacc_sql.y"
               {
      (yyval.aggr_func_type) = AggrFuncType::AGGR_MIN;
    }
#line 2944 "yacc_sql.cpp"
    break;

  case 112:
#line 1054 "yacc_sql.y"
               {
      (yyval.aggr_func_type) = AggrFuncType::AGGR_SUM;
    }
#line 2952 "yacc_sql.cpp"
    break;

  case 113:
#line 1057 "yacc_sql.y"
               {
      (yyval.aggr_func_type) = AggrFuncType::AGGR_AVG;
    }
#line 2960 "yacc_sql.cpp"
    break;

  case 114:
#line 1060 "yacc_sql.y"
                 {
      (yyval.aggr_func_type) = AggrFuncType::AGGR_COUNT;
    }
#line 2968 "yacc_sql.cpp"
    break;

  case 115:
#line 1068 "yacc_sql.y"
    {
      ValueListExprSqlNode* value_list_expr = new ValueListExprSqlNode;
      if ((yyvsp[-1].value_list) != nullptr) {
        value_list_expr->values = *(yyvsp[-1].value_list);
        delete (yyvsp[-1].value_list);
      }
      value_list_expr->values.emplace_back(*(yyvsp[-2].value));
      delete (yyvsp[-2].value);
      std::reverse(value_list_expr->values.begin(), value_list_expr->values.end());

      ExprSqlNode* expr = new ExprSqlNode;
      expr->type = ExprSqlNodeType::VALUELIST;
      expr->value_list_expr = value_list_expr;
      (yyval.expr) = expr;
    }
#line 2988 "yacc_sql.cpp"
    break;

  case 116:
#line 1087 "yacc_sql.y"
    {
      SelectSqlNode* select_node = new SelectSqlNode;
      if ((yyvsp[-7].expr_list) != nullptr) {
        select_node->project_exprs.swap(*(yyvsp[-7].expr_list));
        delete (yyvsp[-7].expr_list);
      }
      if ((yyvsp[-5].relation_list) != nullptr) {
        select_node->relation_names.swap((yyvsp[-5].relation_list)->relation_names);
        select_node->alias_names.swap((yyvsp[-5].relation_list)->alias_names);
        select_node->inner_join_conditions.swap((yyvsp[-5].relation_list)->conditions);
        delete (yyvsp[-5].relation_list);
      }
      std::reverse(select_node->relation_names.begin(), select_node->relation_names.end());
      std::reverse(select_node->alias_names.begin(), select_node->alias_names.end());
      if ((yyvsp[-4].expr) != nullptr) {
        select_node->condition = *((yyvsp[-4].expr)->condition_expr);
        delete (yyvsp[-4].expr);
      }
      if ((yyvsp[-3].rel_attr_list) != nullptr) {
        select_node->group_by_cols.swap(*(yyvsp[-3].rel_attr_list));
        delete (yyvsp[-3].rel_attr_list);
      }
      if ((yyvsp[-2].condition_list) != nullptr) {
        select_node->having_conditions.swap(*(yyvsp[-2].condition_list));
        delete (yyvsp[-2].condition_list);
      }
      if ((yyvsp[-1].order_attr_list) != nullptr) {
        select_node->order_by_cols.swap(*(yyvsp[-1].order_attr_list));
        delete (yyvsp[-1].order_attr_list);
      }

       SubQueryExprSqlNode* sub_query_expr = new SubQueryExprSqlNode;
       sub_query_expr->sub_select = select_node;

       ExprSqlNode* expr = new ExprSqlNode;
       expr->type = ExprSqlNodeType::SUBQUERY;
       expr->sub_query_expr = sub_query_expr;
       (yyval.expr) = expr;
    }
#line 3032 "yacc_sql.cpp"
    break;

  case 117:
#line 1130 "yacc_sql.y"
    {
      (yyval.rel_index_attr_list) = nullptr;
    }
#line 3040 "yacc_sql.cpp"
    break;

  case 118:
#line 1133 "yacc_sql.y"
                               {
      if ((yyvsp[0].rel_index_attr_list) != nullptr) {
        (yyval.rel_index_attr_list) = (yyvsp[0].rel_index_attr_list);
      } else {
        (yyval.rel_index_attr_list) = new std::vector<string>;
      }

      (yyval.rel_index_attr_list)->emplace_back((yyvsp[-1].string));
      free((yyvsp[-1].string));
    }
#line 3055 "yacc_sql.cpp"
    break;

  case 119:
#line 1145 "yacc_sql.y"
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
#line 3076 "yacc_sql.cpp"
    break;

  case 120:
#line 1162 "yacc_sql.y"
                     {
      if ((yyvsp[0].expr_list) != nullptr) {
        (yyval.expr_list) = (yyvsp[0].expr_list);
      } else {
        (yyval.expr_list) = new std::vector<ExprSqlNode*>;
      }
      (yyval.expr_list)->emplace_back((yyvsp[-1].expr));
    }
#line 3089 "yacc_sql.cpp"
    break;

  case 121:
#line 1170 "yacc_sql.y"
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
#line 3104 "yacc_sql.cpp"
    break;

  case 122:
#line 1180 "yacc_sql.y"
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
#line 3119 "yacc_sql.cpp"
    break;

  case 123:
#line 1193 "yacc_sql.y"
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
#line 3134 "yacc_sql.cpp"
    break;

  case 124:
#line 1203 "yacc_sql.y"
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
#line 3150 "yacc_sql.cpp"
    break;

  case 125:
#line 1214 "yacc_sql.y"
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
#line 3166 "yacc_sql.cpp"
    break;

  case 126:
#line 1228 "yacc_sql.y"
       {
      (yyval.rel_attr) = new RelAttrSqlNode;
      (yyval.rel_attr)->attribute_name = (yyvsp[0].string);
      free((yyvsp[0].string));
    }
#line 3176 "yacc_sql.cpp"
    break;

  case 127:
#line 1233 "yacc_sql.y"
                {
      (yyval.rel_attr) = new RelAttrSqlNode;
      (yyval.rel_attr)->relation_name  = (yyvsp[-2].string);
      (yyval.rel_attr)->attribute_name = (yyvsp[0].string);
      free((yyvsp[-2].string));
      free((yyvsp[0].string));
    }
#line 3188 "yacc_sql.cpp"
    break;

  case 128:
#line 1261 "yacc_sql.y"
    {
      (yyval.relation_list) = nullptr;
    }
#line 3196 "yacc_sql.cpp"
    break;

  case 129:
#line 1264 "yacc_sql.y"
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
#line 3211 "yacc_sql.cpp"
    break;

  case 130:
#line 1274 "yacc_sql.y"
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
#line 3227 "yacc_sql.cpp"
    break;

  case 131:
#line 1285 "yacc_sql.y"
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
#line 3243 "yacc_sql.cpp"
    break;

  case 132:
#line 1296 "yacc_sql.y"
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
#line 3264 "yacc_sql.cpp"
    break;

  case 133:
#line 1314 "yacc_sql.y"
                    {
       (yyval.condition_list) = nullptr;
    }
#line 3272 "yacc_sql.cpp"
    break;

  case 134:
#line 1317 "yacc_sql.y"
                            {
       (yyval.condition_list) = (yyvsp[0].condition_list);
	}
#line 3280 "yacc_sql.cpp"
    break;

  case 135:
#line 1323 "yacc_sql.y"
    {
      (yyval.condition_list) = nullptr;
    }
#line 3288 "yacc_sql.cpp"
    break;

  case 136:
#line 1326 "yacc_sql.y"
                           {
      (yyval.condition_list) = (yyvsp[0].condition_list);  
    }
#line 3296 "yacc_sql.cpp"
    break;

  case 137:
#line 1333 "yacc_sql.y"
    {
      (yyval.condition_list) = nullptr;
    }
#line 3304 "yacc_sql.cpp"
    break;

  case 138:
#line 1336 "yacc_sql.y"
                            {
      (yyval.condition_list) = (yyvsp[0].condition_list);
    }
#line 3312 "yacc_sql.cpp"
    break;

  case 139:
#line 1343 "yacc_sql.y"
    {
        (yyval.rel_attr_list) = new std::vector<RelAttrSqlNode>;
        (yyval.rel_attr_list)->emplace_back(*(yyvsp[0].rel_attr));
        delete (yyvsp[0].rel_attr);
    }
#line 3322 "yacc_sql.cpp"
    break;

  case 140:
#line 1349 "yacc_sql.y"
        {
        (yyval.rel_attr_list) = (yyvsp[0].rel_attr_list);
        (yyval.rel_attr_list)->emplace_back(*(yyvsp[-2].rel_attr));
        delete (yyvsp[-2].rel_attr);
	}
#line 3332 "yacc_sql.cpp"
    break;

  case 141:
#line 1357 "yacc_sql.y"
    {
      (yyval.rel_attr_list) = nullptr;
    }
#line 3340 "yacc_sql.cpp"
    break;

  case 142:
#line 1360 "yacc_sql.y"
                          {
      (yyval.rel_attr_list) = (yyvsp[0].rel_attr_list);
      std::reverse((yyval.rel_attr_list)->begin(), (yyval.rel_attr_list)->end());
    }
#line 3349 "yacc_sql.cpp"
    break;

  case 143:
#line 1368 "yacc_sql.y"
        {
		(yyval.order_attr) = new OrderBySqlNode;
		(yyval.order_attr)->attribute = *(yyvsp[0].rel_attr);
		(yyval.order_attr)->is_asc = true;

		delete (yyvsp[0].rel_attr);
	}
#line 3361 "yacc_sql.cpp"
    break;

  case 144:
#line 1377 "yacc_sql.y"
        {
		(yyval.order_attr) = new OrderBySqlNode;
        (yyval.order_attr)->attribute = *(yyvsp[-1].rel_attr);
      	(yyval.order_attr)->is_asc = true;

      	delete (yyvsp[-1].rel_attr);
	}
#line 3373 "yacc_sql.cpp"
    break;

  case 145:
#line 1386 "yacc_sql.y"
        {
		(yyval.order_attr) = new OrderBySqlNode;
        (yyval.order_attr)->attribute = *(yyvsp[-1].rel_attr);
      	(yyval.order_attr)->is_asc = false;

      	delete (yyvsp[-1].rel_attr);
	}
#line 3385 "yacc_sql.cpp"
    break;

  case 146:
#line 1396 "yacc_sql.y"
        {
        (yyval.order_attr_list) = nullptr;
	}
#line 3393 "yacc_sql.cpp"
    break;

  case 147:
#line 1400 "yacc_sql.y"
    {
        (yyval.order_attr_list) = new std::vector<OrderBySqlNode>;
        (yyval.order_attr_list)->emplace_back(*(yyvsp[0].order_attr));
        delete (yyvsp[0].order_attr);
    }
#line 3403 "yacc_sql.cpp"
    break;

  case 148:
#line 1406 "yacc_sql.y"
        {
        (yyval.order_attr_list) = (yyvsp[0].order_attr_list);
        (yyval.order_attr_list)->emplace_back(*(yyvsp[-2].order_attr));
        delete (yyvsp[-2].order_attr);
	}
#line 3413 "yacc_sql.cpp"
    break;

  case 149:
#line 1414 "yacc_sql.y"
    {
      (yyval.order_attr_list) = nullptr;
    }
#line 3421 "yacc_sql.cpp"
    break;

  case 150:
#line 1417 "yacc_sql.y"
                         {
      (yyval.order_attr_list) = (yyvsp[0].order_attr_list);
      std::reverse((yyval.order_attr_list)->begin(), (yyval.order_attr_list)->end());
    }
#line 3430 "yacc_sql.cpp"
    break;

  case 151:
#line 1425 "yacc_sql.y"
    {
      (yyval.expr) = nullptr;
    }
#line 3438 "yacc_sql.cpp"
    break;

  case 152:
#line 1428 "yacc_sql.y"
                         {
      (yyval.expr) = (yyvsp[0].expr);
    }
#line 3446 "yacc_sql.cpp"
    break;

  case 153:
#line 1435 "yacc_sql.y"
     {
       (yyval.expr) = (yyvsp[0].expr);
     }
#line 3454 "yacc_sql.cpp"
    break;

  case 154:
#line 1439 "yacc_sql.y"
     {
       ConditionSqlNode* con_expr = new ConditionSqlNode;
       con_expr->comp = OR_OP;
       con_expr->left = (yyvsp[-2].expr);
       con_expr->right = (yyvsp[0].expr);

       ExprSqlNode* expr = new ExprSqlNode;
       expr->type = ExprSqlNodeType::CONDITION;
       expr->condition_expr = con_expr;
       (yyval.expr) = expr;
     }
#line 3470 "yacc_sql.cpp"
    break;

  case 155:
#line 1453 "yacc_sql.y"
     {
       ExprSqlNode* expr = new ExprSqlNode;
       expr->type = ExprSqlNodeType::CONDITION;
       expr->condition_expr = (yyvsp[0].condition);
       (yyval.expr) = expr;
     }
#line 3481 "yacc_sql.cpp"
    break;

  case 156:
#line 1460 "yacc_sql.y"
     {
       ExprSqlNode* right_expr = new ExprSqlNode;
       right_expr->type = ExprSqlNodeType::CONDITION;
       right_expr->condition_expr = (yyvsp[0].condition);

       ConditionSqlNode* con_expr = new ConditionSqlNode;
       con_expr->comp = AND_OP;
       con_expr->left = (yyvsp[-2].expr);
       con_expr->right = right_expr;

       ExprSqlNode* expr = new ExprSqlNode;
       expr->type = ExprSqlNodeType::CONDITION;
       expr->condition_expr = con_expr;
       (yyval.expr) = expr;
     }
#line 3501 "yacc_sql.cpp"
    break;

  case 157:
#line 1478 "yacc_sql.y"
    {
      (yyval.condition_list) = nullptr;
    }
#line 3509 "yacc_sql.cpp"
    break;

  case 158:
#line 1481 "yacc_sql.y"
                {
      (yyval.condition_list) = new std::vector<ConditionSqlNode>;
      (yyval.condition_list)->emplace_back(*(yyvsp[0].condition));
      delete (yyvsp[0].condition);
    }
#line 3519 "yacc_sql.cpp"
    break;

  case 159:
#line 1486 "yacc_sql.y"
                                   {
      (yyval.condition_list) = (yyvsp[0].condition_list);
      (yyval.condition_list)->emplace_back(*(yyvsp[-2].condition));
      delete (yyvsp[-2].condition);
    }
#line 3529 "yacc_sql.cpp"
    break;

  case 160:
#line 1495 "yacc_sql.y"
    {
      (yyval.condition) = new ConditionSqlNode;
      (yyval.condition)->left = (yyvsp[-2].expr);
      (yyval.condition)->comp = (yyvsp[-1].comp);
      (yyval.condition)->right = (yyvsp[0].expr);
    }
#line 3540 "yacc_sql.cpp"
    break;

  case 161:
#line 1502 "yacc_sql.y"
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
#line 3561 "yacc_sql.cpp"
    break;

  case 162:
#line 1519 "yacc_sql.y"
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
#line 3582 "yacc_sql.cpp"
    break;

  case 163:
#line 1536 "yacc_sql.y"
    {
      (yyval.condition) = new ConditionSqlNode;
      (yyval.condition)->left = (yyvsp[-2].expr);
      (yyval.condition)->comp = IN_OP;
      (yyval.condition)->right = (yyvsp[0].expr);
    }
#line 3593 "yacc_sql.cpp"
    break;

  case 164:
#line 1543 "yacc_sql.y"
    {
      (yyval.condition) = new ConditionSqlNode;
      (yyval.condition)->left = (yyvsp[-3].expr);
      (yyval.condition)->comp = NOT_IN_OP;
      (yyval.condition)->right = (yyvsp[0].expr);
    }
#line 3604 "yacc_sql.cpp"
    break;

  case 165:
#line 1550 "yacc_sql.y"
    {
      (yyval.condition) = new ConditionSqlNode;
      (yyval.condition)->left = (yyvsp[0].expr);
      (yyval.condition)->comp = EXISTS_OP;

      // &&->right = 1;
      Value val(1);    // val = 1
      UnaryExprSqlNode* unary = new UnaryExprSqlNode;
      unary->value = val;
      unary->is_attr = false;

      ExprSqlNode* expr = new ExprSqlNode;
      expr->type = ExprSqlNodeType::UNARY;
      expr->unary_expr = unary;

      (yyval.condition)->right = expr;
    }
#line 3626 "yacc_sql.cpp"
    break;

  case 166:
#line 1568 "yacc_sql.y"
    {
      (yyval.condition) = new ConditionSqlNode;
      (yyval.condition)->left = (yyvsp[0].expr);
      (yyval.condition)->comp = NOT_EXISTS_OP;

      // &&->right = 1;
      Value val(1);    // val = 1
      UnaryExprSqlNode* unary = new UnaryExprSqlNode;
      unary->value = val;
      unary->is_attr = false;

      ExprSqlNode* expr = new ExprSqlNode;
      expr->type = ExprSqlNodeType::UNARY;
      expr->unary_expr = unary;

      (yyval.condition)->right = expr;
    }
#line 3648 "yacc_sql.cpp"
    break;

  case 167:
#line 1588 "yacc_sql.y"
         { (yyval.comp) = EQUAL_TO; }
#line 3654 "yacc_sql.cpp"
    break;

  case 168:
#line 1589 "yacc_sql.y"
         { (yyval.comp) = LESS_THAN; }
#line 3660 "yacc_sql.cpp"
    break;

  case 169:
#line 1590 "yacc_sql.y"
         { (yyval.comp) = GREAT_THAN; }
#line 3666 "yacc_sql.cpp"
    break;

  case 170:
#line 1591 "yacc_sql.y"
         { (yyval.comp) = LESS_EQUAL; }
#line 3672 "yacc_sql.cpp"
    break;

  case 171:
#line 1592 "yacc_sql.y"
         { (yyval.comp) = GREAT_EQUAL; }
#line 3678 "yacc_sql.cpp"
    break;

  case 172:
#line 1593 "yacc_sql.y"
         { (yyval.comp) = NOT_EQUAL; }
#line 3684 "yacc_sql.cpp"
    break;

  case 173:
#line 1594 "yacc_sql.y"
           { (yyval.comp) = LIKE_OP; }
#line 3690 "yacc_sql.cpp"
    break;

  case 174:
#line 1595 "yacc_sql.y"
               { (yyval.comp) = NOT_LIKE_OP; }
#line 3696 "yacc_sql.cpp"
    break;

  case 175:
#line 1600 "yacc_sql.y"
    {
      char *tmp_file_name = common::substr((yyvsp[-3].string), 1, strlen((yyvsp[-3].string)) - 2);
      
      (yyval.sql_node) = new ParsedSqlNode(SCF_LOAD_DATA);
      (yyval.sql_node)->load_data.relation_name = (yyvsp[0].string);
      (yyval.sql_node)->load_data.file_name = tmp_file_name;
      free((yyvsp[0].string));
      free(tmp_file_name);
    }
#line 3710 "yacc_sql.cpp"
    break;

  case 176:
#line 1613 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_EXPLAIN);
      (yyval.sql_node)->explain.sql_node = std::unique_ptr<ParsedSqlNode>((yyvsp[0].sql_node));
    }
#line 3719 "yacc_sql.cpp"
    break;

  case 177:
#line 1621 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_SET_VARIABLE);
      (yyval.sql_node)->set_variable.name  = (yyvsp[-2].string);
      (yyval.sql_node)->set_variable.value = *(yyvsp[0].value);
      free((yyvsp[-2].string));
      delete (yyvsp[0].value);
    }
#line 3731 "yacc_sql.cpp"
    break;


#line 3735 "yacc_sql.cpp"

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
  {
    const int yylhs = yyr1[yyn] - YYNTOKENS;
    const int yyi = yypgoto[yylhs] + *yyssp;
    yystate = (0 <= yyi && yyi <= YYLAST && yycheck[yyi] == *yyssp
               ? yytable[yyi]
               : yydefgoto[yylhs]);
  }

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
            yymsg = YY_CAST (char *, YYSTACK_ALLOC (YY_CAST (YYSIZE_T, yymsg_alloc)));
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
  /* Pacify compilers when the user code never invokes YYERROR and the
     label yyerrorlab therefore never appears in user code.  */
  if (0)
    YYERROR;

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


/*-----------------------------------------------------.
| yyreturn -- parsing is finished, return the result.  |
`-----------------------------------------------------*/
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
                  yystos[+*yyssp], yyvsp, yylsp, sql_string, sql_result, scanner);
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
#line 1633 "yacc_sql.y"

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
