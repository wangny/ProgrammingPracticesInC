#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    int a1[100]={0},a2[100]={0},b1[100]={0},b2[100]={0};
    int i=0,j,d;
    int t=0;

    while(1){
        scanf("%d:%d",&a1[i],&a2[i]);
        if(a1[i]==0)
            break;
        i++;
    }
    i=0;
    while(1){
        scanf("%d:%d",&b1[i],&b2[i]);
        if(b1[i]==0){
            d=i;
            break;
        }
        i++;
    }
    for(i=0;a1[i]!=0;i++){
        for(j=0;j<=d;j++){
            if( a1[i]==b1[j] ){
                t=t+a2[i]*b2[j];
            }
        }
    }
    printf("%d\n",t);


    return 0;
}
