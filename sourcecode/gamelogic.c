#include"gamelogic.h"
#include"input.h"
#include"array.h"
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<stdbool.h>


int belote(int **card){
    int scoreT1 = 0, scoreT2 = 0;
    contract *pContract;
    /*do{
        randomize(card)
    }while(scoreT1 >= 701 || scoreT2 >= 701);
    if(scoreT1>scoreT2){return 1;}
    else{return 2;}*/
    defineContract(pContract,card);
    return 0;
}


int defineContract(contract* pContract,int **card){
    int player, value=60, color=0, passes=0,contractOwner=0,maxcard=0,carde=0;
    bool check=false;
    int hasContract = 0;
    char chInput;
    int intInput;
    srand(time(0));
    player = rand()%4+1;
    do{
        printf("The contract is detained by the player %d, and is worth %d on the %d color\n", contractOwner, value, color);
        if (player == 1){
            if (getContract(&value, &color, value, 680) == 1){
                contractOwner = 1;
            }
            else{
                BotContract(card,player,&passes,&value,&contractOwner);
            }

        }
        else{
            passes++;
        }
        player += 1;
        if(player>4){player = 1;}
        if (passes==3 && contractOwner!=0){
            check=true;
        }
        if (passes==4){
            passes = 0;
            randomize(card);
        }
    }while(check==false);
}
