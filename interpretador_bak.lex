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

function    {return FUNCTION;}
for     {return FOR;}
if      {return IF;}
else    {return ELSE;}
print	{return PRINT;}
do      {return DO;}
then    {return THEN;}
end     {return END;}

{numero}+	{ yylval = atoi(yytext);
		  return NUMBER;
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
