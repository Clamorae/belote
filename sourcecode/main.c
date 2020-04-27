#include<stdio.h> // kono stDIO da !
#include<stdlib.h>
#include<string.h>
#include"highscore.h"
#include"array.h"

int main(){
    highscore *HSarray = getHighScore();
    strcpy(HSarray[0].name, "nice"); //update a name in the arry
    HSarray[0].score = 69420;//update a score in the array
    writeHighScore(HSarray);

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
