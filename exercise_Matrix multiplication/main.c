#include <stdio.h>

int main(void)
{
    int a[10][10] = {0};
    int b[10][10] = {0};
    int c[10][10] = {0};
    int m,n,p,i,j,k;

    scanf("%d%d",&m,&n);
    i = 0;

    while(i<m){
        j = 0;
        while(j<n){
            scanf("%d",&a[i][j]);
            j++;
        }
        i++;
    }

    scanf("%d%d",&n,&p);
    i = 0;

    while(i<n){
        j = 0;
        while(j<p){
            scanf("%d",&b[i][j]);
            j++;
        }
        i++;
    }

    i=0;
    while(i<m){
        j=0;
        while (j<p){
            k=0;
            while(k<n){
                c[i][j]= c[i][j] + (a[i][k]*b[k][j]);
                k++;
            }
            printf("%d ",c[i][j]);
            j++;
        }
        printf("\n");
        i++;
    }



    return 0;
}
