#include<stdio.h> // kono stDIO da !
#include<stdlib.h>
#include<string.h>
#include"highscore.h"

int main(){
    highscore *HSarray = getHighScore();
    strcpy(HSarray[0].name, "lol"); //update a name in the arry
    HSarray[0].score = 69420;//update a score in the array
    writeHighScore(HSarray);
    return 0;
}
