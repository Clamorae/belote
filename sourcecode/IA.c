#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<stdbool.h>
#include"input.h"
#include "IA.h"

void BotContract(int** card,int player, int* passes,int* value,int* contractOwner,int* color){
    int count=0,higher[2]={0,0};
    for (int i = 0; i <= 3; i++){
        count=0;
        for (int j = 0; j < 8; j++){
            if ((card[0][((player-1)*8)+j])/10==i){
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
            *contractOwner=player-1;
            *color=higher[1];
        }
        else{
            printf("The player %d pass\n",player-1 );
            (*passes)++;
        }

        break;
    case 4 ... 8:
        if (*value<120){
            *value=120;
            *contractOwner=player-1;
            *color=higher[1];
        }
        else{
            printf("The player %d pass\n",player-1 );
            (*passes)++;
        }
        break;
    default:
        (*passes)++;
        printf("The player %d pass\n",player-1 );
        break;
    }

}


void IAplayCard(int** cards, int* cardsOfRound, int atoutMode, int atout,int player,int turn){
    int playableCards[8] = {-1,-1,-1,-1,-1,-1,-1,-1};
    int higher=0;
    int numberOfPCards = 0;
    bool winnable=false;
    numberOfPCards = IAgetplayablecards(cards,cardsOfRound,playableCards,atoutMode,atout,player);
    if (turn==0){
        int value[8]={0,1,2,4,5,6,3,7};
        for (int i = 0; i < 8; i++){
            for (int j = 0; j < j; j++){
                if (playableCards[j]%10==value[i]&&playableCards[j]/10!=atout){
                    cardsOfRound[turn] = playableCards[j];
                    for(int k=((player-1)*8);k<(player*8);k++){
                        if (cards[0][k] == playableCards[j]){
                        cards[1][k] = 0;
                        }
                    } 
                }
            } 
        }
    }
    
    else if(atoutMode==0 && atout==playableCards[0]/10){
        int value[8]={0,1,2,4,5,6,3,7};
        for (int i = 0; i < 8; i++){
            for (int j = 0; j < j; j++){
                if (playableCards[j]%10==value[i]){
                    cardsOfRound[turn] = playableCards[j];
                    for(int k=((player-1)*8);k<(player*8);k++){
                        if (cards[0][k] == playableCards[j]){
                        cards[1][k] = 0;
                        }
                    } 
                }
            } 
        }   
    }


    else if (atoutMode==0){
        int value[8]={0,1,2,4,5,6,3,7};        
        for (int i = 0; i < turn; i++){
            if (cardsOfRound[turn]/10==cardsOfRound[0]/10){
                for (int j = 0; j < 8; j++){
                    if (value[j]==cardsOfRound[turn]%10){
                        if (j>higher){
                            higher=j;
                        }
                        j=8;
                    }    
                }    
            }   
        }
        for (int i = higher; i < 8; i++){
            for (int j = 0; j < j; j++){
                if (playableCards[j]%10==value[i]){
                    winnable=true;
                    cardsOfRound[turn] = playableCards[j];
                    for(int k=((player-1)*8);k<(player*8);k++){
                        if (cards[0][k] == playableCards[j]){
                        cards[1][k] = 0;
                        }
                    } 
                }
            } 
        }
        if (winnable==false){
            for (int i = higher; i > -1; i--){
                for (int j = 0; j < j; j++){
                    if (playableCards[j]%10==value[i]){
                        cardsOfRound[turn] = playableCards[j];
                        for(int k=((player-1)*8);k<(player*8);k++){
                            if (cards[0][k] == playableCards[j]){
                            cards[1][k] = 0;
                            }
                        } 
                    }
                } 
            }
        }
    }
    
    
    else{
        if(playableCards[0]/10==atout){
            int value[8]={0,1,5,6,3,7,2,4};        
            for (int i = 0; i < turn; i++){
                if (cardsOfRound[turn]/10==atout){
                    for (int j = 0; j < 8; j++){
                        if (value[j]==cardsOfRound[turn]%10){
                            if (j>higher){
                                higher=j;
                            }
                            j=8;
                        }
                    }
                }
            }
            for (int i = higher; i < 8; i++){
                for (int j = 0; j < j; j++){
                    if (playableCards[j]%10==value[i]){
                        winnable=true;
                        cardsOfRound[turn] = playableCards[j];
                        for(int k=((player-1)*8);k<(player*8);k++){
                            if (cards[0][k] == playableCards[j]){
                            cards[1][k] = 0;
                            }
                        }
                    }
                }
            }
            if (winnable==false){
                for (int i = higher; i > -1; i--){
                    for (int j = 0; j < j; j++){
                        if (playableCards[j]%10==value[i]){
                            cardsOfRound[turn] = playableCards[j];
                            for(int k=((player-1)*8);k<(player*8);k++){
                                if (cards[0][k] == playableCards[j]){
                                cards[1][k] = 0;
                                }
                            }
                        }
                    }
                }
            }
        }
        else{
            int value[8]={0,1,5,6,3,7,2,4};
            for (int i = 0; i <8; i++){
                for (int j = 0; j < j; j++){
                    if (playableCards[j]%10==value[i]){
                        cardsOfRound[turn] = playableCards[j];
                        for(int k=((player-1)*8);k<(player*8);k++){
                            if (cards[0][k] == playableCards[j]){
                            cards[1][k] = 0;
                            }
                        }
                    }
                }
            }
        }       
    }
}

int IAgetplayablecards(int** cards, int* cardsOfRound,int* playableCards, int atoutMode, int atout,int player){
    int NofPCards = 0;
    int colorToMatch;
    if(atoutMode == 1){
        colorToMatch = atout;
    }
    else{
        colorToMatch = cardsOfRound[0]/10;
    }

    if(cardsOfRound[0] == -1){
        IAcompareAndAdd(cards,playableCards,&NofPCards,-1,player);
    }
    else{
        IAcompareAndAdd(cards,playableCards,&NofPCards,colorToMatch,player);
        if (NofPCards == 0){
            if(atoutMode != 1){
                IAcompareAndAdd(cards,playableCards,&NofPCards,atout,player);
                if (NofPCards == 0){
                    IAcompareAndAdd(cards,playableCards,&NofPCards,-1,player);
                }
            }
            else{
                IAcompareAndAdd(cards,playableCards,&NofPCards,-1,player);
            }
        }
    }
    return NofPCards;
}

void IAcompareAndAdd(int** cards, int* playableCards,int* NofPCards, int colorToCompare,int player){
    if(colorToCompare == -1){
        for(int i=((player-1)*8);i<(player*8);i++){
            if(cards[1][i] != 0){
                playableCards[*NofPCards] = cards[0][i];
                (*NofPCards)++;
            }
        }
    }
    else{
        for(int i=((player-1)*8);i<(player*8);i++){
            if(cards[1][i] != 0 && cards[0][i]/10 == colorToCompare){
                playableCards[*NofPCards] = cards[0][i];
                (*NofPCards)++;
            }
        }
    }
}
