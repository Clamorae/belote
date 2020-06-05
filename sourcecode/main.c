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
-fix contracts : Done
-create name demand : A Faire après les autres fix, nouveau systeme a coder
-fix main menu : Done
-fix victory save : ???
-fix ordre d'affichage : ???
-add clear : Done
-fix the IAs (end up in an infite loop, dont know if its caused by that)
*/

int main(){
    int **card=create(2,32);
    int exit = 0;
    srand(time(0));
    randomize(card);
    highscore *HSarray = getHighScore();
    int input;
    do{
        input = menu();
        switch (input) {
            case 1:
                belote(card);
                break;
            case 2:
                printHighScore(HSarray);
                break;
            case 3:
                exit = 1;
                break;
        }
    }while(exit!=1);
    writeHighScore(HSarray);
    return 0;
}
