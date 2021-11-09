#include <stdio.h>

int main (void)
{
    int x[9] = {'\0'};
    int i,j;
    scanf("%d%d%d%d%d%d%d%d%d",&x[0],&x[1],&x[2],&x[3],&x[4],&x[5],&x[6],&x[7],&x[8]);
    j = x[0];
    i = x[0]- 1;
    while (i != 0){
        j = j + x[i];
        i = x[i]- 1;
    }
    printf("%d\n",j);
    return 0;
}
