/* A Bison parser, made by GNU Bison 2.3.  */

/* Skeleton interface for Bison's Yacc-like parsers in C

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
/* Line 1529 of yacc.c.  */
#line 148 "bison_code.tab.h"
	YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif

extern YYSTYPE yylval;

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

extern YYLTYPE yylloc;
