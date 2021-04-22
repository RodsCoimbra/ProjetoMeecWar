#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <getopt.h>

int camada2[17][26][42]= {{{}}}, id_peca[41] = {};
int resl=9/**reset da linha, guarda sempre o seu valor*/, resc = 9 /**reset da coluna*/, pecas_num[9] = {0},  contador = 0, modod = 1, total_b = 0, conta_b = 0, tiro = 0, disp_c,disp_l, acertos = 0, identificador = 0;
char tabuleiro [16][25]; /*array que conterá os espaços do tabuleiro. Neste caso o array tem uma dimensão acima tanto nas linhas como nas colunas para facilitar a utilização no código, ou seja,
                         as coordenadas correspondem exatamente com o array, deixando de parte a linha 0 e coluna 0 do array. Por exemplo A9 = tabuleiro [9][1] e não [8][0].*/



/** \brief  Função que cria um tabuleiro e  também dá clear do tabuleiro anterior
 *
 * \return void
 *
 */
void tabu()
{
    int linha, coluna;
    char letra = 'A';
    for(linha = resl; linha >= 1; linha--)
    {
        printf("%2d ", linha);                                  //print do número das linhas
        for(coluna = 1; resc >= coluna; coluna++ )              //print do tabuleiro, com mudança de cor dependente do que tiver no espaço
        {
            printf("%c ", tabuleiro [linha][coluna]);
        }
        printf("\n");
    }
    printf("   ");
    for(coluna = 1; resc >= coluna; coluna++)
    {
        printf("%c ", letra);                                       //print das letras das colunas
        letra++;
    }
    printf("\n\n");
}




/** \brief Esta função serve para guardar os locais dos barcos, os seus tipos e para assinalar os locais onde os próximos barcos não podem ficar
 *
 * \param linha2 int: valor da linha do barco
 * \param coluna2 int: valor da coluna do barco
 * \param peca int: identificador da peça
 * \return void
 *
 */
void camada(int linha2,int coluna2, int peca)
{
    int i, j,l,k;
    total_b++;
    camada2 [linha2][coluna2][0] = peca;                   //camada 2[][][0] é o array que anotará as posições dos barcos e das posições livres
    for(i = -1; i <= 1; i++)
    {
        for(j=-1; j <= 1; j++)
        {
            if(camada2[linha2+i][coluna2+j][0] == 0)       //Os dois "for" permitem a varredura da área toda à volta da peça e entrará no "if" caso alguma dessas coordenadas seja água que se pode colocar barco
            {
                camada2[linha2+i][coluna2+j][0] = 9;           //O número 9 na segunda camada significa lugar onde já não se pode colocar barcos
                if(modod == 3)
                {
                    camada2[linha2+i][coluna2+j][identificador] = 11;   /*camada 2 [][][1-41] serve para guardar locais onde no modo de disparo 3 já não pode disparar
                                                                        os valores do terceiro [] variam entre 1 e 41 e incrementa sempre que avança uma matriz de 3x3*/
                }
            }
            else
            {
            }
        }
    }
    for(l = resl; l >= 1; l--)
    {
        for(k = 1; resc >= k; k++)
        {
            for (i = identificador+1; i < 41; i++)
            {
                camada2[l][k][i] = camada2[l][k][identificador];            //copia camada 2 atual para todas as próximas
            }
        }
    }
}


/** \brief Função que diz onde é que o computador disparou e pede ao utilizador para introduzir o valores no tabuleiro
 *
 * \return void
 *
 */
