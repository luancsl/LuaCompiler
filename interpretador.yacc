%{
#include <stdio.h>
#include "tabela.h"
#include "arvore.h"

int yylex(void);
void yyerror(char *);

pilha_contexto *pilha;

%}

%token PRINT NUMBER ID END IF ELSEIF ELSE WHILE FOR THEN DO TRUE FALSE NIL FUNCTION EXPR ATTR ADD SUB
%left '+' '-'
%left '*' '/'
%%


program:
			
	program expr		            {}
	|
	;

expr:
    Literal                         {}
    |attr                           {}
    |Call                           {}
    |Operator                       {}
    |bloco                          {}
    |'(' expr ')'		            { $$ = $2; }
	;   

bloco: 
	Initbloco			            { tabela *contexto = criar_contexto(topo_pilha(pilha));
				                    pilha = empilhar_contexto(pilha, contexto);}

    expr END	                    { printf("novo Bloco"); imprimir_contexto(topo_pilha(pilha));
                                    desempilhar_contexto(&pilha); }
	;

Initbloco:
    function                        {}
    |if                             {}
    |while                          {}
    |for                            {}
    ;

ArgList:
                                    {}
    |expr                           {}
    |ArgList ',' expr               {}
    ;

ParamList:
                                    {}
    |ID                             {}
    |ParamList ',' ID               {}
    ;

ElseifList:
                                    {}
    |ElseifList ELSEIF expr THEN    {}
    ;

Call:
    ID                              {printf("chamadaa de id"); simbolo * s = localizar_simbolo(topo_pilha(pilha), (char *) $1);
				                    if(s == NULL){
					                    yyerror("Identificador não declarado");
				                    }else  {
					                    no_arvore *n = criar_no_expressao(ID, s, NULL);
					                    $$ = (int) n;
				                    }}
    |ID '(' ArgList ')'             {printf("chamada de funcao");}
    ;

function:
    FUNCTION ID '(' ParamList ')'   {printf("declaracao de funcao");}
    ;

else:
                                    {}
    |ELSE                           {}
    ;
if:
    IF expr THEN ElseifList else    {printf("declaracao if");}
    ;
while:
    WHILE expr DO                   {printf("declaracao while");}
    ;
    
for:
    FOR expr ',' expr DO            {printf("declaracao for simples");}
    |FOR expr ',' expr ',' expr DO  {printf("declaracao for completo");}

Literal:
    NUMBER                          {no_arvore *n = criar_no_expressao(NUMBER, (void *) $1, NULL); 
				                    $$ = (int) n;}
    |TRUE                           {}
    |FALSE                          {}
    ;

Operator:
     expr '+' expr		            { no_arvore *n = criar_no_expressao('+', (void *) $1, (void *) $3); 
				                    $$ = (int) n; }
	| expr '-' expr		            { no_arvore *n = criar_no_expressao('-', (void *) $1, (void *) $3);
                                    $$ = (int) n; }
    | expr '*' expr		            { no_arvore *n = criar_no_expressao('*', (void *) $1, (void *) $3);
                                    $$ = (int) n; }
    | expr '/' expr		            { no_arvore *n = criar_no_expressao('/', (void *) $1, (void *) $3);
                                    $$ = (int) n; }

attr: 
	ID '=' expr 		            { printf("Nova atribuicao"); simbolo * s = localizar_simbolo(topo_pilha(pilha), (char *) $1);
                                    if(s == NULL){
                                        s = criar_simbolo((char *) $1, 1); 
                                        inserir_simbolo(topo_pilha(pilha), s);
                                    }
					                no_arvore *n = criar_no_atribuicao(s, (void *) $3);
					                $$ = (int) n;
				                    }


//passa a referencia para a tabela de símbolos contextual com 
//topo_pilha(pilha) 
				 
	

%%

void yyerror(char *s) {
	fprintf(stderr, "%s\n", s);
}

int main(void) {
	pilha = NULL;
	yyparse();
	return 0;
}
