#include<stdio.h> // kono stDIO da !
#include<stdlib.h>
#include<string.h>
#include"highscore.h"
#include"array.h"
#include"menu.h"
#include"gamelogic.h"

int main(){
    int **card=create(2,32),a=0;
    for (size_t i = 0; i < 32; i++){
        if ((i+a)%10==8){
            a+=2;
        }
        card[0][i]=i+a;
    }

    printf("\n");
    randomize(card);
     for (size_t i = 0; i < 2; i++){
        printf("\n");
        for (size_t j = 0; j < 32; j++){
            printf("%d ",card[i][j]);
        }
    }
    highscore *HSarray = getHighScore();
    if (menu() == 2) {printHighScore(HSarray);}
    writeHighScore(HSarray);
    return 0;
}
