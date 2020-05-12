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
    int isCoinched;//0= none, 1=coinche, 2=surcoinche
} contract;

int belote(int**);//Main function of the game, where everything takes place. The argument is the matrix of cards and player defined in array.c/.h
void defineContract(contract*, int**);/*This function is run at the begining of every round, and will define the contract for it.
It takes a pointeur to a contract variable and the matrix of cards*/
