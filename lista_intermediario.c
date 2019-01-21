#include <stdlib.h>
#include <stdio.h>
#include "lista_intermediario.h"


instr* criar_instrucao(int opcode, char* result, char* firstOp, char* secondOp){
    instr* novo = (instr *) malloc(sizeof(instr));
    novo->opcode = opcode;
    novo->result = result;
    novo->firstOp = firstOp;
    novo->secondOp = secondOp;
    return novo;
}

void inserir_instrucao(lista* lista, instr* instrucao){
    no_lista* novo = (no_lista *) malloc(sizeof(no_lista));
    novo->instrucao = instrucao;
    
    if(lista->primeiro == NULL) {
        
        novo->proximo = NULL;
        lista->primeiro = novo;
        lista->ultimo = novo;
    }else{
        lista->ultimo->proximo = novo;
        lista->ultimo = novo;    
    }
    
}

lista* init_lista(){
    lista* l = (lista *) malloc(sizeof(lista));
    l->primeiro = NULL;
    l->ultimo = NULL;
    return l;
}