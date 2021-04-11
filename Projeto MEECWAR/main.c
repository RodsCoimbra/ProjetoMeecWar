#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

int camada2[17][26][42]={{{}}}, id_peca[41] = {};
int resl=9, resc = 9, pecas_num[9] = {0},  contador = 0, modod = 1, total_b = 0, conta_b = 0, tiro = 0, disp_c,disp_l, veri, identificador = 0;
char tabuleiro [16][25]; //array que conterá os espaços do tabuleiro. Neste caso o array tem uma dimensão acima tanto nas linhas como nas colunas para facilitar a utilização no código, ou seja, as coordenadas correspondem exatamente com o array, deixando de parte a linha 0 e coluna 0 do array. Por exemplo A9 = tabuleiro [9][1] e não [8][0].
char letra = 'A';

void tabu(){                //função que dá print do tabuleiro
     int linha, coluna;
     system("clear");       //apagar o tabuleiro anterior para nao ficar cheio de tabuleiros
     letra = 'A';
     for(linha = resl; linha >= 1; linha--){
            printf("%2d  ", linha);                             //print do número das linhas
            for(coluna = 1; resc >= coluna; coluna++ ){             //print do tabuleiro, com condições para mudar a cor de cada especifico
                if (tabuleiro [linha][coluna] == 'x'){
                printf("\033[0;34m%c \033[0;30m", tabuleiro [linha][coluna]);}          //cor azul para a água que ainda não foi acertada
                else if (tabuleiro [linha][coluna] == '-'){
                  printf("%c ", tabuleiro [linha][coluna]);}         //em preto caso já tenham disparado e acertou na agua
                else {
                   printf("\033[0;31m%c \033[0;30m", tabuleiro [linha][coluna]);}
                }
             printf("\n");}
    printf("    ");
    for(coluna = 1; resc >= coluna; coluna++){
        printf("%c ", letra);                                   //print da letra das colunas
        letra++;}
        printf("\n\n");
}
void camada(int linha2,int coluna2, int peca){          //Esta função serve para simultaniamente guardar os locais dos barcos, como também para assinalar os locais onde os próximos barcos não podem ficar
    int i, j,l,k;
    total_b++;
    camada2 [linha2][coluna2][0] = peca;                   //camada 2 é o array que anotará as posições dos barcos e das posições livres
    //tabuleiro [linha2][coluna2] = peca + '0';         //apenas para teste, caso queiras saber onde está a peça
    for(i = -1; i <= 1; i++){
            for(j=-1; j <= 1; j++){
                if(camada2[linha2+i][coluna2+j][0] == 0){      //Os dois "for" permitem a varedura da área toda à volta da peça e entrará no "if" caso alguma dessas coordenadas tenha o valor '
                camada2[linha2+i][coluna2+j][0] = 9;           //o número 9 na segunda camada significa lugar onde já não se pode colocar barcos
                if(modod == 3){
                camada2[linha2+i][coluna2+j][identificador] = 11;}
                //tabuleiro[linha2+i][coluna2+j] = '9';     //apenas para teste
                }
                else{
                }}}
for(l = resl; l >= 1; l--){
    for(k = 1; resc >= k; k++){
    for (i = identificador+1; i < 41; i++){
    camada2[l][k][i] = camada2[l][k][identificador];}}}
}

void disparo(){
int col;
if(modod == 3 && camada2[disp_l][disp_c][identificador-1] == 11 && camada2[disp_l][disp_c][0] == 9){}
else{
col = disp_c + '@';             //carater a indicar a coluna, soma-se a '@' pois é o simbolo antes do 'A'
tiro++;
if (camada2[disp_l][disp_c][0] == 0 || camada2[disp_l][disp_c][0] == 9){
    tabuleiro[disp_l][disp_c] = 'x';}
else{tabuleiro[disp_l][disp_c] = camada2[disp_l][disp_c][0] + '0';
        conta_b++;
        veri++;}
camada2[disp_l][disp_c][0] = 10;
tabu();
printf("Tiro disparado em : %c%d\n",col,disp_l);
if (tabuleiro[disp_l][disp_c] == 'x'){
    printf("Acertaste na \033[0;34magua\033[0;30m! Mais sorte no proximo tiro.\n\n");
    }
else{
    printf("Acertaste num \033[0;31mbarco %c\033[0;30m!\n\n", tabuleiro[disp_l][disp_c]);}
    //sleep(1);                 //Esperar- Apenas para teste
}
}

