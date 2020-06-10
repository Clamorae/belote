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
    trump in contract
    trump in count
    winner start
    comment
*/

int main(){
    int **card=create(2,32);
    int exit = 0;
    srand(time(0));
    randomize(card);
    //highscore *HSarray = getHighScore();
    int NumberOfProfiles;
    profile* profileArray = getProfiles(&NumberOfProfiles);
    //profileArray = addNewProfile(profileArray,&NumberOfProfiles);
    int input;
    do{
        input = menu();
        switch (input) {
            case 1:
                belote(card);
                break;
            case 2:
                clear();
                printProfiles(profileArray,NumberOfProfiles);
                waitForEnter();
                break;
            case 3:
                exit = 1;
                break;
        }
    }while(exit!=1);
    saveProfiles(profileArray,NumberOfProfiles);
    return 0;
}
