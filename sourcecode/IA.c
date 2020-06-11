#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<stdbool.h>
#include"input.h"
#include "IA.h"

void BotContract(int** card,int player, int* passes,int* value,int* contractOwner,int* color, int* coinche){
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
            if ((card[0][((player-1)*8)+j])/10==i &&((card[0][((player-1)*8)+j]/10==7)||(card[0][((player-1)*8)+j]/10==2)||(card[0][((player-1)*8)+j]/10==4))){
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
    int playableCards[8] = {-1,-1,-1,-1,-1,-1,-1,-1};//initialize the playable car array and reset it before each bot turn
    int higher=0,count=0;//initialize the variable which will check if there a is a belote and who will chekc the best card to play
    int numberOfPCards = 0;
    bool winnable=false;// initialize the boolean which will test if the play is winnable or if its play the lowest card
    IAgetplayablecards(cards,cardsOfRound,playableCards,atoutMode,atout,player);//call the fonction which will define whiwh card the IA can play

    if (turn==0){//this part of the fonction will only be active if the IA is the first to play
        cardsOfRound[turn] = playableCards[0];
        for(int k=((player-1)*8);k<(player*8);k++){
            if (cards[0][k] == cardsOfRound[turn]){
                cards[1][k] = 0;
            }
        }
    }

    else if (atoutMode==2){
        int value[8]={0,1,5,6,3,7,2,4};
        for (int i = 0; i < turn; i++){
            for (int j = 0; j < 8; j++){
                if (value[j]==cardsOfRound[turn]%10){
                    if (j>higher){
                        higher=j;
                    }
                    j=8;
                }
            }
        }
        for (int i = higher; i < 8; i++){
            for (int j = 0; j < 8; j++){
                if (playableCards[j]%10==value[i]){
                    winnable=true;
                    cardsOfRound[turn] = playableCards[j];
                    for(int k=((player-1)*8);k<(player*8);k++){
                        if (cards[0][k] == playableCards[j]){
                            cards[1][k] = 0;
                        }
                    }
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
                        for(int k=((player-1)*8);k<(player*8);k++){
                            if (cards[0][k] == playableCards[j]){
                                cards[1][k] = 0;
                            }
                        }
                        j=8;
                        i=8;
                    }
                }
            }
        }
    }
    else if (atoutMode==3){
        int value[8]={0,1,2,4,5,6,3,7};
        if (cardsOfRound[0]==playableCards[0]){
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
                for (int j = 0; j < 8; j++){
                    if (playableCards[j]%10==value[i]){
                        winnable=true;
                        cardsOfRound[turn] = playableCards[j];
                        for(int k=((player-1)*8);k<(player*8);k++){
                            if (cards[0][k] == playableCards[j]){
                                cards[1][k] = 0;
                            }
                        }
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
                            for(int k=((player-1)*8);k<(player*8);k++){
                                if (cards[0][k] == playableCards[j]){
                                    cards[1][k] = 0;
                                }
                            }
                            j=8;
                            i=8;
                        }
                    }
                }
            }
        }
        else{
            for (int i = 0; i < 8; i++){
                for (int j = 0; j < 8; j++){
                    if (playableCards[j]%10==value[i]){
                        cardsOfRound[turn] = playableCards[j];
                        for(int k=((player-1)*8);k<(player*8);k++){
                            if (cards[0][k] == playableCards[j]){
                                cards[1][k] = 0;
                            }
                        }
                        j=8;
                        i=8;
                    }
                }
            }
        }
    }
    else if(atoutMode==0 && atout==playableCards[0]/10){//In this case the IA doest have the color which is played by the leader so IA will play an atout
        int value[8]={0,1,5,6,3,7,2,4};
        for (int i = 0; i < 8; i++){
            for (int j = 0; j < 8; j++){
                if (playableCards[j]%10==value[i]){
                    cardsOfRound[turn] = playableCards[j];
                    for(int k=((player-1)*8);k<(player*8);k++){
                        if (cards[0][k] == cardsOfRound[turn]){
                            cards[1][k] = 0;
                        }
                    }
                    j=8;
                    i=8;
                }
            }
        }
    }

    else if (atoutMode==0 && cardsOfRound[0]/10==playableCards[0]/10){
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
                    for(int k=((player-1)*8);k<(player*8);k++){
                        if (cards[0][k] == playableCards[j]){
                            cards[1][k] = 0;
                        }
                    }
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
                        for(int k=((player-1)*8);k<(player*8);k++){
                            if (cards[0][k] == playableCards[j]){
                                cards[1][k] = 0;
                            }
                        }
                        j=8;
                        i=8;
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
                for (int j = 0; j < 8; j++){
                    if (playableCards[j]%10==value[i]){
                        winnable=true;
                        cardsOfRound[turn] = playableCards[j];
                        for(int k=((player-1)*8);k<(player*8);k++){
                            if (cards[0][k] == playableCards[j]){
                                cards[1][k] = 0;
                            }
                        }
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
                            for(int k=((player-1)*8);k<(player*8);k++){
                                if (cards[0][k] == playableCards[j]){
                                    cards[1][k] = 0;
                                }
                            }
                            j=8;
                            i=8;
                        }
                    }
                }
            }
        }
        else{
            int value[8]={0,1,5,6,3,7,2,4};
            for (int i = 0; i <8; i++){
                for (int j = 0; j < 8; j++){
                    if (playableCards[j]%10==value[i]){
                        cardsOfRound[turn] = playableCards[j];
                        for(int k=((player-1)*8);k<(player*8);k++){
                            if (cards[0][k] == playableCards[j]){
                                cards[1][k] = 0;
                            }
                        }
                        j=8;
                        i=8;
                    }
                }
            }
        }
    }
    if ((cardsOfRound[turn]/10==atout)&&((cardsOfRound[turn]%10==5)||(cardsOfRound[turn]%10==6))){
        for (int i = 0; i < 8; i++){
            if ((cards[0][i]/10==atout)&&((cards[0][i]%10==5)||(cards[0][i]%10==6))){
                count++;
            }
        }
        if (count==2){
            if (player==3){
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
    int NofPCards=0;
    if (cardsOfRound[0]==-1){
        for(int i=((player-1)*8);i<(player*8);i++){
            if (cards[1][i]!=0){
                playableCards[NofPCards]=cards[0][i];
                NofPCards++;
            }
        }
    }
    else if (atoutMode==2){
        for(int i=((player-1)*8);i<(player*8);i++){
            if (cards[1][i]!=0){
                playableCards[NofPCards]=cards[0][i];
                NofPCards++;
            }
        }
    }
    else if (atoutMode==3){
        for(int i=((player-1)*8);i<(player*8);i++){
            if (cards[0][i]/10==cardsOfRound[0]/10 && cards[1][i]!=0){
                playableCards[NofPCards]=cards[0][i];
                NofPCards++;
            }
        }
        if (NofPCards==0){
            for(int i=((player-1)*8);i<(player*8);i++){
                if (cards[1][i]!=0){
                    playableCards[NofPCards]=cards[0][i];
                    NofPCards++;
                }
            }
        }

    }
    else if (atoutMode==1){
        for(int i=((player-1)*8);i<(player*8);i++){
            if (cards[0][i]/10==atout && cards[1][i]!=0){
                playableCards[NofPCards]=cards[0][i];
                NofPCards++;
            }
        }
        if (NofPCards==0){
            for(int i=((player-1)*8);i<(player*8);i++){
                if (cards[1][i]!=0){
                    playableCards[NofPCards]=cards[0][i];
                    NofPCards++;
                }
            }
        }
    }
    else{
        for(int i=((player-1)*8);i<(player*8);i++){
            if(cardsOfRound[0]/10==cards[0][i]/10 && cards[1][i]!=0){
                playableCards[NofPCards]=cards[0][i];
                NofPCards++;
            }
        }
        if (NofPCards==0){
            for(int i=((player-1)*8);i<(player*8);i++){
                if(atout==cards[0][i]/10 && cards[1][i]!=0){
                    playableCards[NofPCards]=cards[0][i];
                    NofPCards++;
                }
            }
        }
        if (NofPCards==0){
            for(int i=((player-1)*8);i<(player*8);i++){
                if (cards[1][i]!=0){
                    playableCards[NofPCards]=cards[0][i];
                    NofPCards++;
                }
            }
        }
    }
}
