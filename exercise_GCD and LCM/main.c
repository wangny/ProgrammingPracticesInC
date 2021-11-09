#include <stdio.h>

int main(void)
{
    int x,y,GCD,LCM,i,j,k;
    scanf("%d%d",&x,&y);
    i=1;
    while(i<=x || i<=y){
        if(x%i==0){
            if(y%i==0){
                GCD=i;
            }
        }
        i++;
    }

    j = x/GCD;
    k = y/GCD;
    LCM = j*k*GCD;
    printf("GCD: %d\n",GCD);
    printf("LCM: %d\n",LCM);

    return 0;
}
