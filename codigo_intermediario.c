#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "arvore.h"
#include "codigo_intermediario.h"
#include "tabelaNumero.h"
#include "y.tab.h"

int temp_ctr = 1;

int label_ctr = 1;

char * gerar_temp() {
	char buffer[256];
	sprintf(buffer, "t%d", temp_ctr++);
	return strdup(buffer);
}

char * gerar_label(char *label){
    char buffer[256];
    sprintf(buffer, "%s%d", label, label_ctr++);
    return strdup(buffer);
}



void gerar_codigo(no_arvore * raiz) {
	if(raiz != NULL) {
        
		switch(raiz->tipoSintatico) {
			case EXPR: 
				gerar_codigo_expr(raiz);
				break;
			case ATTR:
				gerar_codigo_attr(raiz);
				return;
            case IF:
				gerar_codigo_ifelse(raiz);
				return;
            case WHILE:
				gerar_codigo_while(raiz);
				return;
            case READ:
				gerar_codigo_read(raiz);
				return;
            case PRINT:
				gerar_codigo_print(raiz);
				return;
		}

	}
}

char * gerar_codigo_expr(no_arvore *raiz) {
	char buffer[256];
	char *addr1, *addr2, *addr3;
	if(raiz != NULL) {
		simbolo *s;
		t_expr * dado = raiz->dado.v_expr;
		switch (dado->op){

			case NUMBER:
                {numero* p = (numero *) dado->dir;
				sprintf(buffer, "%d", p->val.ival);
				return strdup(buffer);}

			case ID:
				s = (simbolo *) dado->dir;
				return s->lexema;

			case ADD:
				addr1 = gerar_codigo_expr((no_arvore *) dado->dir);
				addr2 = gerar_codigo_expr((no_arvore *) dado->esq);
				addr3 = gerar_temp(); 				
				printf("%s = %s %c %s\n", addr3, addr1, '+', addr2);
				return addr3;

			case SUB:
				addr1 = gerar_codigo_expr((no_arvore *) dado->dir);
				addr2 = gerar_codigo_expr((no_arvore *) dado->esq);
				addr3 = gerar_temp(); 				
				printf("%s = %s %c %s\n", addr3, addr1, '-', addr2);
				return addr3;

            case MUL:
				addr1 = gerar_codigo_expr((no_arvore *) dado->dir);
				addr2 = gerar_codigo_expr((no_arvore *) dado->esq);
				addr3 = gerar_temp(); 				
				printf("%s = %s %c %s\n", addr3, addr1, '*', addr2);
				return addr3;

            case DIV:
				addr1 = gerar_codigo_expr((no_arvore *) dado->dir);
				addr2 = gerar_codigo_expr((no_arvore *) dado->esq);
				addr3 = gerar_temp(); 				
				printf("%s = %s %c %s\n", addr3, addr1, '/', addr2);
				return addr3;
            
            case MOD:
				addr1 = gerar_codigo_expr((no_arvore *) dado->dir);
				addr2 = gerar_codigo_expr((no_arvore *) dado->esq);
				addr3 = gerar_temp(); 				
				printf("%s = %s %c %s\n", addr3, addr1, '%', addr2);
				return addr3;

            case EQ:
				addr1 = gerar_codigo_expr((no_arvore *) dado->dir);
				addr2 = gerar_codigo_expr((no_arvore *) dado->esq);
				addr3 = gerar_temp(); 				
				printf("%s = %s %s %s\n", addr3, addr1, "==", addr2);
				return addr3;
            
            case LESS:
				addr1 = gerar_codigo_expr((no_arvore *) dado->dir);
				addr2 = gerar_codigo_expr((no_arvore *) dado->esq);
				addr3 = gerar_temp(); 				
				printf("%s = %s %c %s\n", addr3, addr1, '<', addr2);
				return addr3;
            
            case BIGG:
				addr1 = gerar_codigo_expr((no_arvore *) dado->dir);
				addr2 = gerar_codigo_expr((no_arvore *) dado->esq);
				addr3 = gerar_temp(); 				
				printf("%s = %s %c %s\n", addr3, addr1, '>', addr2);
				return addr3;
            
            case NE:
				addr1 = gerar_codigo_expr((no_arvore *) dado->dir);
				addr2 = gerar_codigo_expr((no_arvore *) dado->esq);
				addr3 = gerar_temp(); 				
				printf("%s = %s %s %s\n", addr3, addr1, "!=", addr2);
				return addr3;
            
            case LE:
				addr1 = gerar_codigo_expr((no_arvore *) dado->dir);
				addr2 = gerar_codigo_expr((no_arvore *) dado->esq);
				addr3 = gerar_temp(); 				
				printf("%s = %s %s %s\n", addr3, addr1, "<=", addr2);
				return addr3;

            case GE:
				addr1 = gerar_codigo_expr((no_arvore *) dado->dir);
				addr2 = gerar_codigo_expr((no_arvore *) dado->esq);
				addr3 = gerar_temp(); 				
				printf("%s = %s %s %s\n", addr3, addr1, ">=", addr2);
				return addr3;
            
            case UNARY:
				addr1 = gerar_codigo_expr((no_arvore *) dado->dir);
				addr2 = gerar_codigo_expr((no_arvore *) dado->esq);
				addr3 = gerar_temp(); 				
				printf("%s = %s %c %s\n", addr3, addr1, "-", addr2);
				return addr3;

            case TRUE:
				addr3 = gerar_temp(); 				
				printf("%s = %d \n", addr3, (int) dado->dir);
				return addr3;
            
            case FALSE:
				addr3 = gerar_temp(); 				
				printf("%s = %d \n", addr3, (int) dado->dir);
				return addr3;

            case NOT:
				addr1 = gerar_codigo_expr((no_arvore *) dado->dir);
				addr3 = gerar_temp(); 				
				printf("%s = %s %s\n", addr3, "not", addr1);
				return addr3;
            
            case AND:
				addr1 = gerar_codigo_expr((no_arvore *) dado->dir);
				addr2 = gerar_codigo_expr((no_arvore *) dado->esq);
				addr3 = gerar_temp(); 				
				printf("%s = %s %s %s\n", addr3, addr1, "and", addr2);
				return addr3;
            
            case OR:
				addr1 = gerar_codigo_expr((no_arvore *) dado->dir);
				addr2 = gerar_codigo_expr((no_arvore *) dado->esq);
				addr3 = gerar_temp(); 				
				printf("%s = %s %s %s\n", addr3, addr1, "or", addr2);
				return addr3;

            
            
		}
	}	
}



