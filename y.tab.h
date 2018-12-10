
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
     PRINT = 258,
     NUMBER = 259,
     ID = 260,
     END = 261,
     IF = 262,
     ELSEIF = 263,
     ELSE = 264,
     WHILE = 265,
     FOR = 266,
     THEN = 267,
     DO = 268,
     TRUE = 269,
     FALSE = 270,
     NIL = 271,
     FUNCTION = 272,
     EXPR = 273,
     ATTR = 274,
     ADD = 275,
     SUB = 276
   };
#endif
/* Tokens.  */
#define PRINT 258
#define NUMBER 259
#define ID 260
#define END 261
#define IF 262
#define ELSEIF 263
#define ELSE 264
#define WHILE 265
#define FOR 266
#define THEN 267
#define DO 268
#define TRUE 269
#define FALSE 270
#define NIL 271
#define FUNCTION 272
#define EXPR 273
#define ATTR 274
#define ADD 275
#define SUB 276




#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef int YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif

extern YYSTYPE yylval;


