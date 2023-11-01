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
    VIEW = 319,
    AS = 320,
    IS = 321,
    EQ = 322,
    LT = 323,
    GT = 324,
    LE = 325,
    GE = 326,
    NE = 327,
    NUMBER = 328,
    FLOAT = 329,
    ID = 330,
    SSS = 331,
    DATE_STR = 332,
    UMINUS = 333
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 131 "yacc_sql.y"

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


#line 278 "yacc_sql.cpp"

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
#define YYFINAL  91
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   477

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  83
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  66
/* YYNRULES -- Number of rules.  */
#define YYNRULES  184
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  354

#define YYUNDEFTOK  2
#define YYMAXUTOK   333


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
       2,     2,    80,    78,     2,    79,     2,    81,     2,     2,
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
      75,    76,    77,    82
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   246,   246,   254,   255,   256,   257,   258,   259,   260,
     261,   262,   263,   264,   265,   266,   267,   268,   269,   270,
     271,   272,   273,   274,   275,   276,   280,   286,   291,   297,
     303,   309,   315,   322,   327,   334,   342,   361,   383,   393,
     411,   421,   431,   451,   474,   477,   490,   499,   507,   516,
     525,   534,   543,   554,   557,   558,   559,   560,   563,   579,
     582,   596,   610,   613,   624,   628,   632,   636,   640,   654,
     659,   665,   677,   696,   711,   720,   723,   734,   741,   776,
     786,   791,   802,   805,   808,   811,   814,   818,   821,   832,
     844,   856,   859,   862,   870,   882,   894,   906,   918,   939,
     940,   941,   947,   950,   971,   980,   990,  1003,  1013,  1023,
    1034,  1048,  1058,  1086,  1089,  1092,  1095,  1098,  1105,  1124,
    1168,  1171,  1183,  1199,  1218,  1226,  1236,  1249,  1259,  1270,
    1284,  1289,  1317,  1320,  1330,  1341,  1352,  1370,  1373,  1379,
    1382,  1389,  1392,  1398,  1404,  1413,  1416,  1423,  1432,  1441,
    1452,  1455,  1461,  1470,  1473,  1481,  1484,  1490,  1494,  1508,
    1515,  1534,  1537,  1542,  1550,  1557,  1574,  1591,  1598,  1605,
    1623,  1644,  1645,  1646,  1647,  1648,  1649,  1650,  1651,  1655,
    1668,  1676,  1686,  1687,  1691
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
  "AGGR_AVG", "AGGR_SUM", "LENGTH", "ROUND", "DATE_FORMAT", "VIEW", "AS",
  "IS", "EQ", "LT", "GT", "LE", "GE", "NE", "NUMBER", "FLOAT", "ID", "SSS",
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
  "set_variable_stmt", "opt_semicolon", "create_view_stmt", YY_NULLPTR
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
     325,   326,   327,   328,   329,   330,   331,   332,    43,    45,
      42,    47,   333
};
# endif

#define YYPACT_NINF (-300)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-63)

