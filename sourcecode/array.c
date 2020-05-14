#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

void randomize(int **array){
    srand(time(0));//set the randint function for the rest of the function//
    int a=0,b=0,c=0,d=0,e=0,g=0,h=0,r,f;//initialize all the variable for the rest of the function,one for each player and one for the random number//

    for (int i = 0; i < 32; i++){//this loop initialize or reset the array each round before the card distribution//
        if ((i+e)%10==8){ //there are only 8 card for each colours so after 8 card it will switch into the next one//
            e+=2;         //In this program all the card had a code: we will divide the number by ten, the rest will be the card value and the quotient will be the color//
        }
        array[0][i]=i+e;
        array[1][i]=0;
    }

    for (int i = 0; i < 32; i++){//repeat until the array is complete//
        do{
            r=rand()%4+1;//assignate a random number between 1 and 4//
        } while ((r==1&&a==8)||(r==2&&b==8)||(r==3&&c==8)||(r==4&&d==8));//repeat it until the card is associate with a player who hasn't already 8 card//
        array[1][i]=r;//assignate the player whith a card//
        switch (r){//check at wich player is assignate the card and increment is number of card of the good player//
        case 1:
            a++;
            break;
        case 2:
            b++;
            break;
        case 3:
            c++;
            break;
        default:
            d++;
            break;
        }
    }
    for (int i = 0; i < 31; i++){// In this part the program will sort the array by player//
        f=0;
        while (f<(31-i)){//the programm will pass on the two loop and check if a case is higher than the next one, so after the first passage the last case will have the higher number//
            if (array[1][f]>array[1][f+1]){//if the next case is lower the programm will swapoue two card value and the two player//
                g=array[1][f+1];
                array[1][f+1]=array[1][f];
                array[1][f]=g;
                h=array[0][f+1];
                array[0][f+1]=array[0][f];
                array[0][f]=h;
            }
            f++;
        }
    }

}

int ** create(int lineNumber, int columnNumber){
	if (lineNumber > 0 && columnNumber > 0){//check if the user doesn't try to create an impossible array//
		int** matrix= (int**) malloc(lineNumber * sizeof(int*));// start the dinamyc allocation for each line of the array//
		if (matrix != NULL){// check again if the array is not null//
			for (int i=0;i<lineNumber;i++){//repeat for each line//
				matrix[i] = (int*) malloc(columnNumber * sizeof(int));// start the dynamic allocation for each column of the array//
				if (matrix[i] != NULL){
					for (int j=0;j<columnNumber;j++){//repeat for each line//
						matrix[i][j]=0;//initialize all the values of the array at 0//
					}
				}
			}
		}
		return matrix;
	}else{
		printf("there is a problem with the size of the matrice, make sure you entered a correct value");
		return NULL;
	}
}


//gcc -o main.exe main.c highscore.c array.c menu.c gamelogic.c IA.c input.c//
