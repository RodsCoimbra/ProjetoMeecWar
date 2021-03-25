#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <time.h>

int linha =9, coluna=1, resl, resc = 9, i, modop=1, pecas1, pecas2, pecas3 ,pecas4 ,pecas5 ,pecas6 ,pecas7 ,pecas8, camada2[16][25], contador = 0;
char tabuleiro [16][25]; //array que conterá os espaços do tabuleiro. Neste caso o array tem uma dimensão acima tanto nas linhas como nas colunas para facilitar a utilização no código, ou seja, as coordenadas correspondem exatamente com o array, deixando de parte a linha 0 e coluna 0 do array. Por exemplo A9 = tabuleiro [9][1] e não [8][0].
char letra = 'A';
int bar [3]={0,1,42}; //array que conterá todos as referências de barcos




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

void camada(int linha2,int coluna2, int peca){
    int i, j;
    camada2 [linha2][coluna2] = peca;                   //camada 2 é o array que anotará as posições dos barcos e das posições livres
    tabuleiro [linha2][coluna2] = peca + '0';         //apenas para teste
    for(i = -1; i <= 1; i++){
            for(j=-1; j <= 1; j++){
                if(camada2[linha2+i][coluna2+j] == 0){
                camada2[linha2+i][coluna2+j] = 9;
                //tabuleiro[linha2+i][coluna2+j] = '9';     //apenas para teste
                }           //o número 9 na segunda camada significa lugar onde já não se pode colocar barcos
                else{
                }
        }
    }
}

void modo_p1(){
        int l,j;//variáveis para o ciclo for que servem respetivamente de linha e coluna para a coordenada de posicionamento
        srand(time(NULL));
        for (l=resl; l >= 1; l-=3){
            for(j= 1; j < resc; j+=3){
            barco(bar[rand() % 3],l,j);
            }
        }
}

void barco(int ref, int l, int j){
if(contador == 3){
      ref = 0;}
    if(ref==0){
        contador = 0;
    }
    if(ref==1){
        if(camada2[l][j] == 0){
            camada(l, j, 1);
            contador = 0;
        }
        else{contador++;
            barco(bar[rand() % 3],l,j);}
    }
    else if(ref==42){
        if(camada2[l-2][j]== 0 && camada2[l-1][j]== 0 && camada2[l][j]== 0 && camada2[l-2][j+1] == 0 && camada2[l][j+1]== 0 && camada2[l-2][j+2] == 0 && camada2[l-1][j+2]== 0 && camada2[l][j+2]== 0){
            camada(l-2, j, 8); camada(l-1, j, 8); camada(l, j, 8); camada(l-2, j+1, 8); camada(l, j+1, 8); camada(l-2, j+2, 8); camada(l-1, j+2, 8); camada(l, j+2, 8);
            contador = 0;
        }
        else{contador++;
            barco(bar[rand() % 3],l,j);}
    }
    else{
}
}

int main(int argc, char *argv[]){   int opt, modo;
    int opterr = 0;
    while((opt= getopt(argc, argv,"t:j:p:d:1:2:3:4:5:6:7:8:"))!= -1 ){
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
        sscanf(optarg,"%d", &modop);
        break;
        case 'd':
        break;
        case '1':modo_p1();
        sscanf(optarg, "%d", pecas1);
        break;
        case '2':
        sscanf(optarg, "%d", pecas2);
        break;
        case '3':
        sscanf(optarg, "%d", pecas3);
        break;
        case '4':
        sscanf(optarg, "%d", pecas4);
        break;
        case '5':
        sscanf(optarg, "%d", pecas5);
        break;
        case '6':
        sscanf(optarg, "%d", pecas6);
        break;
        case '7':
        sscanf(optarg, "%d", pecas7);
        break;
        case '8':
        sscanf(optarg, "%d", pecas8);
        break;
        default:{
            printf("Carater %c nao identificado", optopt);
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
    if (modop==1){
    modo_p1();
    }
    tabu();
}


 void help (char zzz){     //colocar as intruções para usar os comandos
    printf("");
    printf("");
    printf("");
    printf("");
    printf("");
}
