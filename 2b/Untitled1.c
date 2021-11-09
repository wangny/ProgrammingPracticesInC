#include <stdio.h>

int main(void)
{
    int i,j,k;
    char alphe[11] = {'J','A','B','C','D','E','F','G','H','I','\0'};
    scanf("%1d",&i);
    scanf("%1d",&j);
    scanf("%1d",&k);
    printf("%c%c%c", alphe[i], alphe[j], alphe[k]);


    return 0;
}
