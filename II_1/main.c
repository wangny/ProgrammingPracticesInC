#include <stdio.h>
#include <stdlib.h>

int cmp (char *a, char *b);

int main(void)
{
    char input[1000]={'/0'};
    char str[100][1000]={'/0'};
    int i,n,op,ed,j;

    scanf("%s",input);
    scanf("%d",&n);

    for(i=0;i<n;i++){
        scanf("%d%d",&op,&ed);
        for(j=op;j<=ed;j++){
            str[i][j-op]=input[j];
        }
    }

    qsort(str,n,sizeof(char)*1000,cmp);

    for(i=0;i<n;i++){
        printf("%s\n",str[i]);
    }

    return 0;
}

int cmp (char *a, char *b)
{
    return strcmp(a,b);

}
