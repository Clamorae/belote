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
    int player, value=60, color=0, passes=0,contractOwner=0,maxcard=0,carde=0;//card???????
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
                passes++;
            }

        }
        else{
            int count=0,higher[2]={0,0};
            for (int i = 0; i < 3; i++){
                for (int j = 0; i < 8; i++){
                    if ((card[0][(player*8)-1+j])/10==i){
                        count++;
                    }
                }
                if (count>higher[0]){
                    higher[0]=count;
                    higher[1]=i;
                }
            }
            if (higher[0]<3){
            passes ++;
            }
            else{
                if (value<80+(10*higher[0])){
                    value+=10;
                    contractOwner=player;
                    color=higher[1];
                }
            }

            printf("The player %d pass\n",player );//ia enemi a faire
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
