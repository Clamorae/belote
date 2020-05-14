#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<stdbool.h>
#include"input.h"

void BotContract(int** card,int player, int* passes,int* value,int* contractOwner,int* color){
    int count=0,higher[2]={0,0};
    for (int i = 0; i <= 3; i++){
        count=0;
        for (int j = 0; j < 8; j++){
            if ((card[0][((player-1)*8)-1+j])/10==i){
                count++;
             }
        }  
        if (count>higher[0]){
            higher[0]=count;
            higher[1]=i;
        }
    }
    if (higher[0]<3){
        *passes ++;
        printf("The player %d pass\n",player );
    }
    else{
        if (*value<(80+(10*higher[0]))){
            *value+=10;
            *contractOwner=player;
            *color=higher[1];
        }
        else{
            *passes++;
        }
    }
}