void cruz(int veri){
switch(veri){
case 0:
disp_c +=1; disp_l -=1;   //meio
disparo();
break;
case 1:
disp_c +=1;               //centro cima
disparo();
break;
case 2:
disp_l -=2; disp_c +=1;   //centro baixo
disparo();
break;
case 3:
disp_l -=1;               //esquerda meio
disparo();
break;
case 4:
disp_c +=2; disp_l -=1;   //direita meio
disparo();
break;
case 5:                   //canto superior esquerdo
disparo();
break;
case 6:
disp_c +=2; disp_l -=2;   //canto inferior direito
disparo();
break;
case 7:
disp_c +=2;               //canto superior direito
disparo();
break;
case 8:
disp_l -=2;               //canto inferior esquerdo
disparo();
break;
default:{}
}
}

void conta_pecas(){
int num, a;
for (a = 1; a < 9 ;a++){
pecas_num[a] = 0;}
for (num = 1; num <= 40; num ++){
    switch (id_peca[num]){
    case 1:
        pecas_num[1]++;
        break;
    case 2:
        pecas_num[2]++;
        break;
    case 3:
        pecas_num[3]++;
        break;
    case 4:
        pecas_num[4]++;
        break;
    case 5:
        pecas_num[5]++;
        break;
    case 6:
        pecas_num[6]++;
        break;
    case 7:
        pecas_num[7]++;
        break;
    case 8:
        pecas_num[8]++;
        break;
    default:
        break;}}
}
void modo_d1(){                                    //Modo de disparo aleatório
srand(time(NULL));
int verificador = 0;
while(verificador == 0){
disp_c = (rand() % resc) +1;
disp_l = (rand() % resl) +1;
if (camada2[disp_l][disp_c][0] != 10){             //impedir repeticoes
    verificador = 1;
}}
disparo();
}

void modo_d2_e_3(){
int num = 0, destruir_b, save_l, save_c, k;
identificador = 1;
for (disp_l=resl; disp_l >= 1; disp_l-=3){
            save_l = disp_l;
            for(disp_c = 1; disp_c < resc && conta_b != total_b; disp_c+=3){
            veri = 0;
            save_c = disp_c;
            num++;
            destruir_b = id_peca[num];
            for(k=0; veri != destruir_b || (destruir_b == 0 && k != 9); k++){
                cruz(k);
                disp_c = save_c;
                disp_l = save_l;}
                if(modod==3){
                identificador++;}
}}}

