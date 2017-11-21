/* A Bison parser, made by GNU Bison 2.3.  */

/* Skeleton implementation for Bison's Yacc-like parsers in C

   Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003, 2004, 2005, 2006
   Free Software Foundation, Inc.

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2, or (at your option)
   any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 51 Franklin Street, Fifth Floor,
   Boston, MA 02110-1301, USA.  */

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
#define YYBISON_VERSION "2.3"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Using locations.  */
#define YYLSP_NEEDED 1



/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     END = 0,
     IF = 258,
     ELSE = 259,
     WHILE = 260,
     CLASS = 261,
     THIS = 262,
     NEW = 263,
     MAIN = 264,
     PUBLIC = 265,
     EXTENDS = 266,
     INT = 267,
     BOOL = 268,
     STRING = 269,
     SQBR_L = 270,
     SQBR_R = 271,
     RNDBR_L = 272,
     RNDBR_R = 273,
     BTBR_L = 274,
     BTBR_R = 275,
     COMMA = 276,
     DOT = 277,
     SEMICOLON = 278,
     EQ = 279,
     AND = 280,
     OR = 281,
     PLUS = 282,
     MINUS = 283,
     STAR = 284,
     LESS = 285,
     EXCL = 286,
     FALSE = 287,
     TRUE = 288,
     PRINT = 289,
     LEN = 290,
     RETURN = 291,
     NUM = 292,
     ID = 293
   };
#endif
/* Tokens.  */
#define END 0
#define IF 258
#define ELSE 259
#define WHILE 260
#define CLASS 261
#define THIS 262
#define NEW 263
#define MAIN 264
#define PUBLIC 265
#define EXTENDS 266
#define INT 267
#define BOOL 268
#define STRING 269
#define SQBR_L 270
#define SQBR_R 271
#define RNDBR_L 272
#define RNDBR_R 273
#define BTBR_L 274
#define BTBR_R 275
#define COMMA 276
#define DOT 277
#define SEMICOLON 278
#define EQ 279
#define AND 280
#define OR 281
#define PLUS 282
#define MINUS 283
#define STAR 284
#define LESS 285
#define EXCL 286
#define FALSE 287
#define TRUE 288
#define PRINT 289
#define LEN 290
#define RETURN 291
#define NUM 292
#define ID 293




/* Copy the first part of user declarations.  */
#line 2 "bison_code"

  #include <iostream>
  #include <string>
  #include "grammar.h"
  #include "treeserializer.h"

  extern "C" int yylex();

  void yyerror(const char* str)
  {
      std::cerr << "ERROR: " << str << std::endl;
  }

  TreeSerializer *ts = new TreeSerializer("./SyntaxTree.gv");


/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 1
#endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* Enabling the token table.  */
#ifndef YYTOKEN_TABLE
# define YYTOKEN_TABLE 0
#endif

#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
#line 73 "bison_code"
{
    Symbol* symbol;
    int intval;
    char* strValue;
    Program* program;
    MainClass* main_class;
    ClassDecl *class_dec;
    ClassDeclList *class_dec_list;
    VarDecl* var_dec;
    VarDeclList* var_dec_list;
    MethodDecl* method;
    MethodDeclList* method_list;
    ArgumentList* arg_list;
    Type* type;
    StatementList* statement_list;
    Statement* statement;
    ExpressionList* expression_list;
    Expression* expression;
    Symbol* id;
}
/* Line 193 of yacc.c.  */
#line 211 "bison_code.tab.c"
	YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif

#if ! defined YYLTYPE && ! defined YYLTYPE_IS_DECLARED
typedef struct YYLTYPE
{
  int first_line;
  int first_column;
  int last_line;
  int last_column;
} YYLTYPE;
# define yyltype YYLTYPE /* obsolescent; will be withdrawn */
# define YYLTYPE_IS_DECLARED 1
# define YYLTYPE_IS_TRIVIAL 1
#endif


/* Copy the second part of user declarations.  */


/* Line 216 of yacc.c.  */
#line 236 "bison_code.tab.c"

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
#elif (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
typedef signed char yytype_int8;
#else
typedef short int yytype_int8;
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
# elif ! defined YYSIZE_T && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
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
#   define YY_(msgid) dgettext ("bison-runtime", msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(msgid) msgid
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(e) ((void) (e))
#else
# define YYUSE(e) /* empty */
#endif

/* Identity function, used to suppress warnings about constant conditions.  */
#ifndef lint
# define YYID(n) (n)
#else
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static int
YYID (int i)
#else
static int
YYID (i)
    int i;
#endif
{
  return i;
}
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
#    if ! defined _ALLOCA_H && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#     ifndef _STDLIB_H
#      define _STDLIB_H 1
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's `empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (YYID (0))
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
#  if (defined __cplusplus && ! defined _STDLIB_H \
       && ! ((defined YYMALLOC || defined malloc) \
	     && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef _STDLIB_H
#    define _STDLIB_H 1
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
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
  yytype_int16 yyss;
  YYSTYPE yyvs;
    YYLTYPE yyls;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE) + sizeof (YYLTYPE)) \
      + 2 * YYSTACK_GAP_MAXIMUM)

