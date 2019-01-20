%{
#include <stdlib.h>
#include <string.h>
void yyerror(char *);
#include "y.tab.h"
#include "tabelaNumero.h"

%}

letra	            [a-z|A-Z|_] 
digito              [0-9]
identificador	    {letra}({letra}|{digito})*
integerNumber       {digito}+
realNumber          {digito}+"."{digito}+ 

%%

"function"              {return FUNCTION;}
"if"                    {return IF;}
"elseif"                {return ELSEIF;}
"else"                  {return ELSE;}
"while"                 {return WHILE;}
"print"	                {return PRINT;}
"do"                    {return DO;}
"then"                  {return THEN;}
"io.read()"             {return READ;}

"end"                   {return END;}
"return" 				{return RETURN;}
"break"                 {return BREAK;}
"local" 				{return LOCAL;}
"nil"					{return NIL;}
"true"                  {yylval = (long int) 1;
                            return TRUE;}
"false"                 {yylval = (long int) 0;
                            return FALSE;}
"and"					{return AND;}
"or"					{return OR;}
"not"					{return NOT;}
">"                     {return BIGG;}
"<"                     {return LESS;}
"=="                    {return EQ;}
"!="					{return NE;}
"<="					{return LE;}
">="					{return GE;}
".."					{return CONC;}
"-"                     {return SUB;}
"+"                     {return ADD;}
"/"                     {return DIV;}
"*"                     {return MUL;}
"%"                     {return MOD;}
\"[^\"]*\" 			| 
\'[^\']*\'	            {return STRING;}

{realNumber}  {
	valorNumero v;
	v.fval = atof(yytext);
	yylval = (long int) criar_numero(v, T_REAL);
	return NUMBER;
}

{integerNumber}	{ 
	valorNumero v;
	v.ival = atoi(yytext);
	yylval = (long int) criar_numero(v, T_INT);
	return NUMBER;
}

{identificador}	{
			yylval = (int) strdup(yytext);
			return ID;
		}	

[-+*/=(){},]	{	return *yytext; }

[ \t\n] 	; /* skip whitespace */

. 	yyerror("invalid character");

%%
int yywrap(void) {
return 1;
}
