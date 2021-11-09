#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int k,m;
int book[500];
int scriber[500];


int check(int U, int L)
{
    int max=0,count,mid;
    int i,j;

    mid = (U+L)/2;
    //printf("%d,%d => %d\n",U,L,mid);
    i=m-1;
    for(j=k-1;j>=0;j--){
        /*if(j==i){
            scriber[j] = i;
            if(book[i]>max) max = book[i];
            i--;

        }*/

        if(i<0) return 1;

        count = 0;
        while(count+book[i] <= mid && i>=0){
            count = count + book[i];
            i--;
        }

        if(j==0){
            while(i>=0) {
                count = count + book[i];
                i--;
            }
        }
        scriber[j] = i;
        if(count>max) max = count;

    }
    if(i>=0) return -1;
    else return (max<=mid);
}


int main()
{
    int N;
    int i,j;

    int U=0, L=0;
    int total=0;
    int res;

    freopen("714.in","r",stdin);
    freopen("myout.out","w",stdout);

    scanf("%d",&N);

    while(N>0){
        scanf("%d%d",&m,&k);

        total = 0; L=0;

        for(i=0; i<m; i++){
            scanf("%d",&book[i]);
            if(book[i]>L) L = book[i];
            total = total + book[i];
        }


        for(i=0; i<k; i++) scriber[i] = 0;

        U = total;



        while( U>L+1 ){

            res = check(U,L);

            if(res == 1 ) U = (U+L)/2;
            else  L = (U+L)/2;

            //res = check(U,L);
        }

        j=1;
        for(i=0; i<m; i++){

            if(i==0) printf("%d",book[i]);
            else printf(" %d",book[i]);

            if(scriber[j]==i && j<k){
                printf(" /");
                j++;
            }

        }
        printf("\n");

        N--;
    }

    return 0;
}