int barco(int ref, int l, int j){      //Função que identifica todos os barcos pelo identificador global de cada peça
    identificador++;
    if(contador == 3){                  //contador da função modo_p1 que quando igual a 3 considera a peça 1 centrada(ref=5)
     camada(l-1,j+1,1);
     return 1;}
    else{
        if(ref==0){                 // matriz vazia
        return 0;                   //retorna 1 para acabar e para parar o while na função modo_p1
        }
    //peças num 1 aqui
    else if(ref==1){                //Caso da peça 1 no canto superior esquerdo
        if(camada2[l][j][0] == 0){     //Confirma se a peça pode ser colocada nesse espaço, ou seja, só se a camada2 tiver com aquela posição a zero
            camada(l, j, 1);        //Chama a função camada com as coordenadas da peça e com o identificador da peça
            return 1; }}            //retorna 1 para acabar e para parar o while na função modo_p1.
    //O resto das peças seguirá o mesmo padrão da primeira
    else if(ref==2){
            if(camada2[l][j+1][0] == 0){
            camada(l, j+1, 1);
            return 1; }}

    else if(ref==3){
            if(camada2[l][j+2][0] == 0){
            camada(l, j+2, 1);
            return 1; }}

    else if(ref==4){
            if(camada2[l-1][j][0] == 0){
            camada(l-1, j, 1);
            return 1; }}

    else if(ref==5){
            if(camada2[l-1][j+1][0] == 0){
            camada(l-1, j+1, 1);
            return 1; }}

    else if(ref==6){
            if(camada2[l-1][j+2][0] == 0){
            camada(l-1, j+2, 1);
            return 1; }}

    else if(ref==7){
            if(camada2[l-2][j][0] == 0){
            camada(l-2, j, 1);
            return 1; }}

    else if(ref==8){
            if(camada2[l-2][j+1][0] == 0){
            camada(l-2, j+1, 1);
            return 1; }}

    else if(ref==9){
            if(camada2[l-2][j+2][0] == 0){
            camada(l-2, j+2, 1);
            return 1; }}
    //Fim peças 1

    //Peças do num 2 aqui
    else if(ref==10){
        if(camada2[l][j][0] == 0 && camada2[l][j+1][0] == 0){
            camada(l, j, 2); camada(l, j+1, 2);
            return 2; }}

    else if(ref==11){
        if(camada2[l][j+1][0] == 0 && camada2[l][j+2][0] == 0){
            camada(l, j+1, 2); camada(l, j+2, 2);
            return 2; }}

    else if(ref==12){
        if(camada2[l-1][j][0] == 0 && camada2[l-1][j+1][0] == 0){
            camada(l-1, j, 2); camada(l-1, j+1, 2);
            return 2; }}

    else if(ref==13){
        if(camada2[l-1][j+1][0] == 0 && camada2[l-1][j+2][0] == 0){
            camada(l-1, j+1, 2); camada(l-1, j+2, 2);
            return 2; }}

    else if(ref==14){
        if(camada2[l-2][j][0] == 0 && camada2[l-2][j+1][0] == 0){
            camada(l-2, j, 2); camada(l-2, j+1, 2);
            return 2; }}

    else if(ref==15){
        if(camada2[l-2][j+1][0] == 0 && camada2[l-2][j+2][0] == 0){
            camada(l-2, j+1, 2); camada(l-2, j+2, 2);
            return 2; }}

    else if(ref==16){
        if(camada2[l][j][0] == 0 && camada2[l-1][j][0]== 0){
            camada(l, j, 2); camada(l-1, j, 2);
            return 2; }}

    else if(ref==17){
        if(camada2[l-1][j][0] == 0 && camada2[l-2][j][0] == 0){
            camada(l-1, j, 2); camada(l-2, j, 2);
            return 2; }}

    else if(ref==18){
        if(camada2[l][j+1][0] == 0 && camada2[l-1][j+1][0] == 0){
            camada(l, j+1, 2); camada(l-1, j+1, 2);
            return 2; }}

    else if(ref==19){
        if(camada2[l-1][j+1][0] == 0 && camada2[l-2][j+1][0] == 0){
            camada(l-1, j+1, 2); camada(l-2, j+1, 2);
            return 2; }}

    else if(ref==20){
        if(camada2[l][j+2][0] == 0 && camada2[l-1][j+2][0] == 0){
            camada(l, j+2, 2); camada(l-1, j+2, 2);
            return 2; }}

    else if(ref==21){
        if(camada2[l-1][j+2][0] == 0 && camada2[l-2][j+2][0] == 0){
            camada(l-1, j+2, 2); camada(l-2, j+2, 2);
            return 2; }}
    //Fim peças 2

    //peças num 3 aqui
    else if(ref==22){
        if(camada2[l][j][0] == 0 && camada2[l][j+1][0] == 0 && camada2[l][j+2][0] == 0 ){
            camada(l, j, 3); camada(l, j+1, 3); camada(l, j+2, 3);
            return 3; }}

    else if(ref==23){
        if(camada2[l-1][j][0] == 0 && camada2[l-1][j+1][0] == 0 && camada2[l-1][j+2][0] == 0 ){
            camada(l-1, j, 3); camada(l-1, j+1, 3); camada(l-1, j+2, 3);
            return 3; }}

    else if(ref==24){
        if(camada2[l-2][j][0] == 0 && camada2[l-2][j+1][0] == 0 && camada2[l-2][j+2][0] == 0 ){
            camada(l-2, j, 3); camada(l-2, j+1, 3); camada(l-2, j+2, 3);
            return 3; }}

    else if(ref==25){
        if(camada2[l][j][0] == 0 && camada2[l-1][j][0] == 0 && camada2[l-2][j][0] == 0 ){
            camada(l, j, 3); camada(l-1, j, 3); camada(l-2, j, 3);
            return 3; }}

    else if(ref==26){
        if(camada2[l][j+1][0] == 0 && camada2[l-1][j+1][0] == 0 && camada2[l-2][j+1][0] == 0 ){
            camada(l, j+1, 3); camada(l-1, j+1, 3); camada(l-2, j+1, 3);
            return 3; }}

    else if(ref==27){
        if(camada2[l][j+2][0] == 0 && camada2[l-1][j+2][0] == 0 && camada2[l-2][j+2][0] == 0 ){
            camada(l, j+2, 3); camada(l-1, j+2, 3); camada(l-2, j+2, 3);
            return 3; }}
    //Fim peças 3

    //peças do num 4 aqui
    else if(ref==28){
        if(camada2[l][j][0] == 0 && camada2[l][j+1][0] == 0 && camada2[l-1][j][0] == 0 && camada2[l-1][j+1][0] == 0){
            camada(l, j, 4); camada(l, j+1, 4); camada(l-1, j, 4); camada(l-1, j+1, 4);
            return 4; }}

    else if(ref==29){
        if(camada2[l][j+1][0] == 0 && camada2[l][j+2][0] == 0 && camada2[l-1][j+1][0] == 0 && camada2[l-1][j+2][0] == 0){
            camada(l, j+1, 4); camada(l, j+2, 4); camada(l-1, j+1, 4); camada(l-1, j+2, 4);
            return 4; }}

    else if(ref==30){
        if(camada2[l-1][j][0] == 0 && camada2[l-1][j+1][0] == 0 && camada2[l-2][j][0] == 0 && camada2[l-2][j+1][0]== 0){
            camada(l-1, j, 4); camada(l-1, j+1, 4); camada(l-2, j, 4); camada(l-2, j+1, 4);
            return 4; }}

    else if(ref==31){
        if(camada2[l-1][j+1][0] == 0 && camada2[l-1][j+2][0] == 0 && camada2[l-2][j+1][0] == 0 && camada2[l-2][j+2][0] == 0){
            camada(l-1, j+1, 4); camada(l-1, j+2, 4); camada(l-2, j+1, 4); camada(l-2, j+2, 4);
            return 4; }}
    //Fim peças 4

    //peças num 5 aqui
    else if(ref==32){
        if(camada2[l][j][0] == 0 && camada2[l][j+1][0] == 0 && camada2[l][j+2][0] == 0 && camada2[l-1][j+1][0] == 0 && camada2[l-2][j+1][0] == 0){
            camada(l, j, 5); camada(l, j+1, 5); camada(l, j+2, 5); camada(l-1, j+1, 5); camada(l-2, j+1, 5);
            return 5; }}

    else if(ref==33){
        if(camada2[l][j][0] == 0 && camada2[l-1][j][0] == 0 && camada2[l-2][j][0] == 0 && camada2[l-1][j+1][0] == 0 && camada2[l-1][j+2][0] == 0){
            camada(l, j, 5); camada(l-1, j, 5); camada(l-2, j, 5); camada(l-1, j+1, 5); camada(l-1, j+2, 5);
            return 5; }}

    else if(ref==34){
        if(camada2[l][j+1][0] == 0 && camada2[l-1][j+1][0] == 0 && camada2[l-2][j][0] == 0 && camada2[l-2][j+1][0] == 0 && camada2[l-2][j+2][0] == 0){
            camada(l, j+1, 5); camada(l-1, j+1, 5); camada(l-2, j, 5); camada(l-2, j+1, 5); camada(l-2, j+2, 5);
            return 5; }}

    else if(ref==35){
        if(camada2[l-1][j][0] == 0 && camada2[l-1][j+1][0] == 0 && camada2[l][j+2][0] == 0 && camada2[l-1][j+2][0] == 0 && camada2[l-2][j+2][0] == 0){
            camada(l-1, j, 5); camada(l-1, j+1, 5); camada(l, j+2, 5); camada(l-1, j+2, 5); camada(l-2, j+2, 5);
            return 5; }}
    //Fim peças 5

    //peças do num 6 aqui
    else if(ref==36){
        if(camada2[l][j+1][0] == 0 && camada2[l-1][j][0] == 0 && camada2[l-1][j+2][0] == 0 && camada2[l-2][j][0] == 0 && camada2[l-2][j+1][0] == 0 && camada2[l-2][j+2][0] == 0){
            camada(l, j+1, 6); camada(l-1, j, 6); camada(l-1, j+2, 6); camada(l-2, j, 6); camada(l-2, j+1, 6); camada(l-2, j+2, 6);
            return 6; }}

    else if(ref==37){
        if(camada2[l][j+1][0] == 0 && camada2[l][j+2][0] == 0 && camada2[l-1][j][0] == 0 && camada2[l-1][j+2][0] == 0 && camada2[l-2][j+1][0] == 0 && camada2[l-2][j+2][0] == 0){
            camada(l, j+1, 6); camada(l, j+2, 6); camada(l-1, j, 6); camada(l-1, j+2, 6); camada(l-2, j+1, 6); camada(l-2, j+2, 6);
            return 6; }}

    else if(ref==38){
        if(camada2[l][j][0] == 0 && camada2[l][j+1][0] == 0 && camada2[l][j+2][0] == 0 && camada2[l-1][j][0] == 0 && camada2[l-1][j+2][0] == 0 && camada2[l-2][j+1][0] == 0){
            camada(l, j, 6); camada(l, j+1, 6); camada(l, j+2, 6); camada(l-1, j, 6); camada(l-1, j+2, 6); camada(l-2, j+1, 6);
            return 6; }}

    else if(ref==39){
        if(camada2[l][j][0] == 0 && camada2[l][j+1][0] == 0 && camada2[l-1][j][0] == 0 && camada2[l-1][j+2][0] == 0 && camada2[l-2][j][0] == 0 && camada2[l-2][j+1][0] == 0){
            camada(l, j, 6); camada(l, j+1, 6); camada(l-1, j, 6); camada(l-1, j+2, 6); camada(l-2, j, 6); camada(l-2, j+1, 6);
            return 6; }}
    //Fim peças 6

    //peças num 7 aqui
    else if(ref==40){
        if(camada2[l][j][0] == 0 && camada2[l][j+2][0] == 0 && camada2[l-1][j][0] == 0 && camada2[l-1][j+1][0] == 0 && camada2[l-1][j+2][0] == 0 && camada2[l-2][j][0] == 0 && camada2[l-2][j+2][0] == 0){
            camada(l, j, 7); camada(l, j+2, 7); camada(l-1, j, 7); camada(l-1, j+1, 7); camada(l-1, j+2, 7); camada(l-2, j, 7); camada(l-2, j+2, 7);
            return 7; }}

    else if(ref==41){
        if(camada2[l][j][0] == 0 && camada2[l][j+1][0] == 0 && camada2[l][j+2][0] == 0 && camada2[l-1][j+1][0] == 0 && camada2[l-2][j][0] == 0 && camada2[l-2][j+1][0] == 0 && camada2[l-2][j+2][0] == 0){
            camada(l, j, 7); camada(l, j+1, 7); camada(l, j+2, 7); camada(l-1, j+1, 7); camada(l-2, j, 7); camada(l-2, j+1, 7); camada(l-2, j+2, 7);
            return 7; }}
    //Fim peças 7

    //peças num 8 aqui
    else if(ref==42){
        if(camada2[l-2][j][0]== 0 && camada2[l-1][j][0]== 0 && camada2[l][j][0]== 0 && camada2[l-2][j+1][0] == 0 && camada2[l][j+1][0] == 0 && camada2[l-2][j+2][0] == 0 && camada2[l-1][j+2][0] == 0 && camada2[l][j+2][0] == 0){
            camada(l-2, j, 8); camada(l-1, j, 8); camada(l, j, 8); camada(l-2, j+1, 8); camada(l, j+1, 8); camada(l-2, j+2, 8); camada(l-1, j+2, 8); camada(l, j+2, 8);
            return 8;}}
    //Fim peças 8
}
identificador--;
return 10;   //caso em que as peças não podem ser colocadas e portanto é retornado o valor 10 o que fará continuar a função while do modo_p1.
}