#define yytable_value_is_error(Yyn) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     407,    19,    83,   157,   142,   -61,    21,  -300,   -16,     2,
     -43,  -300,  -300,  -300,  -300,  -300,   -34,    42,   407,    58,
      96,  -300,  -300,  -300,  -300,  -300,  -300,  -300,  -300,  -300,
    -300,  -300,  -300,  -300,  -300,  -300,  -300,  -300,  -300,  -300,
    -300,  -300,  -300,  -300,    33,    46,   126,    69,    74,    76,
     157,  -300,  -300,  -300,  -300,  -300,   165,  -300,  -300,    23,
      80,  -300,  -300,  -300,  -300,  -300,   138,   141,   154,   143,
     272,  -300,  -300,  -300,   172,  -300,  -300,   203,  -300,  -300,
       6,  -300,  -300,  -300,   139,   108,   111,   147,   128,   152,
    -300,  -300,  -300,  -300,   -10,   170,   149,   148,  -300,   185,
      15,  -300,  -300,  -300,   157,   157,   157,   157,   157,   142,
     194,    28,    67,   281,   281,   281,   -23,  -300,   330,   160,
     207,   281,   281,   281,   281,  -300,   222,    85,  -300,   171,
     173,   219,   231,   180,   105,   193,   181,   258,  -300,   197,
     232,   258,   199,  -300,  -300,    17,    17,  -300,  -300,   239,
     213,   105,   268,  -300,    92,     1,   218,  -300,   207,   257,
     206,   207,  -300,    87,    87,  -300,  -300,  -300,  -300,    -6,
     279,  -300,   274,   247,  -300,   228,   296,     3,  -300,   291,
     285,   331,  -300,   299,   286,  -300,  -300,   171,   340,  -300,
    -300,  -300,   281,   281,  -300,    32,   288,   207,  -300,  -300,
     354,   292,   293,    24,  -300,   247,   316,   105,   347,   319,
     281,   387,  -300,   337,   297,   180,   231,  -300,  -300,   371,
    -300,  -300,  -300,  -300,  -300,   -12,   181,   357,   304,   360,
     279,  -300,   112,   129,   207,   207,  -300,   306,    -3,    24,
    -300,   343,   345,  -300,   333,   342,   340,   274,  -300,   281,
      51,   -17,  -300,   281,   -31,  -300,  -300,  -300,  -300,  -300,
    -300,   281,   247,   383,  -300,  -300,   296,  -300,   321,   324,
     344,  -300,   331,     5,   376,   325,   316,  -300,  -300,  -300,
    -300,   361,   326,    24,  -300,  -300,   247,   247,   335,   247,
     359,   392,   347,    51,  -300,   281,    51,   366,  -300,    51,
    -300,  -300,  -300,  -300,   406,  -300,  -300,   258,  -300,   353,
     408,   376,   342,   247,    24,    24,  -300,   345,  -300,   413,
    -300,  -300,   385,  -300,  -300,  -300,    51,  -300,   -20,  -300,
     376,  -300,   416,   359,  -300,  -300,  -300,   335,   335,   388,
    -300,  -300,  -300,   419,  -300,    50,   420,  -300,  -300,  -300,
    -300,  -300,   335,  -300
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     0,     0,     0,     0,     0,     0,    28,     0,     0,
       0,    29,    30,    31,    27,    26,     0,     0,     0,     0,
     182,    25,    24,    17,    18,    19,    20,    11,    12,    13,
      14,    15,    16,     8,     9,     5,     7,     6,     4,     3,
      21,    22,    23,    10,     0,     0,     0,     0,     0,     0,
       0,    70,    64,    66,    69,    68,     0,    88,    79,    80,
       0,   113,   114,   117,   116,   115,     0,     0,     0,   130,
       0,   122,    89,    99,   102,    91,    92,     0,   101,   100,
       0,    90,    35,    33,     0,     0,     0,     0,     0,     0,
     180,     1,   183,     2,     0,     0,     0,     0,    32,     0,
       0,    64,    66,    87,     0,     0,     0,     0,     0,     0,
     130,    89,     0,     0,     0,     0,     0,    98,     0,     0,
     102,     0,     0,     0,     0,   124,     0,     0,    77,     0,
       0,     0,   139,     0,     0,     0,     0,     0,    41,     0,
       0,     0,     0,    86,    81,    82,    83,    84,    85,     0,
       0,     0,     0,    93,     0,     0,     0,   131,   102,   130,
     102,   102,   126,    94,    95,    96,    97,   112,   111,   132,
     155,    34,     0,   161,    71,     0,    75,     0,   181,     0,
       0,    44,    40,     0,     0,   184,    38,     0,    62,   118,
     107,   108,     0,     0,   123,     0,     0,   102,   104,   125,
       0,     0,     0,   132,   127,     0,   145,     0,    59,     0,
       0,     0,   140,   162,     0,     0,   139,    65,    67,     0,
      54,    55,    56,    57,    47,    48,     0,     0,     0,     0,
     155,    63,     0,     0,   102,   102,   106,     0,   132,   132,
     129,   156,   157,   159,     0,   141,    62,     0,    58,     0,
     169,     0,   177,     0,     0,   171,   172,   173,   174,   175,
     176,     0,   161,     0,    73,    74,    75,    72,     0,     0,
       0,    50,    44,    39,   120,     0,   145,   109,   110,   103,
     105,   137,     0,   132,   133,   128,     0,     0,     0,   161,
     153,     0,    59,   170,   178,     0,   167,     0,   165,   164,
     163,    76,   179,    53,     0,    52,    45,     0,    43,     0,
       0,   120,   141,   161,   132,   132,   135,   158,   160,   143,
     146,   142,     0,    78,    61,    60,   168,   166,    46,    42,
     120,    36,     0,   153,   138,   136,   134,     0,   150,     0,
      49,   121,    37,     0,   144,   147,   151,   154,    51,   119,
     149,   148,   150,   152
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -300,  -300,   426,  -300,  -300,  -300,  -300,  -300,  -300,  -300,
    -300,  -300,  -300,  -300,  -300,  -300,  -300,   174,   224,  -300,
    -300,  -300,   153,   201,  -181,    18,  -300,  -300,   236,   195,
     -93,  -300,   356,   309,  -300,    -4,  -107,  -300,  -300,  -300,
    -300,   248,  -299,   355,   276,  -277,  -199,  -300,   253,   158,
     134,   196,  -300,   121,   144,   244,  -300,   189,  -242,  -200,
    -300,  -300,  -300,  -300,  -300,  -300
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,    19,    20,    21,    22,    23,    24,    25,    26,    27,
      28,    29,    30,    31,    32,    33,    34,   227,   181,   304,
     225,    35,   248,   208,   152,    72,    36,    37,   176,   216,
      38,    39,    58,    59,    73,   211,   125,    75,    76,    77,
      78,    79,   310,    80,   170,    81,   204,   314,   174,   290,
     320,   245,   346,   347,   323,   206,   241,   242,   212,   213,
     261,    40,    41,    42,    93,    43
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      74,   138,     4,   200,   240,   243,   200,   231,   269,   128,
     136,   319,   332,   162,    82,   297,   201,     4,    85,   201,
     300,    57,   191,   192,   298,    44,   339,    45,    83,    84,
     294,   341,    87,   200,   270,   340,   143,   295,    86,   284,
     285,    88,   129,   271,   182,   104,   201,   321,   185,   -62,
     151,   194,   157,   198,   199,   137,   112,   158,    91,   202,
     319,   345,   282,   350,   351,   291,   117,    46,    57,   203,
     307,   334,   283,   127,    57,   345,   217,   218,   111,   121,
     122,   123,   124,    47,   316,    89,   243,   318,   153,    48,
     236,    49,   109,   105,   106,   107,   108,   107,   108,    92,
      60,   105,   106,   107,   108,    74,   168,   157,    94,   154,
     155,   156,   234,   190,   160,   335,   336,   163,   164,   165,
     166,    95,    57,    57,    57,    57,    57,   279,   280,   121,
     122,   123,   124,   277,    96,    51,    61,    62,    63,    64,
      65,    66,    67,    68,    97,   121,   122,   123,   124,    98,
     278,    99,   178,    52,    53,   110,    54,    55,   113,    70,
      51,   114,    60,   121,   122,   123,   124,   123,   124,   188,
     121,   122,   123,   124,   115,   130,   116,    50,    52,    53,
     308,    54,    55,   131,   177,    50,   132,   133,   232,   233,
     121,   122,   123,   124,   118,   134,   135,    51,    61,    62,
      63,    64,    65,    66,    67,    68,   250,   121,   122,   123,
     124,   139,    51,   141,   329,    52,    53,    69,    54,    55,
      51,    70,    71,    60,   140,   246,   142,   150,   118,   118,
      52,    53,   264,    54,    55,   161,    56,   119,   101,   102,
     193,    54,    55,   167,    56,   293,   169,   120,   171,   296,
     121,   122,   123,   124,   172,   175,   180,   299,    51,    61,
      62,    63,    64,    65,    66,    67,    68,    60,   173,   179,
       4,   196,   183,   184,   186,   187,    52,    53,   110,    54,
      55,   197,    70,   126,   121,   122,   123,   124,   157,   189,
     195,   326,    60,   209,   207,   214,   121,   122,   123,   124,
     210,    60,    51,    61,    62,    63,    64,    65,    66,    67,
      68,   220,   221,   222,   223,   224,   205,   263,   215,   228,
      52,    53,   110,    54,    55,   219,    70,    51,    61,    62,
      63,    64,    65,    66,    67,    68,    51,    61,    62,    63,
      64,    65,    66,    67,    68,   101,   102,   110,    54,    55,
      60,    70,    51,   226,    52,    53,   110,    54,    55,   100,
      70,   229,   151,   235,   237,   103,   244,   238,   239,   247,
      52,    53,   249,    54,    55,   262,   177,   268,   273,   274,
     275,   281,   286,   287,   288,    51,    61,    62,    63,    64,
      65,    66,    67,    68,   289,   109,   302,   303,   309,   305,
     311,   315,   313,    52,    53,   159,    54,    55,   322,    70,
     110,     1,     2,   324,   145,   146,   147,   148,     3,     4,
       5,   327,     6,     7,     8,     9,    10,   328,   330,   331,
      11,    12,    13,   251,   252,   337,   338,   342,    14,    15,
     349,   253,   352,   348,    90,   325,   306,    16,   292,    17,
     272,   266,    18,   254,   255,   256,   257,   258,   259,   260,
     144,   301,   265,   230,   149,   121,   122,   123,   124,   267,
     333,   344,   312,   353,   276,   317,     0,   343
};