/* Copy COUNT objects from FROM to TO.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(To, From, Count) \
      __builtin_memcpy (To, From, (Count) * sizeof (*(From)))
#  else
#   define YYCOPY(To, From, Count)		\
      do					\
	{					\
	  YYSIZE_T yyi;				\
	  for (yyi = 0; yyi < (Count); yyi++)	\
	    (To)[yyi] = (From)[yyi];		\
	}					\
      while (YYID (0))
#  endif
# endif

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack)					\
    do									\
      {									\
	YYSIZE_T yynewbytes;						\
	YYCOPY (&yyptr->Stack, Stack, yysize);				\
	Stack = &yyptr->Stack;						\
	yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
	yyptr += yynewbytes / sizeof (*yyptr);				\
      }									\
    while (YYID (0))

#endif

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  6
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   353

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  39
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  18
/* YYNRULES -- Number of rules.  */
#define YYNRULES  55
/* YYNRULES -- Number of states.  */
#define YYNSTATES  149

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   293

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
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
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint8 yyprhs[] =
{
       0,     0,     3,     6,    22,    30,    37,    40,    41,    44,
      45,    49,    52,    54,    68,    81,    94,   106,   109,   110,
     115,   118,   119,   122,   124,   128,   130,   132,   134,   138,
     146,   152,   158,   163,   171,   175,   179,   183,   187,   191,
     196,   200,   207,   209,   211,   213,   215,   217,   223,   228,
     231,   235,   238,   239,   243,   244
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int8 yyrhs[] =
{
      40,     0,    -1,    41,    43,    -1,     6,    56,    19,    10,
       9,    17,    14,    15,    16,    56,    18,    19,    52,    20,
      20,    -1,     6,    56,    44,    19,    46,    48,    20,    -1,
       6,    56,    44,    19,    48,    20,    -1,    43,    42,    -1,
      -1,    11,    56,    -1,    -1,    51,    56,    23,    -1,    46,
      45,    -1,    45,    -1,    10,    51,    56,    17,    49,    18,
      19,    46,    50,    36,    53,    23,    20,    -1,    10,    51,
      56,    17,    49,    18,    19,    50,    36,    53,    23,    20,
      -1,    10,    51,    56,    17,    49,    18,    19,    46,    36,
      53,    23,    20,    -1,    10,    51,    56,    17,    49,    18,
      19,    36,    53,    23,    20,    -1,    48,    47,    -1,    -1,
      49,    21,    51,    56,    -1,    51,    56,    -1,    -1,    50,
      52,    -1,    52,    -1,    12,    15,    16,    -1,    13,    -1,
      12,    -1,    56,    -1,    19,    50,    20,    -1,     3,    17,
      53,    18,    52,     4,    52,    -1,     5,    17,    53,    18,
      52,    -1,    34,    17,    53,    18,    23,    -1,    56,    24,
      53,    23,    -1,    56,    15,    53,    16,    24,    53,    23,
      -1,    53,    25,    53,    -1,    53,    30,    53,    -1,    53,
      27,    53,    -1,    53,    28,    53,    -1,    53,    29,    53,
      -1,    53,    15,    53,    16,    -1,    53,    22,    35,    -1,
      53,    22,    56,    17,    54,    18,    -1,    37,    -1,    33,
      -1,    32,    -1,    56,    -1,     7,    -1,     8,    12,    15,
      53,    16,    -1,     8,    56,    17,    18,    -1,    31,    53,
      -1,    17,    53,    18,    -1,    53,    55,    -1,    -1,    55,
      21,    53,    -1,    -1,    38,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   129,   129,   137,   148,   155,   165,   169,   175,   179,
     185,   193,   197,   204,   214,   223,   232,   244,   248,   254,
     258,   262,   268,   272,   280,   284,   288,   292,   300,   304,
     308,   312,   316,   320,   328,   332,   336,   340,   344,   348,
     352,   356,   360,   364,   368,   372,   376,   380,   384,   388,
     392,   400,   404,   409,   413,   418
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "END", "error", "$undefined", "IF", "ELSE", "WHILE", "CLASS", "THIS",
  "NEW", "MAIN", "PUBLIC", "EXTENDS", "INT", "BOOL", "STRING", "SQBR_L",
  "SQBR_R", "RNDBR_L", "RNDBR_R", "BTBR_L", "BTBR_R", "COMMA", "DOT",
  "SEMICOLON", "EQ", "AND", "OR", "PLUS", "MINUS", "STAR", "LESS", "EXCL",
  "FALSE", "TRUE", "PRINT", "LEN", "RETURN", "NUM", "ID", "$accept",
  "goal", "main_class", "class_dec", "class_dec_list", "extends_block",
  "var_dec", "var_dec_list", "method", "method_list", "arglist",
  "stmnt_list", "type", "statement", "expression", "expression_list",
  "expression_add", "id", 0
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[YYLEX-NUM] -- Internal token number corresponding to
   token YYLEX-NUM.  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    39,    40,    41,    42,    42,    43,    43,    44,    44,
      45,    46,    46,    47,    47,    47,    47,    48,    48,    49,
      49,    49,    50,    50,    51,    51,    51,    51,    52,    52,
      52,    52,    52,    52,    53,    53,    53,    53,    53,    53,
      53,    53,    53,    53,    53,    53,    53,    53,    53,    53,
      53,    54,    54,    55,    55,    56
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     2,    15,     7,     6,     2,     0,     2,     0,
       3,     2,     1,    13,    12,    12,    11,     2,     0,     4,
       2,     0,     2,     1,     3,     1,     1,     1,     3,     7,
       5,     5,     4,     7,     3,     3,     3,     3,     3,     4,
       3,     6,     1,     1,     1,     1,     1,     5,     4,     2,
       3,     2,     0,     3,     0,     1
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     0,     0,     7,    55,     0,     1,     2,     0,     0,
       6,     0,     9,     0,     0,     0,     0,     8,    18,     0,
      26,    25,    12,    18,     0,     0,    27,     0,     0,    11,
       0,     0,     5,    17,     0,     0,    24,     4,     0,    10,
       0,     0,     0,    21,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    20,     0,     0,     0,    23,
       0,     0,     0,     0,     0,     0,    46,     0,     0,     0,
      44,    43,    42,     0,    45,     0,    28,    22,     0,     3,
       0,     0,     0,     0,     0,    27,    19,     0,     0,     0,
      49,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    32,     0,     0,     0,     0,     0,     0,    50,
       0,     0,    40,     0,    34,    36,    37,    38,    35,    30,
      31,     0,     0,     0,     0,     0,     0,    48,    39,     0,
      52,     0,    16,     0,     0,     0,    47,    29,    54,     0,
      33,    15,     0,    14,    51,    41,    13,     0,    53
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     2,     3,    10,     7,    15,    22,    23,    33,    24,
      45,    58,    25,    59,    73,   139,   144,    74
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -53
static const yytype_int16 yypact[] =
{
       3,   -27,    23,   -53,   -53,     8,   -53,    27,    31,   -27,
     -53,    43,    39,    37,   -27,    53,    42,   -53,   -10,    61,
      78,   -53,   -53,   -10,    49,   -27,   -53,    90,    97,   -53,
      70,   -10,   -53,   -53,    35,   -27,   -53,   -53,   -27,   -53,
      76,    98,   100,   -10,     1,    68,   -27,   106,   107,     1,
     110,   114,    -5,   118,   -10,   -53,   125,   125,   102,   -53,
     125,   119,   125,   125,     2,   -27,   -53,    17,   125,   125,
     -53,   -53,   -53,   146,   -53,   162,   -53,   -53,   178,   -53,
     194,   203,   125,    13,    41,    -5,   -53,   123,   124,   219,
     -53,   125,     1,    82,   125,   125,   125,   125,   125,     1,
     120,   122,   -53,   228,   125,   111,   125,   125,   126,   -53,
     244,   144,   -53,   133,   305,    66,    66,    56,   323,   -53,
     -53,   125,   131,   253,   125,   262,   278,   -53,   -53,     1,
     125,   287,   -53,   134,   296,   139,   -53,   -53,   314,   135,
     -53,   -53,   140,   -53,   145,   -53,   -53,   125,   314
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
     -53,   -53,   -53,   -53,   -53,   -53,   -22,   101,   -53,   147,
     -53,   -52,    54,    26,     5,   -53,   -53,    -1
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -1
static const yytype_int16 yytable[] =
{
       5,    29,    20,    21,    47,    47,    48,    48,    12,     1,
      62,     4,    84,    17,    20,    21,    47,    26,    48,    63,
      49,    49,    26,     6,    34,    20,    21,     8,     4,    87,
      26,   105,    49,     9,    40,    50,    50,    41,    82,     4,
       4,    11,    26,    52,    47,    55,    48,    50,    52,   104,
      14,     4,    13,    26,    16,     4,    19,    52,    39,    31,
      49,    29,    75,    85,    86,    78,    88,    80,    81,    32,
      51,    91,    18,    89,    90,    50,    27,   106,    93,     4,
      31,    91,    85,    52,    77,    38,    53,   103,    93,    54,
      37,    52,   113,    28,    42,    97,   110,    46,    52,   114,
     115,   116,   117,   118,    52,    47,    35,    48,    65,   123,
      77,   125,   126,    36,    47,    43,    48,   112,   111,    44,
       4,    49,    76,    56,    57,   119,   131,    60,    52,   134,
      49,    77,    66,    67,    61,   138,    50,    64,   107,    79,
       4,   108,    68,   120,   127,    50,   121,   124,   129,     4,
     130,   132,   148,   145,   141,   137,    69,    70,    71,   143,
     146,    91,    72,     4,    92,    83,   147,     0,    93,     0,
      30,    94,     0,    95,    96,    97,    98,    91,     0,     0,
      99,     0,     0,     0,    93,     0,     0,    94,     0,    95,
      96,    97,    98,    91,     0,     0,   100,     0,     0,     0,
      93,     0,     0,    94,     0,    95,    96,    97,    98,    91,
     101,     0,     0,     0,     0,     0,    93,     0,    91,    94,
       0,    95,    96,    97,    98,    93,   102,     0,    94,     0,
      95,    96,    97,    98,    91,     0,     0,   109,     0,     0,
       0,    93,     0,    91,    94,     0,    95,    96,    97,    98,
      93,   122,     0,    94,     0,    95,    96,    97,    98,    91,
     128,     0,     0,     0,     0,     0,    93,     0,    91,    94,
       0,    95,    96,    97,    98,    93,   133,    91,    94,     0,
      95,    96,    97,    98,    93,   135,     0,    94,     0,    95,
      96,    97,    98,    91,   136,     0,     0,     0,     0,     0,
      93,     0,    91,    94,     0,    95,    96,    97,    98,    93,
     140,    91,    94,     0,    95,    96,    97,    98,    93,   142,
      91,    94,     0,    95,    96,    97,    98,    93,     0,    91,
      -1,     0,    95,    96,    97,    98,    93,     0,    91,    94,
       0,    95,    96,    97,    98,    93,     0,     0,     0,     0,
      95,    96,    97,    -1
};

static const yytype_int16 yycheck[] =
{
       1,    23,    12,    13,     3,     3,     5,     5,     9,     6,
      15,    38,    64,    14,    12,    13,     3,    18,     5,    24,
      19,    19,    23,     0,    25,    12,    13,    19,    38,    12,
      31,    83,    19,     6,    35,    34,    34,    38,    36,    38,
      38,    10,    43,    44,     3,    46,     5,    34,    49,    36,
      11,    38,     9,    54,    17,    38,    14,    58,    23,    10,
      19,    83,    57,    64,    65,    60,    67,    62,    63,    20,
      44,    15,    19,    68,    69,    34,    15,    36,    22,    38,
      10,    15,    83,    84,    58,    31,    18,    82,    22,    21,
      20,    92,    93,    15,    18,    29,    91,    43,    99,    94,
      95,    96,    97,    98,   105,     3,    16,     5,    54,   104,
      84,   106,   107,    16,     3,    17,     5,    35,    92,    19,
      38,    19,    20,    17,    17,    99,   121,    17,   129,   124,
      19,   105,     7,     8,    20,   130,    34,    19,    15,    20,
      38,    17,    17,    23,    18,    34,    24,    36,     4,    38,
      17,    20,   147,    18,    20,   129,    31,    32,    33,    20,
      20,    15,    37,    38,    18,    64,    21,    -1,    22,    -1,
      23,    25,    -1,    27,    28,    29,    30,    15,    -1,    -1,
      18,    -1,    -1,    -1,    22,    -1,    -1,    25,    -1,    27,
      28,    29,    30,    15,    -1,    -1,    18,    -1,    -1,    -1,
      22,    -1,    -1,    25,    -1,    27,    28,    29,    30,    15,
      16,    -1,    -1,    -1,    -1,    -1,    22,    -1,    15,    25,
      -1,    27,    28,    29,    30,    22,    23,    -1,    25,    -1,
      27,    28,    29,    30,    15,    -1,    -1,    18,    -1,    -1,
      -1,    22,    -1,    15,    25,    -1,    27,    28,    29,    30,
      22,    23,    -1,    25,    -1,    27,    28,    29,    30,    15,
      16,    -1,    -1,    -1,    -1,    -1,    22,    -1,    15,    25,
      -1,    27,    28,    29,    30,    22,    23,    15,    25,    -1,
      27,    28,    29,    30,    22,    23,    -1,    25,    -1,    27,
      28,    29,    30,    15,    16,    -1,    -1,    -1,    -1,    -1,
      22,    -1,    15,    25,    -1,    27,    28,    29,    30,    22,
      23,    15,    25,    -1,    27,    28,    29,    30,    22,    23,
      15,    25,    -1,    27,    28,    29,    30,    22,    -1,    15,
      25,    -1,    27,    28,    29,    30,    22,    -1,    15,    25,
      -1,    27,    28,    29,    30,    22,    -1,    -1,    -1,    -1,
      27,    28,    29,    30
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     6,    40,    41,    38,    56,     0,    43,    19,     6,
      42,    10,    56,     9,    11,    44,    17,    56,    19,    14,
      12,    13,    45,    46,    48,    51,    56,    15,    15,    45,
      48,    10,    20,    47,    56,    16,    16,    20,    51,    23,
      56,    56,    18,    17,    19,    49,    51,     3,     5,    19,
      34,    52,    56,    18,    21,    56,    17,    17,    50,    52,
      17,    20,    15,    24,    19,    51,     7,     8,    17,    31,
      32,    33,    37,    53,    56,    53,    20,    52,    53,    20,
      53,    53,    36,    46,    50,    56,    56,    12,    56,    53,
      53,    15,    18,    22,    25,    27,    28,    29,    30,    18,
      18,    16,    23,    53,    36,    50,    36,    15,    17,    18,
      53,    52,    35,    56,    53,    53,    53,    53,    53,    52,
      23,    24,    23,    53,    36,    53,    53,    18,    16,     4,
      17,    53,    20,    23,    53,    23,    16,    52,    53,    54,
      23,    20,    23,    20,    55,    18,    20,    21,    53
};

#define yyerrok		(yyerrstatus = 0)
#define yyclearin	(yychar = YYEMPTY)
#define YYEMPTY		(-2)
#define YYEOF		0

#define YYACCEPT	goto yyacceptlab
#define YYABORT		goto yyabortlab
#define YYERROR		goto yyerrorlab


/* Like YYERROR except do call yyerror.  This remains here temporarily
   to ease the transition to the new meaning of YYERROR, for GCC.
   Once GCC version 2 has supplanted version 1, this can go.  */

#define YYFAIL		goto yyerrlab

#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)					\
do								\
  if (yychar == YYEMPTY && yylen == 1)				\
    {								\
      yychar = (Token);						\
      yylval = (Value);						\
      yytoken = YYTRANSLATE (yychar);				\
      YYPOPSTACK (1);						\
      goto yybackup;						\
    }								\
  else								\
    {								\
      yyerror (YY_("syntax error: cannot back up")); \
      YYERROR;							\
    }								\
while (YYID (0))


#define YYTERROR	1
#define YYERRCODE	256


/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#define YYRHSLOC(Rhs, K) ((Rhs)[K])
#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)				\
    do									\
      if (YYID (N))                                                    \
	{								\
	  (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;	\
	  (Current).first_column = YYRHSLOC (Rhs, 1).first_column;	\
	  (Current).last_line    = YYRHSLOC (Rhs, N).last_line;		\
	  (Current).last_column  = YYRHSLOC (Rhs, N).last_column;	\
	}								\
      else								\
	{								\
	  (Current).first_line   = (Current).last_line   =		\
	    YYRHSLOC (Rhs, 0).last_line;				\
	  (Current).first_column = (Current).last_column =		\
	    YYRHSLOC (Rhs, 0).last_column;				\
	}								\
    while (YYID (0))
#endif


/* YY_LOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

#ifndef YY_LOCATION_PRINT
# if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL
#  define YY_LOCATION_PRINT(File, Loc)			\
     fprintf (File, "%d.%d-%d.%d",			\
	      (Loc).first_line, (Loc).first_column,	\
	      (Loc).last_line,  (Loc).last_column)
# else
#  define YY_LOCATION_PRINT(File, Loc) ((void) 0)
# endif
#endif


/* YYLEX -- calling `yylex' with the right arguments.  */

#ifdef YYLEX_PARAM
# define YYLEX yylex (YYLEX_PARAM)
#else
# define YYLEX yylex ()
#endif

/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)			\
do {						\
  if (yydebug)					\
    YYFPRINTF Args;				\
} while (YYID (0))

# define YY_SYMBOL_PRINT(Title, Type, Value, Location)			  \
do {									  \
  if (yydebug)								  \
    {									  \
      YYFPRINTF (stderr, "%s ", Title);					  \
      yy_symbol_print (stderr,						  \
		  Type, Value, Location); \
      YYFPRINTF (stderr, "\n");						  \
    }									  \
} while (YYID (0))


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp)
#else
static void
yy_symbol_value_print (yyoutput, yytype, yyvaluep, yylocationp)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
    YYLTYPE const * const yylocationp;
#endif
{
  if (!yyvaluep)
    return;
  YYUSE (yylocationp);
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# else
  YYUSE (yyoutput);
# endif
  switch (yytype)
    {
      default:
	break;
    }
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp)
#else
static void
yy_symbol_print (yyoutput, yytype, yyvaluep, yylocationp)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
    YYLTYPE const * const yylocationp;
#endif
{
  if (yytype < YYNTOKENS)
    YYFPRINTF (yyoutput, "token %s (", yytname[yytype]);
  else
    YYFPRINTF (yyoutput, "nterm %s (", yytname[yytype]);

  YY_LOCATION_PRINT (yyoutput, *yylocationp);
  YYFPRINTF (yyoutput, ": ");
  yy_symbol_value_print (yyoutput, yytype, yyvaluep, yylocationp);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_stack_print (yytype_int16 *bottom, yytype_int16 *top)
#else
static void
yy_stack_print (bottom, top)
    yytype_int16 *bottom;
    yytype_int16 *top;
#endif
{
  YYFPRINTF (stderr, "Stack now");
  for (; bottom <= top; ++bottom)
    YYFPRINTF (stderr, " %d", *bottom);
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)				\
do {								\
  if (yydebug)							\
    yy_stack_print ((Bottom), (Top));				\
} while (YYID (0))


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_reduce_print (YYSTYPE *yyvsp, YYLTYPE *yylsp, int yyrule)
#else
static void
yy_reduce_print (yyvsp, yylsp, yyrule)
    YYSTYPE *yyvsp;
    YYLTYPE *yylsp;
    int yyrule;
#endif
{
  int yynrhs = yyr2[yyrule];
  int yyi;
  unsigned long int yylno = yyrline[yyrule];
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
	     yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      fprintf (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr, yyrhs[yyprhs[yyrule] + yyi],
		       &(yyvsp[(yyi + 1) - (yynrhs)])
		       , &(yylsp[(yyi + 1) - (yynrhs)])		       );
      fprintf (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)		\
do {					\
  if (yydebug)				\
    yy_reduce_print (yyvsp, yylsp, Rule); \
} while (YYID (0))

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
#ifndef	YYINITDEPTH
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
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static YYSIZE_T
yystrlen (const char *yystr)
#else
static YYSIZE_T
yystrlen (yystr)
    const char *yystr;
#endif
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
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static char *
yystpcpy (char *yydest, const char *yysrc)
#else
static char *
yystpcpy (yydest, yysrc)
    char *yydest;
    const char *yysrc;
#endif
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

/* Copy into YYRESULT an error message about the unexpected token
   YYCHAR while in state YYSTATE.  Return the number of bytes copied,
   including the terminating null byte.  If YYRESULT is null, do not
   copy anything; just return the number of bytes that would be
   copied.  As a special case, return 0 if an ordinary "syntax error"
   message will do.  Return YYSIZE_MAXIMUM if overflow occurs during
   size calculation.  */
static YYSIZE_T
yysyntax_error (char *yyresult, int yystate, int yychar)
{
  int yyn = yypact[yystate];

  if (! (YYPACT_NINF < yyn && yyn <= YYLAST))
    return 0;
  else
    {
      int yytype = YYTRANSLATE (yychar);
      YYSIZE_T yysize0 = yytnamerr (0, yytname[yytype]);
      YYSIZE_T yysize = yysize0;
      YYSIZE_T yysize1;
      int yysize_overflow = 0;
      enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
      char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
      int yyx;

# if 0
      /* This is so xgettext sees the translatable formats that are
	 constructed on the fly.  */
      YY_("syntax error, unexpected %s");
      YY_("syntax error, unexpected %s, expecting %s");
      YY_("syntax error, unexpected %s, expecting %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s");
# endif
      char *yyfmt;
      char const *yyf;
      static char const yyunexpected[] = "syntax error, unexpected %s";
      static char const yyexpecting[] = ", expecting %s";
      static char const yyor[] = " or %s";
      char yyformat[sizeof yyunexpected
		    + sizeof yyexpecting - 1
		    + ((YYERROR_VERBOSE_ARGS_MAXIMUM - 2)
		       * (sizeof yyor - 1))];
      char const *yyprefix = yyexpecting;

      /* Start YYX at -YYN if negative to avoid negative indexes in
	 YYCHECK.  */
      int yyxbegin = yyn < 0 ? -yyn : 0;

      /* Stay within bounds of both yycheck and yytname.  */
      int yychecklim = YYLAST - yyn + 1;
      int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
      int yycount = 1;

      yyarg[0] = yytname[yytype];
      yyfmt = yystpcpy (yyformat, yyunexpected);

      for (yyx = yyxbegin; yyx < yyxend; ++yyx)
	if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR)
	  {
	    if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
	      {
		yycount = 1;
		yysize = yysize0;
		yyformat[sizeof yyunexpected - 1] = '\0';
		break;
	      }
	    yyarg[yycount++] = yytname[yyx];
	    yysize1 = yysize + yytnamerr (0, yytname[yyx]);
	    yysize_overflow |= (yysize1 < yysize);
	    yysize = yysize1;
	    yyfmt = yystpcpy (yyfmt, yyprefix);
	    yyprefix = yyor;
	  }

      yyf = YY_(yyformat);
      yysize1 = yysize + yystrlen (yyf);
      yysize_overflow |= (yysize1 < yysize);
      yysize = yysize1;

      if (yysize_overflow)
	return YYSIZE_MAXIMUM;

      if (yyresult)
	{
	  /* Avoid sprintf, as that infringes on the user's name space.
	     Don't have undefined behavior even if the translation
	     produced a string with the wrong number of "%s"s.  */
	  char *yyp = yyresult;
	  int yyi = 0;
	  while ((*yyp = *yyf) != '\0')
	    {
	      if (*yyp == '%' && yyf[1] == 's' && yyi < yycount)
		{
		  yyp += yytnamerr (yyp, yyarg[yyi++]);
		  yyf += 2;
		}
	      else
		{
		  yyp++;
		  yyf++;
		}
	    }
	}
      return yysize;
    }
}
#endif /* YYERROR_VERBOSE */


/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep, YYLTYPE *yylocationp)
#else
static void
yydestruct (yymsg, yytype, yyvaluep, yylocationp)
    const char *yymsg;
    int yytype;
    YYSTYPE *yyvaluep;
    YYLTYPE *yylocationp;
#endif
{
  YYUSE (yyvaluep);
  YYUSE (yylocationp);

  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  switch (yytype)
    {

      default:
	break;
    }
}


/* Prevent warnings from -Wmissing-prototypes.  */

#ifdef YYPARSE_PARAM
#if defined __STDC__ || defined __cplusplus
int yyparse (void *YYPARSE_PARAM);
#else
int yyparse ();
#endif
#else /* ! YYPARSE_PARAM */
#if defined __STDC__ || defined __cplusplus
int yyparse (void);
#else
int yyparse ();
#endif
#endif /* ! YYPARSE_PARAM */



/* The look-ahead symbol.  */
int yychar;

/* The semantic value of the look-ahead symbol.  */
YYSTYPE yylval;

/* Number of syntax errors so far.  */
int yynerrs;
/* Location data for the look-ahead symbol.  */
YYLTYPE yylloc;



/*----------.
| yyparse.  |
`----------*/

#ifdef YYPARSE_PARAM
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void *YYPARSE_PARAM)
#else
int
yyparse (YYPARSE_PARAM)
    void *YYPARSE_PARAM;
#endif
#else /* ! YYPARSE_PARAM */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void)
#else
int
yyparse ()

#endif
#endif
{
  
  int yystate;
  int yyn;
  int yyresult;
  /* Number of tokens to shift before error messages enabled.  */
  int yyerrstatus;
  /* Look-ahead token as an internal (translated) token number.  */
  int yytoken = 0;
#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

  /* Three stacks and their tools:
     `yyss': related to states,
     `yyvs': related to semantic values,
     `yyls': related to locations.

     Refer to the stacks thru separate pointers, to allow yyoverflow
     to reallocate them elsewhere.  */

  /* The state stack.  */
  yytype_int16 yyssa[YYINITDEPTH];
  yytype_int16 *yyss = yyssa;
  yytype_int16 *yyssp;

  /* The semantic value stack.  */
  YYSTYPE yyvsa[YYINITDEPTH];
  YYSTYPE *yyvs = yyvsa;
  YYSTYPE *yyvsp;

  /* The location stack.  */
  YYLTYPE yylsa[YYINITDEPTH];
  YYLTYPE *yyls = yylsa;
  YYLTYPE *yylsp;
  /* The locations where the error started and ended.  */
  YYLTYPE yyerror_range[2];

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N), yylsp -= (N))

  YYSIZE_T yystacksize = YYINITDEPTH;

  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;
  YYLTYPE yyloc;

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY;		/* Cause a token to be read.  */

  /* Initialize stack pointers.
     Waste one element of value and location stack
     so that they stay on the same level as the state stack.
     The wasted elements are never initialized.  */

  yyssp = yyss;
  yyvsp = yyvs;
  yylsp = yyls;
