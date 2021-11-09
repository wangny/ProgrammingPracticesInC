#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char input[420][16]={'/0'};
char *p[20][21];

int main(void)
{

    char key[16]={'/0'};
    int N,S,i,j,k;
    int count[20]={0};

    scanf("%d%d",&N,&S);
    for(i=0;i<(N*(S+1));i++){
        scanf("%s",&input[i]);
    }

    k=0;
    for(i=0;i<N;i++){
        for(j=0;j<=S;j++){
            p[i][j]=&input[k];
            k++;
        }
    }

    while(1){
        scanf("%s",&key);
        if(getchar()==EOF){
            break;
        }
        for(i=0;i<N;i++){
            for(j=1;j<=S;j++){
                if(strcmp(key,p[i][j])==0){
                    count[i]++;
                }
            }
        }

    }
    k=0;
    for(i=0;i<N;i++){
        if(count[i]>k){
            k=count[i];
        }
    }
    for(i=0;i<N;i++){
        if(count[i]==k){
            printf("%s\n",p[i][0]);
        }
    }


    return 0;
}
