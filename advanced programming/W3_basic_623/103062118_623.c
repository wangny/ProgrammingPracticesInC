#include <stdio.h>
#include <stdlib.h>

int max_lenght = 500;
int lenght = 1000000;

int big[500];

void mul(int a, int b[max_lenght] )
{
    int ans[max_lenght];
    int i,tmp;
    int carry = 0;

    for(i=0; i<max_lenght; i++){
        ans[i] = 0;

        if(b[i]>0 || carry>0){
            tmp = a * b[i] + carry;
            ans[i] = tmp%lenght;
            carry = tmp/lenght;
        }
    }

    for(i=0; i<max_lenght; i++){
        big[i] = ans[i];
    }

}

int main()
{
    int i,j,n;

    while( scanf("%d",&n)!=EOF ) {

        printf("%d!\n",n);
        big[0] = 1;
        for(i=1;i<max_lenght; i++) big[i] = 0;

        for(j=2; j<=n; j++){
            mul(j,big);
        }

        for(i=max_lenght-1; i>0; i--){
            if(big[i]>0) break;
        }
        printf("%d",big[i]);
        for(i = i-1; i>=0; i-- ){
            if(big[i]==0) printf("000000");
            else if(big[i]<10) printf("00000%d",big[i]);
            else if(big[i]<100) printf("0000%d",big[i]);
            else if(big[i]<1000) printf("000%d",big[i]);
            else if(big[i]<10000) printf("00%d",big[i]);
            else if(big[i]<100000) printf("0%d",big[i]);
            else printf("%d",big[i]);
        }
        printf("\n");
    }

    return 0;
}