#if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL
  /* Initialize the default location before parsing starts.  */
  yylloc.first_line   = yylloc.last_line   = 1;
  yylloc.first_column = yylloc.last_column = 0;
#endif

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
	YYSTACK_RELOCATE (yyss);
	YYSTACK_RELOCATE (yyvs);
	YYSTACK_RELOCATE (yyls);
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

  goto yybackup;

/*-----------.
| yybackup.  |
`-----------*/
yybackup:

  /* Do appropriate processing given the current state.  Read a
     look-ahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to look-ahead token.  */
  yyn = yypact[yystate];
  if (yyn == YYPACT_NINF)
    goto yydefault;

  /* Not known => get a look-ahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid look-ahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = YYLEX;
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
      if (yyn == 0 || yyn == YYTABLE_NINF)
	goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  if (yyn == YYFINAL)
    YYACCEPT;

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the look-ahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

  /* Discard the shifted token unless it is eof.  */
  if (yychar != YYEOF)
    yychar = YYEMPTY;

  yystate = yyn;
  *++yyvsp = yylval;
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
     `$$ = $1'.

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
#line 131 "bison_code"
    { (yyval.program) = new Program((yyvsp[(1) - (2)].main_class), (yyvsp[(2) - (2)].class_dec_list)); (yyval.program)->accept(ts); ;}
    break;

  case 3:
#line 142 "bison_code"
    { (yyval.main_class) = new MainClass((yyvsp[(2) - (15)].id), (yyvsp[(10) - (15)].id), (yyvsp[(13) - (15)].statement)); ;}
    break;

  case 4:
#line 153 "bison_code"
    { (yyval.class_dec) = new ClassDecl((yyvsp[(2) - (7)].id), (yyvsp[(3) - (7)].id), (yyvsp[(5) - (7)].var_dec_list), (yyvsp[(6) - (7)].method_list)); ;}
    break;

  case 5:
#line 159 "bison_code"
    { (yyval.class_dec) = new ClassDecl((yyvsp[(2) - (6)].id), (yyvsp[(3) - (6)].id), nullptr, (yyvsp[(5) - (6)].method_list)); ;}
    break;

  case 6:
#line 167 "bison_code"
    { (yyval.class_dec_list) = new ClassDeclList((yyvsp[(2) - (2)].class_dec), (yyvsp[(1) - (2)].class_dec_list)); ;}
    break;

  case 7:
#line 169 "bison_code"
    { (yyval.class_dec_list) = nullptr; ;}
    break;

  case 8:
#line 177 "bison_code"
    { (yyval.id) = (yyvsp[(2) - (2)].id); ;}
    break;

  case 9:
#line 179 "bison_code"
    { (yyval.id) = nullptr; ;}
    break;

  case 10:
#line 187 "bison_code"
    { (yyval.var_dec) = new VarDecl((yyvsp[(1) - (3)].type), (yyvsp[(2) - (3)].id)); ;}
    break;

  case 11:
#line 195 "bison_code"
    { (yyval.var_dec_list) = new VarDeclList((yyvsp[(2) - (2)].var_dec), (yyvsp[(1) - (2)].var_dec_list)); ;}
    break;

  case 12:
#line 199 "bison_code"
    { (yyval.var_dec_list) = new VarDeclList((yyvsp[(1) - (1)].var_dec), nullptr); ;}
    break;

  case 13:
#line 212 "bison_code"
    { (yyval.method) = new MethodDecl((yyvsp[(2) - (13)].type), (yyvsp[(3) - (13)].id), (yyvsp[(5) - (13)].arg_list), (yyvsp[(8) - (13)].var_dec_list), (yyvsp[(9) - (13)].statement_list), (yyvsp[(11) - (13)].expression)); ;}
    break;

  case 14:
#line 221 "bison_code"
    { (yyval.method) = new MethodDecl((yyvsp[(2) - (12)].type), (yyvsp[(3) - (12)].id), (yyvsp[(5) - (12)].arg_list), nullptr, (yyvsp[(8) - (12)].statement_list), (yyvsp[(10) - (12)].expression)); ;}
    break;

  case 15:
#line 230 "bison_code"
    { (yyval.method) = new MethodDecl((yyvsp[(2) - (12)].type), (yyvsp[(3) - (12)].id), (yyvsp[(5) - (12)].arg_list), (yyvsp[(8) - (12)].var_dec_list), nullptr, (yyvsp[(10) - (12)].expression)); ;}
    break;

  case 16:
#line 238 "bison_code"
    { (yyval.method) = new MethodDecl((yyvsp[(2) - (11)].type), (yyvsp[(3) - (11)].id), (yyvsp[(5) - (11)].arg_list), nullptr, nullptr, (yyvsp[(9) - (11)].expression)); ;}
    break;

  case 17:
#line 246 "bison_code"
    { (yyval.method_list) = new MethodDeclList((yyvsp[(2) - (2)].method), (yyvsp[(1) - (2)].method_list)); ;}
    break;

  case 18:
#line 248 "bison_code"
    { (yyval.method_list) = nullptr; ;}
    break;

  case 19:
#line 256 "bison_code"
    { (yyval.arg_list) = new ArgumentList((yyvsp[(3) - (4)].type), (yyvsp[(4) - (4)].id), (yyvsp[(1) - (4)].arg_list)); ;}
    break;

  case 20:
#line 260 "bison_code"
    { (yyval.arg_list) = new ArgumentList((yyvsp[(1) - (2)].type), (yyvsp[(2) - (2)].id), nullptr); ;}
    break;

  case 21:
#line 262 "bison_code"
    { (yyval.arg_list) = nullptr; ;}
    break;

  case 22:
#line 270 "bison_code"
    { (yyval.statement_list) = new StatementList((yyvsp[(2) - (2)].statement), (yyvsp[(1) - (2)].statement_list)); ;}
    break;

  case 23:
#line 274 "bison_code"
    { (yyval.statement_list) = new StatementList((yyvsp[(1) - (1)].statement), nullptr);; ;}
    break;

  case 24:
#line 282 "bison_code"
    { (yyval.type) = new BasicType(INT_ARRAY_); ;}
    break;

  case 25:
#line 286 "bison_code"
    { (yyval.type) = new BasicType(BOOL_); ;}
    break;

  case 26:
#line 290 "bison_code"
    { (yyval.type) = new BasicType(INT_); ;}
    break;

  case 27:
#line 294 "bison_code"
    { (yyval.type) = new ClassType((Symbol *)((yyvsp[(1) - (1)].id))); ;}
    break;

  case 28:
#line 302 "bison_code"
    { (yyval.statement) = (yyvsp[(2) - (3)].statement_list); ;}
    break;

  case 29:
#line 306 "bison_code"
    { (yyval.statement) = new IfStatement((yyvsp[(3) - (7)].expression), (yyvsp[(5) - (7)].statement), (yyvsp[(7) - (7)].statement)); ;}
    break;

  case 30:
#line 310 "bison_code"
    { (yyval.statement) = new WhileStatement((yyvsp[(3) - (5)].expression), (yyvsp[(5) - (5)].statement)); ;}
    break;

  case 31:
#line 314 "bison_code"
    { (yyval.statement) = new PrintStatement((yyvsp[(3) - (5)].expression)); ;}
    break;

  case 32:
#line 318 "bison_code"
    { (yyval.statement) = new AssignStatement((yyvsp[(1) - (4)].id), (yyvsp[(3) - (4)].expression)); ;}
    break;

  case 33:
#line 322 "bison_code"
    { (yyval.statement) = new AssignSubscriptStatement((yyvsp[(1) - (7)].id), (yyvsp[(3) - (7)].expression), (yyvsp[(6) - (7)].expression)); ;}
    break;

  case 34:
#line 330 "bison_code"
    { (yyval.expression) = new BinaryExpression((yyvsp[(1) - (3)].expression), BinaryOperator::AND_, (yyvsp[(3) - (3)].expression)); ;}
    break;

  case 35:
#line 334 "bison_code"
    { (yyval.expression) = new BinaryExpression((yyvsp[(1) - (3)].expression), BinaryOperator::LESS_, (yyvsp[(3) - (3)].expression)); ;}
    break;

  case 36:
#line 338 "bison_code"
    { (yyval.expression) = new BinaryExpression((yyvsp[(1) - (3)].expression), BinaryOperator::ADD_, (yyvsp[(3) - (3)].expression)); ;}
    break;

  case 37:
#line 342 "bison_code"
    { (yyval.expression) = new BinaryExpression((yyvsp[(1) - (3)].expression), BinaryOperator::SUB_, (yyvsp[(3) - (3)].expression)); ;}
    break;

  case 38:
#line 346 "bison_code"
    { (yyval.expression) = new BinaryExpression((yyvsp[(1) - (3)].expression), BinaryOperator::MUL_, (yyvsp[(3) - (3)].expression)); ;}
    break;

  case 39:
#line 350 "bison_code"
    { (yyval.expression) = new SubscriptExpression((yyvsp[(1) - (4)].expression), (yyvsp[(3) - (4)].expression)); ;}
    break;

  case 40:
#line 354 "bison_code"
    { (yyval.expression) = new LengthExpression((yyvsp[(1) - (3)].expression)); ;}
    break;

  case 41:
#line 358 "bison_code"
    { (yyval.expression) = new MethodCallExpression((yyvsp[(1) - (6)].expression), (yyvsp[(3) - (6)].id), (yyvsp[(5) - (6)].expression_list)); ;}
    break;

  case 42:
#line 362 "bison_code"
    { (yyval.expression) = new IntExpression(yylval.intval); ;}
    break;

  case 43:
#line 366 "bison_code"
    { (yyval.expression) = new BoolExpression(true); ;}
    break;

  case 44:
#line 370 "bison_code"
    { (yyval.expression) = new BoolExpression(false); ;}
    break;

  case 45:
#line 374 "bison_code"
    { (yyval.expression) = new IdExpression((yyvsp[(1) - (1)].id)); ;}
    break;

  case 46:
#line 378 "bison_code"
    { (yyval.expression) = new ThisExpression(); ;}
    break;

  case 47:
#line 382 "bison_code"
    { (yyval.expression) = new NewIntArrayExpression((yyvsp[(4) - (5)].expression)); ;}
    break;

  case 48:
#line 386 "bison_code"
    { (yyval.expression) = new NewObjectExpression((yyvsp[(2) - (4)].id)); ;}
    break;

  case 49:
#line 390 "bison_code"
    { (yyval.expression) = new NegationExpression((yyvsp[(2) - (2)].expression)); ;}
    break;

  case 50:
#line 394 "bison_code"
    { (yyval.expression) = (yyvsp[(2) - (3)].expression); ;}
    break;

  case 51:
#line 402 "bison_code"
    { (yyval.expression_list) = new ExpressionList((yyvsp[(1) - (2)].expression), (yyvsp[(2) - (2)].expression_list)); ;}
    break;

  case 52:
#line 404 "bison_code"
    { (yyval.expression_list) = nullptr;;}
    break;

  case 53:
#line 411 "bison_code"
    { (yyval.expression_list) = new ExpressionList((yyvsp[(3) - (3)].expression), (yyvsp[(1) - (3)].expression_list)); ;}
    break;

  case 54:
#line 413 "bison_code"
    { (yyval.expression_list) = nullptr;;}
    break;

  case 55:
#line 420 "bison_code"
    { (yyval.id) = new Symbol(yyval.strValue);;}
    break;


/* Line 1267 of yacc.c.  */
#line 1881 "bison_code.tab.c"
      default: break;
    }
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;
  *++yylsp = yyloc;

  /* Now `shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*------------------------------------.