void modo_p1(){
        int l,j, num = 0, posi = 0;    //variáveis para o ciclo for que servem respetivamente de linha e coluna para a coordenada de posicionamento e posi que é zero se a posição do barco for inválida e 1 se for válida
        srand(time(NULL));              //seed para o random
        for (l=resl; l >= 1; l-=3){
            for(j= 1; j < resc; j+=3){          //os "for"" servem para mexer a coordenada de posicionamento das peças
            id_peca[num] = posi;
            num++;
            contador = 0;                       //reset do contador para 0
            posi = barco(rand() % 43,l,j);      //posi é igual a 1 ou 0 dependendo da funcao barco. A função barco é chamada com a ref igual a um numero random entre 0 a 42.
            while(posi == 10){
                contador++;                     //incremento contador
                posi = barco(rand() % 43,l,j);
            }}}
id_peca[num] = posi;
}

int *aleatorios (int ini,int vari) {
    static int numeros[12]={};
    int i, j, inc;
    for (i = 0 ; i < vari ; i+= inc) {
        numeros[i]= (rand()%vari)+ini;
        inc= 1;
        for (j= 0 ; j < i ; j++) {
            if (numeros[i]==numeros[j]){
                inc= 0;
                break;
            }}}
return numeros;}

int verificador(int id,int l,int j, int incre){
int a = 0;
    if (id==0){
        barco(0,l,j);
        id_peca[incre] = 0;
        return 0;
  }
    else if (id==1){
    int *num = aleatorios(1, 9);
    for(a=0; a < 9; a++) {
            if((barco(num[a],l,j)) != 10){
                id_peca[incre] = 1;
                return 1;}}}

    else if (id==2){
        int *num = aleatorios(12, 10);
        for(a=0; a < 10; a++) {
            if((barco(num[a],l,j)) != 10){
                id_peca[incre] = 2;
                return 1;}}}


    else if (id==3){
        int *num = aleatorios(22, 6);
        for(a=0; a < 6; a++) {
            if((barco(num[a],l,j)) != 10){
                id_peca[incre]= 3;
                return 1;}}}

    else if (id==4){
        int *num = aleatorios(28, 4);
        for(a=0; a < 4; a++) {
            if((barco(num[a],l,j)) != 10){
                id_peca[incre] = 4;
                return 1;}}}


    else if (id==5){
        int *num = aleatorios(32, 4);
        for(a=0; a < 4; a++) {
            if((barco(num[a],l,j)) != 10){
                id_peca[incre] = 5;
                return 1;}}}


    else if (id==6){
        int *num = aleatorios(36, 4);
        for(a=0; a < 4; a++) {
            if((barco(num[a],l,j)) != 10){
                id_peca[incre] = 6;
                return 1;}}}


    else if (id==7){
        int *num = aleatorios(40, 2);
        for(a=0; a < 2; a++) {
            if((barco(num[a],l,j)) != 10){
                id_peca[incre] = 7;
                return 1;}}}


    else if (id==8){
        if ((barco(42,l,j)) != 10){
            id_peca[incre] = 8;
        return 1;}}

return 2;
}


