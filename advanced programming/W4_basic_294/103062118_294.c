#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main()
{
    int n;
    int L, U;
    int prime_desk[31621];
    int nums[10000];
    int ppows[10000][31];

    int m;
    int i,j,max,max_n,tmp;


    for(i=2; i<31621; i++) prime_desk[i] = 1;
    for(i=2; i<31621; i++){
        if(prime_desk[i]==1){
            for(j = i*i; j<31621; j = j+i) prime_desk[j] = 0;
        }
    }

    scanf("%d",&n);
    while(n>0){

        scanf("%d%d",&L,&U);
        for(i=0; i<=U-L; i++){
            nums[i]=L+i;
            for(j=0; j<31; j++) ppows[i][j] = 0;
        }

        m = (int)(sqrt(U)+0.001);
        for(i=2; i<=m ; i++){
            if(prime_desk[i]==1){
                tmp = (int)(L/i + 0.5) ;
                if(tmp*i < L) tmp++;
                tmp = tmp*i - L;

                for(j = tmp; j <= U-L; j = j+i){
                        ppows[j][0] ++ ;
                    while(nums[j]%i==0){
                        ppows[j][ ppows[j][0] ]++;
                        nums[j] = nums[j]/i;
                    }
                }
            }
        }

        for(i=0; i<=U-L; i++){
            if(nums[i]>1){
                ppows[i][0]++;
                ppows[i][ ppows[i][0] ] = 1;
            }
        }

        max = 0;
        for(i=0; i<=U-L; i++){
            tmp = 1;
            for(j=1; j<=ppows[i][0]; j++) tmp = tmp * (ppows[i][j]+1);
            if(tmp>max){
                max = tmp;
                max_n = i;
            }
        }

        printf("Between %d and %d, %d has a maximum of %d divisors.\n", L, U, L+max_n, max );

        n--;
    }
    return 0;
}
