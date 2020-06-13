char** initializeDisplayMatrix();
/*This function initialize the display Matrix.
The whole interface you see during the game is hardcoded into it (it's probably not the best way to do it):
"+Game-------------------------------------+Profile--------------------------------+");
"|              P3+-------+                |                                       |");
"|                |       |                |name: 0                                |");
"|                |       |                |games played : 1                       |");
"|                |       |                |high score : 2                         |");
"|                |       |                |                                       |");
"|                |       |                |Game-----------------------------------+");
"|                +-------+                |                                       |");
"|    P4+-------+         P2+-------+      |Team 1 Score: 3                        |");
"|      |       |           |       |      |Team 2 Score: 4        Round: 5        |");
"|      |       |           |       |      |                                       |");
"|      |       |           |       |      |Round----------------------------------+");
"|      |       |           |       |      |                                       |");
"|      |       |           |       |      |Turn: 6                                |");
"|      +-------+           +-------+      |Team 1 round score: 7                  |");
"|              P1+-------+                |Team 2 round score: 8                  |");
"|                |       |                |                                       |");
"|                |       |                |Contract-------------------------------+");
"|                |       |                |                                       |");
"|                |       |                |Trump: 9                               |");
"|                |       |                |Value: 10                              |");
"|                +-------+                |Team: 11         coinche: 12           |");
"|Cards----------------------------------------------------------------------------+");
"| +-------+ +-------+ +-------+ +-------+ +-------+ +-------+ +-------+ +-------+ |");
"| |       | |       | |       | |       | |       | |       | |       | |       | |");
"| |       | |       | |       | |       | |       | |       | |       | |       | |");
"| |       | |       | |       | |       | |       | |       | |       | |       | |");
"| |       | |       | |       | |       | |       | |       | |       | |       | |");
"| |       | |       | |       | |       | |       | |       | |       | |       | |");
"| +-------+ +-------+ +-------+ +-------+ +-------+ +-------+ +-------+ +-------+ |");
"+---------------------------------------------------------------------------------+");
Its stored in a 31*84 characthers matrix,and is modified during the game with thing such as the profile, the score, ect ect...
But never in a destructive manner (Nothing permanent like the borders or the categories are ever modified, only the values and the cards).
We tried implementing UTF characters, but issues with cross platforme compatibility and with the display matrix(UTF characters takes more memory than ASCII)
made it too hard to make it in time.
this fucntion returns a double pointer to this matrix.
*/
//All of the following functions don't return anything
void printMatrix(char** displayMatrix);
/*This function is used to display the matrix. It clears the console then print it line by line.
The only parameter is the pointer to the matrix */
void mtrxPrintText(int x, int y, char* string, char** displayMatrix);
/*This function allows to print a string into the matrix. It's never used by itself in gamelogic, only in the following functions
The parameters are:
-x and y coordinates of the position where the text will be printed
-the string to print
-a pointer to the displayMatrix */
void mtrxFillText(int id, char*string, char** displayMatrix);
/*This function allow to display text to a specific field on the upper right of the matrix.
What was previously written will be erased with a bunch of spaces, and new content will then be written
The parameters are:
-an id, wich is the field you want to modify. There is 13 id, from 0 to 12, and they all represent specific x and y coordinates.
They are visible in the commented interface above, at the position that they represent.
-the string to print
-a pointer to the displayMatrix*/
void mtrxFillInt(int id, int number, char** displayMatrix);
//Takes an int, convert it to a string, then use this string as a parameter to to function above to print that number
void mtrxPrintCard(int x, int y, int cardValue, char** displayMatrix);
/*This function is used to display a card in the matrix. Similarly to mtrxPrintText, its never used on its own.
the parameters are:
-x and y coordinates to the position where the card must be print
-the value of the cards
-a pointer to the displayMatrix*/
void mtrxPrintRoundCard(int player, int cardValue, char** displayMatrix);
/*This fuction will print a card specifically on a player spot on the playfield.
The parameters are:
-The player to who the card belongs
-the value of the card
-a pointer to the displayMatrix*/
void mtrxPrintP1Cards(char** displayMatrix, int** cards);
/*This function will print all of the cards the player still has in his deck
the parameters are:
-a pointers to the cards array to check the player 1 cards
-a pointer to the displayMatrix*/
void clearMatrix(char** displayMatrix);
/*This function clears every field so that the matrix is as blank as it was when it was initialized
The only parameter is a pointer to the displayMatrix*/