void disparo()
{
    int condicao = 0;
    char col;
    if(modod == 3 && camada2[disp_l][disp_c][identificador-1] == 11 && camada2[disp_l][disp_c][0] == 9) {}              //Serve para passar os locais que já não podem ser disparados no modo de disparo 3
    else
    {
        col = disp_c + '@';       //carater a indicar a coluna que o computador acertou. Como disp_c é um inteiro logo para transformar numa letra maiúscula soma-se a '@' que é o simbolo antes do 'A'
        tiro++;                   //quantidade de tiros disparados
        do
        {
            printf("%c%d\n",col,disp_l);
            condicao = 0;
            scanf(" %c", &tabuleiro[disp_l][disp_c]);
            if (tabuleiro[disp_l][disp_c] == '-')            //se for água não faz nada
            {
            }
            else if(tabuleiro[disp_l][disp_c] >= ('1' + 0) && tabuleiro[disp_l][disp_c] <= ('8' + 0))
            {
                if(id_peca[0] == 0)
                {
                    id_peca[0] = (int)tabuleiro[disp_l][disp_c] - 48;       //48 equivale a 0 em char, logo isto passa para id_peca[0] o número inserido pelo jogador
                }
                conta_b++;                                    //aumenta quantos barcos foram acertados no total
                acertos++;                                    //aumenta a quantidade do barco da matriz 3x3, assim quando esse número for igual ao número do barco ele para no disparo 2 e 3
                camada(disp_l,disp_c, 1);                     //para saber os lados dos barcos para passar à frente no modo d3
                total_b--;                                    //como a função camada incrementa o total de barcos para os modos -p aqui foi necessário retirar
            }
            else
            {
                printf("*Introduziu um valor impossivel\n");
                condicao = 1;                                //Caso em que o jogador não introduz um valor possivel e portanto a condição fica igual a 1 para repetir o pedido das coordenadas
            }
        }
        while(condicao==1);
        camada2[disp_l][disp_c][0] = 10;                                                //Aquele local fica a 10 para dizer que já foi atingido
    }
}

/** \brief Função que diz os locais onde disparar no modo d2 e d3
 *
 * \param k int: Indica em qual tiro da sequência da matriz 3x3 ele está.
 * \return void
 *
 */
void cruz(int k)
{
    if(acertos >= id_peca[0] && id_peca[0] != 0)    //Serve para parar quando o barco já acertou em todos as peças daquela matriz 3x3, caso seja uma matriz nula ele só para quando acabar toda
    {
        id_peca[0] = 0;
        acertos = 9;                                //Serve apenas para terminar o for no modo_d2_e_3
    }
    else
    {
        switch(k)
        {
        case 0:                       //meio
            disp_c +=1;
            disp_l -=1;
            disparo();
            break;
        case 1:                       //centro cima
            disp_c +=1;
            disparo();
            break;
        case 2:                       //centro baixo
            disp_l -=2;
            disp_c +=1;
            disparo();
            break;
        case 3:                       //esquerda meio
            disp_l -=1;
            disparo();
            break;
        case 4:                       //direita meio
            disp_c +=2;
            disp_l -=1;
            disparo();
            break;
        case 5:                       //canto superior esquerdo
            disparo();
            break;
        case 6:                       //canto inferior direito
            disp_c +=2;
            disp_l -=2;
            disparo();
            break;
        case 7:                       //canto superior direito
            disp_c +=2;
            disparo();
            break;
        case 8:                       //canto inferior esquerdo
            disp_l -=2;
            disparo();
            break;
        default:
        {
            if (id_peca[0] != 0)                //Caso em que o número de peças acertadas na matriz 3x3 não corresponde ao dado pelo utilizador
            {
                printf("*Escreveu os números errados\n");
                exit(-1);
            }
        }
        }
    }
}

/** \brief Função que diz quantos barcos foram criados no modo p1 e de que tipo são.
 *
 * \return void
 *
 */
void conta_pecas()
{
    int num, a;
    for (a = 1; a < 9 ; a++)
    {
        pecas_num[a] = 0;                       //resetar qualquer valor que possa ter sido introduzido por um utilizador
    }
    for (num = 1; num <= 40; num ++)            //40, porque é o máximo de peças que um tabuleiro 15x24 pode ter no modo p1
    {
        switch (id_peca[num])
        {
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
            break;
        }
    }
}


/** \brief Modo de disparo aleatório(-d 1)
 *
 * \return void
 *
 */
