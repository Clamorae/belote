typedef struct highscore {
    char name[6];
    long score;
} highscore;
//struture used to store highscores with the corresponding 5 character name (6 in the declaration because of the /0)

highscore* getHighScore();
void writeHighScore(highscore*);
