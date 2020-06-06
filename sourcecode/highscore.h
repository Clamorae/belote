typedef struct profile {
    char name[11];
    int numberOfGames;
    int numberOfWins;
    int maxScore;
} profile;
//struture used to store highscores with the corresponding 5 character name (6 in the declaration because of the /0)

profile* getProfiles(int*NumberOfProfiles);
void emergencyExit();
int printProfiles(profile* profileArray, int NumberOfProfiles);
profile* addNewProfile(profile* profileArray, int* NumberOfProfiles);
//highscore* getHighScore();
//void writeHighScore(highscore*);
//void printHighScore(highscore *);