void modo_d1()
{
    srand(time(NULL));
    int verificador = 0;
    while(verificador == 0)
    {
        disp_c = (rand() % resc) +1;                        //número aleatório entre 1 e o número de colunas
        disp_l = (rand() % resl) +1;                        //número aleatório entre 1 e o número de linhas
        if (camada2[disp_l][disp_c][0] != 10)              //impedir repeticoes
        {
            verificador = 1;
        }
    }
    disparo();
}

/** \brief Função para o modo de disparo no formato pedido para -d 2 e -d 3
 *
 * \return void
 *
 */
void modo_d2_e_3()
{
    int num = 0, save_l, save_c, k;
    identificador = 0;
    for (disp_l=resl; disp_l >= 1; disp_l-=3)
    {
        save_l = disp_l;
        for(disp_c = 1; disp_c < resc && conta_b < total_b; disp_c+=3)          //Serve como localizador da matriz 3x3 que o pc está a disparar, percorrendo o campo horizontalmente e depois descendo 3 linhas e repetindo
        {
            identificador++;
            save_c = disp_c;
            num++;
            acertos = 0;
            for(k=0; k <= 9 && acertos != 9; k++)           //Função que faz parar caso o pc acerte em todos as peças naquela matriz 3x3
            {
                cruz(k);
                disp_c = save_c;                            //Reset dos valores das linhas e colunas de  disparo
                disp_l = save_l;
            }
            if(modod==3)
            {
                identificador++;                            //Aumenta o identificador apenas no modo d3 para ser usado para identificar quais os locais que deixam de ser necessários acertar devido a estarem ao lado de um barco
            }
        }
    }
}

/** \brief Função que cria um barco a partir da referência e da posição indicada caso esta não tenha nenhuma peça ao lado
 *
 * \param ref int: Identificador global do barco que se pretende colocar
 * \param l int: Linha onde se quer colocar o barco
 * \param j int: Coluna onde se quer colocar o barco
 * \return int: Identificador da peça ou 10 caso não consiga meter a peça pedida
 *
 */
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

/** \brief Função que cria peças random para o modo_p1
 *
 * \return void
 *
 */
void modo_p1()
{
    int l,j, num = 0, posi = 0;             //variáveis para o ciclo for que servem respetivamente de linha e coluna para a coordenada de posicionamento e posi que é zero se a posição do barco for inválida e 1 se for válida
    srand(time(NULL));                      //seed para o random
    for (l=resl; l >= 1; l-=3)
    {
        for(j= 1; j < resc; j+=3)           //os "for"" servem para mexer a coordenada de posicionamento das peças
        {
            id_peca[num] = posi;                //guarda o valor dos posi no id_peca, sendo id_peca[0]=0 e o resto segue a ordem com que foram colocados os barcos o primeiro é 0 e o resto depende do tabuleiro
            num++;
            contador = 0;                       //reset do contador para 0
            posi = barco(rand() % 43,l,j);      //posi é igual ao identificador da peça colocada, ou 10 se não conseguir colocar. A função barco é chamada com a ref igual a um numero random entre 0 a 42.
            while(posi == 10)
            {
                contador++;                     //incremento contador
                posi = barco(rand() % 43,l,j);
            }
        }
    }
    id_peca[num] = posi;
}

/** \brief Fazer números aleatórios, sem repetição para ser usado no verificador
 *
 * \param ini int: Número minimo para o número aleatório
 * \param vari int: Número da variação do random
 * \return Retorna o número
 *
 */
int *aleatorios (int ini,int vari)
{
    static int numeros[12]= {};
    int i, j, inc;
    for (i = 0 ; i < vari ; i+= inc)
    {
        numeros[i]= (rand()%vari)+ini;          //número terá o minimo ini e varia entre ini e ini + (vari-1)
        inc= 1;
        for (j= 0 ; j < i ; j++)
        {
            if (numeros[i]==numeros[j])         //caso em que se repete e portanto o inc fica 0 para voltar a meter na mesma posição do array um novo número
            {
                inc= 0;
                break;
            }
        }
    }
    return numeros;
}

