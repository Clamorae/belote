#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

int randomize(int **array){
    srand(time(0));//set the randint function for the rest of the function//
    int a=0,b=0,c=0,d=0,r;//initialize all the variable for the rest of the function,one for each player and one for the random number//
    for (size_t i = 0; i < 32; i++){//repeat until the array is complete//
        do{
            r=rand()%4+1;//assignate a random number between 1 and 4//
        } while ((r==1&&a==8)||(r==2&&b==8)||(r==3&&c==8)||(r==4&&d==8));//repeat it until the card is associate with a player who hasn't already 8card//
        array[1][i]=r;//assignate the player at the card//
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
    return **array;
}

int ** create(int lineNumber, int columnNumber){
	if (lineNumber > 0 && columnNumber > 0){//check if the user don't try to create an impossible array//
		int** matrix= (int**) malloc(lineNumber * sizeof(int*));// start the dinamyc allocation for each line of the array//
		if (matrix != NULL){// check again if the array is not null//
			for (int i=0;i<lineNumber;i++){//repeat for each line//
				matrix[i] = (int*) malloc(columnNumber * sizeof(int));// start the dinamyc allocation for each column of the array//
				if (matrix[i] != NULL){
					for (int j=0;j<columnNumber;j++){//repeat for each line//
						matrix[i][j]=0;//initialize all the case of the array at 0//
					}
				}
			}
		}
        while (columnNumber) free(matrix[--columnNumber]);
        free(matrix);
		return matrix;
	}else{
		printf("there is a problem with the size of the matrice, make sure you entered a correct value");
		return NULL;
	}
}
