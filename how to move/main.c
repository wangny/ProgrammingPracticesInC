#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    int map[100][100]={0};
    int p[100];
    int t,n;
    int i,j,d,k;

    scanf("%d%d",&t,&n);
    for(i=0;i<n;i++){
        for(j=0;j<n;j++){
            scanf("%d",&map[i][j]);
        }
    }
    i=(n-1)/2;
    j=i;
    //printf("%d %d",t,n);
    k=0;
    while(k<=t){
        p[k]=map[i][j];
        //printf("%d ",p[k]);
        d=map[i][j]%4;
        //printf("%d\n",d);
        k++;
        if( (d==0) && (j+1<n)){
            j++;
        }else if( (d==1) && (i+1<n)){
            i++;
        }else if( (d==2) && (j-1>=0)){
            j--;
        }else if( (d==3) && (i-1>=0)){
            i--;
        }
        //printf("%d\n",k);
    }
    for(k=0;k<t;k++){
        printf("%d ",p[k]);
    }

    printf("%d",p[k]);


    return 0;
}
