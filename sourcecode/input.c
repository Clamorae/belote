#include"input.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#ifdef _WIN32
#define CLS "cls"
#else //In any other OS
#define CLS "clear"
#endif

char getcharB(){//A fucntion that actually return what you fucking want instead of doing stupid bullshit
    char out;
    while((out = getchar())=='\n');
    while(getchar() != '\n');
    return out;
}

int getInt(){
    int out;
    while((scanf("%d",&out))==0){
        printf("Invalid Value, please press enter and retry\n");
        while(getchar() != '\n');
    }
    while(getchar() != '\n');
    return out;
}

void waitForEnter(){
    while(getchar() != '\n');
}


int getContract(int *value, int *color, int minValue, int maxValue, int teamWithContract){//return 1 if a contract was estabished, 0 if the player passed, 2 if the player coinched
    int intInput;
    char chInput, temp;
    if(teamWithContract == 2){
        printf("Do you want to coinche the opposing team contract ? [Y/n]\n");
        chInput = getcharB();
        if(chInput == 'y'||chInput == 'Y'){
            printf("Contract was coinched\n");
            return 2;
        }
    }
    printf("Do you want to announce a contrat ? [Y/n]\n");
    chInput = getcharB();//getchar works in a werid way and sometimes returns \n even with no keyboard inputs, this is used to fix it
    if (chInput == 'N'||chInput == 'n'){
        printf("You pass\n");
        return 0;
    }
    else{
        printf("How much do you want to bet ? (between %d and %d, multiples of 10 only)\n",minValue, maxValue);
        intInput = getInt();
        while(intInput <= minValue || intInput > maxValue || intInput%10 != 0){
            printf("Invalid value, please retry.\n");
            intInput = getInt();
        }
        *value = intInput;
        printf("On Which color do you want to bet ? [H]eart, [S]pade, [D]iamond [C]lover, [F]ull Trump, [N]o Trump ?\n");
        while(1){
            do{
                chInput = getcharB();
            }while(chInput == '\n');
            if(chInput == 'h' || chInput == 'H'){
                *color = 0;
                printf("You anounced a contract\n");
                return 1;
            }
            else if(chInput == 's' || chInput == 'S'){
                *color = 1;
                printf("You anounced a contract\n");
                return 1;
            }
            else if(chInput == 'd' || chInput == 'D'){
                *color = 2;
                printf("You anounced a contract\n");
                return 1;
            }
            else if(chInput == 'c' || chInput == 'C'){
                *color = 3;
                printf("You anounced a contract\n");
                return 1;
            }
            else if(chInput == 'c' || chInput == 'C'){
                *color = 3;
                printf("You anounced a contract\n");
                return 1;
            }
            else if(chInput == 'c' || chInput == 'C'){
                *color = 3;
                printf("You anounced a contract\n");
                return 1;
            }
            else if(chInput == 'f' || chInput == 'F'){
                *color = 5;
                printf("You anounced a contract\n");
                return 1;
            }
            else if(chInput == 'n' || chInput == 'N'){
                *color = 4;
                printf("You anounced a contract\n");
                return 1;
            }
            else{
                printf("Invalid input, please retry.\n");
            }
        }
    }
}

char* getColorString(int color){
    switch (color) {
        case 0:return "Hearts";
        case 1:return "Spades";
        case 2:return "Diamond";
        case 3:return "Clover";
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

void printP1Cards(int** cards){
    printf("The cards in your deck are:\n");
    for(int i=0;i<8;i++){
        if (cards[1][i] != 0){
            printf("%s of %s / ", getValueString(cards[0][i]%10), getColorString(cards[0][i]/10));
        }
    }
    printf("\n");
}

void clear(){
    system(CLS);
}
