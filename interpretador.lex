%{
#include <stdlib.h>
#include <string.h>
void yyerror(char *);
#include "y.tab.h"
%}

letra	[a-z|A-Z|_] 
numero	[0-9]
identificador	{letra}({letra}|{numero})*

%%



{numero}+	{ yylval = atoi(yytext);
		  return NUMBER;
		}


int		{	yylval = INT;
			return TYPE;
		}
float		{
			yylval = FLOAT;
			return TYPE;
		}

PRINT		{	return PRINT; 
		}

{identificador}	{
			yylval = (int) strdup(yytext);
			return ID;
		}	

[-+*/=(){};]	{	return *yytext; }




[ \t\n] 	; /* skip whitespace */
. 	yyerror("invalid character");
%%
int yywrap(void) {
return 1;
}