static const yytype_int16 yycheck[] =
{
       4,    94,    12,     9,   203,   205,     9,   188,    20,     3,
      20,   288,   311,   120,    75,    46,    22,    12,    34,    22,
     262,     3,    21,    22,    55,     6,    46,     8,     7,     8,
      47,   330,    75,     9,    46,    55,    21,    54,    36,   238,
     239,    75,    36,    55,   137,    22,    22,   289,   141,    21,
      22,   158,    75,   160,   161,    65,    60,    80,     0,    65,
     337,   338,    65,    13,    14,   246,    70,    48,    50,    75,
      65,   313,    75,    77,    56,   352,    73,    74,    60,    78,
      79,    80,    81,    64,   283,    43,   286,   287,    21,     6,
     197,     8,    12,    78,    79,    80,    81,    80,    81,     3,
      20,    78,    79,    80,    81,   109,    21,    75,    75,   113,
     114,   115,    80,    21,   118,   314,   315,   121,   122,   123,
     124,    75,   104,   105,   106,   107,   108,   234,   235,    78,
      79,    80,    81,    21,     8,    55,    56,    57,    58,    59,
      60,    61,    62,    63,    75,    78,    79,    80,    81,    75,
      21,    75,   134,    73,    74,    75,    76,    77,    20,    79,
      55,    20,    20,    78,    79,    80,    81,    80,    81,   151,
      78,    79,    80,    81,    20,    36,    33,    20,    73,    74,
     273,    76,    77,    75,    79,    20,    75,    40,   192,   193,
      78,    79,    80,    81,    22,    67,    44,    55,    56,    57,
      58,    59,    60,    61,    62,    63,   210,    78,    79,    80,
      81,    41,    55,    65,   307,    73,    74,    75,    76,    77,
      55,    79,    80,    20,    75,   207,    41,    33,    22,    22,
      73,    74,   214,    76,    77,    75,    79,    65,    73,    74,
      22,    76,    77,    21,    79,   249,    75,    75,    75,   253,
      78,    79,    80,    81,    35,    75,    75,   261,    55,    56,
      57,    58,    59,    60,    61,    62,    63,    20,    37,    76,
      12,    65,    75,    41,    75,    36,    73,    74,    75,    76,
      77,    75,    79,    80,    78,    79,    80,    81,    75,    21,
      33,   295,    20,    46,    20,    67,    78,    79,    80,    81,
      53,    20,    55,    56,    57,    58,    59,    60,    61,    62,
      63,    26,    27,    28,    29,    30,    37,    20,    22,    20,
      73,    74,    75,    76,    77,    34,    79,    55,    56,    57,
      58,    59,    60,    61,    62,    63,    55,    56,    57,    58,
      59,    60,    61,    62,    63,    73,    74,    75,    76,    77,
      20,    79,    55,    22,    73,    74,    75,    76,    77,    50,
      79,    75,    22,    75,    10,    56,    50,    75,    75,    22,
      73,    74,    53,    76,    77,    38,    79,     6,    21,    75,
      20,    75,    39,    38,    51,    55,    56,    57,    58,    59,
      60,    61,    62,    63,    52,    12,    75,    73,    22,    55,
      75,    75,    41,    73,    74,    75,    76,    77,    49,    79,
      75,     4,     5,    21,   105,   106,   107,   108,    11,    12,
      13,    55,    15,    16,    17,    18,    19,    21,    75,    21,
      23,    24,    25,    46,    47,    22,    51,    21,    31,    32,
      21,    54,    22,    55,    18,   292,   272,    40,   247,    42,
     226,   215,    45,    66,    67,    68,    69,    70,    71,    72,
     104,   266,   214,   187,   109,    78,    79,    80,    81,   216,
     312,   337,   276,   352,   230,   286,    -1,   333
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     4,     5,    11,    12,    13,    15,    16,    17,    18,
      19,    23,    24,    25,    31,    32,    40,    42,    45,    84,
      85,    86,    87,    88,    89,    90,    91,    92,    93,    94,
      95,    96,    97,    98,    99,   104,   109,   110,   113,   114,
     144,   145,   146,   148,     6,     8,    48,    64,     6,     8,
      20,    55,    73,    74,    76,    77,    79,   108,   115,   116,
      20,    56,    57,    58,    59,    60,    61,    62,    63,    75,
      79,    80,   108,   117,   118,   120,   121,   122,   123,   124,
     126,   128,    75,     7,     8,    34,    36,    75,    75,    43,
      85,     0,     3,   147,    75,    75,     8,    75,    75,    75,
     116,    73,    74,   116,    22,    78,    79,    80,    81,    12,
      75,   108,   118,    20,    20,    20,    33,   118,    22,    65,
      75,    78,    79,    80,    81,   119,    80,   118,     3,    36,
      36,    75,    75,    40,    67,    44,    20,    65,   113,    41,
      75,    65,    41,    21,   115,   116,   116,   116,   116,   126,
      33,    22,   107,    21,   118,   118,   118,    75,    80,    75,
     118,    75,   119,   118,   118,   118,   118,    21,    21,    75,
     127,    75,    35,    37,   131,    75,   111,    79,   108,    76,
      75,   101,   113,    75,    41,   113,    75,    36,   108,    21,
      21,    21,    22,    22,   119,    33,    65,    75,   119,   119,
       9,    22,    65,    75,   129,    37,   138,    20,   106,    46,
      53,   118,   141,   142,    67,    22,   112,    73,    74,    34,
      26,    27,    28,    29,    30,   103,    22,   100,    20,    75,
     127,   107,   118,   118,    80,    75,   119,    10,    75,    75,
     129,   139,   140,   142,    50,   134,   108,    22,   105,    53,
     118,    46,    47,    54,    66,    67,    68,    69,    70,    71,
      72,   143,    38,    20,   108,   124,   111,   131,     6,    20,
      46,    55,   101,    21,    75,    20,   138,    21,    21,   119,
     119,    75,    65,    75,   129,   129,    39,    38,    51,    52,
     132,   107,   106,   118,    47,    54,   118,    46,    55,   118,
     141,   112,    75,    73,   102,    55,   100,    65,   113,    22,
     125,    75,   134,    41,   130,    75,   129,   140,   142,   128,
     133,   141,    49,   137,    21,   105,   118,    55,    21,   113,
      75,    21,   125,   132,   141,   129,   129,    22,    51,    46,
      55,   125,    21,   137,   133,   128,   135,   136,    55,    21,
      13,    14,    22,   136
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    83,    84,    85,    85,    85,    85,    85,    85,    85,
      85,    85,    85,    85,    85,    85,    85,    85,    85,    85,
      85,    85,    85,    85,    85,    85,    86,    87,    88,    89,
      90,    91,    92,    93,    94,    95,    96,    96,    97,    98,
      99,    99,    99,    99,   100,   100,   101,   101,   101,   101,
     101,   101,   101,   102,   103,   103,   103,   103,   104,   105,
     105,   106,   107,   107,   108,   108,   108,   108,   108,   108,
     108,   109,   110,   111,   111,   112,   112,   113,   113,   114,
     115,   115,   116,   116,   116,   116,   116,   116,   116,   117,
     117,   117,   117,   117,   118,   118,   118,   118,   118,   118,
     118,   118,   119,   119,   119,   119,   119,   120,   120,   120,
     120,   121,   121,   122,   122,   122,   122,   122,   123,   124,
     125,   125,   126,   126,   126,   126,   126,   127,   127,   127,
     128,   128,   129,   129,   129,   129,   129,   130,   130,   131,
     131,   132,   132,   133,   133,   134,   134,   135,   135,   135,
     136,   136,   136,   137,   137,   138,   138,   139,   139,   140,
     140,   141,   141,   141,   142,   142,   142,   142,   142,   142,
     142,   143,   143,   143,   143,   143,   143,   143,   143,   144,
     145,   146,   147,   147,   148
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     2,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     3,     2,     4,     2,     9,    10,     5,     7,
       5,     4,     9,     8,     0,     3,     5,     2,     2,     6,
       3,     7,     4,     1,     1,     1,     1,     1,     6,     0,
       3,     4,     0,     3,     1,     2,     1,     2,     1,     1,
       1,     4,     6,     3,     3,     0,     3,     3,     8,     2,
       1,     3,     3,     3,     3,     3,     3,     2,     1,     1,
       1,     1,     1,     3,     3,     3,     3,     3,     2,     1,
       1,     1,     0,     5,     3,     5,     4,     4,     4,     6,
       6,     3,     3,     1,     1,     1,     1,     1,     4,    10,
       0,     3,     1,     4,     2,     4,     3,     2,     4,     3,
       1,     3,     0,     3,     5,     4,     5,     0,     2,     0,
       2,     0,     2,     1,     3,     0,     3,     1,     2,     2,
       0,     1,     3,     0,     3,     0,     2,     1,     3,     1,
       3,     0,     1,     3,     3,     3,     4,     3,     4,     2,
       3,     1,     1,     1,     1,     1,     1,     1,     2,     7,
       2,     4,     0,     1,     5
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
#line 247 "yacc_sql.y"
  {
    std::unique_ptr<ParsedSqlNode> sql_node = std::unique_ptr<ParsedSqlNode>((yyvsp[-1].sql_node));
    sql_result->add_sql_node(std::move(sql_node));
  }
#line 1871 "yacc_sql.cpp"
    break;

  case 26:
#line 280 "yacc_sql.y"
         {
      (void)yynerrs;  // 这么写为了消除yynerrs未使用的告警。如果你有更好的方法欢迎提PR
      (yyval.sql_node) = new ParsedSqlNode(SCF_EXIT);
    }
#line 1880 "yacc_sql.cpp"
    break;

  case 27:
#line 286 "yacc_sql.y"
         {
      (yyval.sql_node) = new ParsedSqlNode(SCF_HELP);
    }
#line 1888 "yacc_sql.cpp"
    break;

  case 28:
#line 291 "yacc_sql.y"
         {
      (yyval.sql_node) = new ParsedSqlNode(SCF_SYNC);
    }
#line 1896 "yacc_sql.cpp"
    break;

  case 29:
#line 297 "yacc_sql.y"
               {
      (yyval.sql_node) = new ParsedSqlNode(SCF_BEGIN);
    }
#line 1904 "yacc_sql.cpp"
    break;

  case 30:
#line 303 "yacc_sql.y"
               {
      (yyval.sql_node) = new ParsedSqlNode(SCF_COMMIT);
    }
#line 1912 "yacc_sql.cpp"
    break;

  case 31:
#line 309 "yacc_sql.y"
                  {
      (yyval.sql_node) = new ParsedSqlNode(SCF_ROLLBACK);
    }
#line 1920 "yacc_sql.cpp"
    break;

  case 32:
#line 315 "yacc_sql.y"
                  {
      (yyval.sql_node) = new ParsedSqlNode(SCF_DROP_TABLE);
      (yyval.sql_node)->drop_table.relation_name = (yyvsp[0].string);
      free((yyvsp[0].string));
    }
#line 1930 "yacc_sql.cpp"
    break;

  case 33:
#line 322 "yacc_sql.y"
                {
      (yyval.sql_node) = new ParsedSqlNode(SCF_SHOW_TABLES);
    }
#line 1938 "yacc_sql.cpp"
    break;

  case 34:
#line 327 "yacc_sql.y"
                        {
      (yyval.sql_node) = new ParsedSqlNode(SCF_SHOW_INDEX);
      (yyval.sql_node)->show_index.relation_name = (yyvsp[0].string);
      free((yyvsp[0].string));
    }
#line 1948 "yacc_sql.cpp"
    break;

  case 35:
#line 334 "yacc_sql.y"
             {
      (yyval.sql_node) = new ParsedSqlNode(SCF_DESC_TABLE);
      (yyval.sql_node)->desc_table.relation_name = (yyvsp[0].string);
      free((yyvsp[0].string));
    }
#line 1958 "yacc_sql.cpp"
    break;

  case 36:
#line 343 "yacc_sql.y"
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
#line 1981 "yacc_sql.cpp"
    break;

  case 37:
#line 362 "yacc_sql.y"
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
#line 2004 "yacc_sql.cpp"
    break;

  case 38:
#line 384 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_DROP_INDEX);
      (yyval.sql_node)->drop_index.index_name = (yyvsp[-2].string);
      (yyval.sql_node)->drop_index.relation_name = (yyvsp[0].string);
      free((yyvsp[-2].string));
      free((yyvsp[0].string));
    }
