#include<stdio.h> // kono stDIO da !
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include"highscore.h"
#include"array.h"
#include"menu.h"
#include"gamelogic.h"
#include"input.h"
#include"display.h"
/*
    trump in contract: V
    trump in count: x
    winner start: v
    comment: 1/2
    see card before anoucing contracts: V
    dé-coinche when a new contracts is anounced: ?
    display results screen at the end of the game: v
    remove debug prints: v
    make a good clear function (NOT print \n\n\n\n\n\n\n...): v
    add some waitForEnter(); where it needs to: v
    prevent people from creating profiles with the same names: x
*/

int main(){
    char** displayMatrix = initializeDisplayMatrix();
    int **card=create(2,32);
    int exit = 0;
    srand(time(0));
    randomize(card);
    int numberOfProfiles, profileNumber;
    profile* profileArray = getProfiles(&numberOfProfiles);
    int input;
    do{
        input = menu();
        switch (input) {
            case 1:
                profileArray = selectProfile(profileArray, &numberOfProfiles, &profileNumber);
                belote(card, profileArray, profileNumber,displayMatrix);
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
