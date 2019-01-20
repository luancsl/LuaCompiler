#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef unsigned int Word;

int main(){

    float n = atof("11.00");

    Word i = (Word) n;

    printf("%d", (n == (float) i));

    printf("O valor e %d", i );

}