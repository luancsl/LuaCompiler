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
			
	program bloco		            {}
	|
	;

bloco: 
	Initbloco			            { tabela *contexto = criar_contexto(topo_pilha(pilha));
				                    pilha = empilhar_contexto(pilha, contexto);}

    stmts 	                    { printf("novo Bloco"); imprimir_contexto(topo_pilha(pilha));
                                    desempilhar_contexto(&pilha); }
	;

stmts: 
	stmts stmt                      {}
	| 	                            {}
	;

stmt:
	expr		                    {}
	| bloco                         {}
	| attr			                {}
	;


if:
    IF expr THEN bloco END          {printf("declaracao if");}
    ;

while:
    WHILE expr DO bloco END         {printf("declaracao while");}
    ;
    
for:
    FOR expr ',' expr DO bloco END   {printf("declaracao for simples");}
    ;

function:
    FUNCTION ID '(' Param ')'    {printf("declaracao de funcao");}
    ;

Param:
    ParamList                       {}
    |                               {}
    ;

ParamList:
    ID                              {}
    |ID ',' ParamList               {}
    ;

expr:
    Literal                         {}
    |Call                           {}
    |Operator                       {}
    |'(' expr ')'		            { $$ = $2; }
	;  
    
Literal:
    NUMBER                          {no_arvore *n = criar_no_expressao(NUMBER, (void *) $1, NULL); 
				                    $$ = (int) n;}
    ;

Call:
    ID                              {printf("chamadaa de id"); simbolo * s = localizar_simbolo(topo_pilha(pilha), (char *) $1);
				                    if(s == NULL){
					                    yyerror("Identificador não declarado");
				                    }else  {
					                    no_arvore *n = criar_no_expressao(ID, s, NULL);
					                    $$ = (int) n;
				                    }}
    |ID '(' Arg ')'             {printf("chamada de funcao");}
    ;

Arg:
    ArgList                         {}
    |                               {}
    ;

ArgList:
    expr                            {}
    |expr ',' ArgList               {}
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