#line 2016 "yacc_sql.cpp"
    break;

  case 39:
#line 394 "yacc_sql.y"
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
#line 2036 "yacc_sql.cpp"
    break;

  case 40:
#line 412 "yacc_sql.y"
     {
        (yyval.sql_node) = new ParsedSqlNode(SCF_CREATE_TABLE_SELECT);
        CreateTableSelectSqlNode &create_table_select = (yyval.sql_node)->create_table_select;
        create_table_select.relation_name = (yyvsp[-2].string);
        free((yyvsp[-2].string));

        create_table_select.selection = (yyvsp[0].sql_node)->selection;
        delete (yyvsp[0].sql_node);
     }
#line 2050 "yacc_sql.cpp"
    break;

  case 41:
#line 422 "yacc_sql.y"
       {
          (yyval.sql_node) = new ParsedSqlNode(SCF_CREATE_TABLE_SELECT);
          CreateTableSelectSqlNode &create_table_select = (yyval.sql_node)->create_table_select;
          create_table_select.relation_name = (yyvsp[-1].string);
          free((yyvsp[-1].string));

          create_table_select.selection = (yyvsp[0].sql_node)->selection;
          delete (yyvsp[0].sql_node);
       }
#line 2064 "yacc_sql.cpp"
    break;

  case 42:
#line 432 "yacc_sql.y"
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
#line 2088 "yacc_sql.cpp"
    break;

  case 43:
#line 452 "yacc_sql.y"
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
#line 2112 "yacc_sql.cpp"
    break;

  case 44:
#line 474 "yacc_sql.y"
    {
      (yyval.attr_infos) = nullptr;
    }
#line 2120 "yacc_sql.cpp"
    break;

  case 45:
#line 478 "yacc_sql.y"
    {
      if ((yyvsp[0].attr_infos) != nullptr) {
        (yyval.attr_infos) = (yyvsp[0].attr_infos);
      } else {
        (yyval.attr_infos) = new std::vector<AttrInfoSqlNode>;
      }
      (yyval.attr_infos)->emplace_back(*(yyvsp[-1].attr_info));
      delete (yyvsp[-1].attr_info);
    }
#line 2134 "yacc_sql.cpp"
    break;

  case 46:
#line 491 "yacc_sql.y"
    {
      (yyval.attr_info) = new AttrInfoSqlNode;
      (yyval.attr_info)->type = (AttrType)(yyvsp[-3].number);
      (yyval.attr_info)->name = (yyvsp[-4].string);
      (yyval.attr_info)->length = (yyvsp[-1].number);
      (yyval.attr_info)->nullable = true;
      free((yyvsp[-4].string));
    }
#line 2147 "yacc_sql.cpp"
    break;

  case 47:
#line 500 "yacc_sql.y"
    {
      (yyval.attr_info) = new AttrInfoSqlNode;
      (yyval.attr_info)->type = (AttrType)TEXTS;
      (yyval.attr_info)->name = (yyvsp[-1].string);
      (yyval.attr_info)->length = 12;
      free((yyvsp[-1].string));
    }
#line 2159 "yacc_sql.cpp"
    break;

  case 48:
#line 508 "yacc_sql.y"
    {
      (yyval.attr_info) = new AttrInfoSqlNode;
      (yyval.attr_info)->type = (AttrType)(yyvsp[0].number);
      (yyval.attr_info)->name = (yyvsp[-1].string);
      (yyval.attr_info)->length = 4;
      (yyval.attr_info)->nullable = true;
      free((yyvsp[-1].string));
    }
#line 2172 "yacc_sql.cpp"
    break;

  case 49:
#line 517 "yacc_sql.y"
    {
        (yyval.attr_info) = new AttrInfoSqlNode;
        (yyval.attr_info)->type = (AttrType)(yyvsp[-4].number);
        (yyval.attr_info)->name = (yyvsp[-5].string);
        (yyval.attr_info)->length = (yyvsp[-2].number);
        (yyval.attr_info)->nullable = true;
        free((yyvsp[-5].string));
    }
#line 2185 "yacc_sql.cpp"
    break;

  case 50:
#line 526 "yacc_sql.y"
    {
        (yyval.attr_info) = new AttrInfoSqlNode;
        (yyval.attr_info)->type = (AttrType)(yyvsp[-1].number);
        (yyval.attr_info)->name = (yyvsp[-2].string);
        (yyval.attr_info)->length = 4;
        (yyval.attr_info)->nullable = true;
        free((yyvsp[-2].string));
    }
#line 2198 "yacc_sql.cpp"
    break;

  case 51:
#line 535 "yacc_sql.y"
    {
      (yyval.attr_info) = new AttrInfoSqlNode;
      (yyval.attr_info)->type = (AttrType)(yyvsp[-5].number);
      (yyval.attr_info)->name = (yyvsp[-6].string);
      (yyval.attr_info)->length = (yyvsp[-3].number);
      (yyval.attr_info)->nullable = false;
      free((yyvsp[-6].string));
    }
#line 2211 "yacc_sql.cpp"
    break;

  case 52:
#line 544 "yacc_sql.y"
    {
      (yyval.attr_info) = new AttrInfoSqlNode;
      (yyval.attr_info)->type = (AttrType)(yyvsp[-2].number);
      (yyval.attr_info)->name = (yyvsp[-3].string);
      (yyval.attr_info)->length = 4;
      (yyval.attr_info)->nullable = false;
      free((yyvsp[-3].string));
    }
#line 2224 "yacc_sql.cpp"
    break;

  case 53:
#line 554 "yacc_sql.y"
           {(yyval.number) = (yyvsp[0].number);}