void modo_p2 (int n_pecas){
int a,i=0,l,j, k,num = 2, pecas[21] = {},veri1 = 0, veri2 = 0, stop, incre=1, rnum, cnum[41] = {0};      //variáveis para o ciclo for que servem respetivamente de linha e coluna para a coordenada de posicionamento e peca que contera o numero de barcos e a matriz 0 (tamanho de 21 pois o maximo de barcos que se pode ter num tabuleiro 15x24 e 20 e o ultimo e para o valor 0)
static int  b_colocados = 0;
    pecas[0] = 0;
    pecas[1] = 0;
    srand(time(NULL));          //seed para o random
    for(j = 0; j < pecas_num[1]; j++){
    pecas[num] = 1;
    num++;
    }
    for(j = 0; j < pecas_num[2]; j++){
    pecas[num] = 2;
    num++;
    }
    for(j = 0; j < pecas_num[3]; j++){
    pecas[num] = 3;
    num++;
    }
    for(j = 0; j < pecas_num[4]; j++){
    pecas[num] = 4;
    num++;
    }
    for(j = 0; j < pecas_num[5]; j++){
    pecas[num] = 5;
    num++;
    }
    for(j = 0; j < pecas_num[6]; j++){
    pecas[num] = 6;
    num++;
    }
    for(j = 0; j < pecas_num[7]; j++){
    pecas[num] = 7;
    num++;
    }
    for(j = 0; j < pecas_num[8]; j++){
    pecas[num] = 8;
    num++;
    }
    rnum = num;
    num = 0;
    while (n_pecas > b_colocados && veri2 != 1000){
    for (l=resl; l >= 1; l-=3){
            if (veri1 == 8 || n_pecas == b_colocados){
                break;
            }
        for(j= 1; j < resc; j+=3){
        do {
        stop = 0;
        veri1++;
        do{num = rand() % rnum;
        for (k = 0 ; k < 41 ; k++){
            if (num == cnum[k] && num != 0 && num != 1){
                i = 0;
                break;}
            else {i = 1;}}
            cnum[incre] = num;}while(i == 0);
        stop = verificador(pecas[num],l,j,incre);} while(stop == 2 && veri1 != 8);
        if (stop == 0){
        veri1 = 0;}
        else if (stop == 1){
            b_colocados++;
            veri1 = 0;}
            incre++;
        if (veri1 == 8 || n_pecas == b_colocados){
            break;
        }}}
if (n_pecas > b_colocados){
veri1 = 0;
veri2++;
total_b = 0;
incre = 1;
identificador = 1;
b_colocados = 0;
for(l = resl; l >= 1; l--){
        for(k = 1; resc >= k; k++){
        camada2[l][k][0] = 0;
        camada2[l][k][1] = 0;
        }}
for (k = 0 ; k < 41; k++){
        cnum[k] = 0;}

for (k = 0 ; k < 41; k++){
        id_peca[k] = 0;}
}}
if (n_pecas > b_colocados && veri2 == 1000){
    printf("\nErro! Nao consegui colocar as pecas. Tente outra vez \n\n");
    exit(-1);}
else {
printf("\n\nTodas as peças foram colocadas com sucesso! Tens:\n");
for(a=1; a < 9; a++){
printf("peca %d --> %d\n", a, pecas_num[a]);}
printf("\ntotal ---> %d\n", n_pecas);
sleep(3);}}

 void help (char *zzz){     //colocar as intruções para usar os comandos
    /*printf("");
    printf("");
    printf("");
    printf("");
    printf("");*/
}

