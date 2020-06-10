#include"highscore.h"
#include"gamelogic.h"
#include"input.h"
#include"array.h"
#include"IA.h"
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<stdbool.h>
//Faudrait vraiment que je pense a commenter ce truc la


int belote(int **card, profile* profileArray, int profileNumber){
    clear();
    int scoreT1 = 0, scoreT2 = 0,roundT1, roundT2, first, belote;
    contract gameContract;//create a contract type variable for the game
    char nom[255];
    printf("OPEN THE GAME\n");
    do{
        roundT1 = 0;roundT2=0;
        first = rand()%4+1;
        printf("The first to submit a contract for this round will be player %d\n",first);
        waitForEnter();
        randomize(card);//shuffle the cards and sort them (Player 1 cards from index 0 to 7, P2 from 8 to 15, ect...)
        defineContract(first,&gameContract,card);
        first++;
        if (first>4){first = 1;}
        roundT1 = 0;
        roundT2 = 0;
        belote = getBeloteRebelotte(card, gameContract.color);
        for(int i =0;i<8;i++){
            clear();
            printf("Contract is:\n-team: %d\n-value: %d\n-color: %s\n-coinched: %d\n\n",gameContract.team, gameContract.value, getColorString(gameContract.color), gameContract.isCoinched);
            printf("Turn n%d\n\n",i+1);
            printf("Team 1 have %d points\nTeam 2 have %d points\nPress Enter to begin the round\n\n",roundT1,roundT2);
            waitForEnter();
            play(card,first,gameContract.color, &roundT1, &roundT2,&belote,i,&scoreT1,&scoreT2);
            first++;
            if (first>4){first = 1;}
        }
        clear();
        printf("Round Results:\n\n");
        if(computeTotalScore(gameContract,roundT1,roundT2,&scoreT1,&scoreT2)){
            printf("Contract was succesfull !\n");
        }else{
            printf("Contract was not succesfull !\n");
        }
        printf("The score is:\n-%d for team 1\n-%d for team 2\n",scoreT1, scoreT2);
        printf("Press ENTER to start a new round\n");
        waitForEnter();
    }while(scoreT1 < 701 && scoreT2 < 701);
    clear();
    if(scoreT1  > scoreT2){
        printf("TEAM 1 WINS YOUHOU\n");
        updateProfile(profileArray, profileNumber, 1, scoreT1);
    }else{
        printf("TEAM 2 WINS SO SAD\n");
        updateProfile(profileArray, profileNumber, 0, scoreT1);
    }


}

void defineContract(int player, contract* pContract,int **card){
    int passes,temp;
    passes = 0;
    (*pContract).team = 0, (*pContract).value = 60, (*pContract).color = 0, (*pContract).isCoinched = 0;
    bool check=false;
    srand(time(0));
    do{
        clear();
        if((*pContract).team == 0){
            printf("There is currently no contract\n");
        }else{
            printf("The following contract was announced:\nteam:%d\nvalue:%d\ncolor:%s\ncoinche:%d\n\n", (*pContract).team, (*pContract).value, getColorString((*pContract).color),(*pContract).isCoinched);
        }
        printf("It's player %d turn\n",player);
        if (player == 1){
            printP1Cards(card);
            temp = getContract(&pContract->value, &pContract->color, (*pContract).value, 680, (*pContract).team);
            switch(temp) {
                case 1:
                    (*pContract).team = 1;
                    passes = 0;
                    break;
                case 2:
                    (*pContract).isCoinched = 1;
                    passes = 0;
                    break;
                default:
                    passes++;
                    break;
            }
        }
        else{
            BotContract(card,player,&passes,&pContract->value,&pContract->team,&pContract->color);
        }
        player ++;
        if(player>4){player = 1;}
        if (passes==3 && (*pContract).team!=0){
            check=true;
        }
        else if (passes==4){
            passes = 0;
            printf("No contract was established, the cards has been reshuffled\n");
            randomize(card);
        }
        waitForEnter();
    }while(check==false);
}

