#include <stdio.h>
#include <math.h>

int f[100],g[100]={0},temp[100]={0};
int m,n,p;
void cal(int i,int raw,int tmp);

int main(void)
{
    int i,j;

    scanf("%d",&m);
    for(i=m;i>=0;i--){
        scanf("%d",&f[i]);
    }
    scanf("%d",&n);

    cal(0,1,1);



    for(i=m*n;i>=0;i--){
        printf("%5d",g[i]);
    }
    printf("\n");

    return 0;
}

void cal(int i,int raw,int tmp){
    int j,tmp2;
    if (raw>n){
        g[i] = g[i] + tmp;
        tmp = 0;
        //printf("%d : %d\n",i,g[i]);
        return;
    }else{
        for(j=0;j<=m;j++){
            i = i+j;
            tmp2 = tmp*f[j];
            raw++;
            cal(i,raw,tmp2);
            raw--;
            i = i-j;
            //printf("%d,%d\n",f[raw],tmp);
        }
    }
}
