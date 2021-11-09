#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    int table[1000][2]={0};
    int d;
    int i=0,j=0;

    scanf("%d",&d);
    while(d!=-1){
        for(i=0;i<1000;i++){
            if( (table[i][0]<5 ) && (table[i][1]<d) ){
                table[i][1]=d;
                table[i][0]++;

                if(i>j)j=i;

                break;
            }
        }
        scanf("%d",&d);
    }

    for(i=0;i<=j;i++){
        printf("%d\n",table[i][1]);
    }

    return 0;
}
