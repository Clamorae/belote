#include"gamelogic.h"
#include"input.h"
#include"array.h"
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<stdbool.h>


int belote(int **card){
    printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");//we gotta remove that tho
    int scoreT1 = 0, scoreT2 = 0;
    contract gameContract;//create a contract type variable for the game
    randomize(card);//shuffle the cards and sort them (Player 1 cards from index 0 to 7, P2 from 8 to 15, ect...)
    defineContract(&gameContract,card);
    printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
    printf("Contract is:\n-team: %d\n-value: %d\n-color: %s\n",gameContract.team, gameContract.value, getColorString(gameContract.color));
    return 0;
    for(int i=0; i<7;i++){//run through the code once per card
    }
}


void defineContract(contract* pContract,int **card){
    int player,passes,temp;
    bool check;
    passes = 0;
    (*pContract).team = 0, (*pContract).value = 60, (*pContract).color = 0, (*pContract).isCoinched = 0;
    player = rand()%4+1;
    do{
        printf("The contract is detained by the player %d, and is worth %d on %s\n", (*pContract).team, (*pContract).value, getColorString((*pContract).color));
        if (player == 1){
            temp = getContract(&pContract->value, &pContract->color, (*pContract).value, 680);
            printf("%d\n",temp);
            switch(temp) {
                case 1:
                    (*pContract).team = 1;
                    break;
                case 2:
                    if((*pContract).team == 1){
                        (*pContract).isCoinched = 3;
                    }else{
                        (*pContract).isCoinched = 1;
                    }
                    break;
                default:
                    passes++;
                    break;
            }
        }
        else{
            printf("The player %d pass\n",player );
            passes++;//ia enemi a faire
        }
        player ++;
        if(player>4){player = 1;}
        if (passes==3 && (*pContract).team!=0){
            check=true;
        }
        else if (passes==4){
            passes = 0;
            printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
            printf("No contract was established, the cards has been reshuffled\n");
            randomize(card);
        }
    }while(check==false);
}
