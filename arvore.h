#ifndef ARVORE_H
#define ARVORE_H

#include <string.h>
#include "tabela.h"
#include "y.tab.h"

typedef struct t_expr {
	int op; // + - / * UMINUS ID NUMERO
	int tipo; //float ou int
	void *dir, *esq;
	valor valor; // somente para interpretador
} t_expr;

//Cada construção da linguagem que será 
//compilada deverá ter um struct
typedef struct t_attr {
	simbolo *resultado;
	void *expressao;
} t_attr;

typedef struct t_ifelse {
    //int tipo; //if ou ifelse
    void *expr_cond;
    void *stmt_if;
    void *stmt_else;   
} t_ifelse;

typedef struct t_while {
    void *expr_cond;
    void *stmt_while;   
} t_while;

typedef struct t_funcao {
    simbolo *id;
    void *lista_param;
    void *stmt_funcao;
    void *expr_return;   
} t_funcao;

typedef struct t_stmts {
    void *stmts;
    void *stmt;
} t_stmts;

typedef struct t_bloco {
    void *stmt;
}t_bloco;

typedef struct t_print {
    void *expr_print;   
} t_print;


//Simula a superclasse abstrata 
typedef union valor_sintatico {
	t_expr      *v_expr;
	t_attr      *v_attr;
    t_print     *v_print;
    t_ifelse    *v_ifelse;
    t_while     *v_while;
    t_funcao    *v_funcao;
    t_bloco     *v_bloco;
    t_stmts      *v_stmts;
} valor_sintatico;

typedef struct no_arvore {
	int tipoSintatico; //expr, attr, stmt, ...
	valor_sintatico dado;
	//ponteiro para tabela de símbolos
} no_arvore;

no_arvore * criar_no_expressao(int op, void *dir, void *esq);
t_expr * criar_expressao(int op, void *dir, void *esq);

no_arvore * criar_no_atribuicao(simbolo *resultado, void *expressao);
t_attr * criar_atribuicao(simbolo *resultado, void *expressao);

no_arvore * criar_no_ifelse(void *A_expr_cond, void *A_stmt_if, void *A_stmt_else);
t_ifelse * criar_ifelse(void *A_expr_cond, void *A_stmt_if, void *A_stmt_else);

no_arvore * criar_no_while(void *A_expr_cond, void *A_stmt_while);
t_while * criar_while(void *A_expr_cond, void *A_stmt_while);

no_arvore * criar_no_funcao(simbolo *A_id, void *A_lista_param, void *A_stmt_funcao, void *A_expr_return);
t_funcao * criar_funcao(simbolo *A_id, void *A_lista_param, void *A_stmt_funcao, void *A_expr_return);

no_arvore * criar_no_stmts(void *A_stmts, void *A_stmt);
t_stmts * criar_stmts(void *A_stmts, void *A_stmt);

no_arvore * criar_no_bloco(void *A_stmt);
t_bloco * criar_bloco(void *A_stmt);

no_arvore * criar_no_print(void *A_expr_print);
t_print * criar_print(void *A_expr_print);


#endif
