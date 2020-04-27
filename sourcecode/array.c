#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>
#include <time.h>

int randomize(int **array){
    srand(time(0));
    int a=0,b=0,c=0,d=0,r;
    for (size_t i = 0; i < 32; i++){
        do{
            r=rand()%4+1;
        } while ((r==1&&a==8)||(r==2&&b==8)||(r==3&&c==8)||(r==4&&d==8));
        array[1][i]=r;
        switch (r){
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
	if (lineNumber > 0 && columnNumber > 0){
		int** matrix= (int**) malloc(lineNumber * sizeof(int*));
		if (matrix != NULL){
			for (int i=0;i<lineNumber;i++){
				matrix[i] = (int*) malloc(columnNumber * sizeof(int));
				if (matrix[i] != NULL){
					for (int j=0;j<columnNumber;j++){
						matrix[i][j]=0;
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
