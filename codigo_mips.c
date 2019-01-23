#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "codigo_mips.h"
#include "codigo_intermediario.h"
#include "tabela.h"
#include "y.tab.h"


void gerar_var_mips(tabela* tab){
    printf(".data\n");

    if(tab != NULL){
        no_tabela * temp = tab->primeiro;
        while(temp != NULL) {
            printf("%s: .space 4\n", temp->dado->lexema);	
            temp = temp->proximo;
        }
    }
    printf("newline: .asciiz \"\\n\"\n");
    printf("\n");
	printf(".text\n");
    printf(".globl main\n");
    printf("\n");
    printf("main:\n");
}


void gerar_codigo_mips(lista* lista, tabela* tab){

    gerar_var_mips(tab);

    no_lista* no = lista->primeiro;

    while(no != NULL){

        instr* instr = no->instrucao;

        switch (instr->opcode)
        {

            case NUMBER:
                printf("li %s, %s\n", instr->result, instr->firstOp);
                break;

            case ID:
                printf("lw %s, %s\n", instr->result, instr->firstOp);
                break;

            case ATTR:
                printf("%s  %s, %s\n", "sw", instr->firstOp, instr->result);
                printf("\n");
                break;

            case ADD:    
                printf("%s  %s, %s, %s\n", "add", instr->result, instr->firstOp, instr->secondOp);
                printf("\n");
                break;
            
            case SUB:
                printf("%s  %s, %s, %s\n", "sub", instr->result, instr->firstOp, instr->secondOp);
                printf("\n");
                break;

            case MUL:
                printf("%s  %s, %s, %s\n", "mul", instr->result, instr->firstOp, instr->secondOp);
                printf("\n");
                break;

            case DIV:
                printf("%s  %s, %s, %s\n", "div", instr->result, instr->firstOp, instr->secondOp);
                printf("\n");
                break;

            case MOD:
                printf("%s  %s, %s, %s\n", "rem", instr->result, instr->firstOp, instr->secondOp);
                printf("\n");
                break;

            case EQ:
                printf("%s  %s, %s, %s\n", "subu", instr->result, instr->firstOp, instr->secondOp);
                printf("%s  %s, %s, %s\n", "sltu", instr->result, "$zero", instr->result);
                printf("%s  %s, %s, %s\n", "xori", instr->result, instr->result, "1");
                printf("\n");
                break;

            case LESS:
                printf("%s  %s, %s, %s\n", "slt", instr->result, instr->firstOp, instr->secondOp);
                printf("\n");
                break;

            case BIGG:
                printf("%s  %s, %s, %s\n", "slt", instr->result, instr->secondOp, instr->firstOp);
                printf("\n");
                break;

            case NE:
                printf("%s  %s, %s, %s\n", "subu", instr->result, instr->firstOp, instr->secondOp);
                printf("%s  %s, %s, %s\n", "sltu", instr->result, "$zero", instr->result);
                printf("\n");
                break;

            case LE:
                printf("%s  %s, %s, %s\n", "sltu", instr->result, instr->secondOp, instr->firstOp);
                printf("xori %s, %s, %s\n", instr->result, instr->result, "1");
                printf("\n");
                break;

            case GE:
                printf("%s  %s, %s, %s\n", "sltu", instr->result, instr->firstOp, instr->secondOp);
                printf("xori %s, %s, %s\n", instr->result, instr->result, "1");
                printf("\n");
                break;

            case UNARY:
                break;

            case TRUE:
                printf("li %s, %s\n", instr->result, instr->firstOp);
                break;

            case FALSE:
                printf("li %s, %s\n", instr->result, instr->firstOp);
                break;

            case NOT:
                printf("%s  %s, %s\n", "not", instr->result, instr->firstOp);
                break;

            case AND:
                printf("%s  %s, %s, %s\n", "and", instr->result, instr->firstOp, instr->secondOp);
                printf("\n");
                break;

            case OR:
                printf("%s  %s, %s, %s\n", "or", instr->result, instr->firstOp, instr->secondOp);
                printf("\n");
                break;

            case LAB:
                printf("%s: \n", instr->result);
                printf("\n");
                break;
            
            case GOTO:
                printf("%s %s\n", "j", instr->result);
                printf("\n");
                break;

            case IF:
                printf("%s  %s, %s, %s\n", "beq", instr->result, "$zero", instr->firstOp);
                printf("\n");
                break;

            case ELSE:
                break;

            case WHILE:
                printf("%s  %s, %s, %s\n", "beq", instr->result, "$zero", instr->firstOp);
                printf("\n");
                break;

            case READ:
                printf("li $v0, 5\n");
                printf("syscall\n");
                printf("move %s, %s\n", instr->result, "$v0");
                printf("\n");
                break;

            case PRINT:

                printf("li $v0, 1\n");
                printf("%s %s, %s\n", "move", "$a0", instr->result);
                printf("syscall\n");

                printf("li $v0, 4\n");
                printf("%s %s, %s\n", "la", "$a0", "newline");
                printf("syscall\n");
                printf("\n");
                break;

            case FUNCTION:
                printf("addi $sp, $sp, -4\n");
	            printf("sw $ra, 0($sp)\n");

                printf("%s  %s, %s\n", "sw", "$a0", instr->result);
        
                printf("\n");
                break;

            case RETURN:
                printf("%s  %s, %s\n", "sw", instr->firstOp, instr->result);
                printf("addi $sp, $sp, -4\n");
                printf("jr $ra\n");
                printf("\n");
                break;

            case FUNCTION_C:
                printf("move $a0, %s\n", instr->secondOp);
                printf("jal %s\n", instr->firstOp);
                printf("lw $ra, 0($sp)\n");
                printf("%s  %s, %s\n", "sw", "$v0", instr->firstOp);
                printf("lw %s, %s\n", instr->result, instr->firstOp);
                printf("\n");
                break;
        
            default:
                break;
        }

        no = no->proximo;
    
    }
    
}


