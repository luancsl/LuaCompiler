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


no_arvore * criar_no_ifelse(void *A_expr_cond, void *A_stmt_if, void *A_stmt_else) {
	no_arvore *novo = (no_arvore *)  malloc(sizeof(no_arvore));
	novo->tipoSintatico = IF;
	novo->dado.v_ifelse =  criar_ifelse(A_expr_cond, A_stmt_if, A_stmt_else);
	return novo;
}

t_ifelse * criar_ifelse(void *A_expr_cond, void *A_stmt_if, void *A_stmt_else){ 
	t_ifelse * novo = (t_ifelse *) malloc(sizeof(t_ifelse));
	novo->expr_cond = A_expr_cond; 
	novo->stmt_if = A_stmt_if;
    novo->stmt_else = A_stmt_else;
	return novo;
}


no_arvore * criar_no_while(void *A_expr_cond, void *A_stmt_while) {
	no_arvore *novo = (no_arvore *)  malloc(sizeof(no_arvore));
	novo->tipoSintatico = WHILE;
	novo->dado.v_while =  criar_while(A_expr_cond, A_stmt_while);
	return novo;
}

t_while * criar_while(void *A_expr_cond, void *A_stmt_while){ 
	t_while * novo = (t_while *) malloc(sizeof(t_while));
	novo->expr_cond = A_expr_cond; 
    novo->stmt_while = A_stmt_while;
	return novo;
}

no_arvore * criar_no_stmt(no_arvore *A_no_stmt, void *A_stmt) {
	no_arvore *novo = (no_arvore *)  malloc(sizeof(no_arvore));
	novo->tipoSintatico = STMT;
	novo->dado.v_stmt =  criar_stmt(A_no_stmt, A_stmt);
	return novo;
}

t_stmt * criar_stmt(no_arvore *A_no_stmt, void *A_stmt){ 
	t_stmt * novo = (t_stmt *) malloc(sizeof(t_stmt));
	novo->no_stmt = A_no_stmt; 
    novo->stmt = A_stmt;
	return novo;
}

no_arvore * criar_no_bloco(void *A_stmt) {
	no_arvore *novo = (no_arvore *)  malloc(sizeof(no_arvore));
	novo->tipoSintatico = BLOCO;
	novo->dado.v_bloco =  criar_bloco(A_stmt);
	return novo;
}

t_bloco * criar_bloco(void *A_stmt){ 
	t_bloco * novo = (t_bloco *) malloc(sizeof(t_bloco));
    novo->stmt = A_stmt;
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

no_arvore * criar_no_read() {
	no_arvore *novo = (no_arvore *)  malloc(sizeof(no_arvore));
	novo->tipoSintatico = READ;
	novo->dado.v_read =  criar_read();
	return novo;
}

t_read * criar_read(){ 
	t_read * novo = (t_read *) malloc(sizeof(t_read));
	return novo;
}


void print_arvore(no_arvore *no){

    if (no != NULL){

        switch (no->tipoSintatico){
            case BLOCO:
                print_arvore(no->dado.v_bloco->stmt);
                printf("Bloco\n"); 
                break;
            
            case STMT:           
                print_arvore(no->dado.v_stmt->stmt);
                //print_arvore((no_arvore*)no->dado.v_stmt->no_stmt);             
                printf("Stmts\n"); 
                break;
            
            case ATTR:
                print_arvore((no_arvore*)no->dado.v_attr->expressao);
                simbolo *s = (simbolo *) no->dado.v_attr->resultado; 
                printf("ATTR\n");
                printf("%s = %s\n", s->lexema, "addr");
                break;
        
            case EXPR:
                if(no->dado.v_expr->op != NUMBER && no->dado.v_expr->op != ID){              
                    print_arvore((no_arvore*)no->dado.v_expr->dir);
                    if(no->dado.v_expr->esq != NULL)
                        print_arvore((no_arvore*)no->dado.v_expr->esq);
                }
                printf("EXPR\n");
                break;
                    
            case READ:
                printf("Read %s\n", no->dado.v_read);
                break;
            
            case PRINT:
                printf("Read %s\n", no->dado.v_read);
                break;           
            
            case IF:
                printf("++++++++++++++++++++++++++++++++++++++++++++++\n");                
                
                
                print_arvore((no_arvore*)no->dado.v_ifelse->stmt_if);
                print_arvore((no_arvore*)no->dado.v_ifelse->expr_cond);
                printf("IF\n");

                if(no->dado.v_ifelse->stmt_else != NULL){
                    print_arvore((no_arvore*)no->dado.v_ifelse->stmt_else);
                    printf("ELSE\n");
                } 
                
                printf("++++++++++++++++++++++++++++++++++++++++++++++\n");
                break;
            
            case WHILE:
                printf("++++++++++++++++++++++++++++++++++++++++++++++\n");                
                
                
                print_arvore((no_arvore*)no->dado.v_ifelse->stmt_if);
                print_arvore((no_arvore*)no->dado.v_ifelse->expr_cond);
                printf("IF\n");

                if(no->dado.v_ifelse->stmt_else != NULL){
                    print_arvore((no_arvore*)no->dado.v_ifelse->stmt_else);
                    printf("ELSE\n");
                } 
                
                printf("++++++++++++++++++++++++++++++++++++++++++++++\n");
                break; 
        
            default:
                printf("Tipo inexistente -- Tipo %d\n", no->tipoSintatico);           
        }      

    } 
}