/** \brief Função que escolhe uma variante da peca pedida, tem um random para cada tipo de peca (do 1 ao 8)
 *
 * \param id int: Identificador da peça
 * \param l int: linha para mandar para a função barco
 * \param j int: coluna para mandar para a função barco
 * \param incre int: número que sobe à medida que o localizador da matriz 3x3 avança
 * \return int: retorna 0 se for uma matriz vazia, 1 se for uma peça e 2 se não conseguir colocar uma peça
 *
 */
int verificador(int id,int l,int j, int incre)
{
    int a = 0;
    if (id==0)
    {
        barco(0,l,j);
        id_peca[incre] = 0;        //matriz nula
        return 0;
    }
    else if (id==1)
    {
        int *num = aleatorios(1, 9);
        for(a=0; a < 9; a++)
        {
            if((barco(num[a],l,j)) != 10)           //tenta meter o barco, caso não consiga ele experimenta todas as outras posições dessa peça
            {
                id_peca[incre] = 1;                 //mete o número correspodente ao identificador da peça no id_peca
                return 1;
            }
        }
    }
                                                    //o resto da função segue o mesmo padrão da primeira
    else if (id==2)
    {
        int *num = aleatorios(12, 10);
        for(a=0; a < 10; a++)
        {
            if((barco(num[a],l,j)) != 10)
            {
                id_peca[incre] = 2;
                return 1;
            }
        }
    }


    else if (id==3)
    {
        int *num = aleatorios(22, 6);
        for(a=0; a < 6; a++)
        {
            if((barco(num[a],l,j)) != 10)
            {
                id_peca[incre]= 3;
                return 1;
            }
        }
    }

    else if (id==4)
    {
        int *num = aleatorios(28, 4);
        for(a=0; a < 4; a++)
        {
            if((barco(num[a],l,j)) != 10)
            {
                id_peca[incre] = 4;
                return 1;
            }
        }
    }


    else if (id==5)
    {
        int *num = aleatorios(32, 4);
        for(a=0; a < 4; a++)
        {
            if((barco(num[a],l,j)) != 10)
            {
                id_peca[incre] = 5;
                return 1;
            }
        }
    }


    else if (id==6)
    {
        int *num = aleatorios(36, 4);
        for(a=0; a < 4; a++)
        {
            if((barco(num[a],l,j)) != 10)
            {
                id_peca[incre] = 6;
                return 1;
            }
        }
    }


    else if (id==7)
    {
        int *num = aleatorios(40, 2);
        for(a=0; a < 2; a++)
        {
            if((barco(num[a],l,j)) != 10)
            {
                id_peca[incre] = 7;
                return 1;
            }
        }
    }


    else if (id==8)
    {
        if ((barco(42,l,j)) != 10)
        {
            id_peca[incre] = 8;
            return 1;
        }
    }

    return 2;           //Retorna 2 caso não consiga meter nenhuma das variantes daquela peça
}


/** \brief
 *
 * \param n_pecas int: Quantidade total de pecas desde o tipo 1 ao 8
 * \return void
 *
 */
