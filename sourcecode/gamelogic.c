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
    clear();
    int scoreT1 = 0, scoreT2 = 0,roundT1 =0, roundT2 =0, first, belote = 0;
    contract gameContract;//create a contract type variable for the game
    printf("OPEN THE GAME\n");
    waitForEnter();
    do{
        roundT1 = 0;roundT2=0;
        first = rand()%4+1;
        printf("The first to submit a contract for this round will be player %d\n",first);
        randomize(card);//shuffle the cards and sort them (Player 1 cards from index 0 to 7, P2 from 8 to 15, ect...)
        defineContract(first,&gameContract,card);
        first++;
        if (first>4){first = 1;}
        roundT1 = 0;
        roundT2 = 0;
        for(int i =0;i<8;i++){
            clear();
            printf("Contract is:\n-team: %d\n-value: %d\n-color: %s\n-coinched: %d\n\n",gameContract.team, gameContract.value, getColorString(gameContract.color), gameContract.isCoinched);
            printf("Turn n%d\n\n",i+1);
            printf("Team 1 have %d points\nTeam 2 have %d points\n\n",roundT1,roundT2);
            play(card,first,gameContract.color, &roundT1, &roundT2,&belote);
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
    }while(scoreT1 <= 701 || scoreT2 <= 701);
    clear();
    if(scoreT1  > scoreT2){
        printf("TEAM 1 WINS YOUHOU\n");
    }else{
        printf("TEAM 2 WINS YOUHOU\n");
    }
}

void defineContract(int player, contract* pContract,int **card){
    int passes,temp;
    passes = 0;
    (*pContract).team = 0, (*pContract).value = 60, (*pContract).color = 0, (*pContract).isCoinched = 0;
    bool check=false;
    srand(time(0));
    do{
        if((*pContract).team == 0){
            printf("There is currently no contract\n");
        }else{
            printf("The contract is detained by the player %d, and is worth %d on %s\n", (*pContract).team, (*pContract).value, getColorString((*pContract).color));
        }
        if (player == 1){
            temp = getContract(&pContract->value, &pContract->color, (*pContract).value, 680, (*pContract).team);
            switch(temp) {
                case 1:
                    (*pContract).team = 1;
                    passes = 0;
                    break;
                case 2:
                    (*pContract).isCoinched = 1;
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
            clear();
            printf("No contract was established, the cards has been reshuffled\n");
            randomize(card);
        }
        waitForEnter();
    }while(check==false);
}

int play(int** cards,int player, int atout, int* roundT1, int* roundT2, int* belote){
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
            playCard(cards,cardsOfRound,&atoutMode,atout,i,belote);
        }
        else{
            printf("Le joeur %d joue\n",player);
            IAplayCard(cards,cardsOfRound,atoutMode,atout,player,i,belote);
            waitForEnter();

        }
        player++;
        if(player>4){player = 1;}
        if(cardsOfRound[i]/10 == atout && cardsOfRound[i] != -1){
            atoutMode = 1;
        }
        clear();
    }
    int winTeam, score;
    CalculateScore(&winTeam, &score, cardsOfRound, player,atout, atoutMode);
    printf("C'est l'équipe %d qui l'emporte avec %d points\n",winTeam,score);
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
                    printf("pas de carte jouable, atout mode off\n");
                    compareAndAdd(cards,playableCards,&NofPCards,-1);
                }
            }
            else{
                printf("pas de carte jouable, atout mode on\n");
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

/*void annonce(){
    check annonce 1 pour chaque joueur
    return type1
}*/