void resultado(int inicio,int total){
time_t fim = time(NULL);
        if (tiro == total){
            modod = 0;
            printf("\nTiveste de acertar todas as coordenadas para acabar, que vergonha :c\nDemoraste %d segundos.",fim-inicio);
        }
        else if (conta_b == total_b){
            modod = 0;
            printf("\nAcertaste todas as pecas com %d tiros, numa matriz de %d entradas!!!\nDemoraste %d segundos.\n",tiro, total,fim-inicio);}}

int main(int argc, char *argv[]){
    int opt, total, n_pecas, modop=1, a, p, linha, coluna;
    opterr = 0;
    float n_pecas_max;
    while((opt= getopt(argc, argv,"t:j:p:d:1:2:3:4:5:6:7:8:h"))!= -1 ){
        switch (opt){
        case 't':
        sscanf(optarg,"%dx%d", &resl, &resc);
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
        sscanf(optarg,"%d", &modod);
        break;
        case '1':
        sscanf(optarg, "%d", &pecas_num[1]);
        break;
        case '2':
        sscanf(optarg, "%d", &pecas_num[2]);
        break;
        case '3':
        sscanf(optarg, "%d", &pecas_num[3]);
        break;
        case '4':
        sscanf(optarg, "%d", &pecas_num[4]);
        break;
        case '5':
        sscanf(optarg, "%d", &pecas_num[5]);
        break;
        case '6':
        sscanf(optarg, "%d", &pecas_num[6]);
        break;
        case '7':
        sscanf(optarg, "%d", &pecas_num[7]);
        break;
        case '8':
        sscanf(optarg, "%d", &pecas_num[8]);
        break;
        default:{
            printf("Carater %c nao identificado", optopt);
        }}}

    if((resl%3) !=0 || (resc%3 != 0) || (resl < 9) || (resl > 15) || (resc < 9) || (resc> 24)){ //caso em que não são verificadas as condições corretas para criar o tabuleiro
        printf("Erro! As dimensões do seu tabuleiro são invalidas. Tanto as linhas como as colunas tem de ser divisiveis por 3. Para alem disso a matriz minima e de 9x9 e a maxima e de 15x24. \n");
        exit(0);
    }
    total = resc * resl;
    for(linha = resl; linha >= 1; linha--){
            printf("%2d  ", linha);
            for(coluna = 1; resc >= coluna; coluna++ ){
                tabuleiro [linha][coluna] = '-';
                printf("%c ", tabuleiro [linha][coluna]);
            }
             printf("\n");
}
printf("    ");
for(coluna = 1; resc >= coluna; coluna++){
    printf("%c ", letra);
    letra++;
    }
printf("\n");
time_t inicio = time(NULL);
if (modop==1){
    modo_p1();
    conta_pecas();
    for(a=1, p=0; a < 9; a++){
    printf("peca %d --> %d\n", a, pecas_num[a]);
    p+=pecas_num[a];}
    printf("\ntotal ---> %d\n", p);
    sleep(4);       //esperar
    }

else if (modop==2){
    n_pecas_max=((resl*resc/9)/2);
    n_pecas = pecas_num[1]+pecas_num[2]+pecas_num[3]+pecas_num[4]+pecas_num[5]+pecas_num[6]+pecas_num[7]+pecas_num[8];
    if ( n_pecas > n_pecas_max || pecas_num[1]< pecas_num[2] || pecas_num[2] < pecas_num[3] || pecas_num[3] < pecas_num[4] || pecas_num[4] < pecas_num[5] || pecas_num[5] < pecas_num[6] || pecas_num[6] < pecas_num[7] || pecas_num[7] < pecas_num[8]) {
    printf("\nNúmero de peças inválido!\n");
       return -1; }
    modo_p2(n_pecas);
}
    while (modod==1){
    modo_d1();
    resultado(inicio,total);}

    if (modod==2){
        modo_d2_e_3();
        resultado(inicio,total);}

    else if (modod==3){
        modo_d2_e_3();
        resultado(inicio,total);}

return 0;
}






