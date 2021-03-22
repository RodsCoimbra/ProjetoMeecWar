#include <stdio.h>
#include <stdlib.h>
int main()
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
