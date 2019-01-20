#ifndef TABELA_NUMERO_H
#define TABELA_NUMERO_H

typedef union valorNumero {
	int ival;
	float fval;
} valorNumero;

typedef struct numero {
	int tipo;
	valorNumero val;
} numero;

numero *  criar_numero (valorNumero val, int tipo);

#endif
