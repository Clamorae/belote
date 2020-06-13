#include"highscore.h"
#include"gamelogic.h"
#include"input.h"
#include"array.h"
#include"IA.h"
#include"display.h"
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<stdbool.h>



void belote(int **cards, profile* profileArray, int profileNumber,char** displayMatrix){
    int scoreT1 = 0, scoreT2 = 0,roundT1, roundT2, first, belote;
    int round = 0;
    contract gameContract;//create a contract type variable for the game
    clearMatrix(displayMatrix);//Clear the display matric before the game
    mtrxFillText(0,profileArray[profileNumber].name,displayMatrix);//fill it with information
    mtrxFillInt(1,profileArray[profileNumber].numberOfGames,displayMatrix);
    mtrxFillInt(2,profileArray[profileNumber].maxScore,displayMatrix);
    printf("The game is about to begin...Be ready\n");
    waitForEnter();
    do{
        //this loop won't exit until the game has been won by a team
        round ++;
        mtrxFillInt(3,scoreT1,displayMatrix);
        mtrxFillInt(4,scoreT2,displayMatrix);
        mtrxFillInt(5,round,displayMatrix);
        mtrxFillInt(6,0,displayMatrix);
        randomize(cards);//cards are beeing shuffled and redistributed;
        mtrxPrintP1Cards(displayMatrix,cards);//The matrix is displayed for the first time
        roundT1 = 0;roundT2=0;//score of the round of the game
        mtrxFillInt(7,roundT1,displayMatrix);
        mtrxFillInt(8,roundT2,displayMatrix);
        printMatrix(displayMatrix);
        first = rand()%4+1;//the first player is choosen randomly
        printf("ROUND NUMBER %d\n",round);
        printf("The first to submit a contract for this round will be player %d\n",first);
        waitForEnter();
        defineContract(first,&gameContract,cards,displayMatrix);//contract is defined here
        first++;
        if (first>4){first = 1;}
        roundT1 = 0;
        roundT2 = 0;
        belote = getBeloteRebelotte(cards, gameContract.color);//get wich player has the belote rebelote
        for(int i =0;i<8;i++){
            //the loop will be ran once for each turn (8 turns)
            mtrxFillInt(6,i+1,displayMatrix);
            mtrxFillInt(7,roundT1,displayMatrix);
            mtrxFillInt(8,roundT2,displayMatrix);
            printMatrix(displayMatrix);
            printf("Press Enter to begin the turn...\n");
            first = turn(cards,first,gameContract.color, &roundT1, &roundT2,&belote,i,&scoreT1,&scoreT2,displayMatrix);
        }
        mtrxFillInt(7,roundT1,displayMatrix);
        mtrxFillInt(8,roundT2,displayMatrix);
        printMatrix(displayMatrix);
        printf("Round Results:\n\n");
        if(computeTotalScore(gameContract,roundT1,roundT2,&scoreT1,&scoreT2)){
            printf("Contract was successsfull !\n");
        }else{
            printf("Contract was not successfull !\n");
        }
        printf("The score is:\n-%d for team 1\n-%d for team 2\n",scoreT1, scoreT2);
        printf("Press ENTER to continue");
        waitForEnter();
    }while(scoreT1 < 701 && scoreT2 < 701);
    clear();
    printf("FINAL RESULTS\\___________________________________________________________\n\n");
    printf("The final score is :\nT1:%d\nT2:%d\n\n",scoreT1,scoreT2);
    if(scoreT1  > scoreT2){
        printf("CONGRATULATION! YOU'RE THE WINNER!\n");
        updateProfile(profileArray, profileNumber, 1, scoreT1);
    }else{
        printf("You lost. Maybe next time :(\n");
        updateProfile(profileArray, profileNumber, 0, scoreT1);
    }
    waitForEnter();
}

