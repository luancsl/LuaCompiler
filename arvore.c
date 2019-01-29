#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "arvore.h"
#include "y.tab.h"


no_arvore * criar_no_expressao(int op, void *dir, void *esq) {
	no_arvore *novo = (no_arvore *)  malloc(sizeof(no_arvore));
	novo->tipoSintatico = EXPR;
	novo->dado.v_expr =  criar_expressao(op, dir, esq);
	return novo;
}

t_expr * criar_expressao(int op, void *dir, void *esq) {
	t_expr * novo = (t_expr *) malloc(sizeof(t_expr));
	novo->op = op;
	novo->dir = dir;
	novo->esq = esq;
	return novo;
}

no_arvore * criar_no_atribuicao(simbolo *resultado, void *expressao) {
	no_arvore *novo = (no_arvore *)  malloc(sizeof(no_arvore));
	novo->tipoSintatico = ATTR;
	novo->dado.v_attr =  criar_atribuicao(resultado, expressao);
	return novo;
}

t_attr * criar_atribuicao(simbolo *resultado, void *expressao){ 
	t_attr * novo = (t_attr *) malloc(sizeof(t_attr));
	novo->resultado = resultado;
	novo->expressao = expressao;
	return novo;
}


no_arvore * criar_no_ifelse(void *A_expr_cond, void *A_bloco_if, void *A_bloco_else) {
	no_arvore *novo = (no_arvore *)  malloc(sizeof(no_arvore));
	novo->tipoSintatico = IF;
	novo->dado.v_ifelse =  criar_ifelse(A_expr_cond, A_bloco_if, A_bloco_else);
	return novo;
}

t_ifelse * criar_ifelse(void *A_expr_cond, void *A_bloco_if, void *A_bloco_else){ 
	t_ifelse * novo = (t_ifelse *) malloc(sizeof(t_ifelse));
	novo->expr_cond = A_expr_cond; 
	novo->bloco_if = A_bloco_if;
    novo->bloco_else = A_bloco_else;
	return novo;
}


no_arvore * criar_no_while(void *A_expr_cond, void *A_bloco_while) {
	no_arvore *novo = (no_arvore *)  malloc(sizeof(no_arvore));
	novo->tipoSintatico = WHILE;
	novo->dado.v_while =  criar_while(A_expr_cond, A_bloco_while);
	return novo;
}

t_while * criar_while(void *A_expr_cond, void *A_bloco_while){ 
	t_while * novo = (t_while *) malloc(sizeof(t_while));
	novo->expr_cond = A_expr_cond; 
    novo->bloco_while = A_bloco_while;
	return novo;
}


no_arvore * criar_no_funcao(simbolo *A_id, void *A_lista_param, void *A_bloco_funcao){
	no_arvore *novo = (no_arvore *)  malloc(sizeof(no_arvore));
	novo->tipoSintatico = FUNCTION;
	novo->dado.v_funcao =  criar_funcao(A_id, A_lista_param, A_bloco_funcao);
	return novo;
}

t_funcao * criar_funcao(simbolo *A_id, void *A_lista_param, void *A_bloco_funcao){ 
	t_funcao * novo = (t_funcao *) malloc(sizeof(t_funcao));
	novo->id = A_id; 
    novo->lista_param = A_lista_param;
    novo->bloco_funcao = A_bloco_funcao;
	return novo;
}

no_arvore * criar_no_stmts(void *A_stmts, void *A_stmt) {
	no_arvore *novo = (no_arvore *)  malloc(sizeof(no_arvore));
	novo->tipoSintatico = STMTS;
	novo->dado.v_stmts =  criar_stmts(A_stmts, A_stmt);
	return novo;
}

t_stmts * criar_stmts(void *A_stmts, void *A_stmt){ 
	t_stmts * novo = (t_stmts *) malloc(sizeof(t_stmts));
	novo->stmts = A_stmts; 
    novo->stmt = A_stmt;
	return novo;
}

no_arvore * criar_no_bloco(void *A_stmts, void *A_expr_return) {
	no_arvore *novo = (no_arvore *)  malloc(sizeof(no_arvore));
	novo->tipoSintatico = BLOCO;
	novo->dado.v_bloco =  criar_bloco(A_stmts, A_expr_return);
	return novo;
}

t_bloco * criar_bloco(void *A_stmts, void *A_expr_return){ 
	t_bloco * novo = (t_bloco *) malloc(sizeof(t_bloco));
    novo->stmts = A_stmts;
    novo->expr_return = A_expr_return;
	return novo;
}

no_arvore * criar_no_print(void *A_expr_print) {
	no_arvore *novo = (no_arvore *)  malloc(sizeof(no_arvore));
	novo->tipoSintatico = PRINT;
	novo->dado.v_print =  criar_print(A_expr_print);
	return novo;
}

t_print * criar_print(void *A_expr_print){ 
	t_print * novo = (t_print *) malloc(sizeof(t_print));
    novo->expr_print = A_expr_print;
	return novo;
}