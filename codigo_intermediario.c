#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "arvore.h"
#include "codigo_intermediario.h"
#include "lista_intermediario.h"
#include "tabelaNumero.h"
#include "y.tab.h"

int temp_ctr = 1;

int label_ctr = 1;



char * gerar_temp() {
	char buffer[256];
	sprintf(buffer, "$t%d", temp_ctr++);
	return strdup(buffer);
}

char * gerar_label(char *label){
    char buffer[256];
    sprintf(buffer, "%s%d", label, label_ctr++);
    return strdup(buffer);
}



void gerar_codigo(lista* list, no_arvore * raiz) {
	if(raiz != NULL) {
        
		switch(raiz->tipoSintatico) {
			case EXPR: 
				gerar_codigo_expr(list, raiz);
				break;
			case ATTR:
				gerar_codigo_attr(list, raiz);
				return;
            case IF:
				gerar_codigo_ifelse(list, raiz);
				return;
            case WHILE:
				gerar_codigo_while(list, raiz);
				return;
            case PRINT:
				gerar_codigo_print(list, raiz);
				return;
		}

	}
}

char * gerar_codigo_expr(lista* list, no_arvore *raiz) {
	char buffer[256];
	char *addr1, *addr2, *addr3;
	if(raiz != NULL) {
		simbolo *s;
		t_expr * dado = raiz->dado.v_expr;
		switch (dado->op){

			case NUMBER:{
                numero* p = (numero *) dado->dir;
				sprintf(buffer, "%d", p->val.ival);
                char* addr1 = gerar_temp();
                instr* instr = criar_instrucao(NUMBER, addr1, strdup(buffer), NULL);
                inserir_instrucao(list, instr);
				return addr1;}

			case ID:{
                char* addr1 = gerar_temp();
				s = (simbolo *) dado->dir;
                instr* instr = criar_instrucao(ID, addr1, s->lexema, NULL);
                inserir_instrucao(list, instr);
				return addr1;}

			case ADD:{
				addr1 = gerar_codigo_expr(list, (no_arvore *) dado->dir);
				addr2 = gerar_codigo_expr(list, (no_arvore *) dado->esq);
				addr3 = gerar_temp(); 				
				/* printf("%s = %s %c %s\n", addr3, addr1, '+', addr2); */
                instr* instr = criar_instrucao(ADD, addr3, addr1, addr2);
                inserir_instrucao(list, instr);
				temp_ctr = 1;
                return addr3;}

			case SUB:{
				addr1 = gerar_codigo_expr(list, (no_arvore *) dado->dir);
				addr2 = gerar_codigo_expr(list, (no_arvore *) dado->esq);
				addr3 = gerar_temp(); 				
				/* printf("%s = %s %c %s\n", addr3, addr1, '-', addr2); */
                instr* instr = criar_instrucao(SUB, addr3, addr1, addr2);
                inserir_instrucao(list, instr);
				temp_ctr = 1;
                return addr3;}

            case MUL:{
				addr1 = gerar_codigo_expr(list, (no_arvore *) dado->dir);
				addr2 = gerar_codigo_expr(list, (no_arvore *) dado->esq);
				addr3 = gerar_temp(); 				
				/* printf("%s = %s %c %s\n", addr3, addr1, '*', addr2); */
                instr* instr = criar_instrucao(MUL, addr3, addr1, addr2);
                inserir_instrucao(list, instr);
				temp_ctr = 1;
                return addr3;}

            case DIV:{
				addr1 = gerar_codigo_expr(list, (no_arvore *) dado->dir);
				addr2 = gerar_codigo_expr(list, (no_arvore *) dado->esq);
				addr3 = gerar_temp(); 				
				/* printf("%s = %s %c %s\n", addr3, addr1, '/', addr2); */
                instr* instr = criar_instrucao(DIV, addr3, addr1, addr2);
                inserir_instrucao(list, instr);
				temp_ctr = 1;
                return addr3;}
            
            case MOD:{
				addr1 = gerar_codigo_expr(list, (no_arvore *) dado->dir);
				addr2 = gerar_codigo_expr(list, (no_arvore *) dado->esq);
				addr3 = gerar_temp(); 				
				/* printf("%s = %s %c %s\n", addr3, addr1, '%', addr2); */
                instr* instr = criar_instrucao(MOD, addr3, addr1, addr2);
                inserir_instrucao(list, instr);
				temp_ctr = 1;
                return addr3;}

            case EQ:{
				addr1 = gerar_codigo_expr(list, (no_arvore *) dado->dir);
				addr2 = gerar_codigo_expr(list, (no_arvore *) dado->esq);
				addr3 = gerar_temp(); 				
				/* printf("%s = %s %s %s\n", addr3, addr1, "==", addr2); */
                instr* instr = criar_instrucao(EQ, addr3, addr1, addr2);
                inserir_instrucao(list, instr);
				temp_ctr = 1;
                return addr3;}

            case LESS:{
				addr1 = gerar_codigo_expr(list, (no_arvore *) dado->dir);
				addr2 = gerar_codigo_expr(list, (no_arvore *) dado->esq);
				addr3 = gerar_temp(); 				
				/* printf("%s = %s %c %s\n", addr3, addr1, '<', addr2); */
                instr* instr = criar_instrucao(LESS, addr3, addr1, addr2);
                inserir_instrucao(list, instr);
				temp_ctr = 1;
                return addr3;} 

            case BIGG:{
				addr1 = gerar_codigo_expr(list, (no_arvore *) dado->dir);
				addr2 = gerar_codigo_expr(list, (no_arvore *) dado->esq);
				addr3 = gerar_temp(); 				
				/* printf("%s = %s %c %s\n", addr3, addr1, '>', addr2); */
                instr* instr = criar_instrucao(BIGG, addr3, addr1, addr2);
                inserir_instrucao(list, instr);
				temp_ctr = 1;
                return addr3;} 

            case NE:{
				addr1 = gerar_codigo_expr(list, (no_arvore *) dado->dir);
				addr2 = gerar_codigo_expr(list, (no_arvore *) dado->esq);
				addr3 = gerar_temp(); 				
				/* printf("%s = %s %s %s\n", addr3, addr1, "!=", addr2); */
                instr* instr = criar_instrucao(NE, addr3, addr1, addr2);
                inserir_instrucao(list, instr);
				temp_ctr = 1;
                return addr3;} 

            case LE:{
				addr1 = gerar_codigo_expr(list, (no_arvore *) dado->dir);
				addr2 = gerar_codigo_expr(list, (no_arvore *) dado->esq);
				addr3 = gerar_temp(); 				
				/* printf("%s = %s %s %s\n", addr3, addr1, "<=", addr2); */
                instr* instr = criar_instrucao(LE, addr3, addr1, addr2);
                inserir_instrucao(list, instr);
				temp_ctr = 1;
                return addr3;}

            case GE:{
				addr1 = gerar_codigo_expr(list, (no_arvore *) dado->dir);
				addr2 = gerar_codigo_expr(list, (no_arvore *) dado->esq);
				addr3 = gerar_temp(); 				
				/* printf("%s = %s %s %s\n", addr3, addr1, ">=", addr2); */
                instr* instr = criar_instrucao(GE, addr3, addr1, addr2);
                inserir_instrucao(list, instr);
				temp_ctr = 1;
                return addr3;}

            case UNARY:{
				addr1 = gerar_codigo_expr(list, (no_arvore *) dado->dir);
				addr2 = gerar_codigo_expr(list, (no_arvore *) dado->esq);
				addr3 = gerar_temp(); 				
				/* printf("%s = %s %c %s\n", addr3, addr1, "-", addr2); */
                
				temp_ctr = 1;
                return addr3;}

            case TRUE:{
				int p = (int) dado->dir;
				sprintf(buffer, "%d", p);
                char* addr1 = gerar_temp();
                instr* instr = criar_instrucao(NUMBER, addr1, strdup(buffer), NULL);
                inserir_instrucao(list, instr);
				return addr1;}  

            case FALSE:{
				int p = (int) dado->dir;
				sprintf(buffer, "%d", p);
                char* addr1 = gerar_temp();
                instr* instr = criar_instrucao(NUMBER, addr1, strdup(buffer), NULL);
                inserir_instrucao(list, instr);
				return addr1;}

            case NOT:{
				addr1 = gerar_codigo_expr(list, (no_arvore *) dado->dir);
				addr3 = gerar_temp(); 				
				/* printf("%s = %s %s\n", addr3, "not", addr1); */
                instr* instr = criar_instrucao(NOT, addr3, addr1, NULL);
                inserir_instrucao(list, instr);
				temp_ctr = 1;
                return addr3;}

            case AND:{
				addr1 = gerar_codigo_expr(list, (no_arvore *) dado->dir);
				addr2 = gerar_codigo_expr(list, (no_arvore *) dado->esq);
				addr3 = gerar_temp(); 				
				/* printf("%s = %s %s %s\n", addr3, addr1, "and", addr2); */
                instr* instr = criar_instrucao(AND, addr3, addr1, addr2);
                inserir_instrucao(list, instr);
				temp_ctr = 1;
                return addr3;}

            case OR:{
				addr1 = gerar_codigo_expr(list, (no_arvore *) dado->dir);
				addr2 = gerar_codigo_expr(list, (no_arvore *) dado->esq);
				addr3 = gerar_temp(); 				
				/* printf("%s = %s %s %s\n", addr3, addr1, "or", addr2); */
                instr* instr = criar_instrucao(OR, addr3, addr1, addr2);
                inserir_instrucao(list, instr);
				temp_ctr = 1;
                return addr3;}

            case READ:{
				addr3 = gerar_temp(); 				
                instr* instr = criar_instrucao(READ, addr3, NULL, NULL);
                inserir_instrucao(list, instr);
                return addr3;
            }
            
		}
	}	
}


