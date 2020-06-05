typedef struct highscore {
    char name[11];
    int score;
} highscore;
//struture used to store highscores with the corresponding 5 character name (6 in the declaration because of the /0)

highscore* getHighScore();
void writeHighScore(highscore*);
void printHighScore(highscore *);