void modo_p2 (int n_pecas)
{
    int i=0,l,j, k,num = 2, pecas[21] = {},veri1 = 0, veri2 = 0, stop, incre=1, rnum, cnum[41] = {0}; //variáveis para o ciclo for que servem respetivamente de linha e coluna para a coordenada de posicionamento e peca que contera o numero de barcos e a matriz 0 (tamanho de 21 pois o maximo de barcos que se pode ter num tabuleiro 15x24 e 20 e o ultimo e para o valor 0)
    static int  b_colocados = 0;
    pecas[0] = 0;  // estes dois espacos estao reservados para 0 para aumentar a probabilidade de sair matriz nula no random 
    pecas[1] = 0;  
    srand(time(NULL));          //seed para o random 
    for(j = 0; j < pecas_num[1]; j++)      // Este conjunto de for's coloca as pecas do jogo escolhidas num array
    {   
        pecas[num] = 1; // coloca o numero 1 referente ao tipo da peca na posicao "num" do array 
        num++;          // contador para ir avancando no array
    }
    for(j = 0; j < pecas_num[2]; j++)      // o resto da linha de for's continua com o mesmo principio do primeiro mas para o resto das pecas
     {
        pecas[num] = 2;
        num++;
    }
    for(j = 0; j < pecas_num[3]; j++)
    {
        pecas[num] = 3;
        num++;
    }
    for(j = 0; j < pecas_num[4]; j++)
    {
        pecas[num] = 4;
        num++;
    }
    for(j = 0; j < pecas_num[5]; j++)
    {
        pecas[num] = 5;
        num++;
    }
    for(j = 0; j < pecas_num[6]; j++)
    {
        pecas[num] = 6;
        num++;
    }
    for(j = 0; j < pecas_num[7]; j++)
    {
        pecas[num] = 7;
        num++;
    }
    for(j = 0; j < pecas_num[8]; j++)
    {
        pecas[num] = 8;
        num++;
    }
    rnum = num; // passa para rnum a quantidade de pecas preenchidas no array
    num = 0;
    while (n_pecas > b_colocados && veri2 != 1000)      //verificacao 1000x se e possivel colocar, se este nao conseguir depois das 1000x deiste e retorna Erro
    {
        for (l=resl; l >= 1; l-=3)  // for que percorre as matrizes do tabuleiro na vertical, isto de 3 em 3 linhas
        {
            if (veri1 == 8 || n_pecas == b_colocados) // se todas as matrizes foram verificadas ou se todas as pecas forem colocadas ele para a funcao
            {
                break;
            }
            for(j= 1; j < resc; j+=3) // for que percorre as matrizes do tabuleiro na horizontal, isto e de 3 em 3 colunas  
            {
                do  // loop que corre até tentar colocar a peca ou para se falhar 8x
                {
                    stop = 0; 
                    veri1++;
                    do
                    {
                        num = rand() % rnum;  // gera um numero aleatorio até um certo valor "rnum"
                        for (k = 0 ; k < 41 ; k++) // for que nao deixa a repeticao de pecas
                        {
                            if (num == cnum[k] && num != 0 && num != 1) // num= 0 ou 1 representa a matriz nula que pode repetir no tabuleiro
                            {
                                i = 0;
                                break;
                            }
                            else
                            {
                                i = 1;
                            }
                        }
                        cnum[incre] = num; // guarda os valores das pecas ja usadas
                    }
                    while(i == 0);
                    stop = verificador(pecas[num],l,j,incre);  // coloca 0 ou 1 dependendo se a pocicao da peca esta disponivel
                }
                while(stop == 2 && veri1 != 8);   
                if (stop == 0)                   // 0 = nao se pode colocar a peca na matriz           
                {
                    veri1 = 0;
                }
                else if (stop == 1) // 1 = a matriz esta livre pode se colocar a peca
                {
                    b_colocados++; //peca colocada
                    veri1 = 0;
                }
                incre++;
                if (veri1 == 8 || n_pecas == b_colocados)  // se todas as pecas forem colocadas a funcao para 
                {
                    break;
                }
            }
        }
        if (n_pecas > b_colocados) // enquanto as pecas todas nao foram colocadas este if corre
        {
            veri1 = 0;
            veri2++;
            total_b = 0;
            incre = 1;
            identificador = 1;
            b_colocados = 0;
            for(l = resl; l >= 1; l--) // coloca a terceira dimensao da camada 2 a 0's
            {
                for(k = 1; resc >= k; k++)   
                {
                    camada2[l][k][0] = 0;
                    camada2[l][k][1] = 0;
                }
            }
            for (k = 0 ; k < 41; k++) // percorre o vetor cnum e coloca todas as posicoes a 0
            {
                cnum[k] = 0;
            }

            for (k = 0 ; k < 41; k++) // percorre o vetor id_peca e coloca todas as posicoes a 0
            {
                id_peca[k] = 0;
            }
        }
    }
    if (n_pecas > b_colocados && veri2 == 1000)         //  Retorno do Erro depois das 1000 tentativas
    {
        printf("\n*Erro! Nao consegui colocar as pecas. Tente outra vez \n\n");
        exit(-1);
    }
    else
    {
    }
}

/** \brief Função que ajuda o jogador a saber que comandos utilizar para usar de forma correta o programa, quando invocada com o "-h"
 *
 * \return void
 *
 */
