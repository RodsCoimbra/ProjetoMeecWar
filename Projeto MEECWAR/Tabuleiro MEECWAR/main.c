#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>

int linha, coluna=1, resl, resc = 9, i;
char tabuleiro [16][25]; //array que conterá os espaços do tabuleiro. Neste caso o array tem uma dimensão acima tanto nas linhas como nas colunas para facilitar a utilização no código, ou seja, as coordenadas correspondem exatamente com o array, deixando de parte a linha 0 e coluna 0 do array. Por exemplo A9 = tabuleiro [9][1] e não [8][0].
char letra = 'A';


void tabu(){
     letra = 'A';
     linha = resl;
     coluna = 1;
     for(linha; linha >= 1; linha--){
            printf("%2d  ", linha);
            for(coluna; resc >= coluna; coluna++ ){
                printf("%c ", tabuleiro [linha][coluna]);
            }
             printf("\n");
             coluna = 1;
    }
    printf("    ");
    for(coluna; resc >= coluna; coluna++ ){
        printf("%c ", letra);
        letra++;
}
}


int main(int argc, char *argv[])
{   int opt;
    int opterr = 0;
    while((opt= getopt(argc, argv,"t:"))!= -1 ){                
        switch (opt){
        case 't':
            sscanf(optarg,"%dx%d", &linha, &resc);
        break;
        case 'h':
            help(argv[0]);
            return 0;  //acho que não é necessário
        break;
        case 'j': //modo de jogo
        break;                  
        case 'p':
        break;
        case 'd':
        break;
        case '1':
        sscanf(optarg, "%d", peças1);
        break;
        case '2':
        sscanf(optarg, "%d", peças2);
        break;
        case '3':
        sscanf(optarg, "%d", peças3);
        break;
        case '4':
        sscanf(optarg, "%d", peças4);
        break;
        case '5':
        sscanf(optarg, "%d", peças5);
        break;
        case '6':
        sscanf(optarg, "%d", peças6);
        break;
        case '7':
        sscanf(optarg, "%d", peças7);
        break;
        case '8':
        sscanf(optarg, "%d", peças8);
        break;
        default{
            printf("Carater %c não identificado", optopt);

        }
        }
    }


    if((linha%3) !=0 || (resc%3 != 0) || (linha < 9) || (linha > 15) || (resc < 9) || (resc> 24)){ //caso em que não são verificadas as condições corretas para criar o tabuleiro
        printf("Erro! As dimensões do seu tabuleiro são invalidas. Tanto as linhas como as colunas tem de ser divisiveis por 3. Para alem disso a matriz minima e de 9x9 e a maxima e de 15x24 \n");
        exit(0);
    }
    resl = linha;
    for(linha; linha >= 1; linha--){
            printf("%2d  ", linha);
            for(coluna; resc >= coluna; coluna++ ){
                tabuleiro [linha][coluna] = '~';
                printf("%c ", tabuleiro [linha][coluna]);
            }
             printf("\n");
             coluna = 1;
    }
    printf("    ");
    for(coluna; resc >= coluna; coluna++){
        printf("%c ", letra);
        letra++;
    }
    printf("\n\n\n\n\n");

    tabuleiro[2][2] = '1';
    tabu();
}



void camada()
{
    int linha2 = 3, coluna2 = 2, i, j, resj, resi, camada2[16][25];
    camada2 [linha2][coluna2] = 2;
    j = resj;
    i = resi;
    for(i = -1; i <= 1; i++){
            for(j=-1; j <= 1; j++){
                if(camada2[linha2+i][coluna2+j] == 2){}
                else{
                    camada2[linha2+i][coluna2+j] = 1;
                }
        }
    }
}

void help (char *?????????){     //colocar as intruções para usar os comandos
    printf("");
    printf("");
    printf("");
    printf("");
    printf("");
}