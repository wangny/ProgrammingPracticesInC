#include <stdio.h>
#include <stdlib.h>

unsigned int prime[46350];
unsigned int table[15500];

int main()
{
    char tmp[12];
    unsigned int N,t;
    int sign;
    int factor[15500];

    int i,j,k,m=0;

    for(i=2; i<46350; i++) prime[i]=1;
    for(i=2; i<46350; i++){
        if(prime[i]==1){
            table[m] = i;
            m++;
            for(j=i+i; j<46350; j = j+i) prime[j]=0;
        }
    }

    scanf("%s",tmp);
    if(tmp[0]=='-'){
        sign = 1;
        N = atoi(&tmp[1]);
    }else{
        sign = 0;
        N = atoi(tmp);
    }

    while(N!=0){

        for(i=0; i<m; i++){
            if(N==0){
                factor[i]=-1;
                break;
            }
            while(N>0 && N%table[i]==0){
                N = N/table[i];
                factor[i]++;
            }
        }

        t=0;
        printf("%s =",tmp);
        if(sign==1){
            printf(" -1");
            t = 1;
        }
        for(i=0; i<m; i++){
            while(factor[i]>0){
                if(t==0) printf(" %d",table[i]);
                else printf(" x %d",table[i]);
                factor[i]--; t=1;
            }
            if(factor[i]==-1){
                factor[i]=0;
                break;
            }
        }
        if(N>1 && t==0) printf(" %d",N);
        else if(N>1 && t==1) printf(" x %d",N);

        printf("\n");

        scanf("%s",tmp);
        if(tmp[0]=='-'){
            sign = 1;
            N = atoi(&tmp[1]);
        }else{
            sign = 0;
            N = atoi(tmp);
        }
    }

    return 0;
}
