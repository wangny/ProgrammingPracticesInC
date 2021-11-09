#include <stdio.h>
#include <stdlib.h>

int main()
{
    int n,count=0;
    int i;

    scanf("%d",&n);
    while(n!=0){
        for(i=1;i<=n;i++){
            count=count+ (n-i+1)*(n-i+1);
        }
        printf("%d\n",count);
        count=0;
        scanf("%d",&n);
    }

    return 0;
}