void defineContract(int player, contract* pContract,int **card, char** displayMatrix){
    int passes,temp;
    passes = 0;
    (*pContract).team = 0, (*pContract).value = 60, (*pContract).color = 0, (*pContract).isCoinched = 0;// the previous contract is cleared
    bool check=false;// this bool will turn to true whenever the contract is established
    srand(time(0));
    do{
        if((*pContract).team == 0){// if team == 0, thats mean there's no contract
            mtrxFillText(9,"No contract anounced",displayMatrix);
        }else{
            mtrxFillText(9,getColorString((*pContract).color),displayMatrix);
            mtrxFillInt(10,(*pContract).value,displayMatrix);
            mtrxFillInt(11,(*pContract).team,displayMatrix);
            mtrxFillInt(12,(*pContract).isCoinched,displayMatrix);
        }
        printMatrix(displayMatrix);
        printf("It's player %d turn\n",player);
        if (player == 1){
            temp = getContract(&pContract->value, &pContract->color, (*pContract).value, 680, (*pContract).team);//atout == 4 and 5 are for no trump and full trump
            switch(temp) {
                case 1://a contract was anounced
                    (*pContract).team = 1;
                    passes = 0;
                    break;
                case 2://the prvious contract was coinched
                    (*pContract).isCoinched = 1;
                    passes = 0;
                    break;
                default://the player passed
                    passes++;
                    break;
            }
        }
        else{
            BotContract(card,player,&passes,&pContract->value,&pContract->team,&pContract->color,&pContract->isCoinched);//get a contract from the bot
        }
        player ++;
        if(player>4){player = 1;}
        if (passes==3 && (*pContract).team!=0){
            printf("The contract was established\n");
            check=true;
        }
        else if (passes==4){
            passes = 0;
            printf("No contract was established, the cards has been reshuffled\n");
            randomize(card);
            mtrxPrintP1Cards(displayMatrix,card);
        }
        waitForEnter();
    }while(check==false);
}

int getContract(int *value, int *color, int minValue, int maxValue, int teamWithContract){//return 1 if a contract was estabished, 0 if the player passed, 2 if the player coinched
    int intInput;
    char chInput, temp;
    if(teamWithContract == 2){//if the team has a contrat, it gives you the poddibility to coinche
        printf("Do you want to coinche the opposing team contract ? [Y/n]\n");
        chInput = getcharB();
        if(chInput == 'y'||chInput == 'Y'){
            printf("Contract was coinched\n");
            return 2;
        }
    }
    printf("Do you want to announce a contrat ? [Y/n]\n");
    chInput = getcharB();//getchar works in a werid way and sometimes returns \n even with no keyboard inputs, this is used to fix it
    if (chInput == 'N'||chInput == 'n'){
        printf("You pass\n");
        return 0;
    }
    else{
        printf("How much do you want to bet ? (between %d and %d, multiples of 10 only)\n",minValue, maxValue);
        intInput = getInt();
        while(intInput <= minValue || intInput > maxValue || intInput%10 != 0){
            printf("Invalid value, please retry.\n");
            intInput = getInt();
        }
        *value = intInput;
        printf("On Which color do you want to bet ? [H]eart, [S]pade, [D]iamond, [C]lub, [F]ull Trump, [N]o Trump ?\n");
        while(1){
            do{
                chInput = getcharB();
            }while(chInput == '\n');
            if(chInput == 'h' || chInput == 'H'){
                *color = 0;
                printf("You anounced a contract\n");
                return 1;
            }
            else if(chInput == 's' || chInput == 'S'){
                *color = 1;
                printf("You anounced a contract\n");
                return 1;
            }
            else if(chInput == 'd' || chInput == 'D'){
                *color = 2;
                printf("You anounced a contract\n");
                return 1;
            }
            else if(chInput == 'c' || chInput == 'C'){
                *color = 3;
                printf("You anounced a contract\n");
                return 1;
            }
            else if(chInput == 'c' || chInput == 'C'){
                *color = 3;
                printf("You anounced a contract\n");
                return 1;
            }
            else if(chInput == 'c' || chInput == 'C'){
                *color = 3;
                printf("You anounced a contract\n");
                return 1;
            }
            else if(chInput == 'f' || chInput == 'F'){
                *color = 5;
                printf("You anounced a contract\n");
                return 1;
            }
            else if(chInput == 'n' || chInput == 'N'){
                *color = 4;
                printf("You anounced a contract\n");
                return 1;
            }
            else{
                printf("Invalid input, please retry.\n");
            }
        }
    }
}