#line 2230 "yacc_sql.cpp"
    break;

  case 54:
#line 557 "yacc_sql.y"
               { (yyval.number)=INTS; }
#line 2236 "yacc_sql.cpp"
    break;

  case 55:
#line 558 "yacc_sql.y"
               { (yyval.number)=CHARS; }
#line 2242 "yacc_sql.cpp"
    break;

  case 56:
#line 559 "yacc_sql.y"
               { (yyval.number)=FLOATS; }
#line 2248 "yacc_sql.cpp"
    break;

  case 57:
#line 560 "yacc_sql.y"
               { (yyval.number)=DATES; }
#line 2254 "yacc_sql.cpp"
    break;

  case 58:
#line 564 "yacc_sql.y"
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
#line 2271 "yacc_sql.cpp"
    break;

  case 59:
#line 579 "yacc_sql.y"
        {
	    (yyval.row_value_list) = nullptr;
	}
#line 2279 "yacc_sql.cpp"
    break;

  case 60:
#line 582 "yacc_sql.y"
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
#line 2296 "yacc_sql.cpp"
    break;

  case 61:
#line 597 "yacc_sql.y"
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
#line 2311 "yacc_sql.cpp"
    break;

  case 62:
#line 610 "yacc_sql.y"
    {
      (yyval.value_list) = nullptr;
    }
#line 2319 "yacc_sql.cpp"
    break;

  case 63:
#line 613 "yacc_sql.y"
                              {
      if ((yyvsp[0].value_list) != nullptr) {
        (yyval.value_list) = (yyvsp[0].value_list);
      } else {
        (yyval.value_list) = new std::vector<Value>;
      }
      (yyval.value_list)->emplace_back(*(yyvsp[-1].value));
      delete (yyvsp[-1].value);
    }
#line 2333 "yacc_sql.cpp"
    break;

  case 64:
#line 624 "yacc_sql.y"
           {
      (yyval.value) = new Value((int)(yyvsp[0].number));
      (yyloc) = (yylsp[0]);
    }
#line 2342 "yacc_sql.cpp"
    break;

  case 65:
#line 628 "yacc_sql.y"
                 {
      (yyval.value) = new Value(-(int)(yyvsp[0].number));
      (yyloc) = (yylsp[-1]);
    }
#line 2351 "yacc_sql.cpp"
    break;

  case 66:
#line 632 "yacc_sql.y"
            {
      (yyval.value) = new Value((float)(yyvsp[0].floats));
      (yyloc) = (yylsp[0]);
    }
#line 2360 "yacc_sql.cpp"
    break;

  case 67:
#line 636 "yacc_sql.y"
                {
      (yyval.value) = new Value(-(float)(yyvsp[0].floats));
      (yyloc) = (yylsp[-1]);
    }
#line 2369 "yacc_sql.cpp"
    break;

  case 68:
#line 640 "yacc_sql.y"
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
#line 2388 "yacc_sql.cpp"
    break;

  case 69:
#line 654 "yacc_sql.y"
          {
      char *tmp = common::substr((yyvsp[0].string),1,strlen((yyvsp[0].string))-2);
      (yyval.value) = new Value(tmp);
      free(tmp);
    }
#line 2398 "yacc_sql.cpp"
    break;

  case 70:
#line 659 "yacc_sql.y"
             {
        (yyval.value) = new Value();
    }
#line 2406 "yacc_sql.cpp"
    break;

  case 71:
#line 666 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_DELETE);
      (yyval.sql_node)->deletion.relation_name = (yyvsp[-1].string);
      if ((yyvsp[0].condition_list) != nullptr) {
        (yyval.sql_node)->deletion.conditions.swap(*(yyvsp[0].condition_list));
        delete (yyvsp[0].condition_list);
      }
      free((yyvsp[-1].string));
    }
#line 2420 "yacc_sql.cpp"
    break;

  case 72:
#line 678 "yacc_sql.y"
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
#line 2440 "yacc_sql.cpp"
    break;

  case 73:
#line 696 "yacc_sql.y"
                {
      UnaryExprSqlNode* unary = new UnaryExprSqlNode;
      unary->is_attr = false;
      unary->value = *(yyvsp[0].value);
      delete (yyvsp[0].value);

      ExprSqlNode* expr = new ExprSqlNode;
      expr->type = ExprSqlNodeType::UNARY;
      expr->unary_expr = unary;

      (yyval.update_value) = new UpdateValueNode;
      (yyval.update_value)->attribute_name = (yyvsp[-2].string);
      (yyval.update_value)->expr = expr;
      free((yyvsp[-2].string));
    }
#line 2460 "yacc_sql.cpp"
    break;

  case 74:
#line 711 "yacc_sql.y"
                       {
      (yyval.update_value) = new UpdateValueNode;
      (yyval.update_value)->attribute_name = (yyvsp[-2].string);
      (yyval.update_value)->expr = (yyvsp[0].expr);
      free((yyvsp[-2].string));
    }
#line 2471 "yacc_sql.cpp"
    break;

  case 75:
#line 720 "yacc_sql.y"
    {
      (yyval.update_value_list) = nullptr;
    }
#line 2479 "yacc_sql.cpp"
    break;

  case 76:
#line 723 "yacc_sql.y"
                                           {
      if ((yyvsp[0].update_value_list) != nullptr) {
        (yyval.update_value_list) = (yyvsp[0].update_value_list);
      } else {
        (yyval.update_value_list) = new std::vector<UpdateValueNode>;
      }
      (yyval.update_value_list)->emplace_back(*(yyvsp[-1].update_value));
      delete (yyvsp[-1].update_value);
    }
#line 2493 "yacc_sql.cpp"
    break;

  case 77:
#line 734 "yacc_sql.y"
                                 {  // function 可能出现，加上;防止读取select_attr后的非法输入
      (yyval.sql_node) = new ParsedSqlNode(SCF_SELECT);
      if ((yyvsp[-1].expr_list) != nullptr) {
        (yyval.sql_node)->selection.project_exprs.swap(*(yyvsp[-1].expr_list));
        delete (yyvsp[-1].expr_list);
      }
    }
#line 2505 "yacc_sql.cpp"
    break;

  case 78:
#line 742 "yacc_sql.y"
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
#line 2541 "yacc_sql.cpp"
    break;

  case 79:
#line 777 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_CALC);
      std::reverse((yyvsp[0].expression_list)->begin(), (yyvsp[0].expression_list)->end());
      (yyval.sql_node)->calc.expressions.swap(*(yyvsp[0].expression_list));
      delete (yyvsp[0].expression_list);
    }
#line 2552 "yacc_sql.cpp"
    break;

  case 80:
#line 787 "yacc_sql.y"
    {
      (yyval.expression_list) = new std::vector<Expression*>;
      (yyval.expression_list)->emplace_back((yyvsp[0].expression));
    }
#line 2561 "yacc_sql.cpp"
    break;

  case 81:
#line 792 "yacc_sql.y"
    {
      if ((yyvsp[0].expression_list) != nullptr) {
        (yyval.expression_list) = (yyvsp[0].expression_list);
      } else {
        (yyval.expression_list) = new std::vector<Expression *>;
      }
      (yyval.expression_list)->emplace_back((yyvsp[-2].expression));
    }
#line 2574 "yacc_sql.cpp"
    break;

  case 82:
#line 802 "yacc_sql.y"
                              {
      (yyval.expression) = create_arithmetic_expression(ArithmeticExpr::Type::ADD, (yyvsp[-2].expression), (yyvsp[0].expression), sql_string, &(yyloc));
    }
#line 2582 "yacc_sql.cpp"
    break;

  case 83:
#line 805 "yacc_sql.y"
                                {
      (yyval.expression) = create_arithmetic_expression(ArithmeticExpr::Type::SUB, (yyvsp[-2].expression), (yyvsp[0].expression), sql_string, &(yyloc));
    }
#line 2590 "yacc_sql.cpp"
    break;

  case 84:
