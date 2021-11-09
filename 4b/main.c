#include <stdio.h>

int main(void)
{
    int N,i,j;
    int x[20][20];

    scanf("%d",&N);
    scanf("%d",&x[1][1]);
    for (j = N; j >= 2; j = j-1){
        scanf("%d",&x[1][j]);
    }
    for (j = 1;j <= N;j++){
        printf("%2d",x[1][j]);
    }
    printf("\n");
    for (i = 2; i <= N; i++){
        x[i][1] = x[i-1][N];
        printf("%2d",x[i][1]);
        for (j = 2; j <= N; j++){
            x[i][j] = x[i-1][j-1];
            printf("%2d",x[i][j]);
        }
        printf("\n");
    }

    return 0;
}