int turn(int** cards,int player, int atout, int* roundT1, int* roundT2, int* belote,int turn,int* T1,int* T2, char** displayMatrix){
    int cardsOfRound[4] = {-1,-1,-1,-1};
    int atoutMode = 0;
    int tsequence=0, fosequence=0, fisequence=0,asquare=0,nsquare=0,jsquare=0;
    for(int i = 0;i<4;i++){
        waitForEnter();
        printMatrix(displayMatrix);
        if(player == 1){
            if (turn==1) {
                int colour;
                announcement(cards ,player ,&tsequence ,&fosequence ,&fisequence ,&asquare ,&nsquare ,&jsquare);//check if the player has an anouncement, could've been optimzed more by making a single function for all of the players
                if (jsquare==1){
                    printf("You're announcing a square of Jack, for a 200 points value\n");
                    *T1+=200;
                    mtrxFillInt(7,*T1,displayMatrix);
                }
                else if (nsquare==1){
                    printf("You're announcing a square of 9, for a 150 points value\n");
                    *T1+=150;
                    mtrxFillInt(7,*T1,displayMatrix);
                }
                else if (tsequence==1){
                    printf("You're announcing a sequence of 3, for a 20 points value\n");
                    *T1+=20;
                    mtrxFillInt(7,*T1,displayMatrix);
                }
                else if (fosequence==1){
                    printf("You're announcing a sequence of 4, for a 50 points value\n");
                    *T1+=50;
                    mtrxFillInt(7,*T1,displayMatrix);
                }
                else if (nsquare==1){
                    printf("You're announcing a sequence of 5, for a 100 points value\n");
                    *T1+=100;
                    mtrxFillInt(7,*T1,displayMatrix);
                }
                switch (asquare){
                case 3:
                    printf("You're announcing a square of 10, for a 100 points value\n");
                    *T1+=100;
                    mtrxFillInt(7,*T1,displayMatrix);
                    break;
                case 5:
                    printf("You're announcing a square of Queen, for a 100 points value\n");
                    *T1+=100;
                    mtrxFillInt(7,*T1,displayMatrix);
                    break;
                case 6:
                    printf("You're announcing a square of King, for a 100 points value\n");
                    *T1+=100;
                    mtrxFillInt(7,*T1,displayMatrix);
                    break;
                case 7:
                    printf("You're announcing a square of Ace, for a 100 points value\n");
                    *T1+=100;
                    mtrxFillInt(7,*T1,displayMatrix);
                    break;
                default:
                    break;
                }
            }
            playCard(cards,cardsOfRound,&atoutMode,atout,i,belote);
        }
        else{
            if (turn==1) {
                    announcement(cards ,player ,&tsequence ,&fosequence ,&fisequence ,&asquare ,&nsquare ,&jsquare);
                if (jsquare==1){
                    printf("The %d player is announcing a square of Jack, for a 200 points value\n",player);
                    switch (player){
                    case 2||4:
                        *T2+=200;
                        mtrxFillInt(8,*T2,displayMatrix);
                        break;

                    default:
                        *T1+=200;
                        mtrxFillInt(7,*T1,displayMatrix);
                        break;
                    }
                }
                else if (nsquare==1){
                    printf("The %d player is announcing a square of 9, for a 150 points value\n",player);
                    switch (player){
                    case 2||4:
                        *T2+=150;
                        mtrxFillInt(8,*T2,displayMatrix);
                        break;

                    default:
                        *T1+=150;
                        mtrxFillInt(7,*T1,displayMatrix);
                        break;
                    }
                }
                else if (tsequence==1){
                    printf("The %d player is announcing a sequence of 3, for a 20 points value\n",player);
                    switch (player){
                    case 2||4:
                        *T2+=20;
                        mtrxFillInt(8,*T2,displayMatrix);
                        break;

                    default:
                        *T1+=20;
                        mtrxFillInt(7,*T1,displayMatrix);
                        break;
                    }
                }
                else if (fosequence==1){
                    printf("The %d player is announcing a sequence of 4, for a 50 points value\n",player);
                    switch (player){
                    case 2||4:
                        *T2+=500;
                        mtrxFillInt(8,*T2,displayMatrix);
                        break;

                    default:
                        *T1+=500;
                        mtrxFillInt(7,*T1,displayMatrix);
                        break;
                    }
                }
                else if (nsquare==1){
                    printf("The %d player is announcing a sequence of 5, for a 100 points value\n",player);
                    switch (player){
                    case 2||4:
                        *T2+=100;
                        mtrxFillInt(8,*T2,displayMatrix);
                        break;

                    default:
                        *T1+=100;
                        mtrxFillInt(7,*T1,displayMatrix);
                        break;
                    }
                }
                switch (asquare){
                case 3:
                    printf("The %d player is announcing a square of 10, for a 100 points value\n",player);
                    switch (player){
                    case 2||4:
                        *T2+=100;
                        mtrxFillInt(8,*T2,displayMatrix);
                        break;

                    default:
                        *T1+=100;
                        mtrxFillInt(7,*T1,displayMatrix);
                        break;
                    }
                    break;
                case 5:
                    printf("The %d player is announcing a square of Queen, for a 100 points value\n",player);
                    switch (player){
                    case 2||4:
                        *T2+=100;
                        mtrxFillInt(8,*T2,displayMatrix);
                        break;

                    default:
                        *T1+=100;
                        mtrxFillInt(7,*T1,displayMatrix);
                        break;
                    }
                    break;
                case 6:
                    printf("The %d player is announcing a square of King, for a 100 points value\n",player);
                    switch (player){
                    case 2||4:
                        *T2+=100;
                        mtrxFillInt(8,*T2,displayMatrix);
                        break;

                    default:
                        *T1+=100;
                        mtrxFillInt(7,*T1,displayMatrix);
                        break;
                    }
                    break;
        atoutMode = 1;
                case 7:
                    printf("The %d player is announcing a square of Ace, for a 100 points value\n",player);
                    switch (player){
                    case 2||4:
                        *T2+=100;
                        mtrxFillInt(8,*T2,displayMatrix);
                        break;

                    default:
                        *T1+=100;
                        mtrxFillInt(7,*T1,displayMatrix);
                        break;
                    }
                    break;
                default:
                    break;
                }
            }
            IAplayCard(cards,cardsOfRound,atoutMode,atout,player,i,belote);

        }
        mtrxPrintRoundCard(player,cardsOfRound[i],displayMatrix);
        mtrxPrintP1Cards(displayMatrix,cards);
        printMatrix(displayMatrix);
        printf("Player %d plays\n",player);
        player++;
        if(player>4){player = 1;}
        if((cardsOfRound[i]/10 == atout && cardsOfRound[i] != -1 && atout != 4)|| atout == 5){
            atoutMode = i+1;
        }//If one of the player plays an atout, this variable will change to the turn when it was played. It used for the computation of the score later on

    }
    int winTeam, score;
    player = CalculateScore(&winTeam, &score, cardsOfRound, player,atout, atoutMode);
    printf("Player %d from team %d win this turn with %d points\n",player,winTeam,score);
    waitForEnter();
    for(int i=0;i<4;i++){
        mtrxPrintRoundCard(i+1,-1,displayMatrix);
    }
    if (winTeam == 1){
        (*roundT1) += score;
    }else{
        (*roundT2) += score;
    }

    return player;
}