#line 808 "yacc_sql.y"
                                {
      (yyval.expression) = create_arithmetic_expression(ArithmeticExpr::Type::MUL, (yyvsp[-2].expression), (yyvsp[0].expression), sql_string, &(yyloc));
    }
#line 2598 "yacc_sql.cpp"
    break;

  case 85:
#line 811 "yacc_sql.y"
                                {
      (yyval.expression) = create_arithmetic_expression(ArithmeticExpr::Type::DIV, (yyvsp[-2].expression), (yyvsp[0].expression), sql_string, &(yyloc));
    }
#line 2606 "yacc_sql.cpp"
    break;

  case 86:
#line 814 "yacc_sql.y"
                               {
      (yyval.expression) = (yyvsp[-1].expression);
      (yyval.expression)->set_name(token_name(sql_string, &(yyloc)));
    }
#line 2615 "yacc_sql.cpp"
    break;

  case 87:
#line 818 "yacc_sql.y"
                                  {
      (yyval.expression) = create_arithmetic_expression(ArithmeticExpr::Type::NEGATIVE, (yyvsp[0].expression), nullptr, sql_string, &(yyloc));
    }
#line 2623 "yacc_sql.cpp"
    break;

  case 88:
#line 821 "yacc_sql.y"
            {
      (yyval.expression) = new ValueExpr(*(yyvsp[0].value));
      (yyval.expression)->set_name(token_name(sql_string, &(yyloc)));
      delete (yyvsp[0].value);
    }
#line 2633 "yacc_sql.cpp"
    break;

  case 89:
#line 832 "yacc_sql.y"
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
#line 2650 "yacc_sql.cpp"
    break;

  case 90:
#line 844 "yacc_sql.y"
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
#line 2667 "yacc_sql.cpp"
    break;

  case 91:
#line 856 "yacc_sql.y"
                {
      (yyval.expr) = (yyvsp[0].expr);
    }
#line 2675 "yacc_sql.cpp"
    break;

  case 92:
#line 859 "yacc_sql.y"
                     {
      (yyval.expr) = (yyvsp[0].expr);
    }
#line 2683 "yacc_sql.cpp"
    break;

  case 93:
#line 862 "yacc_sql.y"
                         {
      (yyvsp[-1].expr)->with_brace = true;
      (yyval.expr) = (yyvsp[-1].expr);
    }
#line 2692 "yacc_sql.cpp"
    break;

  case 94:
#line 870 "yacc_sql.y"
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
#line 2709 "yacc_sql.cpp"
    break;

  case 95:
#line 882 "yacc_sql.y"
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
#line 2726 "yacc_sql.cpp"
    break;

  case 96:
#line 894 "yacc_sql.y"
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
#line 2743 "yacc_sql.cpp"
    break;

  case 97:
#line 906 "yacc_sql.y"
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
#line 2760 "yacc_sql.cpp"
    break;

  case 98:
#line 918 "yacc_sql.y"
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
#line 2786 "yacc_sql.cpp"
    break;

  case 99:
#line 939 "yacc_sql.y"
                 { (yyval.expr) = (yyvsp[0].expr); }
#line 2792 "yacc_sql.cpp"
    break;

  case 100:
#line 940 "yacc_sql.y"
                 { (yyval.expr) = (yyvsp[0].expr); }
#line 2798 "yacc_sql.cpp"
    break;

  case 101:
#line 941 "yacc_sql.y"
                    { (yyval.expr) = (yyvsp[0].expr); }
#line 2804 "yacc_sql.cpp"
    break;

  case 102:
#line 947 "yacc_sql.y"
    {
      (yyval.expr_list) = nullptr;
    }
#line 2812 "yacc_sql.cpp"
    break;

  case 103:
#line 950 "yacc_sql.y"
                                 {
      if ((yyvsp[0].expr_list) != nullptr) {
       (yyval.expr_list) = (yyvsp[0].expr_list);
      } else {
        (yyval.expr_list) = new std::vector<ExprSqlNode *>;
      }

      RelAttrSqlNode attr;
      attr.relation_name  = (yyvsp[-3].string);
      attr.attribute_name = "*";

      UnaryExprSqlNode* unary = new UnaryExprSqlNode;
      unary->is_attr = true;
      unary->attr = attr;

      ExprSqlNode* expr = new ExprSqlNode;
      expr->type = ExprSqlNodeType::UNARY;
      expr->unary_expr = unary;

      (yyval.expr_list)->emplace_back(expr);
    }
#line 2838 "yacc_sql.cpp"
    break;

  case 104:
#line 971 "yacc_sql.y"
                           {
      if ((yyvsp[0].expr_list) != nullptr) {
        (yyval.expr_list) = (yyvsp[0].expr_list);
      } else {
        (yyval.expr_list) = new std::vector<ExprSqlNode *>;
      }

      (yyval.expr_list)->emplace_back((yyvsp[-1].expr));
    }
#line 2852 "yacc_sql.cpp"
    break;

  case 105:
#line 980 "yacc_sql.y"
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
#line 2867 "yacc_sql.cpp"
    break;

  case 106:
#line 990 "yacc_sql.y"
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
#line 2882 "yacc_sql.cpp"
    break;

  case 107:
#line 1003 "yacc_sql.y"
                              {
      FuncExprSqlNode* func = new FuncExprSqlNode;
      func->type = FuncType::FUNC_LENGTH;
      func->exprs.emplace_back((yyvsp[-1].expr));

      ExprSqlNode* expr = new ExprSqlNode;
      expr->type = ExprSqlNodeType::FUNCTION;
      expr->func_expr = func;
      (yyval.expr) = expr;
    }
#line 2897 "yacc_sql.cpp"
    break;

  case 108:
#line 1013 "yacc_sql.y"
                               {
      FuncExprSqlNode* func = new FuncExprSqlNode;
      func->type = FuncType::FUNC_ROUND;
      func->exprs.emplace_back((yyvsp[-1].expr));

      ExprSqlNode* expr = new ExprSqlNode;
      expr->type = ExprSqlNodeType::FUNCTION;
      expr->func_expr = func;
      (yyval.expr) = expr;
    }
#line 2912 "yacc_sql.cpp"
    break;

  case 109:
#line 1023 "yacc_sql.y"
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
#line 2928 "yacc_sql.cpp"
    break;

  case 110:
#line 1034 "yacc_sql.y"
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
#line 2944 "yacc_sql.cpp"
    break;

  case 111:
#line 1048 "yacc_sql.y"
                               {
      AggrExprSqlNode* aggr = new AggrExprSqlNode;
      aggr->type = (yyvsp[-2].aggr_func_type);
      aggr->expr = (yyvsp[-1].expr);

      ExprSqlNode* expr = new ExprSqlNode;
      expr->type = ExprSqlNodeType::AGGREGATION;
      expr->aggr_expr = aggr;
      (yyval.expr) = expr;
    }
#line 2959 "yacc_sql.cpp"
    break;

  case 112:
#line 1058 "yacc_sql.y"
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
#line 2989 "yacc_sql.cpp"
    break;

  case 113:
#line 1086 "yacc_sql.y"
             {
      (yyval.aggr_func_type) = AggrFuncType::AGGR_MAX;
    }
#line 2997 "yacc_sql.cpp"
    break;

  case 114:
#line 1089 "yacc_sql.y"
               {
      (yyval.aggr_func_type) = AggrFuncType::AGGR_MIN;
    }
#line 3005 "yacc_sql.cpp"
    break;

  case 115:
#line 1092 "yacc_sql.y"
               {
      (yyval.aggr_func_type) = AggrFuncType::AGGR_SUM;
    }
#line 3013 "yacc_sql.cpp"
    break;

  case 116:
#line 1095 "yacc_sql.y"
               {
      (yyval.aggr_func_type) = AggrFuncType::AGGR_AVG;
    }
#line 3021 "yacc_sql.cpp"
    break;

  case 117:
#line 1098 "yacc_sql.y"
                 {
      (yyval.aggr_func_type) = AggrFuncType::AGGR_COUNT;
    }