void gerar_codigo_attr(lista* list, no_arvore *raiz) {
	t_attr * dado = raiz->dado.v_attr;	
	char * addr = gerar_codigo_expr(list, dado->expressao);
	simbolo *s = (simbolo *) dado->resultado;
	/* printf("%s = %s\n", s->lexema, addr); */
    instr* instr = criar_instrucao(ATTR, s->lexema, addr, NULL);
    inserir_instrucao(list, instr);
}

void gerar_codigo_ifelse(lista* list, no_arvore *raiz){
    temp_ctr = 1;
    char *addr1, *label_else, *label_fim;
    instr* instr;
    t_ifelse *dado = raiz->dado.v_ifelse;
    no_arvore *no_aux;
    t_bloco * b;
    t_stmt * st;

    addr1 = gerar_codigo_expr(list, dado->expr_cond);
    label_else = gerar_label("L");
    instr = criar_instrucao(IF, addr1, label_else, NULL);
    inserir_instrucao(list, instr);
    
    if(dado->stmt_else != NULL){
        label_fim = gerar_label("L");
        no_aux = (no_arvore *) dado->stmt_if;
        b = no_aux->dado.v_bloco;
        no_aux = (no_arvore *) b->stmt;
        st = no_aux->dado.v_stmt;
        gerar_codigo(list, (no_arvore *) st->stmt);

        instr = criar_instrucao(GOTO, label_fim, NULL, NULL);
        inserir_instrucao(list, instr);

        instr = criar_instrucao(LAB, label_else, NULL, NULL);
        inserir_instrucao(list, instr);
        no_aux = (no_arvore *) dado->stmt_else;
        b = no_aux->dado.v_bloco;
        no_aux = (no_arvore *) b->stmt;
        st = no_aux->dado.v_stmt;
        gerar_codigo(list, (no_arvore *) st->stmt);

        instr = criar_instrucao(LAB, label_fim, NULL, NULL);
        inserir_instrucao(list, instr);
    }else{
        no_aux = (no_arvore *) dado->stmt_if;
        b = no_aux->dado.v_bloco;
        no_aux = (no_arvore *) b->stmt;
        st = no_aux->dado.v_stmt;
        gerar_codigo(list, (no_arvore *) st->stmt);

        instr = criar_instrucao(LAB, label_else, NULL, NULL);
        inserir_instrucao(list, instr);
    }

}

