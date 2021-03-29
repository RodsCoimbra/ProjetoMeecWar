#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <time.h>

int linha =9, coluna=1, resl, resc = 9, i, modop=1, pecas1, pecas2, pecas3 ,pecas4 ,pecas5 ,pecas6 ,pecas7 ,pecas8, camada2[16][25], contador = 0;
char tabuleiro [16][25]; //array que conterá os espaços do tabuleiro. Neste caso o array tem uma dimensão acima tanto nas linhas como nas colunas para facilitar a utilização no código, ou seja, as coordenadas correspondem exatamente com o array, deixando de parte a linha 0 e coluna 0 do array. Por exemplo A9 = tabuleiro [9][1] e não [8][0].
char letra = 'A';


void tabu(){                //função que dá print do tabuleiro
     printf("\n\n\n");
     letra = 'A';
     linha = resl;          //linha volta ao seu valor inicial
     coluna = 1;
     for(linha; linha >= 1; linha--){
            printf("%2d  ", linha);                             //print do número das linhas
            for(coluna; resc >= coluna; coluna++ ){
                printf("%c ", tabuleiro [linha][coluna]);       //print do tabuleiro
            }
             printf("\n");
             coluna = 1;                                        //reset da coluna para 1
    }
    printf("    ");
    for(coluna; resc >= coluna; coluna++){
        printf("%c ", letra);                                   //print da letra das colunas
        letra++;}
        printf("\n\n");
}

void camada(int linha2,int coluna2, int peca){          //Esta função serve para simultaniamente guardar os locais dos barcos, como também para assinalar os locais onde os próximos barcos não podem ficar
    int i, j;
    camada2 [linha2][coluna2] = peca;                   //camada 2 é o array que anotará as posições dos barcos e das posições livres
    tabuleiro [linha2][coluna2] = peca + '0';         //apenas para teste, caso queiras saber onde está a peça
    for(i = -1; i <= 1; i++){
            for(j=-1; j <= 1; j++){
                if(camada2[linha2+i][coluna2+j] == 0){      //Os dois "for" permitem a varedura da área toda à volta da peça e entrará no "if" caso alguma dessas coordenadas tenha o valor '
                camada2[linha2+i][coluna2+j] = 9;           //o número 9 na segunda camada significa lugar onde já não se pode colocar barcos
                //tabuleiro[linha2+i][coluna2+j] = '9';     //apenas para teste
                }
                else{
                }}}
}

