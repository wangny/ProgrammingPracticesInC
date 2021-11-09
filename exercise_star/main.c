#include <stdio.h>

int main(void)
{
    char A[15][15];
    int i,j,x,y,M,N;

    i=0;
    while(i<=14){
        j=0;
        while(j<=14){
            A[i][j] = '-';
            j++;
        }
        i++;
    }

    scanf("%d%d%d%d",&N,&M,&x,&y);

    i=0;
    while(i<N){
        A[i][y]='+';
        i++;
    }
    j=0;
    while(j<M){
        A[x][j]='+';
        j++;
    }

    for(i=x,j=y; i>=0 && j>=0; i--,j--){
        A[i][j]='*';
    }

    for(i=x,j=y; i>=0 && j<M; i--,j++){
        A[i][j]='*';
    }

    for(i=x,j=y; i<N && j<M; i++,j++){
        A[i][j]='*';
    }

    for(i=x,j=y; i<N && j>=0; i++,j--){
        A[i][j]='*';
    }


    A[x][y]='S';
    i=0;
    while(i<N){
        j=0;
        while(j<M){
            printf("%c",A[i][j]);
            j++;
        }
        printf("\n");
        i++;
    }

    return 0;
}
