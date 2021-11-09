#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int compare3 (const void *a, const void *b)
{
    char * *pa;
    char * *pb;
    pa = (char **)a;
    pb = (char **)b;
    return strcmp(*pa,*pb);
}

int main(void)
{
    char s[10][10];
    char *p [10];
    int n;
    int i,j;

    scanf("%d\n",&n);
    for(i=0;i<n;i++){
        p[i] = &s[i];
        scanf("%s",&s[i]);
    }
    qsort(p,n,sizeof(char*),compare3);
    for(i=0;i<n;i++){
        printf("%s",p[i]);
        printf("\n");
    }


    return 0;
}
