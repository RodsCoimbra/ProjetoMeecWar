#include <stdio.h>
#include <stdlib.h>

int main()
{
    int linha, coluna, res, verificador = 0;
    while(verificador == 0){
        printf("Escreva as dimensões do jogo (linha coluna): ");
            // condicao que permite repetir o tamanho do tabuleiro caso o utilizador se engane.

    if(scanf("%d %d", &linha, &coluna) != 2){ //caso em que o utilizador não escreve dois números inteiros
        printf("Erro!Input invalido. Escreva linha e depois espaço coluna.\n");
        exit(0);

    }
    if((linha%3) !=0 || (coluna%3 != 0) || (linha < 9) || (linha > 15) || (coluna < 9) || (coluna > 24)){ //caso em que não são verificadas as condições corretas para criar o tabuleiro
        printf("Erro! As dimensões do seu tabuleiro são invalidas. Tanto as linhas como as colunas tem de ser divisiveis por 3. Para alem disso a matriz minima e de 9x9 e a maxima e de 15x24 \n");
        verificador = 0;
    }
    else{
        verificador = 1; //caso em que está tudo correto e portanto o verificador fica igual 1 para não pedir novamente o input do utilizador
    }
    }
    char tabuleiro [16][25]; //array que conterá os espaços do tabuleiro. Neste caso o array tem uma dimensão acima tanto nas linhas como nas colunas para facilitar a utilização no código, ou seja, as coordenadas correspondem exatamente com o array, deixando de parte a linha 0 e coluna 0 do array. Por exemplo A9 = tabuleiro [9][1] e não [8][0].
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