int barco(int ref, int l, int j){      //Função que identifica todos os barcos pelo identificador global de cada peça
    if(contador == 3){                  //contador da função modo_p1 que quando igual a 3 considera a peça 1 centrada(ref=5)
      camada(l-1,j+1,1);
      return 1;}
    else{
        if(ref==0){                 // matriz vazia
        return 1;                   //retorna 1 para acabar e para parar o while na função modo_p1
        }
    ///peças num 1 aqui
    else if(ref==1){                //Caso da peça 1 no canto superior esquerdo
        if(camada2[l][j] == 0){     //Confirma se a peça pode ser colocada nesse espaço, ou seja, só se a camada2 tiver com aquela posição a zero
            camada(l, j, 1);        //Chama a função camada com as coordenadas da peça e com o identificador da peça
            return 1; }}              //retorna 1 para acabar e para parar o while na função modo_p1.
    //O resto das peças seguirá o mesmo padrão da primeira
    else if(ref==2){          
            if(camada2[l][j+1] == 0){
            camada(l, j+1, 1);
            return 1; }}
    
    else if(ref==3){          
            if(camada2[l][j+2] == 0){
            camada(l, j+2, 1);
            return 1; }}

    else if(ref==4){          
            if(camada2[l-1][j] == 0){
            camada(l-1, j, 1);
            return 1; }}
    
    else if(ref==5){          
            if(camada2[l-1][j+1] == 0){
            camada(l-1, j+1, 1);
            return 1; }}

    else if(ref==6){          
            if(camada2[l-1][j+2] == 0){
            camada(l-1, j+2, 1);
            return 1; }}

    else if(ref==7){          
            if(camada2[l-2][j] == 0){
            camada(l-2, j, 1);
            return 1; }}

    else if(ref==8){          
            if(camada2[l-2][j+1] == 0){
            camada(l-2, j+1, 1);
            return 1; }}

    else if(ref==9){          
            if(camada2[l-2][j+2] == 0){
            camada(l-2, j+2, 1);
            return 1; }}
    ///Fim peças 1

    ///Peças do num 2 aqui
    else if(ref==10){
        if(camada2[l][j] == 0 && camada2[l][j+1] == 0){
            camada(l, j, 2); camada(l, j+1, 2);
            return 1; }}

    else if(ref==11){
        if(camada2[l][j+1] == 0 && camada2[l][j+2] == 0){
            camada(l, j+1, 2); camada(l, j+2, 2);
            return 1; }}

    else if(ref==12){
        if(camada2[l-1][j] == 0 && camada2[l-1][j+1] == 0){
            camada(l-1, j, 2); camada(l-1, j+1, 2);
            return 1; }}

    else if(ref==13){
        if(camada2[l-1][j+1] == 0 && camada2[l-1][j+2] == 0){
            camada(l-1, j+1, 2); camada(l-1, j+2, 2);
            return 1; }}

    else if(ref==14){
        if(camada2[l-2][j] == 0 && camada2[l-2][j+1] == 0){
            camada(l-2, j, 2); camada(l-2, j+1, 2);
            return 1; }}

    else if(ref==15){
        if(camada2[l-2][j+1] == 0 && camada2[l-2][j+2] == 0){
            camada(l-2, j+1, 2); camada(l-2, j+2, 2);
            return 1; }}

    else if(ref==16){
        if(camada2[l][j] == 0 && camada2[l-1][j] == 0){
            camada(l, j, 2); camada(l-1, j, 2);
            return 1; }}

    else if(ref==17){
        if(camada2[l-1][j] == 0 && camada2[l-2][j] == 0){
            camada(l-1, j, 2); camada(l-2, j, 2);
            return 1; }}

    else if(ref==18){
        if(camada2[l][j+1] == 0 && camada2[l-1][j+1] == 0){
            camada(l, j+1, 2); camada(l-1, j+1, 2);
            return 1; }}

    else if(ref==19){
        if(camada2[l-1][j+1] == 0 && camada2[l-2][j+1] == 0){
            camada(l-1, j+1, 2); camada(l-2, j+1, 2);
            return 1; }}

    else if(ref==20){
        if(camada2[l][j+2] == 0 && camada2[l-1][j+2] == 0){
            camada(l, j+2, 2); camada(l-1, j+2, 2);
            return 1; }}

    else if(ref==21){
        if(camada2[l-1][j+2] == 0 && camada2[l-2][j+2] == 0){
            camada(l-1, j+2, 2); camada(l-2, j+2, 2);
            return 1; }}
    ///Fim peças 2

    ///peças num 3 aqui
    else if(ref==22){
        if(camada2[l][j] == 0 && camada2[l][j+1] == 0 && camada2[l][j+2] == 0 ){
            camada(l, j, 3); camada(l, j+1, 3); camada(l, j+2, 3);
            return 1; }}
    
    else if(ref==23){
        if(camada2[l-1][j] == 0 && camada2[l-1][j+1] == 0 && camada2[l-1][j+2] == 0 ){
            camada(l-1, j, 3); camada(l-1, j+1, 3); camada(l-1, j+2, 3);
            return 1; }}

    else if(ref==24){
        if(camada2[l-2][j] == 0 && camada2[l-2][j+1] == 0 && camada2[l-2][j+2] == 0 ){
            camada(l-2, j, 3); camada(l-2, j+1, 3); camada(l-2, j+2, 3);
            return 1; }}

    else if(ref==25){
        if(camada2[l][j] == 0 && camada2[l-1][j] == 0 && camada2[l-2][j] == 0 ){
            camada(l, j, 3); camada(l-1, j, 3); camada(l-2, j, 3);
            return 1; }}

    else if(ref==26){
        if(camada2[l][j+1] == 0 && camada2[l-1][j+1] == 0 && camada2[l-2][j+1] == 0 ){
            camada(l, j+1, 3); camada(l-1, j+1, 3); camada(l-2, j+1, 3);
            return 1; }}

    else if(ref==27){
        if(camada2[l][j+2] == 0 && camada2[l-1][j+2] == 0 && camada2[l-2][j+2] == 0 ){
            camada(l, j+2, 3); camada(l-1, j+2, 3); camada(l-2, j+2, 3);
            return 1; }}
    ///Fim peças 3

    ///peças do num 4 aqui
    else if(ref==28){
        if(camada2[l][j] == 0 && camada2[l][j+1] == 0 && camada2[l-1][j] == 0 && camada2[l-1][j+1] == 0){
            camada(l, j, 4); camada(l, j+1, 4); camada(l-1, j, 4); camada(l-1, j+1, 4);
            return 1; }}

    else if(ref==29){
        if(camada2[l][j+1] == 0 && camada2[l][j+2] == 0 && camada2[l-1][j+1] == 0 && camada2[l-1][j+2] == 0){
            camada(l, j+1, 4); camada(l, j+2, 4); camada(l-1, j+1, 4); camada(l-1, j+2, 4);
            return 1; }}

    else if(ref==30){
        if(camada2[l-1][j] == 0 && camada2[l-1][j+1] == 0 && camada2[l-2][j] == 0 && camada2[l-2][j+1] == 0){
            camada(l-1, j, 4); camada(l-1, j+1, 4); camada(l-2, j, 4); camada(l-2, j+1, 4);
            return 1; }}

    else if(ref==31){
        if(camada2[l-1][j+1] == 0 && camada2[l-1][j+2] == 0 && camada2[l-2][j+1] == 0 && camada2[l-2][j+2] == 0){
            camada(l-1, j+1, 4); camada(l-1, j+2, 4); camada(l-2, j+1, 4); camada(l-2, j+2, 4);
            return 1; }}
    ///Fim peças 4

    ///peças num 5 aqui
    ///Fim peças 5

    ///peças do num 6 aqui
    else if(ref==36){
        if(camada2[l][j+1] == 0 && camada2[l-1][j] == 0 && camada2[l-1][j+2] == 0 && camada2[l-2][j] == 0 && camada2[l-2][j+1] == 0 && camada2[l-2][j+2] == 0){
            camada(l, j+1, 6); camada(l-1, j, 6); camada(l-1, j+2, 6); camada(l-2, j, 6); camada(l-2, j+1, 6); camada(l-2, j+2, 6);
            return 1; }}

    else if(ref==37){
        if(camada2[l][j+1] == 0 && camada2[l][j+2] == 0 && camada2[l-1][j] == 0 && camada2[l-1][j+2] == 0 && camada2[l-2][j+1] == 0 && camada2[l-2][j+2] == 0){
            camada(l, j+1, 6); camada(l, j+2, 6); camada(l-1, j, 6); camada(l-1, j+2, 6); camada(l-2, j+1, 6); camada(l-2, j+2, 6);
            return 1; }}

    else if(ref==38){
        if(camada2[l][j] == 0 && camada2[l][j+1] == 0 && camada2[l][j+2] == 0 && camada2[l-1][j] == 0 && camada2[l-1][j+2] == 0 && camada2[l-2][j+1] == 0){
            camada(l, j, 6); camada(l, j+1, 6); camada(l, j+2, 6); camada(l-1, j, 6); camada(l-1, j+2, 6); camada(l-2, j+1, 6);
            return 1; }}

    else if(ref==39){
        if(camada2[l][j] == 0 && camada2[l][j+1] == 0 && camada2[l-1][j] == 0 && camada2[l-1][j+2] == 0 && camada2[l-2][j] == 0 && camada2[l-2][j+1] == 0){
            camada(l, j, 6); camada(l, j+1, 6); camada(l-1, j, 6); camada(l-1, j+2, 6); camada(l-2, j, 6); camada(l-2, j+1, 6);
            return 1; }}
    ///Fim peças 6

    ///peças num 7 aqui
    ///Fim peças 7

    ///peças num 8 aqui
    else if(ref==42){
        if(camada2[l-2][j]== 0 && camada2[l-1][j]== 0 && camada2[l][j]== 0 && camada2[l-2][j+1] == 0 && camada2[l][j+1]== 0 && camada2[l-2][j+2] == 0 && camada2[l-1][j+2]== 0 && camada2[l][j+2]== 0){
            camada(l-2, j, 8); camada(l-1, j, 8); camada(l, j, 8); camada(l-2, j+1, 8); camada(l, j+1, 8); camada(l-2, j+2, 8); camada(l-1, j+2, 8); camada(l, j+2, 8);
            return 1;}}
    ///Fim peças 8 
}
return 0;   //caso em que as peças não podem ser colocadas e portanto é retornado o valor 0 o que fará continuar a função while do modo_p1.
}


void modo_p1(){
        int l,j, posi;      //variáveis para o ciclo for que servem respetivamente de linha e coluna para a coordenada de posicionamento e posi que é zero se a posição do barco for inválida e 1 se for válida
        srand(time(NULL));  //seed para o random
        for (l=resl; l >= 1; l-=3){
            for(j= 1; j < resc; j+=3){          //os "for"" servem para mexer a coordenada de posicionamento das peças
            contador = 0;                       //reset do contador para 0
            posi = barco(rand() % 43,l,j);      //posi é igual a 1 ou 0 dependendo da funcao barco. A função barco é chamada com a ref igual a um numero random entre 0 a 42.
            ///Caso queiras testar uma peça podes substituir em cima o rand() % 43, pela referencia do barco e assim ele imprime na primeira matriz(canto superior esquerdo) o barco.
            while(posi == 0 ){
                contador++;                     //incremento contador
                posi = barco(rand() % 43,l,j);
            }
            }
        }
}

 void help (char *zzz){     //colocar as intruções para usar os comandos
    printf("");
    printf("");
    printf("");
    printf("");
    printf("");
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
    if (modop==1){
    modo_p1();
    }
    printf("\n\n");
    tabu();
}