int play(int** cards,int player, int atout, int* roundT1, int* roundT2, int* belote,int turn,int* T1,int* T2){


    int atoutMode = 0;
    int cardsOfRound[4] = {-1,-1,-1,-1};
    int tsequence=0, fosequence=0, fisequence=0,asquare=0,nsquare=0,jsquare=0;
    for(int i = 0;i<4;i++){
        if(player == 1){
            if (turn==1) {
                    announcement(cards ,player ,&tsequence ,&fosequence ,&fisequence ,&asquare ,&nsquare ,&jsquare );
                if (jsquare==1){
                    printf("You're announcing a square of Jack, for a 200 points value");
                    T1+=200;
                }
                else if (nsquare==1){
                    printf("You're announcing a square of 9, for a 150 points value");
                    T1+=150;
                }
                else if (tsequence==1){
                    printf("You're announcing a sequence of 3, for a 20 points value");
                    T1+=20;
                }
                else if (fosequence==1){
                    printf("You're announcing a sequence of 4, for a 50 points value");
                    T1+=50;
                }
                else if (nsquare==1){
                    printf("You're announcing a sequence of 5, for a 100 points value");
                    T1+=100;
                }
                switch (asquare){
                case 3:
                    printf("You're announcing a square of 10, for a 100 points value");
                    T1+=100;
                    break;
                case 5:
                    printf("You're announcing a square of Queen, for a 100 points value");
                    T1+=100;
                    break;
                case 6:
                    printf("You're announcing a square of King, for a 100 points value");
                    T1+=100;
                    break;
                case 7:
                    printf("You're announcing a square of Ace, for a 100 points value");
                    T1+=100;
                    break;
                default:
                    break;
                }
            }
            playCard(cards,cardsOfRound,&atoutMode,atout,i,belote);
        }
        else{
            if (turn==1) {
                    announcement(cards ,player ,&tsequence ,&fosequence ,&fisequence ,&asquare ,&nsquare ,&jsquare );
                if (jsquare==1){
                    printf("The %d player is announcing a square of Jack, for a 200 points value",player);
                    switch (player){
                    case 2||4:
                        T2+=200;
                        break;
                    
                    default:
                        T1+=200;
                        break;
                    }
                }
                else if (nsquare==1){
                    printf("The %d player is announcing a square of 9, for a 150 points value",player);
                    switch (player){
                    case 2||4:
                        T2+=150;
                        break;
                    
                    default:
                        T1+=150;
                        break;
                    }
                }
                else if (tsequence==1){
                    printf("The %d player is announcing a sequence of 3, for a 20 points value",player);
                    switch (player){
                    case 2||4:
                        T2+=20;
                        break;
                    
                    default:
                        T1+=20;
                        break;
                    }
                }
                else if (fosequence==1){
                    printf("The %d player is announcing a sequence of 4, for a 50 points value",player);
                    switch (player){
                    case 2||4:
                        T2+=500;
                        break;
                    
                    default:
                        T1+=500;
                        break;
                    }
                }
                else if (nsquare==1){
                    printf("The %d player is announcing a sequence of 5, for a 100 points value",player);
                    switch (player){
                    case 2||4:
                        T2+=100;
                        break;
                    
                    default:
                        T1+=100;
                        break;
                    }
                }
                switch (asquare){
                case 3:
                    printf("The %d player is announcing a square of 10, for a 100 points value",player);
                    switch (player){
                    case 2||4:
                        T2+=100;
                        break;
                    
                    default:
                        T1+=100;
                        break;
                    }
                    break;
                case 5:
                    printf("The %d player is announcing a square of Queen, for a 100 points value",player);
                    switch (player){
                    case 2||4:
                        T2+=100;
                        break;
                    
                    default:
                        T1+=100;
                        break;
                    }
                    break;
                case 6:
                    printf("The %d player is announcing a square of King, for a 100 points value",player);
                    switch (player){
                    case 2||4:
                        T2+=100;
                        break;
                    
                    default:
                        T1+=100;
                        break;
                    }
                    break;
                case 7:
                    printf("The %d player is announcing a square of Ace, for a 100 points value",player);
                    switch (player){
                    case 2||4:
                        T2+=100;
                        break;
                    
                    default:
                        T1+=100;
                        break;
                    }
                    break;
                default:
                    break;
                }
            }
            printf("Player %d is currently playing\n",player);
            IAplayCard(cards,cardsOfRound,atoutMode,atout,player,i,belote);
            waitForEnter();

        }
        player++;
        if(player>4){player = 1;}
        if(cardsOfRound[i]/10 == atout && cardsOfRound[i] != -1){
            atoutMode = 1;
        }
        clear();
        printf("Currently, the game is:\n");
        for(int j=0;j<4;j++){
            if(cardsOfRound[j] == -1){
                printf("-No Card\n");
            }
            else{
                printf("-%s of %s\n",getValueString(cardsOfRound[j]%10),getColorString(cardsOfRound[j]/10));
            }
        }
    }
    int winTeam, score;
    CalculateScore(&winTeam, &score, cardsOfRound, player,atout, atoutMode);
    printf("Team %d win this play with %d points\n",winTeam,score);
    while(getchar()!='\n');
    getchar();
    if (winTeam == 1){
        (*roundT1) += score;
    }else{
        (*roundT2) += score;
    }

    return 0;
}

