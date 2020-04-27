#include <stdlib.h>
#include <stdio.h>
#include "highscore.h"

highscore* getHighScore(){
    //This function is used to get the highscores from the file hs.sav to an array of highscores, wich is a structure defined in the .h
    //It is called at the launch of the program
    highscore *HSArray = malloc(sizeof(highscore) * 5);//Malloc is used here so we can return a pointer and use the array in the main fucntion
    FILE* hsSaveFile = fopen("hs.sav","r");
    for(int i = 0; i<5;i++){
        fscanf(hsSaveFile,"%s",HSArray[i].name);//Here, fscanf is used to get the data from the file to the array, so we can directly get the good data types (string and long)
        fscanf(hsSaveFile,"%d",&HSArray[i].score);//It is read line by line, alternating between a name and a score (The score is corresponding to the name above itself)
    }
    fclose(hsSaveFile);
    printf("Highscore loaded sucessfully\n");
    return HSArray;//Returning the pointer to the array of highscores, wich will be used to modify the highscores during runtime
}

void writeHighScore(highscore *array){
    //this function is used to write the data from the array to the file hs.sav
    //The argument is the pointer to the array, wich is returned by the previous function.
    //This function is called at the end of the program, and is mandatory if getHighScore was called
    FILE* hsSaveFile = fopen("hs.sav","w");
    for(int i=0; i<5;i++){
        fprintf(hsSaveFile,"%s\n",array[i].name);//The data from the array is printed line by line, so the structure of the save file is
        fprintf(hsSaveFile,"%d\n",array[i].score);// not modified (name \n score \n name \n score...)
    }
    printf("Highscore written sucessfully on hs.sav\n");
    free(array);//This free the memory used by the malloc in getHighScore(), wich is why it is mandatory
    fclose(hsSaveFile);
}

void printHighScore(highscore *array){
    printf("HIGH SCORES\\__________________________________________\n\n");
    for(int i = 0; i<5; i++){
        printf(" %d | %s | %d\n",i+1,array[i].name,array[i].score);
    }
    printf("_______________________________________________________\n");
}
