#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int desk[1000001];

int main()
{
    int prime[46340];
    int p[15500];
    unsigned int L,U;
    int N=0;

    int min, max;
    unsigned int minpair[2], maxpair[2];

    int is_prime = 0;
    int i,j,k;
    int tmp1,tmp2;

    for(i=2; i<46340; i++) prime[i] = 1;
    for(i=2; i<46340; i++){
        if(prime[i]==1){
            p[N] = i;
            N++;
            for(j = i*i; j<46340; j = j+i) prime[j] = 0;
        }
    }

    while(scanf("%d%d",&L,&U)==2){
        max = 0; min = U-L+1;
        maxpair[0] = 0; maxpair[1]=0;
        minpair[0] = 0; minpair[1]=0;

        for(i=0; i<=U-L; i++) desk[i] = 1;
        for(;i<1000001; i++) desk[i]=0;

        for(i=L; i<=U; i++){
            if(i==1){
                desk[i-1]=0;
                continue;
            }
            if(desk[i-L]==1){
                is_prime = 1;
                for(k=0; k<N ; k++){
                    if(i%p[k]==0){
                        if(i!=p[k]) desk[i-L]=0;
                        is_prime = 0;
                        break;
                    }
                }
                if(is_prime==0){
                    for(j=i+p[k]; j<=U; j=j+p[k]) desk[j-L]=0;
                }
            }
        }

        tmp1=0;tmp2=0;
        for(i=L; i<=U; i++){
            if(desk[i-L]==1){

                if(tmp2<tmp1) tmp2 = i;
                else tmp1 = i;

                if(tmp1>0 && tmp2>0){
                    if( abs(tmp1-tmp2) > max){
                        max = abs(tmp1-tmp2);
                        maxpair[0] = tmp1;
                        maxpair[1] = tmp2;
                    }
                    if(min > abs(tmp1-tmp2) ){
                        min = abs(tmp1-tmp2);
                        minpair[0] = tmp1;
                        minpair[1] = tmp2;
                    }
                }
            }
        }

        if(tmp2==0) printf("There are no adjacent primes.\n");
        else{
            if(minpair[0]>minpair[1]) printf("%d,%d are closest, ",minpair[1],minpair[0]);
            else printf("%d,%d are closest, ",minpair[0],minpair[1]);

            if(maxpair[0]>maxpair[1]) printf("%d,%d are most distant.\n",maxpair[1],maxpair[0]);
            else printf("%d,%d are most distant.\n",maxpair[0],maxpair[1]);
        }
    }

    return 0;
}
