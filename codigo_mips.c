#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "codigo_mips.h"
#include "codigo_intermediario.h"
#include "tabela.h"
#include "y.tab.h"



void gerar_header_mips(tabela* tab){
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

void gerar_end_main(){
    printf("\tli $v0,10\n");
    printf("\tsyscall\n");
    printf("\n");
}


void gerar_codigo_mips(lista* lista){

    no_lista* no = lista->primeiro;

    while(no != NULL){

        instr* instr = no->instrucao;

        switch (instr->opcode)
        {

            case NUMBER:
                printf("\tli %s, %s\n", instr->result, instr->firstOp);
                break;

            case ID:
                printf("\tlw %s, %s\n", instr->result, instr->firstOp);
                break;

            case ATTR:
                printf("\t%s  %s, %s\n", "sw", instr->firstOp, instr->result);
                printf("\n");
                break;

            case ADD:    
                printf("\t%s  %s, %s, %s\n", "add", instr->result, instr->firstOp, instr->secondOp);
                printf("\n");
                break;
            
            case SUB:
                printf("\t%s  %s, %s, %s\n", "sub", instr->result, instr->firstOp, instr->secondOp);
                printf("\n");
                break;

            case MUL:
                printf("\t%s  %s, %s, %s\n", "mul", instr->result, instr->firstOp, instr->secondOp);
                printf("\n");
                break;

            case DIV:
                printf("\t%s  %s, %s, %s\n", "div", instr->result, instr->firstOp, instr->secondOp);
                printf("\n");
                break;

            case MOD:
                printf("\t%s  %s, %s, %s\n", "rem", instr->result, instr->firstOp, instr->secondOp);
                printf("\n");
                break;

            case EQ:
                printf("\t%s  %s, %s, %s\n", "subu", instr->result, instr->firstOp, instr->secondOp);
                printf("\t%s  %s, %s, %s\n", "sltu", instr->result, "$zero", instr->result);
                printf("\t%s  %s, %s, %s\n", "xori", instr->result, instr->result, "1");
                printf("\n");
                break;

            case LESS:
                printf("\t%s  %s, %s, %s\n", "slt", instr->result, instr->firstOp, instr->secondOp);
                printf("\n");
                break;

            case BIGG:
                printf("\t%s  %s, %s, %s\n", "slt", instr->result, instr->secondOp, instr->firstOp);
                printf("\n");
                break;

            case NE:
                printf("\t%s  %s, %s, %s\n", "subu", instr->result, instr->firstOp, instr->secondOp);
                printf("\t%s  %s, %s, %s\n", "sltu", instr->result, "$zero", instr->result);
                printf("\n");
                break;

            case LE:
                printf("\t%s  %s, %s, %s\n", "sltu", instr->result, instr->secondOp, instr->firstOp);
                printf("\txori %s, %s, %s\n", instr->result, instr->result, "1");
                printf("\n");
                break;

            case GE:
                printf("\t%s  %s, %s, %s\n", "sltu", instr->result, instr->firstOp, instr->secondOp);
                printf("\txori %s, %s, %s\n", instr->result, instr->result, "1");
                printf("\n");
                break;

            case UNARY:
                break;

            case TRUE:
                printf("\tli %s, %s\n", instr->result, instr->firstOp);
                break;

            case FALSE:
                printf("\tli %s, %s\n", instr->result, instr->firstOp);
                break;

            case NOT:
                printf("\t%s  %s, %s\n", "not", instr->result, instr->firstOp);
                break;

            case AND:
                printf("\t%s  %s, %s, %s\n", "and", instr->result, instr->firstOp, instr->secondOp);
                printf("\n");
                break;

            case OR:
                printf("\t%s  %s, %s, %s\n", "or", instr->result, instr->firstOp, instr->secondOp);
                printf("\n");
                break;

            case LAB:
                printf("%s: \n", instr->result);
                break;
            
            case GOTO:
                printf("\t%s %s\n", "j", instr->result);
                printf("\n");
                break;

            case IF:
                printf("\t%s  %s, %s, %s\n", "beq", instr->result, "$zero", instr->firstOp);
                printf("\n");
                break;

            case ELSE:
                break;

            case WHILE:
                printf("\t%s  %s, %s, %s\n", "beq", instr->result, "$zero", instr->firstOp);
                printf("\n");
                break;

            case READ:
                printf("\tli $v0, 5\n");
                printf("\tsyscall\n");
                printf("\tmove %s, %s\n", instr->result, "$v0");
                printf("\n");
                break;

            case PRINT:

                printf("\tli $v0, 1\n");
                printf("\t%s %s, %s\n", "move", "$a0", instr->result);
                printf("\tsyscall\n");

                printf("\tli $v0, 4\n");
                printf("\t%s %s, %s\n", "la", "$a0", "newline");
                printf("\tsyscall\n");
                printf("\n");
                break;

            case FUNCTION:
                printf("\taddi $sp, $sp, -16\n");
	            printf("\tsw $ra, 0($sp)\n");
                printf("\tsw $t1, 4($sp)\n");
                printf("\tsw $t2, 8($sp)\n");
                printf("\tsw $t3, 12($sp)\n");
                
                printf("\t%s  %s, %s\n", "sw", "$a0", instr->firstOp);
        
                printf("\n");
                break;

            case RETURN:
                printf("\t%s $v1, %s\n", "move", instr->firstOp);
                printf("\tlw $ra, 0($sp)\n");
                printf("\tlw $t1, 4($sp)\n");
                printf("\tlw $t2, 8($sp)\n");
                printf("\tlw $t3, 12($sp)\n");
                printf("\taddi $sp, $sp, 16\n");
                printf("\tjr $ra\n");
                printf("\n");
                break;

            case FUNCTION_C:
                printf("\tmove $a0, %s\n", instr->secondOp);
                printf("\tjal %s\n", instr->firstOp);
                printf("\t%s  %s, %s\n", "move", instr->result, "$v1");
                printf("\n");
                break;
        
            default:
                break;
        }

        no = no->proximo;
    
    }
    
}


