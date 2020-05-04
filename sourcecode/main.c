#include<stdio.h> // kono stDIO da !
#include<stdlib.h>
#include<string.h>
#include <time.h>
#include"highscore.h"
#include"array.h"
#include"menu.h"
#include"gamelogic.h"
#include"input.c"


int main(){
    int **card=create(2,32),a=0,giver=0;
    srand(time(0));
    randomize(card);
    for (int i = 0; i < 2; i++){
       printf("\n");
       for (int j = 0; j < 32; j++){
           printf("%d ",card[i][j]);
       }
    }
    highscore *HSarray = getHighScore();
    if (menu() == 2) {printHighScore(HSarray);}
    writeHighScore(HSarray);
    belote(card);
    return 0;
}
