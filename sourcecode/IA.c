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

int IAplay(int** cards,int player){
    srand(time(0));
    int a=rand()%8;
    return (cards[0][((player-1)*8)+a]);
}
    
 
int IAplayCard(int** cards, int* cardsOfRound, int* atoutMode, int atout,int player){
    int playableCards[8] = {-1,-1,-1,-1,-1,-1,-1,-1};
    int numberOfPCards = 0;
    printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
    //ici valeur de test
    cardsOfRound[0] = 10;
    //fin de valeur de test
    numberOfPCards = IAgetplayablecards(cards,cardsOfRound,playableCards,*atoutMode,atout,player);
    for(int i=0; i<numberOfPCards; i++){
        printf("%s of %s\n",getValueString(playableCards[i]%10),getColorString(playableCards[i]/10));
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
        IAcompareAndAdd(cards,playableCards,&NofPCards,-1);
    }
    else{
        IAcompareAndAdd(cards,playableCards,&NofPCards,colorToMatch);
        if (NofPCards == 0){
            if(atoutMode != 1){
                IAcompareAndAdd(cards,playableCards,&NofPCards,atout);
                if (NofPCards == 0){
                    IAcompareAndAdd(cards,playableCards,&NofPCards,-1);
                }
            }
            else{
                IAcompareAndAdd(cards,playableCards,&NofPCards,-1);
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