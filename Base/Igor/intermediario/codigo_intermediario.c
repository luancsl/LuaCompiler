#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "arvore.h"
#include "codigo_intermediario.h"
#include "y.tab.h"

int temp_ctr = 1;

char * gerar_temp() {
	char buffer[256];
	sprintf(buffer, "t%d", temp_ctr++);
	return strdup(buffer);
}


void gerar_codigo(no_arvore * raiz) {
	if(raiz != NULL) {
		switch(raiz->tipo) {
			case EXPR: 
				gerar_codigo_expr(raiz);
				break;
			case ATTR:
				gerar_codigo_attr(raiz);
				return;
		}

	}
}

char * gerar_codigo_expr(no_arvore *raiz) {
	char buffer[256];
	char *addr1, *addr2, *addr3;
	if(raiz != NULL) {
		simbolo *s;
		t_expr * dado = raiz->dado.expr;
		switch (dado->op) {
			case NUMBER: 
				sprintf(buffer, "%d", (int) dado->dir);
				return strdup(buffer);
			case ID:
				s = (simbolo *) dado->dir;
				return s->lexema;

			case '+':
			case '-':
				
				addr1 = gerar_codigo_expr((no_arvore *) dado->dir);
				addr2 = gerar_codigo_expr((no_arvore *) dado->esq);
				addr3 = gerar_temp(); 				
				printf("%s = %s %c %s\n", addr3, addr1, dado->op, addr2);
				return addr3;

		}
	}	
}



void gerar_codigo_attr(no_arvore *raiz) {
	t_attr * dado = raiz->dado.attr;	
	char * addr = gerar_codigo_expr(dado->expressao);
	simbolo *s = (simbolo *) dado->resultado;
	printf("%s = %s\n", s->lexema, addr);
}

















