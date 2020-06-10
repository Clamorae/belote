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
full trump
*/

int main(){
    int **card=create(2,32);
    int exit = 0;
    srand(time(0));
    randomize(card);
    //highscore *HSarray = getHighScore();
    int numberOfProfiles, profileNumber;
    profile* profileArray = getProfiles(&numberOfProfiles);
    //profileArray = addNewProfile(profileArray,&NumberOfProfiles);
    int input;
    do{
        input = menu();
        switch (input) {
            case 1:
                profileArray = selectProfile(profileArray, &numberOfProfiles, &profileNumber);
                belote(card, profileArray, profileNumber);
                break;
            case 2:
                clear();
                printProfiles(profileArray,numberOfProfiles);
                waitForEnter();
                break;
            case 3:
                exit = 1;
                break;
        }
    }while(exit!=1);
    saveProfiles(profileArray,numberOfProfiles);
    return 0;
}
