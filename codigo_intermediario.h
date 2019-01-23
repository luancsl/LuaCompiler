#ifndef CODIGO_INTERMEDIARIO_H
#define CODIGO_INTERMEDIARIO_H

#include <string.h>
#include "arvore.h"
#include "lista_intermediario.h"


void gerar_codigo(lista* list, no_arvore * raiz);
char * gerar_codigo_expr(lista* list, no_arvore *raiz);
void gerar_codigo_attr(lista* list, no_arvore *raiz);
void gerar_codigo_ifelse(lista* list, no_arvore *raiz);
void gerar_codigo_while(lista* list, no_arvore *raiz);
void gerar_codigo_funcao(lista* list, no_arvore *raiz);
void gerar_codigo_print(lista* list, no_arvore *raiz);

#endif
