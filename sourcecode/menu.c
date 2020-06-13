#include<stdio.h>
#include<stdlib.h>
#include"input.h"

int menu(){
    clear();
    int input = 0;
    printf("%s", ".______    _______  __        ______   .___________. _______ \n");
    printf("%s", "|   _  \\  |   ____||  |      /  __  \\  |           ||   ____|\n");
    printf("%s", "|  |_)  | |  |__   |  |     |  |  |  | `---|  |----`|  |__   \n");
    printf("%s", "|   _  <  |   __|  |  |     |  |  |  |     |  |     |   __|  \n");
    printf("%s", "|  |_)  | |  |____ |  `----.|  `--'  |     |  |     |  |____ \n");
    printf("%s", "|______/  |_______||_______| \\______/      |__|     |_______|\n");
    printf("%s", "_____________________________________________________________\n");
    printf("Please choose: \n1-Start a new game\n2-Check profiles statistics\n3-Quit\n");
    do{
        //display the menu and return a number corresponding to the choice of the user using the getint() function 
        input = getInt();
    }while(input<1 || input>3);
    return input;
}
