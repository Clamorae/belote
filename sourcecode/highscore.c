#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "highscore.h"
#include "input.h"


profile* getProfiles(int*NumberOfProfiles){
    FILE* profilFile = fopen("profiles.sav","r");
    if(profilFile == NULL){
        printf("The profiles.sav file could not be open. It might have been moved, deleted or renamed.\nA new file wille be created and the game will quit(Your previous data wont be available until you restore your previous save file).\n");
        waitForEnter();
        FILE* temp = fopen("profiles.sav","w");
        fprintf(temp,"0\n");
        fclose(temp);
        exit(0);
    }
    if(fscanf(profilFile,"%d",NumberOfProfiles) == 0){emergencyExit();}
    profile* profileArray = NULL;
    if(*NumberOfProfiles != 0){
        profileArray = malloc(sizeof(profile)* *NumberOfProfiles);
        for(int i = 0; i<*NumberOfProfiles; i++){
            if(fscanf(profilFile,"%s",profileArray[i].name) == 0){emergencyExit();}
            if(fscanf(profilFile,"%d",&profileArray[i].numberOfGames) == 0){emergencyExit();};
            if(fscanf(profilFile,"%d",&profileArray[i].numberOfWins) == 0){emergencyExit();}
            if(fscanf(profilFile,"%d",&profileArray[i].maxScore) == 0){emergencyExit();};
        }
    }
    printf("Highscore loaded succesfully ! %d profiles were loaded.\n",*NumberOfProfiles);
    waitForEnter();
    fclose(profilFile);
    return profileArray;
}


void emergencyExit(){
    printf("Your save file could not be read properly. The data inside might have been modified or corrupted.\nTry to restore the file to a previous state or delete it (you will lose all your data).\nThe program will now exit.");
    exit(0);
}

int printProfiles(profile* profileArray, int NumberOfProfiles){
    if (NumberOfProfiles == 0){
        printf("No saved profiles :(\n");
        return 0;
    }
    printf("PROFILES\\_______________________________________________________\n");
    printf("NOM - NOMBRE DE PARTIE - RATIO VICTOIRE/DEFAITE - SCORE MAXIMUM\n");
    printf("_________________________________________________________________\n");
    for(int i=0; i<NumberOfProfiles;i++){
        printf("%s - %d - %d/%d - %d\n",profileArray[i].name,profileArray[i].numberOfGames,profileArray[i].numberOfWins,(profileArray[i].numberOfGames - profileArray[i].numberOfWins),profileArray[i].maxScore);
        printf("_ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _\n");
    }
    return 0;
}


profile* addNewProfile(profile* profileArray, int* NumberOfProfiles){
    char name[11];
    printf("Please enter your name :");
    scanf("%s", name);
    (*NumberOfProfiles)++;
    printf("%d\n",*NumberOfProfiles);
    profileArray = realloc(profileArray, sizeof(profile) * *NumberOfProfiles);
    strcpy(profileArray[*NumberOfProfiles-1].name,name);
    profileArray[*NumberOfProfiles-1].numberOfGames = 0;
    profileArray[*NumberOfProfiles-1].numberOfWins = 0;
    profileArray[*NumberOfProfiles-1].maxScore = 0;
    return profileArray;

}















//profile* getHighScore(){
//    //This function is used to get the highscores from the file hs.sav to an array of highscores, which is a structure defined in the .h
//    //It is called at the launch of the program
//    FILE* hsSaveFile = fopen("hs.sav","r");
//
//
//
//    profile *HSArray = malloc(sizeof(profile) * 10);//Malloc is used here so we can return a pointer and use the array in the main fucntion
//
//    for(int i = 0; i<10;i++){
//        fscanf(hsSaveFile,"%s",HSArray[i].name);//Here, fscanf is used to get the data from the file to the array, so we can directly get the good data types (string and long)
//        fscanf(hsSaveFile,"%d",&HSArray[i].score);//It is read line by line, alternating between a name and a score (The score is corresponding to the name above itself)
//    }
//    fclose(hsSaveFile);
//    return HSArray;//Returning the pointer to the array of highscores, which will be used to modify the highscores during runtime
//}
//
//void writeHighScore(highscore *array){
//    //this function is used to write the data from the array to the file hs.sav
//    //The argument is the pointer to the array, which is returned by the previous function.
//    //This function is called at the end of the program, and is mandatory if getHighScore was called
//    FILE* hsSaveFile = fopen("hs.sav","w");
//    for(int i=0; i<10;i++){
//        fprintf(hsSaveFile,"%s\n",array[i].name);//The data from the array is printed line by line, so the structure of the save file is
//        fprintf(hsSaveFile,"%d\n",array[i].score);// not modified (name \n score \n name \n score...)
//    }
//    printf("Highscore written sucessfully on hs.sav\n");
//    free(array);//This free the memory used by the malloc in getHighScore(), which is why it is mandatory
//    fclose(hsSaveFile);
//}
//
//void printHighScore(highscore *array){
//    clear();
//    printf("HIGH SCORES\\__________________________________________\n\n");
//    for(int i = 0; i<10; i++){
//        printf(" %d | %s | %d\n",i+1,array[i].name,array[i].score);
//    }
//    printf("_______________________________________________________\n");
//    waitForEnter();
//}
//
