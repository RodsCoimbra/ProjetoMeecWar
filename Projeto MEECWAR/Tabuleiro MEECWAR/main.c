#include <stdio.h>
#include <stdlib.h>

int main()
{
    int linha, coluna, res;
    printf("Escreva as dimensões do jogo (linha coluna): ");
    if(scanf("%d %d", &linha, &coluna) != 2){
        printf("ERRO!Input inválido. Escreva linha e depois espaço coluna.\n");
        exit(0);
    }
    char tabuleiro [15][24];
    char letra = 'A';
    res = coluna;
    for(linha; linha >= 1; linha--){
            printf("%2d ", linha);
            for(coluna; coluna >= 1; coluna-- ){
                tabuleiro [linha][coluna] = '~';
                printf("%c ", tabuleiro [linha][coluna]);
            }
             printf("\n");
             coluna = res;
    }
    printf("   ");
    for(coluna; coluna >= 1; coluna-- ){
        printf("%c ", letra);
        letra++;
    }

}
