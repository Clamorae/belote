#include"input.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int getContract(int *value, int *color, int minValue, int maxValue){//return 1 if a contract was estabished, 0 if the player passed, 2 if the player coinched
    int intInput;
    char chInput;
    printf("Do you want to announce a contract ? [y/n]\n");
    do{
        chInput = getchar();
    }while(chInput == '\n');
    if (chInput == 'N'||chInput == 'n'){
        return 0;
    }
    else{
        printf("How much do you want to bet ? (between %d and %d)\n",minValue, maxValue);
        scanf("%d",&intInput);
        while(intInput <= minValue || intInput > maxValue || intInput%10 != 0){
            printf("Invalid value, please retry.\n");
            scanf("%d",&intInput);
        }
        *value = intInput;
        printf("On Which color do you want to bet ? [H]eart, [S]pade, [D]iamond or [C]lover ?\n");
        while(1){
            do{
                chInput = getchar();
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
    if(color == 0){return "Hearts";}
    else if(color == 1){return "Spades";}
    else if(color == 2){return "Diamonds";}
    else if(color == 3) {return "Clover";}
    else{return "None";}
}
