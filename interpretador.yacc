%{
#include <stdio.h>
#include "tabela.h"
#include "tabelaNumero.h"
#include "arvore.h"
#include "codigo_intermediario.h"
#include "lista_intermediario.h"
#include "codigo_mips.h"

int yylex(void);
void yyerror(char *);

pilha_contexto *pilha;
tabela *tab_c;
lista* list;

%}

 
%token NIL
%token PRINT
%token READ
%token IF THEN ELSE ELSEIF WHILE DO END
%token BREAK   
%token RETURN
%token LOCAL
%token FUNCTION
%token NUMBER
%token STRING
%token ID 
%token T_INT
%token T_REAL
%token LAB
%token GOTO
%token BLOCO 
%token STMT
%token EXPR
%token ATTR

%token TRUE 
%token FALSE 

%left AND OR
%left EQ NE BIGG LESS LE GE
%right CONC
%left ADD SUB
%left MUL DIV MOD
%left NOT
%right '^'

%nonassoc UNARY

%%

program:
			
	program bloco		            {}
	|
	;

bloco: 
	openc stmts closec              {no_arvore *n = criar_no_bloco((void *) $2);
                                    $$ = (long int) n;}
	;

openc:
     /* empty */                    { tabela *contexto = criar_contexto(topo_pilha(pilha));
				                        pilha = empilhar_contexto(pilha, contexto);
                                    }
    ;

closec:
     /* empty */                    {/* imprimir_contexto(topo_pilha(pilha)); */
                                        desempilhar_contexto(&pilha); 
                                    }
    ;

stmts: 
	stmts stmt                      {no_arvore *n = criar_no_stmt(NULL, (void *) $2);
                                    $$ = (long int) n;}
	| 	                            {}
	;

stmt:
	expr		                    {gerar_codigo((lista *) list, (no_arvore *) $1);
                                    $$ = (long int) $1;}
    |print                          {gerar_codigo((lista *) list, (no_arvore *) $1);
                                    $$ = (long int) $1;}
    |if                             {gerar_codigo((lista *) list, (no_arvore *) $1);
                                    $$ = (long int) $1;}
    |while                          {gerar_codigo((lista *) list, (no_arvore *) $1);
                                    $$ = (long int) $1;}
    |function                       {}
	|attr			                {gerar_codigo((lista *) list, (no_arvore *) $1);
                                    $$ = (long int) $1;}
	;

