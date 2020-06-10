#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "highscore.h"
#include "input.h"


profile* getProfiles(int*NumberOfProfiles){
    FILE* profilFile = fopen("profiles.sav","r");
    if(profilFile == NULL){
        printf("The profiles.sav file could not be open. It might have been moved, deleted or renamedgdb.\nA new file wille be created and the game will quit(Your previous data wont be available until you restore your previous save file).\n");
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
    float pourcentage;
    printf("PROFILES\\_______________________________________________________\n");
    printf("NOM | NOMBRE DE PARTIE | RATIO VICTOIRE/DEFAITE | SCORE MAXIMUM\n");
    printf("_________________________________________________________________\n");
    for(int i=0; i<NumberOfProfiles;i++){
        printf("\n");
        if(profileArray[i].numberOfGames == 0){
            pourcentage = 0;
        }
        else{
            pourcentage = ((float)profileArray[i].numberOfWins/(float)profileArray[i].numberOfGames)*100;
        }
        printf("%s | %d | %d/%d (%.1f%) | %d\n",profileArray[i].name,profileArray[i].numberOfGames,profileArray[i].numberOfWins,(profileArray[i].numberOfGames - profileArray[i].numberOfWins),pourcentage,profileArray[i].maxScore);
        printf("_ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _\n");
    }
    return 0;
}


profile* addNewProfile(profile* profileArray, int* NumberOfProfiles){
    char name[255];
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

profile* selectProfile(profile* profileArray, int* numberOfProfiles, int* profileNumber){
    int intInput;
    clear();
    printf("Please select a profile\n\n");
    printf("1 - Create a new profile\n");
    for(int i = 0; i< *numberOfProfiles;i++){
        printf("%d - %s\n",i+2,profileArray[i].name);
    }
    intInput = getInt();
    while(intInput<1 || intInput > *numberOfProfiles+2){
        printf("Invalid Input, please retry\n");
        intInput = getInt();
    }
    if(intInput == 1){
        profileArray = addNewProfile(profileArray,numberOfProfiles);
        *profileNumber = *numberOfProfiles-1;
    }else{
        *profileNumber = intInput - 2;
    }
    printf("profile %s sélectionner\n",profileArray[*profileNumber].name);
    waitForEnter();
    waitForEnter();
    return profileArray;
}

void updateProfile(profile* profileArray, int profileNumber, int win, int score){
    (profileArray[profileNumber].numberOfGames)++;
    if(win == 1){
        (profileArray[profileNumber].numberOfWins)++;
    }
    if(score > profileArray[profileNumber].maxScore){
        printf("New high score! Congrats!\n");
        profileArray[profileNumber].maxScore = score;
    }
    printf("Your profile has been updated:\nname:%s\nWin/Lose:%d-%d\nhigh score:%d\n",profileArray[profileNumber].name,\
    profileArray[profileNumber].numberOfWins,profileArray[profileNumber].numberOfGames - profileArray[profileNumber].numberOfWins,profileArray[profileNumber].maxScore);
}

void saveProfiles(profile* profileArray, int NumberOfProfiles){
    FILE* profilFile = fopen("profiles.sav","w");
    fprintf(profilFile,"%d\n",NumberOfProfiles);
    for(int i=0;i<NumberOfProfiles;i++){
        fprintf(profilFile,"%s\n",profileArray[i].name);
        fprintf(profilFile,"%d\n",profileArray[i].numberOfGames);
        fprintf(profilFile,"%d\n",profileArray[i].numberOfWins);
        fprintf(profilFile,"%d\n",profileArray[i].maxScore);
    }
    fclose(profilFile);
    free(profileArray);
}