void playCard(int** cards, int* cardsOfRound, int* atoutMode, int atout,int turn,int* belote){
    int playableCards[8] = {-1,-1,-1,-1,-1,-1,-1,-1};//create an array where all the playable crads will be stored
    int numberOfPCards = 0, count=0;
    numberOfPCards = getplayablecards(cards,cardsOfRound,playableCards,*atoutMode,atout);
    printf("Your playable cards are:\n");
    for(int i=0; i<numberOfPCards; i++){
        printf("%d - %s of %s\n",i+1,getValueString(playableCards[i]%10),getColorString(playableCards[i]/10));
    }
    printf("Please select a card to play\n");
    int UserInput;
    do{
        UserInput = getInt();
    }while(UserInput < 1 || UserInput > numberOfPCards);
    cardsOfRound[turn] = playableCards[UserInput - 1];//copy the playable cards into the array of the game
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
    for(int i=0; i<8; i++){// clear the played card from the "cards" array
        if (cards[0][i] == playableCards[UserInput - 1]){
            cards[1][i] = 0;
        }
    }
}

int getplayablecards(int** cards, int* cardsOfRound,int* playableCards, int atoutMode, int atout){
    int NofPCards = 0;
    int colorToMatch;
    if(atout == 5){
        compareAndAdd(cards,playableCards,&NofPCards,-1);//Allows you to play what you want in the case of a full trump
        return NofPCards;
    }else if(atout == 4){
        atoutMode = 1;//Override the atout value to force you to continue or to play something else if you cant
        colorToMatch = cardsOfRound[0]/10;
    }else{
        if(atoutMode != 0){
            colorToMatch = atout;
        }
        else{
            colorToMatch = cardsOfRound[0]/10;
        }
    }
    //if you're first, you can play whatever you want. If you're not fist, depending on atoutMode, you can play an atout or what you want. If you don't have any atout, you can just play what you want
    if(cardsOfRound[0] == -1){
        compareAndAdd(cards,playableCards,&NofPCards,-1);
    }
    else{
        compareAndAdd(cards,playableCards,&NofPCards,colorToMatch);
        if (NofPCards == 0){
            if(atoutMode == 0){
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
    if(colorToCompare == -1){//if equals to -1, all cards will be playable
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
    int atoutArray[8] = {4,2,7,3,6,5,1,0};// arrays of cards, from the strongest to the weakest, depending if an atout has been played or not
    int notAtoutArray[8] = {7,3,6,5,4,2,1,0};
    int comparaisonArray[8];
    int fullTrump = 0, noTrump=0;
    *score = 0;

    if(atout == 4){
        atoutMode = 0;
        for(int i = 0; i<8; i++){
            comparaisonArray[i] = notAtoutArray[i];
        }
        colorToMatch = cardsOfRound[0]/10;
        noTrump = 1;
    }else if (atout == 5){
        atoutMode = 1;
        for(int i = 0; i<8; i++){
            comparaisonArray[i] = atoutArray[i];
        }
        colorToMatch = cardsOfRound[0]/10;
        fullTrump = 1 ;
    }else{
        if(atoutMode != 0){
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
    }
    //this loop will determine the winner of the the round
    for(int i=0;i<8;i++){
        for(int j=0;j<4;j++){
            if(cardsOfRound[j]/10 == colorToMatch && cardsOfRound[j]%10 == comparaisonArray[i] && fullTrump==0){
                strongestCard = j;
                j = 4;
                i = 8;
            }
            else if (cardsOfRound[j]%10 == comparaisonArray[i]){
                strongestCard = j;
                j = 4;
                i = 8;
            }

        }
    }

    for(int i = 0; i<strongestCard; i++){//since we know who was the first player, we can use this information to determine to wich player belongs the winning card
        player++;
        if(player>4){player = 1;}
    }
    if (player%2 != 0){
        *winTeam = 1;
    }else{
        *winTeam = 2;
    }
    //this will calculate the  wortj of all the played cards
    if(noTrump == 0 && fullTrump == 0){
        for(int i = 0; i<4;i++){
            if(i+1 < atoutMode){
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
            }else{
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
            }
        }
    }else{
        if(fullTrump == 1){
            for(int i = 0; i<4;i++){
                switch (cardsOfRound[i]%10) {
                    case 0: *score+=0;break;
                    case 1: *score+=0;break;
                    case 2: *score+=9;break;
                    case 3: *score+=5;break;
                    case 4: *score+=14;break;
                    case 5: *score+=1;break;
                    case 6: *score+=3;break;
                    case 7: *score+=6;break;
                }
            }
        }else{
            for(int i = 0; i<4;i++){
                switch (cardsOfRound[i]%10) {
                    case 0: *score+=0;break;
                    case 1: *score+=0;break;
                    case 2: *score+=0;break;
                    case 3: *score+=10;break;
                    case 4: *score+=2;break;
                    case 5: *score+=3;break;
                    case 6: *score+=4;break;
                    case 7: *score+=19;break;
                }
            }
        }
    }
    return player;
}

int computeTotalScore(contract contract, int roundT1, int roundT2, int* scoreT1, int* scoreT2){
    int AttackingTeam, ATeamScore, DTeamScore, ATeamFinalScore, DTeamFinalScore,isSucessFull;

    if(contract.team == 1){//define the "attacking team" and the "defending" one
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
        (*scoreT1) += ATeamFinalScore;//add the points to the teams
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
    int count=0,higher=0;//count is for the square and higher for the sequences because for sequences I need to find the colour of the bid
    count=squarebid(cards,player,4);//call to the count function which will count the number of jack in the player's hand
    if (count==4){
        *jsquare=1;
    }
    count=0;//the count variable is reset between each bid check
    count=squarebid(cards,player,2);
    if (count==4){
        *nsquare=1;
    }
    count=0;
    count=squarebid(cards,player,7);
    if (count==4){
        *asquare=7;
    }
    count=0;
    count=squarebid(cards,player,7);
    if (count==4){
        *asquare=6;
    }
    count=0;
    count=squarebid(cards,player,5);
    if (count==4){
        *asquare=5;
    }
    count=0;
    count=squarebid(cards,player,3);
    if (count==4){
        *asquare=3;
    }
    count=0;
    //the part below is the sequence bid check
    for (int i = 8*(player-1); i < 8*player; i++){
        if ((cards[0][i]%10==(cards[0][i-1]%10)+1)&&(cards[0][i]/10==(cards[0][i-1]/10))){//the programme will check if there is a sequence of two and incrment the count variable for eeach of them
            count++;
        }
        else{
            if (higher<count){
                higher=count;//If the sequence is break and the sequences count is superior as previuosly the new higher sequence will be stocked here
            }
            count=0; //The count variable will be reset
        }
        if (higher==2){//each type of sequence has a variable which is changed if the sequences exist
            *tsequence=1;
        }
        else if (higher==3){
            *fosequence=1;
        }
        else if (higher>3){
            *fisequence=1;
        }
    }
}

int squarebid(int** cards,int player,int search){
    int count=0;
    for (int i = 8*(player-1); i < 8*player; i++){// this function will increment count each time their is a cards of the "search" value in the player's hand
        if (cards[0][i]%10==search){
            count++;
        }
    }
    return count;
}
