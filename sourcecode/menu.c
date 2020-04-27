#include<stdio.h>
#include<stdlib.h>

int menu(){
    //display the menu and return a number corresponding to the hoice of the user
    int input = 0;
    printf("%s", ".______    _______  __        ______   .___________. _______ \n");
    printf("%s", "|   _  \\  |   ____||  |      /  __  \\  |           ||   ____|\n");
    printf("%s", "|  |_)  | |  |__   |  |     |  |  |  | `---|  |----`|  |__   \n");
    printf("%s", "|   _  <  |   __|  |  |     |  |  |  |     |  |     |   __|  \n");
    printf("%s", "|  |_)  | |  |____ |  `----.|  `--'  |     |  |     |  |____ \n");
    printf("%s", "|______/  |_______||_______| \\______/      |__|     |_______|\n");
    printf("%s", "_____________________________________________________________\n");
    printf("Veuilliez choisir une action: \n1-Commencer une partie\n2-Regarder les highscores\n3-Quitter\n");
    do{
        scanf("%d\n",&input);
    }while(input<1 || input>3);
    return input;
}
