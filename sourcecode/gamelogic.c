#include"gamelogic.h"
#include"input.h"
#include<stdio.h>
#include<stdlib.h>
#include<time.h>


int belote(/*int **cardArray*/){
    int scoreJ1 = 0, scoreJ2 = 0, scoreJ3 = 0, scoreJ4 = 0;
    int scoreT1 = 0, scoreT2 = 0;
    contract *pContract;
    //do{
    //    //distribution des cartes
    //}while(scoreT1 >= 701 || scoreT2 >= 701);
    //if(scoreT1>scoreT2){return 1;}
    //else{return 2;}
    defineContract(pContract);
    return 0;
}


int defineContract(contract* pContract){
    int player, value=60, color=0, passes,contractOwner=0,maxcard=0,card=0;
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
        }
        else{
            passes ++;
            printf("The player %d pass\n",player );//ia enemi a faire
        }
        player += 1;
        if(player>4){player = 1;}
    }while(1);
}
