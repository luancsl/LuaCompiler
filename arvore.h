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

//Simula a superclasse abstrata 
typedef union valor_sintatico {
	t_expr *expr;
	t_attr *attr;
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


#endif
