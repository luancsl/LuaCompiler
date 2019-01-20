#ifndef CODIGO_INTERMEDIARIO_H
#define CODIGO_INTERMEDIARIO_H

#include <string.h>
#include "arvore.h"

void gerar_codigo(no_arvore * raiz);
char * gerar_codigo_expr(no_arvore *raiz);
void gerar_codigo_attr(no_arvore *raiz);

#endif
