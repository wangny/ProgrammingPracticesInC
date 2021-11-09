#include <stdio.h>

char ch[4096];

int main(void)
{
    int h,w,N,i,j,k;
    char ans[64][64];

    scanf("%d%d%d\n",&N,&h,&w);

    i=0;
    scanf("%1c",&ch[i]);
    while(ch[i] != '\n'){
        if(ch[i] != ' '){
           i++;
        }
        scanf("%1c",&ch[i]);
    }

    k=0;
    for(j=w-1;j>=0;j--){
        for(i=0;i<h;i++,k++){
            ans[i][j] = ch[k];
            //printf("(%d,%d)%c",i,j,ans[i][j]);
        }
    }
    ans[h-1][0] = ' ';

    for(i=0;i<h;i++){
        for(j=0;j<w;j++){
            //printf("%d,%d",i,j);
            printf("%c",ans[i][j]);
        }
        printf("\n");
    }


    return 0;
}
