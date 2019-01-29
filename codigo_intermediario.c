#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "arvore.h"
#include "codigo_intermediario.h"
#include "lista_intermediario.h"
#include "tabelaNumero.h"
#include "y.tab.h"

int temp_ctr = 1;

int temp_ctr_s = 1;

int label_ctr = 1;



char * gerar_temp() {
	char buffer[256];
	sprintf(buffer, "$t%d", temp_ctr++);
	return strdup(buffer);
}

char * gerar_temp_s() {
	char buffer[256];
	sprintf(buffer, "$s%d", temp_ctr_s++);
	return strdup(buffer);
}

char * gerar_label(char *label){
    char buffer[256];
    sprintf(buffer, "%s%d", label, label_ctr++);
    return strdup(buffer);
}

char * vartofunc(char *label){
    char buffer[256];
    sprintf(buffer, "f_%s", label);
    return strdup(buffer);
}




void gerar_codigo(lista* list, lista* list_f, no_arvore * raiz) {
	if(raiz != NULL) {
        
		switch(raiz->tipoSintatico) {
			case EXPR:
				gerar_codigo_expr(list, raiz);
				break;
			case ATTR:
				gerar_codigo_attr(list, raiz);
				return;
            case IF:
				gerar_codigo_ifelse(list, list_f, raiz);
				return;
            case WHILE:
				gerar_codigo_while(list, list_f, raiz);
				return;
            case FUNCTION:
                gerar_codigo_funcao(list_f, list, raiz);
                return;
            case PRINT:
				gerar_codigo_print(list, raiz);
				return;
            case BLOCO:
                gerar_codigo_bloco(list, list_f, raiz);
                return;
            case STMTS:{
                t_stmts *s = (t_stmts *) raiz->dado.v_stmts;
                gerar_codigo(list, list_f, (no_arvore *) s->stmts);
                gerar_codigo(list, list_f, (no_arvore *) s->stmt);
                return;}
            default:
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

            case FUNCTION_C:{
                char* addr1 = gerar_temp();
                s = (simbolo *) dado->dir;
                char * addr2 = gerar_codigo_expr(list, (no_arvore *) dado->esq);
                instr* instr = criar_instrucao(FUNCTION_C, addr1, vartofunc(s->lexema), addr2);
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
                temp_ctr_s = 1;
                return addr3;}

			case SUB:{
				addr1 = gerar_codigo_expr(list, (no_arvore *) dado->dir);
				addr2 = gerar_codigo_expr(list, (no_arvore *) dado->esq);
				addr3 = gerar_temp(); 				
				/* printf("%s = %s %c %s\n", addr3, addr1, '-', addr2); */
                instr* instr = criar_instrucao(SUB, addr3, addr1, addr2);
                inserir_instrucao(list, instr);
				temp_ctr = 1;
                temp_ctr_s = 1;
                return addr3;}

            case MUL:{
				addr1 = gerar_codigo_expr(list, (no_arvore *) dado->dir);
				addr2 = gerar_codigo_expr(list, (no_arvore *) dado->esq);
				addr3 = gerar_temp_s(); 				
				/* printf("%s = %s %c %s\n", addr3, addr1, '*', addr2); */
                instr* instr = criar_instrucao(MUL, addr3, addr1, addr2);
                inserir_instrucao(list, instr);
                temp_ctr = 1;
                return addr3;}

            case DIV:{
				addr1 = gerar_codigo_expr(list, (no_arvore *) dado->dir);
				addr2 = gerar_codigo_expr(list, (no_arvore *) dado->esq);
				addr3 = gerar_temp_s(); 				
				/* printf("%s = %s %c %s\n", addr3, addr1, '/', addr2); */
                instr* instr = criar_instrucao(DIV, addr3, addr1, addr2);
                inserir_instrucao(list, instr);
                temp_ctr = 1;
                return addr3;}
            
            case MOD:{
				addr1 = gerar_codigo_expr(list, (no_arvore *) dado->dir);
				addr2 = gerar_codigo_expr(list, (no_arvore *) dado->esq);
				addr3 = gerar_temp_s(); 				
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

void gerar_codigo_ifelse(lista* list, lista* list_f, no_arvore *raiz){
    temp_ctr = 1;
    char *addr1, *label_else, *label_fim;
    instr* instr;
    t_ifelse *dado_ifelse = raiz->dado.v_ifelse;
    no_arvore *no_aux;

    addr1 = gerar_codigo_expr(list, dado_ifelse->expr_cond);
    label_else = gerar_label("L");
    instr = criar_instrucao(IF, addr1, label_else, NULL);
    inserir_instrucao(list, instr);
    
    if(dado_ifelse->bloco_else != NULL){
        label_fim = gerar_label("L");
        no_aux = (no_arvore *) dado_ifelse->bloco_if;
        gerar_codigo(list, list_f, no_aux);

        instr = criar_instrucao(GOTO, label_fim, NULL, NULL);
        inserir_instrucao(list, instr);

        instr = criar_instrucao(LAB, label_else, NULL, NULL);
        inserir_instrucao(list, instr);
        
        no_aux = (no_arvore *) dado_ifelse->bloco_else;
        gerar_codigo(list, list_f, no_aux);

        instr = criar_instrucao(LAB, label_fim, NULL, NULL);
        inserir_instrucao(list, instr);
    }else{
        no_aux = (no_arvore *) dado_ifelse->bloco_if;
        gerar_codigo(list, list_f, no_aux);

        instr = criar_instrucao(LAB, label_else, NULL, NULL);
        inserir_instrucao(list, instr);
    }

}

void gerar_codigo_while(lista* list, lista* list_f, no_arvore *raiz){
    temp_ctr = 1;
    char *addr1, *label_inicio, *label_fim;
    instr* instr;
    t_while *dado = raiz->dado.v_while;
    no_arvore *no_aux;

    label_inicio = gerar_label("L");
    instr = criar_instrucao(LAB, label_inicio, NULL, NULL);
    inserir_instrucao(list, instr);

    addr1 = gerar_codigo_expr(list, dado->expr_cond);
    label_fim = gerar_label("L");
    instr = criar_instrucao(WHILE, addr1, label_fim, NULL);
    inserir_instrucao(list, instr);

    no_aux = (no_arvore *) dado->bloco_while;
    gerar_codigo(list, list_f, no_aux);

    instr = criar_instrucao(GOTO, label_inicio, NULL, NULL);
    inserir_instrucao(list, instr);

    instr = criar_instrucao(LAB, label_fim, NULL, NULL);
    inserir_instrucao(list, instr);
    
}

void gerar_codigo_funcao(lista* list, lista* list_f, no_arvore *raiz){
    temp_ctr = 1;
    instr* instr;
    t_funcao *dado = raiz->dado.v_funcao;
    no_arvore *no_aux;

    simbolo *s = (simbolo *) dado->id;

    instr = criar_instrucao(LAB, vartofunc(s->lexema), NULL, NULL);
    inserir_instrucao(list, instr);

    simbolo *p = (simbolo *) dado->lista_param;

    instr = criar_instrucao(FUNCTION, s->lexema, p->lexema, NULL);
    inserir_instrucao(list, instr);

    no_aux = (no_arvore *) dado->bloco_funcao;
    gerar_codigo(list, list_f, no_aux);

    
    
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


void gerar_codigo_bloco(lista* list, lista* list_f, no_arvore *raiz){
    temp_ctr = 1;
    instr* instr;
    char* addr;
    t_bloco *dado = raiz->dado.v_bloco;
    no_arvore *no_aux;

    no_aux = (no_arvore *) dado->stmts;
    gerar_codigo(list, list_f, no_aux);

    if(dado->expr_return != NULL){
        addr = gerar_codigo_expr(list, (no_arvore *) dado->expr_return);
        instr = criar_instrucao(RETURN, NULL, addr, NULL);
        inserir_instrucao(list, instr);
    }


}



