| yyerrlab -- here on detecting error |
`------------------------------------*/
yyerrlab:
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
      {
	YYSIZE_T yysize = yysyntax_error (0, yystate, yychar);
	if (yymsg_alloc < yysize && yymsg_alloc < YYSTACK_ALLOC_MAXIMUM)
	  {
	    YYSIZE_T yyalloc = 2 * yysize;
	    if (! (yysize <= yyalloc && yyalloc <= YYSTACK_ALLOC_MAXIMUM))
	      yyalloc = YYSTACK_ALLOC_MAXIMUM;
	    if (yymsg != yymsgbuf)
	      YYSTACK_FREE (yymsg);
	    yymsg = (char *) YYSTACK_ALLOC (yyalloc);
	    if (yymsg)
	      yymsg_alloc = yyalloc;
	    else
	      {
		yymsg = yymsgbuf;
		yymsg_alloc = sizeof yymsgbuf;
	      }
	  }

	if (0 < yysize && yysize <= yymsg_alloc)
	  {
	    (void) yysyntax_error (yymsg, yystate, yychar);
	    yyerror (yymsg);
	  }
	else
	  {
	    yyerror (YY_("syntax error"));
	    if (yysize != 0)
	      goto yyexhaustedlab;
	  }
      }
#endif
    }

  yyerror_range[0] = yylloc;

  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse look-ahead token after an
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
		      yytoken, &yylval, &yylloc);
	  yychar = YYEMPTY;
	}
    }

  /* Else will try to reuse look-ahead token after shifting the error
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

  yyerror_range[0] = yylsp[1-yylen];
  /* Do not reclaim the symbols of the rule which action triggered
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
  yyerrstatus = 3;	/* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (yyn != YYPACT_NINF)
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

      yyerror_range[0] = *yylsp;
      yydestruct ("Error: popping",
		  yystos[yystate], yyvsp, yylsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  if (yyn == YYFINAL)
    YYACCEPT;

  *++yyvsp = yylval;

  yyerror_range[1] = yylloc;
  /* Using YYLLOC is tempting, but would change the location of
     the look-ahead.  YYLOC is available though.  */
  YYLLOC_DEFAULT (yyloc, (yyerror_range - 1), 2);
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

#ifndef yyoverflow
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEOF && yychar != YYEMPTY)
     yydestruct ("Cleanup: discarding lookahead",
		 yytoken, &yylval, &yylloc);
  /* Do not reclaim the symbols of the rule which action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
		  yystos[*yyssp], yyvsp, yylsp);
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
  /* Make sure YYID is used.  */
  return YYID (yyresult);
}


#line 423 "bison_code"



int main(void) {
    //extern int yydebug;
    //yydebug = 1;
    yyparse();
    delete ts;
}

