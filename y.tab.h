
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
     NUMBER = 272,
     STRING = 273,
     ID = 274,
     T_INT = 275,
     T_REAL = 276,
     BLOCO = 277,
     STMT = 278,
     EXPR = 279,
     ATTR = 280,
     TRUE = 281,
     FALSE = 282,
     OR = 283,
     AND = 284,
     GE = 285,
     LE = 286,
     LESS = 287,
     BIGG = 288,
     NE = 289,
     EQ = 290,
     CONC = 291,
     SUB = 292,
     ADD = 293,
     MOD = 294,
     DIV = 295,
     MUL = 296,
     NOT = 297,
     UNARY = 298
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
#define NUMBER 272
#define STRING 273
#define ID 274
#define T_INT 275
#define T_REAL 276
#define BLOCO 277
#define STMT 278
#define EXPR 279
#define ATTR 280
#define TRUE 281
#define FALSE 282
#define OR 283
#define AND 284
#define GE 285
#define LE 286
#define LESS 287
#define BIGG 288
#define NE 289
#define EQ 290
#define CONC 291
#define SUB 292
#define ADD 293
#define MOD 294
#define DIV 295
#define MUL 296
#define NOT 297
#define UNARY 298




#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef int YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif

extern YYSTYPE yylval;