int playCard(int** cards, int* cardsOfRound, int* atoutMode, int atout,int turn,int* belote){
    int playableCards[8] = {-1,-1,-1,-1,-1,-1,-1,-1};
    int numberOfPCards = 0, count=0;
    clear();
    printf("Currently, the game is:\n");
    for(int i=0;i<4;i++){
        if(cardsOfRound[i] == -1){
            printf("-No cards\n");
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
    printf("Please select a card to play\n");
    int UserInput;
    do{
        UserInput = getInt();
    }while(UserInput < 1 || UserInput > numberOfPCards);
    cardsOfRound[turn] = playableCards[UserInput - 1];
    if ((playableCards[UserInput - 1]/10==atout)&&((playableCards[UserInput - 1]%10==5)||(playableCards[UserInput - 1]%10==6))){
        for (int i = 0; i < 8; i++){
            if ((cards[0][i]/10==atout)&&((cards[0][i]%10==5)||(cards[0][i]%10==6))){
                count++;
            }
        }
        if (count==2){
            *belote=1;
            if (playableCards[UserInput - 1]%10==5){
                printf("Belote\n");
            }
            else{
                printf("Rebelote\n");
            }
        }
    }
    for(int i=0; i<8; i++){
        if (cards[0][i] == playableCards[UserInput - 1]){
            cards[1][i] = 0;
        }
    }
    return 0;

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

    /*if ( Full-Trump ){
        for (int i = 0; i < 8; i++){
            if (cards[1][i]!=0){
                playableCards[NofPCards]==cards[0][i];
                NofPCards++;
            }
            
        }
        
    }*/
    /*else if (No Trump){
        for(int i=0;i<8;i++){
            if (cards[0][i]/10==cardsOfRound[0]/10 && cards[1][i]!=0){
                playableCards[NofPCards]=cards[0][i];
                NofPCards++;
            }
        }
        if (NofPCards==0){
            for(int i=0;i<8;i++){
                if (cards[1][i]!=0){
                    playableCards[NofPCards]=cards[0][i];
                    NofPCards++;
                }    
            }
        }
    }*/
    
    

    if(cardsOfRound[0] == -1){
        printf("no first cards\n");
        compareAndAdd(cards,playableCards,&NofPCards,-1);
    }
    else{
        compareAndAdd(cards,playableCards,&NofPCards,colorToMatch);
        if (NofPCards == 0){
            if(atoutMode != 1){
                compareAndAdd(cards,playableCards,&NofPCards,atout);
                if (NofPCards == 0){
                    printf("No playable card, atout mode off\n");
                    compareAndAdd(cards,playableCards,&NofPCards,-1);
                }
            }
            else{
                printf("No playable card, atout mode on\n");
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

int CalculateScore(int* winTeam, int* score, int* cardsOfRound, int player, int atout, int atoutMode){
    int strongestCard, colorToMatch;
    int atoutArray[8] = {4,2,7,3,6,5,1,0};
    int notAtoutArray[8] = {7,3,6,5,4,2,1,0};
    int comparaisonArray[8];
    *score = 0;

    if(atoutMode == 1){
        colorToMatch = atout;
        for(int i = 0; i<8; i++){
            comparaisonArray[i] = atoutArray[i];
        }
    }else{
        colorToMatch = cardsOfRound[0]/10;
        for(int i = 0; i<8; i++){
            comparaisonArray[i] = notAtoutArray[i];
        }
    }

    for(int i=0;i<8;i++){
        for(int j=0;j<4;j++){
            if(cardsOfRound[j]/10 == colorToMatch && cardsOfRound[j]%10 == comparaisonArray[i]){
                strongestCard = j;
                j = 4;
                i = 8;
            }
        }
    }

    for(int i = 0; i<strongestCard; i++){
        player++;
        if(player>4){player = 1;}
    }
    if (player%2 != 0){
        *winTeam = 1;
    }else{
        *winTeam = 2;
    }

    for(int i = 0; i<4;i++){
        if(cardsOfRound[i]/10 == atout){
            switch (cardsOfRound[i]%10) {
                case 0: *score+=0;break;
                case 1: *score+=0;break;
                case 2: *score+=14;break;
                case 3: *score+=10;break;
                case 4: *score+=20;break;
                case 5: *score+=3;break;
                case 6: *score+=4;break;
                case 7: *score+=11;break;
            }
        }else{
            switch (cardsOfRound[i]%10) {
                case 0: *score+=0;break;
                case 1: *score+=0;break;
                case 2: *score+=0;break;
                case 3: *score+=10;break;
                case 4: *score+=2;break;
                case 5: *score+=3;break;
                case 6: *score+=4;break;
                case 7: *score+=11;break;
            }
        }
    }
    return 0;
}

int computeTotalScore(contract contract, int roundT1, int roundT2, int* scoreT1, int* scoreT2){
    int AttackingTeam, ATeamScore, DTeamScore, ATeamFinalScore, DTeamFinalScore,isSucessFull;

    if(contract.team == 1){
        AttackingTeam = 1;
        ATeamScore = roundT1;
        DTeamScore = roundT2;
    }else{
        AttackingTeam = 2;
        ATeamScore = roundT2;
        DTeamScore = roundT1;
    }

    if(ATeamScore >= contract.value){
        isSucessFull = 1;
        if(contract.isCoinched){
            ATeamFinalScore = (ATeamScore + contract.value)*2;
            DTeamFinalScore = 0;
        }else{
            ATeamFinalScore = ATeamScore + contract.value;
            DTeamFinalScore = DTeamScore;
        }
    }else{
        isSucessFull = 0;
        if(contract.isCoinched){
            ATeamFinalScore = 0;
            DTeamFinalScore = (162 + contract.value)*2;
        }else{
            ATeamFinalScore = 0;
            DTeamFinalScore = DTeamScore;
        }
    }
    if(AttackingTeam == 1){
        (*scoreT1) += ATeamFinalScore;
        (*scoreT2) += DTeamFinalScore;
    }else{
        (*scoreT2) += ATeamFinalScore;
        (*scoreT1) += DTeamFinalScore;
    }
    return isSucessFull;
}

int getBeloteRebelotte(int** cards, int atout){//return 0 if no belote rebelote, or return the player with the belote
    int count;
    for(int i=0; i<4; i++){
        for (int j = 0; j < 8; j++){
            count = 0;
            if ((cards[0][(i*8)+j]/10==atout)&&((cards[0][(i*8)+j]%10==5)||(cards[0][(i*8)+j]%10==6))){
                count++;
            }
            if(count == 2){
                return i+1;
            }
        }
    }
    return 0;
}

void announcement(int** cards,int player ,int* tsequence,int* fosequence,int* fisequence,int* asquare,int* nsquare,int* jsquare){
    int count=0,higher[2]={0,0};
    for (int i = 8*(player-1); i < 8*player; i++){
        if (cards[0][i]%10==4){
            count++;
        }
    }
    if (count==4){
        *jsquare=1;
    }
    count=0;
    for (int i = 8*(player-1); i < 8*player; i++){
        if (cards[0][i]%10==2){
            count++;
        }
    }
    if (count==4){
        *nsquare=1;
    }
    count=0;
    for (int i = 8*(player-1); i < 8*player; i++){
        if (cards[0][i]%10==7){
            count++;
        }
    }
    if (count==4){
        *asquare=7;
    }
    count=0;
    for (int i = 8*(player-1); i < 8*player; i++){
        if (cards[0][i]%10==6){
            count++;
        }
    }
    if (count==4){
        *asquare=6;
    }
    count=0;
    for (int i = 8*(player-1); i < 8*player; i++){
        if (cards[0][i]%10==5){
            count++;
        }
    }
    if (count==4){
        *asquare=5;
    }
    count=0;
    for (int i = 8*(player-1); i < 8*player; i++){
        if (cards[0][i]%10==3){
            count++;
        }
    }
    if (count==4){
        *asquare=3;
    }
    count=0;
    for (int i = 8*(player-1); i < 8*player; i++){
        if ((cards[0][i]%10==(cards[0][i-1]%10)+1)&&(cards[0][i]/10==(cards[0][i-1]/10))){
            count++;
        }
        else{
            higher[0]=count;
            higher[1]=cards[0][i]/10;
            count=0;
        }
    }
    if (higher[0]==3){
        *tsequence=1;
    }
    else if (higher[0]==4){
        *fosequence=1;
    }
    else if (higher[0]>4){
        *fisequence=1;
    }


}
