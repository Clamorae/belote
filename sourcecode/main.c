#include<stdio.h> // kono stDIO da !
#include<stdlib.h>
#include<string.h>
#include"highscore.h"
#include"array.h"
#include"menu.h"

int main(){
    highscore *HSarray = getHighScore();
    if (menu() == 2) {printHighScore(HSarray);}
    writeHighScore(HSarray);
    return 0;
}
