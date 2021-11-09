#include <stdio.h>
#include <stdlib.h>

int base[12];
int time[12];
int used[12];
int T, k, l;

int cursum;
int NONE=1;

void find(int layer){

    int i,j;
    int last, lastl;;

    if(cursum==T){
        printf("%d",used[0]);
        for(i=1; i<l; i++) printf("+%d",used[i]);
        printf("\n");
        NONE=0;
        return;
    }


    if(layer>=k) return;



    for(i=time[layer]; i>=0; i--){
        last = cursum;
        lastl = l;
        if(cursum + base[layer]*i <= T){
           for(j=0; j<i; j++){
                used[l] = base[layer];
                l++;
           }
           cursum = cursum + base[layer]*i;
           find(layer+1);
        }
        cursum = last;
        l = lastl;
    }
}




int main()
{
    int N;
    int i,t;

    scanf("%d%d",&T,&N);

    while(N!=0){

        for(i=0; i<12; i++) base[i]=0;
        for(i=0; i<12; i++) time[i]=0;

        k=0;
        for(i=0; i<N; i++){
            scanf("%d",&t);
            if(k>0 && t==base[k-1]) time[k-1]++;
            else{
                base[k] = t;
                time[k]++;
                k++;
            }
        }

        cursum=0; l=0; NONE=1;

        printf("Sums of %d:\n",T);

        find(0);
        if(NONE) printf("NONE\n");



        scanf("%d%d",&T,&N);
    }






    return 0;
}
