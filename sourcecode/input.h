char* getColorString(int); // return a string of the color based of the int input value. It takes the value of a card and return a string
char* getValueString(int); //same thing, but for the value of the card
//The following functions are all used to fix issues caused by the operation of scanf/getchar. Thoses issues are all caused by the usage of a buffer, wich stores unused data, such as all \n thats the user inputs
//Most of them are a bit "too much", but they made sur I didn't encounter any problem while asking for user input
char getcharB();//-> getchar();
int getInt();//->scanf("%d",integer), returns the int that the user wrote
void waitForEnter();//-> getchar();, but doesn't return anything and wait for \n to be entred
void clear();//used to clear the console screen
