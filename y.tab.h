
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
     LAB = 277,
     GOTO = 278,
     BLOCO = 279,
     STMT = 280,
     EXPR = 281,
     ATTR = 282,
     TRUE = 283,
     FALSE = 284,
     OR = 285,
     AND = 286,
     GE = 287,
     LE = 288,
     LESS = 289,
     BIGG = 290,
     NE = 291,
     EQ = 292,
     CONC = 293,
     SUB = 294,
     ADD = 295,
     MOD = 296,
     DIV = 297,
     MUL = 298,
     NOT = 299,
     UNARY = 300
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
#define LAB 277
#define GOTO 278
#define BLOCO 279
#define STMT 280
#define EXPR 281
#define ATTR 282
#define TRUE 283
#define FALSE 284
#define OR 285
#define AND 286
#define GE 287
#define LE 288
#define LESS 289
#define BIGG 290
#define NE 291
#define EQ 292
#define CONC 293
#define SUB 294
#define ADD 295
#define MOD 296
#define DIV 297
#define MUL 298
#define NOT 299
#define UNARY 300




#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef int YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif

extern YYSTYPE yylval;