expr:
    '(' expr ')'                    { $$ = $2; }
    | expr EQ  expr	                {no_arvore *n = criar_no_expressao(EQ, (void *) $1, (void *) $3); 
				                    $$ = (long int) n;}
    | expr LESS expr	            {no_arvore *n = criar_no_expressao(LESS, (void *) $1, (void *) $3); 
				                    $$ = (long int) n;}
    | expr BIGG expr	            {no_arvore *n = criar_no_expressao(BIGG, (void *) $1, (void *) $3); 
				                    $$ = (long int) n;}
    | expr NE  expr	                {no_arvore *n = criar_no_expressao(NE, (void *) $1, (void *) $3); 
				                    $$ = (long int) n;}
    | expr LE  expr	                {no_arvore *n = criar_no_expressao(LE, (void *) $1, (void *) $3); 
				                    $$ = (long int) n;}
    | expr GE  expr	                {no_arvore *n = criar_no_expressao(GE, (void *) $1, (void *) $3); 
				                    $$ = (long int) n;}
    | expr ADD expr		            { no_arvore *n = criar_no_expressao(ADD, (void *) $1, (void *) $3); 
				                    $$ = (long int) n; }
	| expr SUB expr		            { no_arvore *n = criar_no_expressao(SUB, (void *) $1, (void *) $3);
                                    $$ = (long int) n; }
    | expr MUL expr		            { no_arvore *n = criar_no_expressao(MUL, (void *) $1, (void *) $3);
                                    $$ = (long int) n; }
    | expr DIV expr		            { no_arvore *n = criar_no_expressao(DIV, (void *) $1, (void *) $3);
                                    $$ = (long int) n; }
    | expr MOD expr		            { no_arvore *n = criar_no_expressao(MOD, (void *) $1, (void *) $3);
                                    $$ = (long int) n; }
    |'-' expr %prec UNARY	        {}
    | NUMBER                        {no_arvore *n = criar_no_expressao(NUMBER, (void *) $1, NULL); 
                                    $$ = (int) n;}
    | ID                            { simbolo * s = localizar_simbolo(topo_pilha(pilha), (char *) $1);
				                    if(s == NULL){
					                    yyerror("Identificador nao declarado");
				                    }else  {
					                    no_arvore *n = criar_no_expressao(ID, s, NULL);
					                    $$ = (long int) n;}
                                    }
    | STRING                        {}
    | functioncall                  {}
    | NIL		                    {no_arvore *n = criar_no_expressao(NIL, NULL, NULL); 
				                    $$ = (long int) n;}
    | TRUE                          {no_arvore *n = criar_no_expressao(TRUE, (void *) $1, NULL); 
				                    $$ = (long int) n;}
    | FALSE                         {no_arvore *n = criar_no_expressao(FALSE, (void *) $1, NULL); 
				                    $$ = (long int) n;}
    | NOT expr	                    {no_arvore *n = criar_no_expressao(NOT, (void *) $2, NULL); 
				                    $$ = (long int) n;}
    | expr AND expr                 {no_arvore *n = criar_no_expressao(AND, (void *) $1, (void *) $3); 
				                    $$ = (long int) n;}
    | expr OR  expr                 {no_arvore *n = criar_no_expressao(OR, (void *) $1, (void *) $3); 
				                    $$ = (long int) n;}
    | READ                          {no_arvore *n = criar_no_expressao(READ, NULL, NULL); 
				                    $$ = (long int) n;}
	;  

attr: 
	ID '=' expr 		            { simbolo * s = localizar_simbolo(topo_pilha(pilha), (char *) $1);
                                    if(s == NULL){
                                        s = criar_simbolo((char *) $1, 1); 
                                        inserir_simbolo(topo_pilha(pilha), s);
                                        inserir_simbolo(tab_c, s);
                                    }
					                no_arvore *n = criar_no_atribuicao(s, (void *) $3);
					                $$ = (long int) n;
				                    }
    ;

if:
    IF expr THEN bloco END                  {no_arvore *n = criar_no_ifelse((void *) $2, (void *) $4, NULL ); 
				                            $$ = (long int) n;}
    | IF expr THEN bloco ELSE bloco END     {no_arvore *n = criar_no_ifelse((void *) $2, (void *) $4, (void *) $6); 
				                            $$ = (long int) n;}
    ;

while:
    WHILE expr DO bloco END                 {no_arvore *n = criar_no_while((void *) $2, (void *) $4); 
				                            $$ = (long int) n;}
    ;

function:
    FUNCTION ID '(' _param ')' bloco END  {}
    ;

_param:
    _paramlist                       {}
    |                               {}
    ;

_paramlist:
    ID                              {}
    |_paramlist ',' ID               {}
    ;


functioncall:
    ID '(' _arg ')'                  {}
    ;

_arg:
    _arglist                         {}
    |                               {}
    ;

_arglist:
    expr                            {}
    |_arglist ',' expr               {}
    ;

print:
    PRINT '(' expr ')'                      {no_arvore *n = criar_no_print((void *) $3); 
				                            $$ = (long int) n;} 
    ;

%%

void yyerror(char *s) {
	fprintf(stderr, "%s\n", s);
}

int main(void) {
	pilha = NULL;
    tab_c = (tabela *) malloc(sizeof(tabela));
    tab_c->pai = NULL;
    tab_c->primeiro = NULL;
    list = (lista *) init_lista();
	yyparse();
    gerar_codigo_mips(list, tab_c);
	return 0;
}
