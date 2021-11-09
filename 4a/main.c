#include <stdio.h>

int main(void)
{
    long long int n,k,M,i,q,a,b,c;
    scanf("%lld",&M);
    M = M-1;

    for(n = 0; n <= M; n++){
            for(k = 0; k <= n; k++){
                for (c = 0, q = 1; c <= k-1; c++){
                    q = q*(n-c);
                }
                for(a = 1,b = 1; a <= k; a++){
                    b = b*a;
                }
                i = q / b;
                printf("%10lld",i);
             }
             printf("\n");
    }

    return 0;
}
