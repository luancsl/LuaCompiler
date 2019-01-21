echo off
cls
lex interpretador.lex
bison -dy -v interpretador.yacc
gcc -o program lex.yy.c y.tab.c y.tab.h arvore.c arvore.h tabela.c tabela.h tabelaNumero.c tabelaNumero.h codigo_intermediario.c codigo_intermediario.h lista_intermediario.h lista_intermediario.c codigo_mips.h codigo_mips.c