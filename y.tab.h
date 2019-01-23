
/* A Bison parser, made by GNU Bison 2.4.1.  */

/* Skeleton interface for Bison's Yacc-like parsers in C
   
      Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003, 2004, 2005, 2006
   Free Software Foundation, Inc.
   
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


/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     NIL = 258,
     PRINT = 259,
     READ = 260,
     IF = 261,
     THEN = 262,
     ELSE = 263,
     ELSEIF = 264,
     WHILE = 265,
     DO = 266,
     END = 267,
     BREAK = 268,
     RETURN = 269,
     LOCAL = 270,
     FUNCTION = 271,
     FUNCTION_C = 272,
     NUMBER = 273,
     STRING = 274,
     ID = 275,
     T_INT = 276,
     T_REAL = 277,
     LAB = 278,
     GOTO = 279,
     BLOCO = 280,
     STMTS = 281,
     EXPR = 282,
     ATTR = 283,
     TRUE = 284,
     FALSE = 285,
     OR = 286,
     AND = 287,
     GE = 288,
     LE = 289,
     LESS = 290,
     BIGG = 291,
     NE = 292,
     EQ = 293,
     CONC = 294,
     SUB = 295,
     ADD = 296,
     MOD = 297,
     DIV = 298,
     MUL = 299,
     NOT = 300,
     UNARY = 301
   };
#endif
/* Tokens.  */
#define NIL 258
#define PRINT 259
#define READ 260
#define IF 261
#define THEN 262
#define ELSE 263
#define ELSEIF 264
#define WHILE 265
#define DO 266
#define END 267
#define BREAK 268
#define RETURN 269
#define LOCAL 270
#define FUNCTION 271
#define FUNCTION_C 272
#define NUMBER 273
#define STRING 274
#define ID 275
#define T_INT 276
#define T_REAL 277
#define LAB 278
#define GOTO 279
#define BLOCO 280
#define STMTS 281
#define EXPR 282
#define ATTR 283
#define TRUE 284
#define FALSE 285
#define OR 286
#define AND 287
#define GE 288
#define LE 289
#define LESS 290
#define BIGG 291
#define NE 292
#define EQ 293
#define CONC 294
#define SUB 295
#define ADD 296
#define MOD 297
#define DIV 298
#define MUL 299
#define NOT 300
#define UNARY 301




#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef int YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif

extern YYSTYPE yylval;