void gerar_codigo_attr(no_arvore *raiz) {
	t_attr * dado = raiz->dado.v_attr;	
	char * addr = gerar_codigo_expr(dado->expressao);
	simbolo *s = (simbolo *) dado->resultado;
	printf("%s = %s\n", s->lexema, addr);
}

void gerar_codigo_ifelse(no_arvore *raiz){
    temp_ctr = 1;
    char *addr1, *addr2, *addr3, *addr4, *label_else;
    t_ifelse *dado = raiz->dado.v_ifelse;
    addr1 = "if_false";
    addr2 = gerar_codigo_expr(dado->expr_cond);
    addr3 = "goto";
    addr4 = gerar_label("L");
    printf("%s %s %s %s\n", addr1, addr2, addr3, addr4);
    
    if(dado->stmt_else != NULL){
        label_else = gerar_label("L");
        printf("goto %s\n", label_else);
        printf("%s\n", addr4);
        //codigo bloco
        printf("%s\n", label_else);
    }else{
        printf("%s\n", addr4);
    }

}

void gerar_codigo_while(no_arvore *raiz){
    temp_ctr = 1;
    char *addr1, *addr2, *addr3, *addr4, *label_inicio;
    t_while *dado = raiz->dado.v_while;
    label_inicio = gerar_label("L");
    printf("%s\n", label_inicio);
    addr1 = "if_false";
    addr2 = gerar_codigo_expr(dado->expr_cond);
    addr3 = "goto";
    addr4 = gerar_label("L");
    printf("%s %s %s %s\n", addr1, addr2, addr3, addr4);
    printf("goto %s\n", label_inicio);
    printf("%s\n", addr4);
}

void gerar_codigo_read(no_arvore *raiz){
    
}

void gerar_codigo_print(no_arvore *raiz){
    temp_ctr = 1;
    char *addr1, *addr2, *addr3, *addr4;
    t_print *dado = raiz->dado.v_print;
    addr1 = "print";
    addr2 = gerar_codigo_expr(dado->expr_print);
    printf("%s %s\n", addr1, addr2);
    
}

















