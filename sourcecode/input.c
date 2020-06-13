#include"input.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#ifdef _WIN32
    #define CLS "cls"
#else
    #define CLS "clear"
#endif
//command to clear the screen respectively on windows or Unix based system such as Linux/MacOS

char getcharB(){//A fucntion that actually return what you fucking want instead of doing stupid bullshit
    char out;
    while((out = getchar())=='\n');//clear all previous \n in the buffer and wait for an actual char stored in out
    while(getchar() != '\n');//clear the last \n
    return out;
}

int getInt(){
    int out;
    while((scanf("%d",&out))==0){
        printf("Invalid Value, please press enter and retry\n");//make sure bad/empty data isn't parsed
        while(getchar() != '\n');
    }
    while(getchar() != '\n');//clear the last input//
    return out;
}

void waitForEnter(){
    while(getchar() != '\n');//clear all the previos data that was stored in the buffer
}


char* getColorString(int color){
    switch (color) {
        case 0:return "Heart";
        case 1:return "Spade";
        case 2:return "Diamond";
        case 3:return "Club";
        case 4:return "No Trump";
        case 5:return "Full Trump";
        default:return"None";
    }
}

char* getValueString(int value){
    switch (value) {
        case 0:return "7";
        case 1:return "8";
        case 2:return "9";
        case 3:return "10";
        case 4:return "Jack";
        case 5:return "Queen";
        case 6:return "King";
        case 7:return "Ace";
        default: return "None";
    }
}


void clear(){
    system(CLS);//CLS is replaced by the good command depending of the system
}
