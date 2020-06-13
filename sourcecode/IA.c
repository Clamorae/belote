#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<stdbool.h>
#include"input.h"
#include "IA.h"

void BotContract(int** cards,int player, int* passes,int* value,int* contractOwner,int* color, int* coinche){
    int count=0,higher[2]={0,0},team=0;
    if (player==1||player==3){
        team=1;
    }
    else{
        team=2;
    }


    for (int i = 0; i <= 3; i++){
        count=0;
        for (int j = 0; j < 8; j++){
            if ((cards[0][((player-1)*8)+j])/10==i &&((cards[0][((player-1)*8)+j]/10==7)||(cards[0][((player-1)*8)+j]/10==2)||(cards[0][((player-1)*8)+j]/10==4))){
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
            *contractOwner=team;
            *color=higher[1];
            *passes=0;
            printf("The player %d bet: %d %s\n",player,*value, getColorString(*color));
            *coinche = 0;
        }
        else{
            printf("The player %d pass\n",player);
            (*passes)++;
        }

        break;
    case 4 ... 8:
        if (*value<120){
            *value=120;
            *contractOwner=team;
            *color=higher[1];
            *passes=0;
            printf("The player %d bet: %d %s\n",player,*value, getColorString(*color));
            *coinche = 0;
        }
        else{
            printf("The player %d pass\n",player);
            (*passes)++;
        }
        break;
    default:
        (*passes)++;
        printf("The player %d pass\n",player);
        break;
    }

}


void IAplayCard(int** cards, int* cardsOfRound, int atoutMode, int atout,int player,int turn,int* belote){
    int playableCards[8] = {-1,-1,-1,-1,-1,-1,-1,-1};//initialize the playable car array and reset it before each IA turn
    int higher=0,count=0;//initialize the variable which will check if there a is a belote and who will chekc the best card to play
    int numberOfPCards = 0;
    bool winnable=false;// initialize the boolean which will test if the play is winnable or if the IA need to plays it's lowest card
    IAgetplayablecards(cards,cardsOfRound,playableCards,atoutMode,atout,player);//call the fonction which will define whiwh card the IA can play

    if (turn==0){//this part of the fonction will only be active if the IA is the first to play
        cardsOfRound[turn] = playableCards[0];//The IA will play the first card it can use
        for(int k=((player-1)*8);k<(player*8);k++){//In this for loop it will search in the card array wich card has been played and remove it from the plyers hand
                                                   //The research will only be effective in the IA's hand
            if (cards[0][k] == cardsOfRound[turn]){
                cards[1][k] = 0;
            }
        }
    }

    else if (atout==5){// In this case the IA know she will play in a Full trump round
        int value[8]={0,1,5,6,3,7,2,4}; //all the "value" array in IA.c is a classification of the card by card value for the current contract
        for (int i = 0; i < turn; i++){
            for (int j = 0; j < 8; j++){//the double for loop will check which card in play is actually winning the round
                if (value[j]==cardsOfRound[turn]%10){
                    if (j>higher){
                        higher=j; // the rank of the winning card in the value array will be stocked in the higher value
                    }
                    j=8;//when the value of the in-game card is finded the loop will break
                }
            }
        }
        for (int i = higher; i < 8; i++){ //in this double loop the IA will check if it had a winning card in hand
            for (int j = 0; j < 8; j++){
                if (playableCards[j]%10==value[i]){
                    winnable=true;//this boolean indicate the played carte is able to win the round
                    cardsOfRound[turn] = playableCards[j];//the IA will play the lowest card with which it can win
                    removeCard(cards,player,cardsOfRound,turn,&i,&j);
                }
            }
        }
        if (winnable==false){ //in this case the round is not winnable 
            for (int i = 0; i < higher; i++){
                for (int j = 0; j < 8; j++){
                    if (playableCards[j]%10==value[i]){
                        cardsOfRound[turn] = playableCards[j];
                        removeCard(cards,player,cardsOfRound,turn,&i,&j);
                    }
                }
            }
        }
    }
    else if (atout==4){// In this case the IA know she will play in a No-trump round
        int value[8]={0,1,2,4,5,6,3,7}; //all the "value" array in IA.c is a classification of the card by card value for the current contract
        if (cardsOfRound[0]==playableCards[0]){ //In this case the Ia's knows it's allowed to played card of the same color as the first card
           for (int i = 0; i < turn; i++){//The code below is pretty similar to the one upwards
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
                for (int j = 0; j < 8; j++){
                    if (playableCards[j]%10==value[i]){
                        winnable=true;
                        cardsOfRound[turn] = playableCards[j];
                        removeCard(cards,player,cardsOfRound,turn,&i,&j);
                        j=8;
                        i=8;
                    }
                }
            }
            if (winnable==false){
                for (int i = 0; i < higher; i++){
                    for (int j = 0; j < 8; j++){
                        if (playableCards[j]%10==value[i]){
                            cardsOfRound[turn] = playableCards[j];
                            removeCard(cards,player,cardsOfRound,turn,&i,&j);
                        }
                    }
                }
            }
        }
        else{//in this part the IA know it's in a no-Trump round and it has'nt any card which one it can win the round 
            for (int i = 0; i < 8; i++){
                for (int j = 0; j < 8; j++){
                    if (playableCards[j]%10==value[i]){//this double loop will check which one is the lowest in the playablecard array and play it
                        cardsOfRound[turn] = playableCards[j];
                        removeCard(cards,player,cardsOfRound,turn,&i,&j);
                    }
                }
            }
        }
    }

    else if(atoutMode==0 && atout==playableCards[0]/10){//In this case the IA doest have the color which is played by the leader so IA will play a trump
        int value[8]={0,1,5,6,3,7,2,4};
        for (int i = 0; i < 8; i++){
            for (int j = 0; j < 8; j++){
                if (playableCards[j]%10==value[i]){
                    cardsOfRound[turn] = playableCards[j];
                    removeCard(cards,player,cardsOfRound,turn,&i,&j);
                }
            }
        }
    }
    
    else if (atoutMode==0 && cardsOfRound[0]/10==playableCards[0]/10){// In this case the IA know there is no trump in game and she can play card from the same color as the leader
        int value[8]={0,1,2,4,5,6,3,7};
        for (int i = 0; i < turn; i++){
            if (cardsOfRound[i]/10==cardsOfRound[0]/10){
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
            for (int j = 0; j < 8; j++){
                if (playableCards[j]%10==value[i]){
                    winnable=true;
                    cardsOfRound[turn] = playableCards[j];
                    removeCard(cards,player,cardsOfRound,turn,&i,&j);
                }
            }
        }
        if (winnable==false){
            for (int i = 0; i < higher; i++){
                for (int j = 0; j < 8; j++){
                    if (playableCards[j]%10==value[i]){
                        cardsOfRound[turn] = playableCards[j];
                        removeCard(cards,player,cardsOfRound,turn,&i,&j);
                    }
                }
            }
        }
    }

    else{//In This case the cars which has been played before are trump
        if(playableCards[0]/10==atout){//This case the IA will play a trump in a game where a trump has already been played
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
                for (int j = 0; j < 8; j++){
                    if (playableCards[j]%10==value[i]){
                        winnable=true;
                        cardsOfRound[turn] = playableCards[j];
                        removeCard(cards,player,cardsOfRound,turn,&i,&j);
                    }
                }
            }
            if (winnable==false){
                for (int i = 0; i < higher; i++){
                    for (int j = 0; j < 8; j++){
                        if (playableCards[j]%10==value[i]){
                            cardsOfRound[turn] = playableCards[j];
                            removeCard(cards,player,cardsOfRound,turn,&i,&j);
                        }
                    }
                }
            }
        }
        else{// In this case the IA has no trump in hand so it will play his lowest cards 
            int value[8]={0,1,5,6,3,7,2,4};
            for (int i = 0; i <8; i++){
                for (int j = 0; j < 8; j++){
                    if (playableCards[j]%10==value[i]){
                        cardsOfRound[turn] = playableCards[j];
                        removeCard(cards,player,cardsOfRound,turn,&i,&j);
                    }
                }
            }
        }
    }
    //the code below will check if the IA is playing a Trump king or a TrumpQueen and will check if it's the bot as a elote,rebelote
    //if it's true it will display belote and rebelote and then add the point ot the right team
    if ((cardsOfRound[turn]/10==atout)&&((cardsOfRound[turn]%10==5)||(cardsOfRound[turn]%10==6))){//this line check if the card played is a TrumpKing or a trumpQueen
        for (int i = 0; i < 8; i++){//in this loop it will check if the other major Trump is in the players hand
            if ((cards[0][i]/10==atout)&&((cards[0][i]%10==5)||(cards[0][i]%10==6))){
                count++;
            }
        }
        if (count==2){//in this case the player can make a belote/rebelote
            if (player==3){//this will assignate which team has a belote for a later point distribution
                *belote=1;
                }
            else{
                *belote=2;
            }
            if (cardsOfRound[turn]%10==5){
                printf("Belote\n");
            }
            else{
                printf("Rebelote\n");
            }
        }
    }
}

void IAgetplayablecards(int** cards,int* cardsOfRound, int* playableCards, int atoutMode, int atout,int player){
    int NofPCards=0;// this variable indicate the Number Of Playble cards in the array
    if (cardsOfRound[0]==-1){//if it's the first turn the playable cards array will get filled with all the IA'hands because it can play anything
        for(int i=((player-1)*8);i<(player*8);i++){
            if (cards[1][i]!=0){
                playableCards[NofPCards]=cards[0][i];
                NofPCards++;
            }
        }
    }
    else if (atout==5){//IF the Full-Trump mode is active the playable cards array will get filled with all the IA'hands because it can play anything
        for(int i=((player-1)*8);i<(player*8);i++){
            if (cards[1][i]!=0){
                playableCards[NofPCards]=cards[0][i];
                NofPCards++;
            }
        }
    }
    else if (atout==4){//If the No-Trump mode is active the playable cards array will get filled with the correspounding color
        for(int i=((player-1)*8);i<(player*8);i++){
            if (cards[0][i]/10==cardsOfRound[0]/10 && cards[1][i]!=0){
                playableCards[NofPCards]=cards[0][i];
                NofPCards++;
            }
        }
        if (NofPCards==0){//if the IA has not the corresponding colors the array will fill with all the cards in IA hands
            for(int i=((player-1)*8);i<(player*8);i++){
                if (cards[1][i]!=0){
                    playableCards[NofPCards]=cards[0][i];
                    NofPCards++;
                }
            }
        }

    }
    else if (atoutMode==1){//If the card played was an Trump the array will fill wwith all the trump in IA's hands
        for(int i=((player-1)*8);i<(player*8);i++){
            if (cards[0][i]/10==atout && cards[1][i]!=0){
                playableCards[NofPCards]=cards[0][i];
                NofPCards++;
            }
        }
        if (NofPCards==0){//If there is no Trumps in hand the array will fill with all the cards in IA hands
            for(int i=((player-1)*8);i<(player*8);i++){
                if (cards[1][i]!=0){
                    playableCards[NofPCards]=cards[0][i];
                    NofPCards++;
                }
            }
        }
    }
    else{//If enter in this loop the array will fill with card of the same color as the first card played this round
        for(int i=((player-1)*8);i<(player*8);i++){
            if(cardsOfRound[0]/10==cards[0][i]/10 && cards[1][i]!=0){//Here is the color check
                playableCards[NofPCards]=cards[0][i];
                NofPCards++;
            }
        }
        if (NofPCards==0){//If there is no card of the corresponding color the only card the IA can play is the Trump so it will fill the array with Trumps in his hands
            for(int i=((player-1)*8);i<(player*8);i++){
                if(atout==cards[0][i]/10 && cards[1][i]!=0){//here is the trump check
                    playableCards[NofPCards]=cards[0][i];
                    NofPCards++;
                }
            }
        }
        if (NofPCards==0){//If there is no trump left then the array will fill wit all the card in IA's hand
            for(int i=((player-1)*8);i<(player*8);i++){
                if (cards[1][i]!=0){
                    playableCards[NofPCards]=cards[0][i];
                    NofPCards++;
                }
            }
        }
    }
}

void removeCard(int** cards,int player,int* cardsOfround, int turn, int* i, int* j){
    for(int k=((player-1)*8);k<(player*8);k++){
        if (cards[0][k] == cardsOfround[turn]){
            cards[1][k] = 0;
        }
    }
    *i=8;
    *j=8;
}