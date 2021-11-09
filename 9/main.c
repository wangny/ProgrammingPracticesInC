#include <stdio.h>

#define WIDTH 4
#define HEIGHT 4

int map[HEIGHT][WIDTH];

void collapse(int dir){
    /* your code here */
}

void slide(int dir){
    int i,j,k;
    if(dir==1){
        k=0;
        for(j=0;j<=4;j++){
            for(i=0;(i<=3) && map[i][j];i++){
                map[k][j] = map[i][j];
                map[i][j] = 0;
                k=i;
            }
        }
    }else if(dir==2){
        for(i=0;i<=4;i++){
            for(j=4;(j>0) && (!map[i][j]);j--){
                map[i][j] = map[i][j-1];
                map[i][j-1] = 0;
            }
        }
    }else if(dir==3){
        for(j=0;j<=4;j++){
            for(i=4;(i>0) && (!map[i][j]);i--){
                map[i][j] = map[i-1][j];
                map[i-1][j] = 0;
            }
        }
    }else{
        for(i=0;i<=4;i++){
            for(j=0;(j<=3) && (!map[i][j]);j++){
                map[i][j] = map[i][j+1];
                map[i][j+1] = 0;
            }
        }
    }
}

void show(){
    int i, j;
    for(i = 0; i < HEIGHT; i++){
        for(j = 0; j < WIDTH; j++){
            printf(" %4d", map[i][j]);
        }
        printf("\n");
    }
}

int main()
{
    int N, d;
    int i, j;

    scanf("%d", &N);
    for(i = 0; i < HEIGHT; i++){
        for(j = 0; j < WIDTH; j++){
            scanf("%d", &map[i][j]);
        }
    }

    for(i = 0; i < N; i++){
        scanf("%d", &d);
        slide(d);
    }

    show();

    return 0;
}
