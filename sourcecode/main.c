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
    trump in count: V
    winner start: v
    see card before anoucing contracts: V
    dé-coinche when a new contracts is anounced: ?
    display results screen at the end of the game: v
    remove debug prints: v
    make a good clear function (NOT print \n\n\n\n\n\n\n...): v
    add some waitForEnter(); where it needs to: v
    comment main and menu: V
    display/input in the report: x
    verify the report : x
    comment display: x
    prevent people from creating profiles with the same names: x

*/

int main(){
    char** displayMatrix = initializeDisplayMatrix();
    int **card=create(2,32);//this two line arecallign the function which will create and initialize the two dimensionnal array
    int exit = 0;
    srand(time(0));
    randomize(card);//call for the first time the function which is shuffling the cards deck
    int numberOfProfiles, profileNumber;
    profile* profileArray = getProfiles(&numberOfProfiles);//cal the function which will search in profile.sav the existant profile and display it
    int input;
    do{
        input = menu();//this function will call the menu which display the 3 choices to the player and return which one the player has choose
        switch (input) {
            case 1:// be fore the start of the game the profile selection function is called and the player can create a new profil or play with one which already exist
                profileArray = selectProfile(profileArray, &numberOfProfiles, &profileNumber);
                belote(card, profileArray, profileNumber,displayMatrix);//then the game is launched
                break;
            case 2:
                clear();
                printProfiles(profileArray,numberOfProfiles);//call of the function which display profiles
                waitForEnter();
                break;
            case 3:
                exit = 1;//the programm will shut down
                break;
        }
    }while(exit!=1);
    saveProfiles(profileArray,numberOfProfiles);//call the function which will save your game in your profile statistics
    return 0;
}
