#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"input.h"


char** initializeDisplayMatrix(){//could've make it into a file and copy from that file but hardcoding is cool
    char** displayMatrix = (char**) malloc(31 * sizeof(char*));
    for(int i=0;i<31;i++){
        displayMatrix[i] = (char*) malloc(84 * sizeof(char));
    }
    strcpy(displayMatrix[0],"+Game-------------------------------------+Profile--------------------------------+");
    strcpy(displayMatrix[1],"|              P3+-------+                |                                       |");
    strcpy(displayMatrix[2],"|                |       |                |name:                                  |");
    strcpy(displayMatrix[3],"|                |       |                |games/win/lost:                        |");
    strcpy(displayMatrix[4],"|                |       |                |high score :                           |");
    strcpy(displayMatrix[5],"|                |       |                |                                       |");
    strcpy(displayMatrix[6],"|                |       |                |Game-----------------------------------+");
    strcpy(displayMatrix[7],"|                +-------+                |                                       |");
    strcpy(displayMatrix[8],"|    P4+-------+         P2+-------+      |Team 1 Score:                          |");
    strcpy(displayMatrix[9],"|      |       |           |       |      |Team 2 Score:          Round:          |");
    strcpy(displayMatrix[10],"|      |       |           |       |      |                                       |");
    strcpy(displayMatrix[11],"|      |       |           |       |      |Round----------------------------------+");
    strcpy(displayMatrix[12],"|      |       |           |       |      |                                       |");
    strcpy(displayMatrix[13],"|      |       |           |       |      |Turn:                                  |");
    strcpy(displayMatrix[14],"|      +-------+           +-------+      |Team 1 round score:                    |");
    strcpy(displayMatrix[15],"|              P1+-------+                |Team 2 round score:                    |");
    strcpy(displayMatrix[16],"|                |       |                |                                       |");
    strcpy(displayMatrix[17],"|                |       |                |Contract-------------------------------+");
    strcpy(displayMatrix[18],"|                |       |                |                                       |");
    strcpy(displayMatrix[19],"|                |       |                |Atout:                                 |");
    strcpy(displayMatrix[20],"|                |       |                |Value:                                 |");
    strcpy(displayMatrix[21],"|                +-------+                |Team:            coinche:              |");
    strcpy(displayMatrix[22],"|Cards----------------------------------------------------------------------------+");
    strcpy(displayMatrix[23],"| +-------+ +-------+ +-------+ +-------+ +-------+ +-------+ +-------+ +-------+ |");
    strcpy(displayMatrix[24],"| |       | |       | |       | |       | |       | |       | |       | |       | |");
    strcpy(displayMatrix[25],"| |       | |       | |       | |       | |       | |       | |       | |       | |");
    strcpy(displayMatrix[26],"| |       | |       | |       | |       | |       | |       | |       | |       | |");
    strcpy(displayMatrix[27],"| |       | |       | |       | |       | |       | |       | |       | |       | |");
    strcpy(displayMatrix[28],"| |       | |       | |       | |       | |       | |       | |       | |       | |");
    strcpy(displayMatrix[29],"| +-------+ +-------+ +-------+ +-------+ +-------+ +-------+ +-------+ +-------+ |");
    strcpy(displayMatrix[30],"+---------------------------------------------------------------------------------+");
    return displayMatrix;
}

void printMatrix(char** displayMatrix){
    clear();
    for(int i = 0; i<31;i++){
        printf("%s\n",displayMatrix[i]);
    }
}

void mtrxPrintText(int x, int y, char* string, char** displayMatrix){
    int length = (int) strlen(string);
    strncpy(&displayMatrix[y][x], string, length);
}

void mtrxFillText(int id, char*string, char** displayMatrix){
    switch (id) {
        case 0:
            mtrxPrintText(49,2,"          ",displayMatrix);
            mtrxPrintText(49,2,string,displayMatrix);
            break;
        case 1:
            mtrxPrintText(59,3,"                    ",displayMatrix);
            mtrxPrintText(59,3,string,displayMatrix);
            break;
        case 2:
            mtrxPrintText(56,4,"         ",displayMatrix);
            mtrxPrintText(56,4,string,displayMatrix);
            break;
        case 3:
            mtrxPrintText(57,8,"         ",displayMatrix);
            mtrxPrintText(57,8,string,displayMatrix);
            break;
        case 4:
            mtrxPrintText(57,9,"         ",displayMatrix);
            mtrxPrintText(57,9,string,displayMatrix);
            break;
        case 5:
            mtrxPrintText(73,9,"         ",displayMatrix);
            mtrxPrintText(73,9,string,displayMatrix);
            break;
        case 6:
            mtrxPrintText(49,13,"        ",displayMatrix);
            mtrxPrintText(49,13,string,displayMatrix);
            break;
        case 7:
            mtrxPrintText(63,14,"        ",displayMatrix);
            mtrxPrintText(63,14,string,displayMatrix);
            break;
        case 8:
            mtrxPrintText(63,15,"        ",displayMatrix);
            mtrxPrintText(63,15,string,displayMatrix);
            break;
        case 9:
            mtrxPrintText(50,19,"         ",displayMatrix);
            mtrxPrintText(50,19,string,displayMatrix);
            break;
        case 10:
            mtrxPrintText(50,20,"         ",displayMatrix);
            mtrxPrintText(50,20,string,displayMatrix);
            break;
        case 11:
            mtrxPrintText(49,21,"         ",displayMatrix);
            mtrxPrintText(49,21,string,displayMatrix);
            break;
        case 12:
            mtrxPrintText(69,21,"         ",displayMatrix);
            mtrxPrintText(69,21,string,displayMatrix);
            break;

    }
}

void mtrxPrintCard(int x, int y, int cardValue, char** displayMatrix){
    mtrxPrintText(x+1,y+1,"       ",displayMatrix);
    mtrxPrintText(x+1,y+5,"       ",displayMatrix);
    if(cardValue != -1){
        mtrxPrintText(x+1,y+1,getValueString(cardValue%10),displayMatrix);
        mtrxPrintText(x+1,y+5,getColorString(cardValue/10),displayMatrix);
    }
}

void mtrxPrintRoundCard(int player, int cardValue, char** displayMatrix){
    switch (player) {
        case 1:
            mtrxPrintCard(17,15 ,cardValue,displayMatrix);
            break;
        case 2:
            mtrxPrintCard(27, 8,cardValue,displayMatrix);
            break;
        case 3:
            mtrxPrintCard(17, 1,cardValue,displayMatrix);
            break;
        case 4:
            mtrxPrintCard(7, 8,cardValue,displayMatrix);
            break;
    }
}

void mtrxPrintP1Cards(char** displayMatrix, int** cards){
    for(int i=0; i<8; i++){
        if(cards[1][i] != 0){
            mtrxPrintCard((i*10)+2,23,cards[0][i], displayMatrix);
        }else{
            mtrxPrintCard((i*10)+2,23,-1, displayMatrix);
        }
    }
}

void clearMatrix(char** displayMatrix){
    for(int i=0;i<13;i++){
        mtrxFillText(i,"",displayMatrix);
    }
    for(int i=0;i<4;i++){
        mtrxPrintRoundCard(i+1,-1,displayMatrix);
    }
    for(int i=0; i<8; i++){
        mtrxPrintCard((i*10)+2,23,-1, displayMatrix);
    }
}
