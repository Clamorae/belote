#include <stdlib.h>
#include <stdio.h>

 typedef struct highscore {
    char name[6];
    long score;
} highscore;

highscore* getHighScore(){
    highscore *HSArray = malloc(sizeof(highscore) * 5);//Malloc is used here so we can return a pointer and use the array in the main fucntion
    FILE* hsSaveFile = fopen("hs.sav","rt");
    for(int i = 0; i<5;i++){
        fscanf(hsSaveFile,"%s",HSArray[i].name);
        fscanf(hsSaveFile,"%d",&HSArray[i].score);
    }
    //test print
    for(int i = 0; i<5;i++){
        printf("%s\n",HSArray[i].name);
        printf("%d\n",HSArray[i].score);
        printf("\n");
    }
    fclose(hsSaveFile);
    return HSArray;
}
