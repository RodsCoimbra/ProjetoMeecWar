#include <stdio.h>
#include <stdlib.h>

int main()
{
    int a, b, c;
    printf("Escreva as dimensões do jogo (linha coluna): ");
    if(scanf("%d %d", &a, &b) != 2){
        printf("ERRO!Input inválido. Escreva linha e depois espaço coluna.\n");
        exit(0);
    }
    char letra = 'A';
    c = b;
    for(a; a >= 1; a--){
            printf("%d ", a);
            for(b; b >= 1; b-- ){
                printf("~ ");
            }
             printf("\n");
             b = c;
    }
    printf("  ");
    for(b; b >= 1; b-- ){
        printf("%c ", letra);
        letra++;
    }

}