#line 3029 "yacc_sql.cpp"
    break;

  case 118:
#line 1106 "yacc_sql.y"
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
#line 3049 "yacc_sql.cpp"
    break;

  case 119:
#line 1125 "yacc_sql.y"
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
#line 3093 "yacc_sql.cpp"
    break;

  case 120:
#line 1168 "yacc_sql.y"
    {
      (yyval.rel_index_attr_list) = nullptr;
    }
#line 3101 "yacc_sql.cpp"
    break;

  case 121:
#line 1171 "yacc_sql.y"
                               {
      if ((yyvsp[0].rel_index_attr_list) != nullptr) {
        (yyval.rel_index_attr_list) = (yyvsp[0].rel_index_attr_list);
      } else {
        (yyval.rel_index_attr_list) = new std::vector<string>;
      }

      (yyval.rel_index_attr_list)->emplace_back((yyvsp[-1].string));
      free((yyvsp[-1].string));
    }
#line 3116 "yacc_sql.cpp"
    break;

  case 122:
#line 1183 "yacc_sql.y"
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
#line 3137 "yacc_sql.cpp"
    break;

  case 123:
#line 1199 "yacc_sql.y"
                           {
      RelAttrSqlNode attr;
      attr.relation_name  = (yyvsp[-3].string);
      attr.attribute_name = "*";

      UnaryExprSqlNode* unary = new UnaryExprSqlNode;
      unary->is_attr = true;
      unary->attr = attr;

      ExprSqlNode* expr = new ExprSqlNode;
      expr->type = ExprSqlNodeType::UNARY;
      expr->unary_expr = unary;
      if ((yyvsp[0].expr_list) != nullptr) {
         (yyval.expr_list) = (yyvsp[0].expr_list);
      } else {
        (yyval.expr_list) = new std::vector<ExprSqlNode*>;
      }
      (yyval.expr_list)->emplace_back(expr);
    }
#line 3161 "yacc_sql.cpp"
    break;

  case 124:
#line 1218 "yacc_sql.y"
                     {
      if ((yyvsp[0].expr_list) != nullptr) {
        (yyval.expr_list) = (yyvsp[0].expr_list);
      } else {
        (yyval.expr_list) = new std::vector<ExprSqlNode*>;
      }
      (yyval.expr_list)->emplace_back((yyvsp[-1].expr));
    }
#line 3174 "yacc_sql.cpp"
    break;

  case 125:
#line 1226 "yacc_sql.y"
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
#line 3189 "yacc_sql.cpp"
    break;

  case 126:
#line 1236 "yacc_sql.y"
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
#line 3204 "yacc_sql.cpp"
    break;

  case 127:
#line 1249 "yacc_sql.y"
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
#line 3219 "yacc_sql.cpp"
    break;

  case 128:
#line 1259 "yacc_sql.y"
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
#line 3235 "yacc_sql.cpp"
    break;

  case 129:
#line 1270 "yacc_sql.y"
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
#line 3251 "yacc_sql.cpp"
    break;

  case 130:
#line 1284 "yacc_sql.y"
       {
      (yyval.rel_attr) = new RelAttrSqlNode;
      (yyval.rel_attr)->attribute_name = (yyvsp[0].string);
      free((yyvsp[0].string));
    }
#line 3261 "yacc_sql.cpp"
    break;

  case 131:
#line 1289 "yacc_sql.y"
                {
      (yyval.rel_attr) = new RelAttrSqlNode;
      (yyval.rel_attr)->relation_name  = (yyvsp[-2].string);
      (yyval.rel_attr)->attribute_name = (yyvsp[0].string);
      free((yyvsp[-2].string));
      free((yyvsp[0].string));
    }
#line 3273 "yacc_sql.cpp"
    break;

  case 132:
#line 1317 "yacc_sql.y"
    {
      (yyval.relation_list) = nullptr;
    }
#line 3281 "yacc_sql.cpp"
    break;

  case 133:
#line 1320 "yacc_sql.y"
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
#line 3296 "yacc_sql.cpp"
    break;

  case 134:
#line 1330 "yacc_sql.y"
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
#line 3312 "yacc_sql.cpp"
    break;

  case 135:
#line 1341 "yacc_sql.y"
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
#line 3328 "yacc_sql.cpp"
    break;

  case 136:
#line 1352 "yacc_sql.y"
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
#line 3349 "yacc_sql.cpp"
    break;

  case 137:
#line 1370 "yacc_sql.y"
                    {
       (yyval.condition_list) = nullptr;
    }
#line 3357 "yacc_sql.cpp"
    break;

  case 138:
#line 1373 "yacc_sql.y"
                            {
       (yyval.condition_list) = (yyvsp[0].condition_list);
	}
#line 3365 "yacc_sql.cpp"
    break;

  case 139:
#line 1379 "yacc_sql.y"
    {
      (yyval.condition_list) = nullptr;
    }
#line 3373 "yacc_sql.cpp"
    break;

  case 140:
#line 1382 "yacc_sql.y"
                           {
      (yyval.condition_list) = (yyvsp[0].condition_list);  
    }
#line 3381 "yacc_sql.cpp"
    break;

  case 141:
#line 1389 "yacc_sql.y"
    {
      (yyval.condition_list) = nullptr;
    }
#line 3389 "yacc_sql.cpp"
    break;

  case 142:
#line 1392 "yacc_sql.y"
                            {
      (yyval.condition_list) = (yyvsp[0].condition_list);
    }
#line 3397 "yacc_sql.cpp"
    break;

  case 143:
#line 1399 "yacc_sql.y"
    {
        (yyval.rel_attr_list) = new std::vector<RelAttrSqlNode>;
        (yyval.rel_attr_list)->emplace_back(*(yyvsp[0].rel_attr));
        delete (yyvsp[0].rel_attr);
    }
#line 3407 "yacc_sql.cpp"
    break;

  case 144:
#line 1405 "yacc_sql.y"
        {
        (yyval.rel_attr_list) = (yyvsp[0].rel_attr_list);
        (yyval.rel_attr_list)->emplace_back(*(yyvsp[-2].rel_attr));
        delete (yyvsp[-2].rel_attr);
	}
#line 3417 "yacc_sql.cpp"
    break;

  case 145:
#line 1413 "yacc_sql.y"
    {
      (yyval.rel_attr_list) = nullptr;
    }
#line 3425 "yacc_sql.cpp"
    break;

  case 146:
#line 1416 "yacc_sql.y"
                          {
      (yyval.rel_attr_list) = (yyvsp[0].rel_attr_list);
      std::reverse((yyval.rel_attr_list)->begin(), (yyval.rel_attr_list)->end());
    }
#line 3434 "yacc_sql.cpp"
    break;

  case 147:
#line 1424 "yacc_sql.y"
        {
		(yyval.order_attr) = new OrderBySqlNode;
		(yyval.order_attr)->attribute = *(yyvsp[0].rel_attr);
		(yyval.order_attr)->is_asc = true;

		delete (yyvsp[0].rel_attr);
	}
#line 3446 "yacc_sql.cpp"
    break;

  case 148:
#line 1433 "yacc_sql.y"
        {
		(yyval.order_attr) = new OrderBySqlNode;
        (yyval.order_attr)->attribute = *(yyvsp[-1].rel_attr);
      	(yyval.order_attr)->is_asc = true;

      	delete (yyvsp[-1].rel_attr);
	}
#line 3458 "yacc_sql.cpp"
    break;

  case 149:
#line 1442 "yacc_sql.y"
        {
		(yyval.order_attr) = new OrderBySqlNode;
        (yyval.order_attr)->attribute = *(yyvsp[-1].rel_attr);
      	(yyval.order_attr)->is_asc = false;

      	delete (yyvsp[-1].rel_attr);
	}
#line 3470 "yacc_sql.cpp"
    break;

  case 150:
#line 1452 "yacc_sql.y"
        {
        (yyval.order_attr_list) = nullptr;
	}
