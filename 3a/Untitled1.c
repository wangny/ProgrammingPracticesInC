#include <stdio.h>

int main (void)
{
    unsigned long long x;
    int i,j;
    int bit[64];
    scanf("%llu", &x);
    i = 63;
    if (x==0) {
        printf("%d",0);
    }
    while (x>0){
        bit[i] = x%2;
        x = x/2;
        i = i-1;
    }
    j = i+1;
    while (j<=63){
        printf("%d",bit[j]);
        j++;
    }
    printf("\n");

    return 0;
}

