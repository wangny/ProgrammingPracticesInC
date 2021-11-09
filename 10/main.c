#include <stdio.h>
#include <stdlib.h>

int main()
{
    int m[100][2]={0},n[100][2]={0},q[100]={0};
    int M,N,Q,i,j;
    int *p,*a,*b;

    scanf("%d",&M);
    for(i=0;i<M;i++){
        scanf("%d%d",&m[i][0],&m[i][1]);
    }
    scanf("%d",&N);
    for(i=0;i<N;i++){
        scanf("%d%d",&n[i][0],&n[i][1]);

    }
    scanf("%d",&Q);
    for(i=0;i<Q;i++){
        scanf("%d",&q[i]);
    }

    p = &q;
    a = &m;
    for(i=0;i<N;i++){
        *(p+n[i][0]-1) = n[i][1];
        for(j=0;j<M;j++){

        }
    }


    return 0;
}
