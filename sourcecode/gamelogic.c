#include"gamelogic.h"
#include"input.h"
#include"array.h"
#include"IA.h"
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<stdbool.h>
//Faudrait vraiment que je pense a commenter ce truc la


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
    play(card,first,gameContract.color);
    return 0;

}

void defineContract(int player, contract* pContract,int **card){
    int passes,temp;
    passes = 0;
    (*pContract).team = 0, (*pContract).value = 60, (*pContract).color = 0, (*pContract).isCoinched = 0;
    bool check=false;
    char chInput;
    int intInput;
    srand(time(0));
    do{
        printf("The contract is detained by the player %d, and is worth %d on %s\n", (*pContract).team, (*pContract).value, getColorString((*pContract).color));
        if (player == 1){
            temp = getContract(&pContract->value, &pContract->color, (*pContract).value, 680, (*pContract).team);
            printf("%d\n",temp);
            switch(temp) {
                case 1:
                    (*pContract).team = 1;
                    passes = 0;
                    break;
                case 2:
                    if((*pContract).team == 1){
                        (*pContract).isCoinched = 2;
                    }else{
                        (*pContract).isCoinched = 1;
                    break;
                    }
                default:
                    passes++;
                    break;
            }
        }
        else{
            BotContract(card,player,&passes,&pContract->value,&pContract->team,&pContract->color);
        }
        printf("%d",passes);
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

int play(int** cards,int player, int atout){
    int atoutMode = 0;
    int cardsOfRound[4] = {-1,-1,-1,-1};
    for(int i = 0;i<4;i++){
        printf("Currently, the game is:\n");
        for(int j=0;j<4;j++){
            if(cardsOfRound[j] == -1){
                printf("-Pas de carte\n");
            }
            else{
                printf("-%s of %s\n",getValueString(cardsOfRound[j]%10),getColorString(cardsOfRound[j]/10));
            }
        }
        if(player == 1){
            playCard(cards,cardsOfRound,&atoutMode,atout,i);
        }
        else{
            printf("Le joeur %d joue\n",player);
            cardsOfRound[i]=IAplay(cards,player);
            getchar();
            getchar();
        }
        player++;
        if(player>4){player = 1;}
        if(cardsOfRound[i]/10 == atout && cardsOfRound[i] != -1){
            atoutMode = 1;
        }
        printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
    }
    return 0;
}

int playCard(int** cards, int* cardsOfRound, int* atoutMode, int atout,int turn){
    int playableCards[8] = {-1,-1,-1,-1,-1,-1,-1,-1};
    int numberOfPCards = 0;
    printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
    //ici valeur de test
    cardsOfRound[0] = 10;
    //fin de valeur de test
    printf("Currently, the game is:\n");
    for(int i=0;i<4;i++){
        if(cardsOfRound[i] == -1){
            printf("-Pas de carte\n");
        }
        else{
            printf("-%s of %s\n",getValueString(cardsOfRound[i]%10),getColorString(cardsOfRound[i]/10));
        }
    }
    printf("\n");
    printP1Cards(cards);
    numberOfPCards = getplayablecards(cards,cardsOfRound,playableCards,*atoutMode,atout);


    printf("\nYour playable cards are:\n");
    for(int i=0; i<numberOfPCards; i++){
        printf("%d - %s of %s\n",i+1,getValueString(playableCards[i]%10),getColorString(playableCards[i]/10));
    }
    printf("Please select a card to play\n");//Putain mais c'est mal opti bordeeeeeeeel
    int UserInput;
    do{
        UserInput = getInt();
    }while(UserInput < 1 || UserInput > numberOfPCards);
    cardsOfRound[turn] = playableCards[UserInput - 1];
    for(int i=0; i<8; i++){
        if (cards[0][i] == playableCards[UserInput - 1]){
            cards[1][i] = 0;
        }
    }

}

int getplayablecards(int** cards, int* cardsOfRound,int* playableCards, int atoutMode, int atout){
    int NofPCards = 0;
    int colorToMatch;
    if(atoutMode == 1){
        colorToMatch = atout;
    }
    else{
        colorToMatch = cardsOfRound[0]/10;
    }


    if(cardsOfRound[0] == -1){
        compareAndAdd(cards,playableCards,&NofPCards,-1);
    }
    else{
        compareAndAdd(cards,playableCards,&NofPCards,colorToMatch);
        if (NofPCards == 0){
            if(atoutMode != 1){
                compareAndAdd(cards,playableCards,&NofPCards,atout);
                if (NofPCards == 0){
                    compareAndAdd(cards,playableCards,&NofPCards,-1);
                }
            }
            else{
                compareAndAdd(cards,playableCards,&NofPCards,-1);
            }
        }
    }
    return NofPCards;
}

void compareAndAdd(int** cards, int* playableCards,int* NofPCards, int colorToCompare){
    if(colorToCompare == -1){
        for(int i=0;i<8;i++){
            if(cards[1][i] != 0){
                playableCards[*NofPCards] = cards[0][i];
                (*NofPCards)++;
            }
        }
    }
    else{
        for(int i=0;i<8;i++){
            if(cards[1][i] != 0 && cards[0][i]/10 == colorToCompare){
                playableCards[*NofPCards] = cards[0][i];
                (*NofPCards)++;
            }
        }
    }
}
