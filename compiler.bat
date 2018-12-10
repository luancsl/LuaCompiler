echo off
cls
lex interpretador.lex
bison -dy interpretador.yacc
gcc -o program lex.yy.c y.tab.c y.tab.h arvore.c arvore.h tabela.c tabela.h