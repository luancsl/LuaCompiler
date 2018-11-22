#ifndef TABELA_H
#define TABELA_H

#include <string.h>

typedef union valor {
	int dval;
	float fval;
} valor;

typedef struct simbolo {
	int tipo;
	char *lexema;
	valor val;
} simbolo;

typedef struct no_tabela {
	simbolo *dado;
	struct no_tabela *proximo;
} no_tabela;

typedef struct tabela {
	no_tabela *primeiro;
	struct tabela *pai;
} tabela;

typedef struct pilha_contexto  {
	tabela *dado;
	struct pilha_contexto *anterior;
} pilha_contexto;

void inserir_simbolo(tabela *t, simbolo *s);
simbolo * localizar_simbolo (tabela *contexto, char *lexema);
simbolo *  criar_simbolo (char *lexema, int tipo);

pilha_contexto* empilhar_contexto(pilha_contexto *pilha, tabela *contexto);
void desempilhar_contexto(pilha_contexto **pilha);
tabela* topo_pilha(pilha_contexto *pilha);
tabela * criar_contexto(tabela *pai);

void imprimir_contexto(tabela *t);

#endif
