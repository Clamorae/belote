#include<stdio.h> // kono stDIO da !
#include<stdlib.h>
#include<string.h>
#include <time.h>
#include"highscore.h"
#include"array.h"
#include"menu.h"
#include"contract.h"

int main(){
    int **card=create(2,32),a=0;
    srand(time(0));
    randomize(card);
    for (size_t i = 0; i < 2; i++){
        printf("\n");
        for (size_t j = 0; j < 32; j++){
            printf("%d ",card[i][j]);
        }
    }
    return 0;
}
