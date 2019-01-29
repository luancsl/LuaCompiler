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
tabela *tab_f;
lista* list;
lista* list_f;

%}

 
%token NIL
%token PRINT
%token READ
%token IF THEN ELSE ELSEIF WHILE DO END
%token BREAK   
%token RETURN
%token LOCAL
%token FUNCTION
%token FUNCTION_C
%token NUMBER
%token STRING
%token ID 
%token T_INT
%token T_REAL
%token LAB
%token GOTO
%token BLOCO 
%token STMTS
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
			
	program bloco		            {$$ = $2; gerar_codigo(list, list_f, (no_arvore *) $2);}
	|                               {$$ = (long int) NULL;}
	;

bloco: 
	openc stmts closec              {$$ = $2;}
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
	stmts stmt                      {no_arvore *n = criar_no_stmts((void *) $1, (void *) $2);
                                    $$ = (long int) n;}
	| 	                            {$$ = (long int) NULL ;}
	;

stmt:
	expr		                    {$$ = (long int) $1;}
    |print                          {$$ = (long int) $1;}
    |if                             {$$ = (long int) $1;}
    |while                          {$$ = (long int) $1;}
    |function                       {$$ = (long int) $1;}
	|attr			                {$$ = (long int) $1;}
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
    | functioncall                  {$$ = (long int) $1;}
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
    FUNCTION ID '(' _param ')' bloco ret END    {simbolo *s = criar_simbolo((char *) $2, 1); 
                                                inserir_simbolo(topo_pilha(pilha), s);
                                                inserir_simbolo(tab_f, s);
                                                no_arvore *n = criar_no_funcao(s, (void *) $4, (void *) $6, (void *) $7);
                                                $$ = (long int) n;}
    ;

_param:
    _paramlist                       {$$ = (long int) $1;}
    |                                {$$ = (long int) NULL;}
    ;

_paramlist:
    ID                              {simbolo *s = criar_simbolo((char *) $1, 1); 
                                    inserir_simbolo(topo_pilha(pilha), s);
                                    inserir_simbolo(tab_c, s);
                                    $$ = (long int) s;}
    |_paramlist ',' ID              {}
    ;

ret:
    /* empty */                      {$$ = (long int) NULL;}
    | RETURN expr                    {$$ = (long int) $2;}

functioncall:
    ID '(' _arg ')'                     {simbolo * s = localizar_simbolo(tab_f, (char *) $1);
				                        if(s == NULL){
					                        yyerror("funcao nao declarada");
				                        }else  {
                                            no_arvore *n = criar_no_expressao(FUNCTION_C, s, (void *) $3);
                                            $$ = (long int) n;}}
    ;

_arg:
    _arglist                            {$$ = (long int) $1;}
    |                                   {$$ = (long int) NULL;}
    ;

_arglist:
    expr                                {$$ = (long int) $1;}
    |_arglist ',' expr                  {}
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
    tab_f = (tabela *) malloc(sizeof(tabela));
    tab_f->pai = NULL;
    tab_f->primeiro = NULL;
    list = (lista *) init_lista();
    list_f = (lista *) init_lista();
	yyparse();
    gerar_header_mips(tab_c);
    gerar_codigo_mips(list);
    gerar_end_main();
    gerar_codigo_mips(list_f);
	return 0;
}
