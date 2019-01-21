#ifndef LISTA_INTERMEDIARIO_H
#define LISTA_INTERMEDIARIO_H

#include "lista_intermediario.h"

typedef struct instr {
  int opcode;
  char* result;
  char* firstOp;
  char* secondOp;
} instr;

typedef struct no_lista{
    struct no_lista *proximo;
    instr* instrucao;
} no_lista;

typedef struct lista {
    no_lista *primeiro;
    no_lista *ultimo;
}lista;

instr * criar_instrucao(int opcode, char* result, char* firstOp, char* secondOp);

void inserir_instrucao(lista* lista, instr* instrucao);

lista* init_lista();

#endif