void help ()
{
    printf("\nMEEC War Game - Versao Intermedia\n-Last Update: 21/04/2021 \n");
    printf("Modo de uso:./wargame[argumento1] [argumento2] ... [argumentoN] -> Inicializa o jogo com as carateristicas definidas nos argumentos");
    printf("\nSendo os argumentos: \n    -h      ajuda para o utilizador\n");
    printf("    -t      dimensões do tabuleiro, sendo o mínimo 9x9 e máximo 15x24. Para além disso as dimensões têm de ser divisíveis por 3.\n");
    printf("    -j      modo de jogo (0 a 2)\n");
    printf("    -p      modo de posicionamento de peças pelo computador (1 a 2)\n");
    printf("    -d      modo de disparo de peças pelo computador (1 a 3)\n");
    printf("    -1      numero de pecas do tipo 1 (minimo 1)\n");
    printf("    -2      numero de pecas do tipo 2\n");
    printf("    -3      numero de pecas do tipo 3\n");
    printf("    -4      numero de pecas do tipo 4\n");
    printf("    -5      numero de pecas do tipo 5\n");
    printf("    -6      numero de pecas do tipo 6\n");
    printf("    -7      numero de pecas do tipo 7\n");
    printf("    -8      numero de pecas do tipo 8\n");
    printf("No modo j0[-j 0] e j1[-j 1], são necessário os argumentos:\n");
    printf("    -t(a sua omissão assume um tabuleiro 9x9)\n");
    printf("    -p[1 ou 2](caso seja o 2 é necessário os argumentos das peças[-1 a -8] também)\n");
    printf("No modo j2, só é necessário os argumentos:\n");
    printf("    -t(a sua omissão assume um tabuleiro 9x9)\n");
    printf("    -d[1 a 3]\n");
    printf("    [-1 a -8]\n");
    printf("    (-p a inclusão deste argumento não afetará em nada o modo de jogo 2\n");
    printf("A inclusão de qualquer argumento não necessário levará a erro.\n");
    exit(-1);
}

/** \brief Funcão que posiciona as pecas de varias formas, modo 1 e 2, este informacao e dada pelo utilizador
 *
 * \param modop int: Informacao dada pelo jogador ao iniciar o programa quando coloca "-p" a 1 ou 2
 * \return void
 *
 */
void modoposi(int modop)
{
    int a;
    if (modop==1)       //  Modo de posicionamento 1
    {
        int n_pecas = pecas_num[1]+pecas_num[2]+pecas_num[3]+pecas_num[4]+pecas_num[5]+pecas_num[6]+pecas_num[7]+pecas_num[8]; //soma para saber o total de barcos em jogo
        if (n_pecas != 0)                                                   //erro por não inserir barcos
        {
            printf("\n*Nao pode meter a quantidade de pecas no modo p1!\n");
            help();
        }
        modo_p1();
        conta_pecas();
    }

    else if (modop==2)      //  Modo de posicionamento 2
    {
        float n_pecas_max=((resl*resc/9)/2);
        int n_pecas = pecas_num[1]+pecas_num[2]+pecas_num[3]+pecas_num[4]+pecas_num[5]+pecas_num[6]+pecas_num[7]+pecas_num[8];
        if (n_pecas == 0)                                                   //erro por não inserir barcos
        {
            printf("\n*Tem de meter a quantidade de pecas no modo p2!\n");
            exit(-1);
        }
        if ( n_pecas > n_pecas_max || pecas_num[1]< pecas_num[2] || pecas_num[2] < pecas_num[3] || pecas_num[3] < pecas_num[4] || pecas_num[4] < pecas_num[5] || pecas_num[5] < pecas_num[6] || pecas_num[6] < pecas_num[7] || pecas_num[7] < pecas_num[8])
        {
            printf("\n*Número de peças inválido!\n");
            exit (-1);
        }
        modo_p2(n_pecas);
    }
    for(a=1; a < 9; a++)
    {
        printf(" %d", pecas_num[a]);
    }
    printf("\n");
}

