char** initializeDisplayMatrix();
void printMatrix(char** displayMatrix);
void mtrxPrintText(int x, int y, char* string, char** displayMatrix);
void mtrxFillText(int id, char*string, char** displayMatrix);
void mtrxPrintCard(int x, int y, int cardValue, char** displayMatrix);
void mtrxPrintRoundCard(int player, int cardValue, char** displayMatrix);
void mtrxPrintP1Cards(char** displayMatrix, int** cards);
void clearMatrix(char** displayMatrix);
