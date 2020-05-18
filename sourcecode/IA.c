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
            if ((card[0][((player)*8)+j])/10==i){
                count++;
             }
        }  
        if (count>higher[0]){
            higher[0]=count;
            higher[1]=i;
        }
    }
    switch (higher[0]){
    case 3:
        if (*value<80){
            *value=80;
            *contractOwner=player;
            *color=higher[1];
        }
        else{
            printf("The player %d pass\n",player );
            *passes=*passes+1;
        }
        
        break;
    case 4 ... 8:
        if (*value<120){
            *value=120;
            *contractOwner=player;
            *color=higher[1];
        }
        else{
            printf("The player %d pass\n",player );
            *passes=*passes+1;
        }
        break;   
    default:
        *passes=*passes+1;
        printf("The player %d pass\n",player );
        break;
    }
    
}