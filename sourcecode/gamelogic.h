/*
0 = Heart
1 = Spike
2 = Square
3 = Clover

0=7
1=8
2=9
3=10
4=J
5=Q
6=K
7=A
*/
typedef struct contract {
    int team;
    int value;
    int color;
} contract;

int belote(/*int***/);
int defineContract(contract*);
