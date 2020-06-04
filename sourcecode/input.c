#include"input.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

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
    return out;
}

void waitForEnter(){
    while(getchar() != '\n');
}


int getContract(int *value, int *color, int minValue, int maxValue, int teamWithContract){//return 1 if a contract was estabished, 0 if the player passed, 2 if the player coinched
    int intInput;
    char chInput, temp;
    if(teamWithContract != 0){
        printf("The following contract was announced:\nteam:%d\nvalue:%d\ncolor:%s\n",teamWithContract,*value,getColorString(*color));
        printf("do you want to coinche, or surcoinche the current contract if it's yours ? [Y/n]\n");
        chInput = getcharB();
        if(chInput == 'y'||chInput == 'Y'){
            printf("Contract was coinched\n");
            return 2;
        }
    }
    printf("Do you want to announce a contrat ? [Y/n]\n");
    chInput = getcharB();//getchar works in a werid way and sometimes returns \n even with no keyboard inputs, this is used to fix it
    if (chInput == 'N'||chInput == 'n'){
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
        printf("On Which color do you want to bet ? [H]eart, [S]pade, [D]iamond or [C]lover ?\n");
        while(1){
            do{
                chInput = getcharB();
            }while(chInput == '\n');
            if(chInput == 'h' || chInput == 'H'){
                *color = 0;
                return 1;
            }
            else if(chInput == 's' || chInput == 'S'){
                *color = 1;
                return 1;
            }
            else if(chInput == 'd' || chInput == 'D'){
                *color = 2;
                return 1;
            }
            else if(chInput == 'c' || chInput == 'C'){
                *color = 3;
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
        case 2:return "Diamonds";
        case 3:return "Clover";
        default:return"None";
    }
    //if(color == 0){return "Hearts";}
    //else if(color == 1){return "Spades";}
    //else if(color == 2){return "Diamonds";}
    //else if(color == 3) {return "Clover";}
    //else{return "None";}
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
    printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
}
