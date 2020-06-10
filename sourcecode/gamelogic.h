/*
0=7
1=8
2=9
3=10
4=J
5=Q
6=K
7=A
*/
typedef struct contract {//This structure is used to define the contract for the current round
    int team;
    int value;//the worth of the contract
    int color;//0=Heart, 1=Spade, 2=Diamond, 3=Clover
    int isCoinched;//0= none, 1=coinche
} contract;

int belote(int**);//Main function of the game, where everything takes place. The argument is the matrix of cards and player defined in array.c/.h
void defineContract(int,contract*, int**);/*This function is run at the begining of every round, and will define the contract for it.
It takes a pointeur to a contract variable and the matrix of cards*/
int gameRound(int** cards,int firstToContract,int* scoreT1, int* scoreT2);//nice
int play(int** cards,int player, int atout, int* roundT1, int* roundT2, int* belote,int turn);
int playCard(int** cards, int* cardsOfRound, int* atoutMode, int atout,int turn,int* belote);
int getplayablecards(int** cards, int* cardsOfRound,int* playableCards, int atoutMode, int atout);
void compareAndAdd(int** cards, int* playableCards,int*NofPCards, int colorToCompare);
int CalculateScore(int* winTeam, int* score, int* cardsOfRound, int player, int atout, int atoutMode);
int computeTotalScore(contract contract, int roundT1, int roundT2, int* scoreT1, int* scoreT2);
int getBeloteRebelotte(int** cards, int atout);
void announcement(int** cards,int player ,int* tsequence,int* fosequence,int* fisequence,int* asquare,int* nsquare,int* jsquare);
