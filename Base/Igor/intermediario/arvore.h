#ifndef ARVORE_H
#define ARVORE_H

#include <string.h>
#include "tabela.h"
#include "y.tab.h"

typedef struct t_expr {
	int op;
	int tipo; //float ou int
	void *dir, *esq;
	valor valor;
} t_expr;

typedef struct t_attr {
	simbolo *resultado;
	void *expressao;
} t_attr;

typedef union valor_sintatico {
	t_expr *expr;
	t_attr *attr;
} valor_sintatico;

typedef struct no_arvore {
	int tipo; //expr, attr, stmt, ...
	valor_sintatico dado;
	//ponteiro para tabela de símbolos
} no_arvore;

no_arvore * criar_no_expressao(int op, void *dir, void *esq);
t_expr * criar_expressao(int op, void *dir, void *esq);

no_arvore * criar_no_atribuicao(simbolo *resultado, void *expressao);
t_attr * criar_atribuicao(simbolo *resultado, void *expressao);


#endif
