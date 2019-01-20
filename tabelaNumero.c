#include <stdlib.h>
#include "tabelaNumero.h"


numero *  criar_numero (valorNumero val, int tipo) {   //valor tipo
	numero *novo = (numero *) malloc(sizeof(numero));
	novo->tipo = tipo;
	novo->val = val;
	return novo;
}