#line 3478 "yacc_sql.cpp"
    break;

  case 151:
#line 1456 "yacc_sql.y"
    {
        (yyval.order_attr_list) = new std::vector<OrderBySqlNode>;
        (yyval.order_attr_list)->emplace_back(*(yyvsp[0].order_attr));
        delete (yyvsp[0].order_attr);
    }
#line 3488 "yacc_sql.cpp"
    break;

  case 152:
#line 1462 "yacc_sql.y"
        {
        (yyval.order_attr_list) = (yyvsp[0].order_attr_list);
        (yyval.order_attr_list)->emplace_back(*(yyvsp[-2].order_attr));
        delete (yyvsp[-2].order_attr);
	}
#line 3498 "yacc_sql.cpp"
    break;

  case 153:
#line 1470 "yacc_sql.y"
    {
      (yyval.order_attr_list) = nullptr;
    }
#line 3506 "yacc_sql.cpp"
    break;

  case 154:
#line 1473 "yacc_sql.y"
                         {
      (yyval.order_attr_list) = (yyvsp[0].order_attr_list);
      std::reverse((yyval.order_attr_list)->begin(), (yyval.order_attr_list)->end());
    }
#line 3515 "yacc_sql.cpp"
    break;

  case 155:
#line 1481 "yacc_sql.y"
    {
      (yyval.expr) = nullptr;
    }
#line 3523 "yacc_sql.cpp"
    break;

  case 156:
#line 1484 "yacc_sql.y"
                         {
      (yyval.expr) = (yyvsp[0].expr);
    }
#line 3531 "yacc_sql.cpp"
    break;

  case 157:
#line 1491 "yacc_sql.y"
     {
       (yyval.expr) = (yyvsp[0].expr);
     }
#line 3539 "yacc_sql.cpp"
    break;

  case 158:
#line 1495 "yacc_sql.y"
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
#line 3555 "yacc_sql.cpp"
    break;

  case 159:
#line 1509 "yacc_sql.y"
     {
       ExprSqlNode* expr = new ExprSqlNode;
       expr->type = ExprSqlNodeType::CONDITION;
       expr->condition_expr = (yyvsp[0].condition);
       (yyval.expr) = expr;
     }
#line 3566 "yacc_sql.cpp"
    break;

  case 160:
#line 1516 "yacc_sql.y"
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
#line 3586 "yacc_sql.cpp"
    break;

  case 161:
#line 1534 "yacc_sql.y"
    {
      (yyval.condition_list) = nullptr;
    }
#line 3594 "yacc_sql.cpp"
    break;

  case 162:
#line 1537 "yacc_sql.y"
                {
      (yyval.condition_list) = new std::vector<ConditionSqlNode>;
      (yyval.condition_list)->emplace_back(*(yyvsp[0].condition));
      delete (yyvsp[0].condition);
    }
#line 3604 "yacc_sql.cpp"
    break;

  case 163:
#line 1542 "yacc_sql.y"
                                   {
      (yyval.condition_list) = (yyvsp[0].condition_list);
      (yyval.condition_list)->emplace_back(*(yyvsp[-2].condition));
      delete (yyvsp[-2].condition);
    }
#line 3614 "yacc_sql.cpp"
    break;

  case 164:
#line 1551 "yacc_sql.y"
    {
      (yyval.condition) = new ConditionSqlNode;
      (yyval.condition)->left = (yyvsp[-2].expr);
      (yyval.condition)->comp = (yyvsp[-1].comp);
      (yyval.condition)->right = (yyvsp[0].expr);
    }
#line 3625 "yacc_sql.cpp"
    break;

  case 165:
#line 1558 "yacc_sql.y"
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
#line 3646 "yacc_sql.cpp"
    break;

  case 166:
#line 1575 "yacc_sql.y"
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
#line 3667 "yacc_sql.cpp"
    break;

  case 167:
#line 1592 "yacc_sql.y"
    {
      (yyval.condition) = new ConditionSqlNode;
      (yyval.condition)->left = (yyvsp[-2].expr);
      (yyval.condition)->comp = IN_OP;
      (yyval.condition)->right = (yyvsp[0].expr);
    }
#line 3678 "yacc_sql.cpp"
    break;

  case 168:
#line 1599 "yacc_sql.y"
    {
      (yyval.condition) = new ConditionSqlNode;
      (yyval.condition)->left = (yyvsp[-3].expr);
      (yyval.condition)->comp = NOT_IN_OP;
      (yyval.condition)->right = (yyvsp[0].expr);
    }
#line 3689 "yacc_sql.cpp"
    break;

  case 169:
#line 1606 "yacc_sql.y"
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
#line 3711 "yacc_sql.cpp"
    break;

  case 170:
#line 1624 "yacc_sql.y"
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
#line 3733 "yacc_sql.cpp"
    break;

  case 171:
#line 1644 "yacc_sql.y"
         { (yyval.comp) = EQUAL_TO; }
#line 3739 "yacc_sql.cpp"
    break;

  case 172:
#line 1645 "yacc_sql.y"
         { (yyval.comp) = LESS_THAN; }
#line 3745 "yacc_sql.cpp"
    break;

  case 173:
#line 1646 "yacc_sql.y"
         { (yyval.comp) = GREAT_THAN; }
#line 3751 "yacc_sql.cpp"
    break;

  case 174:
#line 1647 "yacc_sql.y"
         { (yyval.comp) = LESS_EQUAL; }
#line 3757 "yacc_sql.cpp"
    break;

  case 175:
#line 1648 "yacc_sql.y"
         { (yyval.comp) = GREAT_EQUAL; }
#line 3763 "yacc_sql.cpp"
    break;

  case 176:
#line 1649 "yacc_sql.y"
         { (yyval.comp) = NOT_EQUAL; }
#line 3769 "yacc_sql.cpp"
    break;

  case 177:
#line 1650 "yacc_sql.y"
           { (yyval.comp) = LIKE_OP; }
#line 3775 "yacc_sql.cpp"
    break;

  case 178:
#line 1651 "yacc_sql.y"
               { (yyval.comp) = NOT_LIKE_OP; }
#line 3781 "yacc_sql.cpp"
    break;

  case 179:
#line 1656 "yacc_sql.y"
    {
      char *tmp_file_name = common::substr((yyvsp[-3].string), 1, strlen((yyvsp[-3].string)) - 2);
      
      (yyval.sql_node) = new ParsedSqlNode(SCF_LOAD_DATA);
      (yyval.sql_node)->load_data.relation_name = (yyvsp[0].string);
      (yyval.sql_node)->load_data.file_name = tmp_file_name;
      free((yyvsp[0].string));
      free(tmp_file_name);
    }
#line 3795 "yacc_sql.cpp"
    break;

  case 180:
#line 1669 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_EXPLAIN);
      (yyval.sql_node)->explain.sql_node = std::unique_ptr<ParsedSqlNode>((yyvsp[0].sql_node));
    }
#line 3804 "yacc_sql.cpp"
    break;

  case 181:
#line 1677 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_SET_VARIABLE);
      (yyval.sql_node)->set_variable.name  = (yyvsp[-2].string);
      (yyval.sql_node)->set_variable.value = *(yyvsp[0].value);
      free((yyvsp[-2].string));
      delete (yyvsp[0].value);
    }
#line 3816 "yacc_sql.cpp"
    break;

  case 184:
#line 1692 "yacc_sql.y"
    {
        (yyval.sql_node) = new ParsedSqlNode(SCF_CREATE_VIEW);
        CreateViewSqlNode &create_view = (yyval.sql_node)->create_view;
        create_view.relation_name = (yyvsp[-2].string);
        free((yyvsp[-2].string));

        create_view.selection = (yyvsp[0].sql_node)->selection;
        delete (yyvsp[0].sql_node);
    }
#line 3830 "yacc_sql.cpp"
    break;


#line 3834 "yacc_sql.cpp"

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
#line 1702 "yacc_sql.y"

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
