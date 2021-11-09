#include <stdio.h>
#include <stdlib.h>

int main()
{
    int N,B;
    int a[50][50];
    int i,j,x,y,q=1;
    int z[50];

    scanf("%d",&N);
    for(i=0;i<N;i++){
        for(j=0;j<N;j++){
            scanf("%d",&a[i][j]);
        }
    }

    scanf("%d",&B);

    while(B){
        scanf("%d %d",&x,&y);
        x--;
        y--;
        a[x][y] = 0;
        B--;
    }

    for(i=0,x=0;i<N;i++){
        q=1;
        for(j=0;j<N;j++){
            if(a[i][j]){
                q=0;
                break;
            }
            if(a[j][i]){
                q=0;
                break;
            }
        }
        //printf("%d,%d\n",i,q);
        if(q){
            z[x] = i+1;
            //printf("%d",z[x]);
            x++;
        }
    }

    for(i=0;i<x;i++){
        printf("%d\n",z[i]);
    }

    return 0;
}
