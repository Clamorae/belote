#include"gamelogic.h"
#include<stdio.h>
#include<stdlib.h>
#include<time.h>


int belote(/*int **cardArray*/){
    int scoreJ1 = 0, scoreJ2 = 0, scoreJ3 = 0, scoreJ4 = 0;
    int scoreT1 = 0, scoreT2 = 0;
    contract *pContract;
    //do{
    //    //distribution des cartes
    //}while(scoreT1 >= 701 || scoreT2 >= 701);
    //if(scoreT1>scoreT2){return 1;}
    //else{return 2;}
    defineContract(pContract);
    return 0;
}


int defineContract(contract* pContract){
    int player, value, color, passes,contractOwner;
    int hasContract = 0;
    char chInput;
    int intInput;
    value = 0;
    color = 0;
    contractOwner = 0;
    srand(time(0));
    player = rand()%4+1;
    do{
        printf("le contract est pour le joueur %d, d'une valeur de %d et de couleur %d\n",contractOwner,value,color);
        printf("Au tour du joueur %d\n", player);
        if(player == 1){
            printf("Contract ? [Y/n]\n");
            chInput = getchar();
            printf("%c\n",chInput);
            if(chInput == 'y' || chInput == 'Y'){
                hasContract = 1;
                contractOwner = 1;
                passes = 0;
                printf("Value of the contract ? [Value/Color]\n");
                scanf("%d/%d", &value, &color);
            }else{
                passes ++;
            }
        }else{
            //Choix de l'ia a faire
            passes ++;
        }
        player += 1;
        if(player>4){player = 1;}
    }while(1);
}
