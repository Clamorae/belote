#include<stdio.h> // kono stDIO da !
#include<stdlib.h>
#include<string.h>
#include <time.h>
#include"highscore.h"
#include"array.h"
#include"menu.h"
#include"gamelogic.h"
#include"input.h"

/*
create annonce
create name demand
fix main menu
fix victory save
fix ordre d'affichage
add clear
*/

int main(){
    int **card=create(2,32),a=0,giver=0;
    srand(time(0));
    randomize(card);
    highscore *HSarray = getHighScore();
    if (menu() == 2) {printHighScore(HSarray);}
    writeHighScore(HSarray);
    belote(card);
    return 0;
}