/** \brief Funcao que mostra a informacao relativa ao modo de jogo 2, numero de tiros, tempo demorado e tabuleiro final
 *
 * \param inicio int: Valor do tempo que em que o jogo começa
 * \return void
 *
 */
void resultado(int inicio)
{
    time_t fim = time(NULL);   // reset do cronometro

    if (conta_b >= total_b)
    {
        modod = 0;
        printf("\nFim de Jogo: %d jogadas em %d segundos\n",tiro, (int)fim-inicio);
        tabu();
    }
}


/** \brief Função que executa o modo de disparo (1,2 ou 3) escolhido pelo jogador ao iniciar o programa
 *
 * \param inicio int: Valor do tempo que em que o jogo começa
 * \return void
 *
 */
void mododis(int inicio)
{

    while (modod==1)
    {
        modo_d1();
        resultado(inicio);
        if (conta_b >= total_b)
        {
            exit(0);
        }
    }

    if (modod==2 || modod == 3)
    {
        modo_d2_e_3();
        resultado(inicio);
        exit(0);
    }
}


int main(int argc, char *argv[])       //   Rececao da informacao dada pelo jogador no inicio do programa me termos de dimensao do tabuleiro, modo de disparo, posicionamento e numero de pecas por tipo
{
    int opt, modop=1, modoj = 0, n_pecas,a, linha, coluna, mod = 0;
    float n_pecas_max;
    char col;
    opterr = 0;
    while((opt= getopt(argc, argv,"t:j:p:d:1:2:3:4:5:6:7:8:h"))!= -1 )
    {
        switch (opt)
        {
        case 't':
            sscanf(optarg,"%dx%d", &resl, &resc);
            break;
        case 'h':   // Ajuda ao utilizador
            help();
            return 0;
            break;
        case 'j': //modo de jogo
            sscanf(optarg,"%d", &modoj);
            if(modoj > 2 || modoj < 0){
            printf("*Erro na introdução de argumento.\n");
            help();}
            break;
        case 'p': // Posicionamneto
            sscanf(optarg,"%d", &modop);
            if(modop > 2 || modop < 1){
            printf("*Erro na introdução de argumento.\n");
            help();}
            break;
        case 'd':  // Modo de disparo
            sscanf(optarg,"%d", &modod);
            if(modod > 3 || modod < 1){
            printf("*Erro na introdução de argumento.\n");
            help();}
            mod = 1;
            break;
        case '1':   // Numero de pecas 1
            sscanf(optarg, "%d", &pecas_num[1]);
            if(pecas_num[1] < 0){
            printf("*Erro na introdução de argumento.\n");
            help();}
            break;
        case '2':   // Numero de pecas 2
            sscanf(optarg, "%d", &pecas_num[2]);
            if(pecas_num[2] < 0){
            printf("*Erro na introdução de argumento.\n");
            help();}
            break;
        case '3':   // Numero de pecas 3
            sscanf(optarg, "%d", &pecas_num[3]);
            if(pecas_num[3] < 0){
            printf("*Erro na introdução de argumento.\n");
            help();}
            break;
        case '4':   // Numero de pecas 4
            sscanf(optarg, "%d", &pecas_num[4]);
            if(pecas_num[4] < 0){
            printf("*Erro na introdução de argumento.\n");
            help();}
            break;
        case '5':   // Numero de pecas 5
            sscanf(optarg, "%d", &pecas_num[5]);
            if(pecas_num[5] < 0){
            printf("*Erro na introdução de argumento.\n");
            help();}
            break;
        case '6':   // Numero de pecas 6
            sscanf(optarg, "%d", &pecas_num[6]);
            if(pecas_num[6] < 0){
            printf("*Erro na introdução de argumento.\n");
            help();}
            break;
        case '7':   // Numero de pecas 7
            sscanf(optarg, "%d", &pecas_num[7]);
            if(pecas_num[7] < 0){
            printf("*Erro na introdução de argumento.\n");
            help();}
            break;
        case '8':   // Numero de pecas 8
            sscanf(optarg, "%d", &pecas_num[8]);
            if(pecas_num[8] < 0){
            printf("*Erro na introdução de argumento.\n");
            help();}
            break;
        default:    // Mostra a mensagem se for escrito um carater sem sentido no programa
        {
            printf("*Carater %c nao identificado", optopt);
            help();
        }
        }
    }

    if((resl%3) !=0 || (resc%3 != 0) || (resl < 9) || (resl > 15) || (resc < 9) || (resc> 24))  //caso em que não são verificadas as condições corretas para criar o tabuleiro
    {
        printf("*Erro! As dimensões do seu tabuleiro são invalidas.\n");
        help();
    }

    for(linha = resl; linha >= 1; linha--)              // Preenche o tabuleiro com "-"
    {
        for(coluna = 1; resc >= coluna; coluna++ )
        {
            tabuleiro [linha][coluna] = '-';
        }
    }

    time_t inicio = time(NULL);
    if (modoj == 0)
    {
    if (mod == 1){
    printf("*Não pode introduzir modo de disparo\n");
    help();
    }
        printf("%dx%d",resl,resc);
        modoposi(modop);
        for(linha = resl; linha >= 1; linha--)
        {
            for(coluna = 1; resc >= coluna; coluna++ )
            {
                if (camada2[linha][coluna][0] >= 1 && camada2[linha][coluna][0] <= 8)
                {
                    tabuleiro[linha][coluna] = camada2[linha][coluna][0] + '0';
                }
            }
        }
        printf("\n");
        tabu();
        return 0;

    }


    else if (modoj == 1)
    {
        if (mod == 1){
        printf("*Não pode introduzir modo de disparo\n");
        help();}
        printf("* ================================\n* Modo de Jogo 1\n* Insira as Coordenadas de Disparo\n* ================================\n%dx%d",resl,resc);
        modoposi(modop);
        conta_b=0;
        while (conta_b < total_b)
        {
            scanf(" %c%d", &col, &linha);
            coluna = col-'@';
            if (camada2[linha][coluna][0] >= 1 && camada2[linha][coluna][0] <= 8)
            {
                tabuleiro[linha][coluna] = camada2[linha][coluna][0] + '0';
                printf("%c\n", tabuleiro[linha][coluna]);
                conta_b++;
                camada2[linha][coluna][0] = 12;
                tiro++;
            }
            else if(camada2[linha][coluna][0] == 12)
            {
                printf("*Já disparou aqui!!!\n");
            }
            else
            {
                printf("-\n");
                camada2[linha][coluna][0] = 12;
                tiro++;
            }
        }
        resultado(inicio);
        return 0;
    }


    else if (modoj == 2)
    {
        n_pecas_max=((resl*resc/9)/2);
        n_pecas = pecas_num[1]+pecas_num[2]+pecas_num[3]+pecas_num[4]+pecas_num[5]+pecas_num[6]+pecas_num[7]+pecas_num[8];
        if (n_pecas == 0)                                                   //erro por não inserir barcos
        {
            printf("*Tem de meter a quantidade de pecas no modo j2!\n");
            return -1;
        }
        if ( n_pecas > n_pecas_max || pecas_num[1]< pecas_num[2] || pecas_num[2] < pecas_num[3] || pecas_num[3] < pecas_num[4] || pecas_num[4] < pecas_num[5] || pecas_num[5] < pecas_num[6] || pecas_num[6] < pecas_num[7] || pecas_num[7] < pecas_num[8])
        {
            printf("*Número de peças inválido!\n");
            exit (-1);
        }
        printf("* ================================\n* Modo de Jogo 2\n* Crie um tabuleiro com as características indicadas\n* Responda aos disparos do programa\n* ================================\n%dx%d ",resl,resc);
        for(a=1; a < 9; a++)
        {
            printf(" %d ", pecas_num[a]);
        }
        printf("\n");
        total_b = pecas_num[1]+2*pecas_num[2]+3*pecas_num[3]+4*pecas_num[4]+5*pecas_num[5]+6*pecas_num[6]+7*pecas_num[7]+8*pecas_num[8];
        mododis(inicio);
    }
    return -1;
}
