#include <stdio.h>
#include <stdlib.h>

int sort[101];


int compare(const void* a, const void* b){
    int c = *(int*)a;
    int d = *(int*)b;

    if(sort[c]!=sort[d]) return sort[c]-sort[d];
    else return c-d;
}


int main()
{
    char strings[100][51];
    int order[100];

    int M;
    int m,n;
    int unsort;
    int i,j,k;

    scanf("%d",&M);

    while(M>0){
        scanf("%d%d",&n,&m);
        for(i=0; i<m; i++){
            scanf("%s",strings[i]);
            order[i] = i;
        }

        for(i=0; i<m; i++){
            unsort = 0;
            for(j=0; j<n-1; j++){
                for(k=j+1; k<n; k++){
                    if(strings[i][k]<strings[i][j]) unsort++;
                }
            }
            sort[i] = unsort;
        }

        qsort(order,m,sizeof(int),compare);

        for(i=0; i<m; i++){
            printf("%s\n", strings[order[i]] );
        }

        M--;
        if(M>0)printf("\n");
    }

    return 0;
}
