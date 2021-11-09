#include <stdio.h>
int b[100][100];
int main(void)
{
    int i,j,M;
    scanf("%d",&M);
    i = 1;
    j = 1;
    for (i = 1; i <= M; i++) {
        j = 1;
        b[i][j] = 1;
        printf("%10d",b[i][j]);

        for (j = 2; j <= i; j++) {
            b[i][j] = b[i-1][j-1] + b[i-1][j];
            printf("%10d", b[i][j]);
        }
        printf("\n");
    }

    return 0;
}