void gerar_codigo_while(lista* list, no_arvore *raiz){
    temp_ctr = 1;
    char *addr1, *label_inicio, *label_fim;
    instr* instr;
    t_while *dado = raiz->dado.v_while;
    no_arvore *no_aux;
    t_bloco * b;
    t_stmt * st;

    label_inicio = gerar_label("L");
    instr = criar_instrucao(LAB, label_inicio, NULL, NULL);
    inserir_instrucao(list, instr);

    addr1 = gerar_codigo_expr(list, dado->expr_cond);
    label_fim = gerar_label("L");
    instr = criar_instrucao(WHILE, addr1, label_fim, NULL);
    inserir_instrucao(list, instr);

    no_aux = (no_arvore *) dado->stmt_while;
    b = no_aux->dado.v_bloco;
    no_aux = (no_arvore *) b->stmt;
    st = no_aux->dado.v_stmt;
    gerar_codigo(list, (no_arvore *) st->stmt);

    instr = criar_instrucao(GOTO, label_inicio, NULL, NULL);
    inserir_instrucao(list, instr);

    instr = criar_instrucao(LAB, label_fim, NULL, NULL);
    inserir_instrucao(list, instr);
    
}

void gerar_codigo_print(lista* list, no_arvore *raiz){
    temp_ctr = 1;
    char *addr1, *addr2, *addr3, *addr4;
    t_print *dado = raiz->dado.v_print;
    addr1 = "print";
    addr2 = gerar_codigo_expr(list, dado->expr_print);
   /*  printf("%s %s\n", addr1, addr2); */
    instr* instr = criar_instrucao(PRINT, addr2, NULL, NULL);
    inserir_instrucao(list, instr);
    
}



















