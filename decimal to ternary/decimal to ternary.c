#include <stdio.h>

int main (void)
{
    int x,y,i;
    int ter[8];
    scanf("%d%d",&x,&y);
    i = y-1;
    while (x>0){
        ter[i] = x%3;
        x = x/3;
        i = i-1;
     }
    while (i >= 0) {
        ter[i] = 0;
        i = i-1;
    }
    i = 0;
    while (i <= y-1){
        printf("%d",ter[i]);
        i++;
    }
    printf("\n");

    return 0;
}
