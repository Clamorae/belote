#include"gamelogic.h"
#include"input.h"
#include"array.h"
#include"IA.h"
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<stdbool.h>


int belote(int **card){
    printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");//we gotta remove that tho
    int scoreT1 = 0, scoreT2 = 0, first;
    contract gameContract;//create a contract type variable for the game
    first = rand()%4+1;
    printf("The first to submit a contract for this round will be player %d\n",first);
    randomize(card);//shuffle the cards and sort them (Player 1 cards from index 0 to 7, P2 from 8 to 15, ect...)
    defineContract(first,&gameContract,card);
    printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
    printf("Contract is:\n-team: %d\n-value: %d\n-color: %s\n",gameContract.team, gameContract.value, getColorString(gameContract.color));
    first++;
    if (first>4){first = 1;}
    play(card,first);
    return 0;

}


void defineContract(int player, contract* pContract,int **card){
    int passes,temp;
    passes = 0;
    (*pContract).team = 0, (*pContract).value = 60, (*pContract).color = 0, (*pContract).isCoinched = 0;
    int player, value=60, color=0, passes=0,contractOwner=0,maxcard=0,carde=0;
    bool check=false;
    int hasContract = 0;
    char chInput;
    int intInput;
    srand(time(0));
    player = rand()%4+1;
    do{
        printf("The contract is detained by the player %d, and is worth %d on %s\n", (*pContract).team, (*pContract).value, getColorString((*pContract).color));
        if (player == 1){
            temp = getContract(&pContract->value, &pContract->color, (*pContract).value, 680, (*pContract).team = 0);
            printf("%d\n",temp);
            switch(temp) {
                case 1:
                    (*pContract).team = 1;
                    break;
                case 2:
                    if((*pContract).team == 1){
                        (*pContract).isCoinched = 2;
                    }else{
                        (*pContract).isCoinched = 1;
                    }
                    break;
                default:
                    BotContract(card,player,&passes,&value,&contractOwner,&color);
                    break;
        else{
            printf("The player %d pass\n",player);
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

int gameRound(int** cards,int firstToContract,int* scoreT1, int* scoreT2){}//nice

int play(int** cards,int player){
    for(int i = 0;i<4;i++){
        if(player == 1){
            printf("The cards in your deck are:\n");
            for(int i=0;i<8;i++){
                if (cards[1][i] != 0){
                    printf("%s of %s\n", getValueString(cards[0][i]%10), getColorString(cards[0][i]/10));
                }
            }


        }
        else{
            printf("L'ia fait un truc\n");
        }
        player++;
        if(player>4){player = 1;}
    }

}
