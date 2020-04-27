#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>
#include <time.h>

void randomize(int **array){
    srand(time(0));
    int a=0,b=0,c=0,d=0,r;
    for (size_t i = 0; i < 32; i++){
        do{
            r=rand()%4+1;
        } while ((r==1&&a==8)||(r==2&&b==8)||(r==3&&c==8)||(r==4&&d==8));
        array[2][i]=r;
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
        printf("%d ",array[2][i]);
    }
}

int ** create(int lineNumber, int columnNumber){
	if (lineNumber > 0 && columnNumber > 0){
		int** matrix= (int**) malloc(lineNumber * sizeof(float*));
		if (matrix != NULL){
			for (int i=0;i<lineNumber;i++){
				matrix[i] = (int*) malloc(columnNumber * sizeof(float));
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

int main(){
    int **card=create(3,32),a=0;
    //card[2][32]={'0','1','2','3','4','5','6','7','10','11','12','13','14','15','16','17','20','21','22','23','24','25','26','27','30','31','32','33','34','35','36','37'}//

    for (size_t i = 0; i < 2; i++){
        for (size_t j = 0; j < 32; j++){
            printf("%d",card[i][j]);
        }   
    }
    printf("\n");
    randomize(card);
    return 0;
}