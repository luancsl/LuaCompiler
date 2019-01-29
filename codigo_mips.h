#ifndef CODIGO_MIPS_H
#define CODIGO_MIPS_H

#include "lista_intermediario.h"
#include "tabela.h"

void gerar_codigo_mips(lista* lista);
void gerar_header_mips(tabela* tab);
void gerar_end_main();

#endif