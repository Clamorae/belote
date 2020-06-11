/*
This sturcture is used to define the contract for the round.
it contains the team to wich the contracts belong, the value of it, the color, and if the
contract was "coinched" ()

*/
typedef struct contract {
    int team;
    int value;
    int color;//0=Heart, 1=Spade, 2=Diamond, 3=Clover
    int isCoinched;//0= none, 1=coinche
} contract;

void belote(int **cards, profile* profileArray, int profileNumber);
/*This is the main function of the game. It starts after the player choose his profile and end at the end of the game. It calls most other functions in this file.
the parameters are :
-The cards array(explained in array.h) because, well, it's going to be difficult to play without cards
-The profileArray and the profileNumber, used to save the results after the game in the profilArray.
It doesn't return anything
*/
void defineContract(int player,contract* pContract, int** cards);
/*This function is run at the begining of every round, and will define the contract for it.It ask a contract for both the player and the bots.
The parameters are :
-the player integer, wich is the first player to anounce a contracts
-a pointer to a contract, wich values are set to 0 then to the new contract values
-the cards array is only used to print the cards of the player before he has to submit a contract
It doesn't return anything
*/
int turn(int** cards,int player, int atout, int* roundT1, int* roundT2, int* belote,int turn,int* T1,int* T2);
/*This function is called once each turn. Every player plays they card. The score and the winner of said turn are then computed
the parameters are:
-the cards array
-the player int, wich is the first player to play
-the atout for the current round
-pointers to roundT1 and roundT2, wich are the score of both team for the round (not the total score)
-the int belote, worth 0 if no one has a belotte rebelotte. Else, it's the value of the player detaining it.
-The turn number and pointers to the global score. Mostly Used for the announcement
It returns the player that won the turn
*/
void playCard(int** cards, int* cardsOfRound, int* atoutMode, int atout,int turn,int* belote);
/*
This function is called when the player must play a card.It will ask the player what card he want to play and modify the cards and round array according to it.
the parameters are:
-the cards array
-the round array, containing all cards played during a turn, in order of play.
-a pointer to atoutMode, wich is equal to 1 if an atout as been played, hence changing the available cards to play
-the color of the atout
-the turn, used to determine in what position the card should be added in cards of round
-a pointer to belote, wich turns to 1 if the player has a belotte
It doesn't return anything
*/
int getplayablecards(int** cards, int* cardsOfRound,int* playableCards, int atoutMode, int atout);
/*
This function is used to get the cards that the player can play
the parameters are:
-the cards array
-the round array, containing all cards played during a turn, in order of play.
-the playable card array, an array with a length of 8, filled with -1 (no cards) beforehand. It is then filled with the player's playable cards
-atoutMode, equal to 1 if an atout has been played, and the atout value
-the turn, used to determine in what position the card should be added in cards of round
-a pointer to belote, wich turns to 1 if the player has a belotte
It returns the number of playable cards.
*/
void compareAndAdd(int** cards, int* playableCards,int*NofPCards, int colorToCompare);
/*This function add every card of a said color to the playableCards array. It's only used in the getplayablecards function
the parameters are:
-the cards array
-the playable cards array, wich is filled by this function
-a pointer to the number of plyable cards
-the color to compare the cards of the player deck with (if its egal to -1, every card are added by default)
It doesn't return anything
*/
int CalculateScore(int* winTeam, int* score, int* cardsOfRound, int player, int atout, int atoutMode);
/*This function is used to calculate the final score based on the contracts and the score of the turn
the parameters are:
-a pointer to winTeam, wich will be modified to the winning team
-a pointer to the values of the cards, wich will be computed by this function
-the cardsOfRound array, containing every cards played during this round
-the player value, using to determine wich cards belong to who
-the atout and the atoutMode, used to change the values
it returns the winning player
*/
int computeTotalScore(contract contract, int roundT1, int roundT2, int* scoreT1, int* scoreT2);
/*This function is used to compute the final score of the round, and wich team win
the parameters are:
-the contract of the game
-the score of the round of both team 1 and team 2
-pointer to scoreT1 and scoreT2, wich are the global scores.
it ruturns 1 if the contract was succesfull, 0 if its not
*/
int getBeloteRebelotte(int** cards, int atout);
/*
this function check if any player can anounce a belote rebelote
the parameters are:
-the cards array
-the atout
it ruturns the player who has the belotte/rebelotte, 0 if no one does
*/
void announcement(int** cards,int player ,int* tsequence,int* fosequence,int* fisequence,int* asquare,int* nsquare,int* jsquare);
/*
    Kant1 comment la
*/

//Copyright (c) 2018 Copyright Holder All Rights Reserved.
