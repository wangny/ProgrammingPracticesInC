#include <stdio.h>
#include <stdlib.h>
#include <string.h>


char names[25][26];
int matrix[25][25];


int main()
{
    int N,M;
    int setnum=1;
    int flag[25];
    int i,j,k,l,m;
    char clear[26]={'\0'};
    char t1[26]={'\0'},t2[26]={'\0'};

    scanf("%d%d",&N,&M);
    while(N!=0 || M!=0){

        for(i=0; i<25; i++) for(j=0;j<25; j++) matrix[i][j]=10000;
        for(i=0; i<25; i++) strcmp(names[i],clear);

        k=0;
        for(i=0; i<M; i++){
            scanf("%s %s",t1,t2);
            l=-1; m=-1;
            for(j=0; j<k; j++){
                if(strcmp(t1,names[j])==0) l = j;
                if(strcmp(t2,names[j])==0) m = j;
            }
            if(l==-1){
                strcpy(names[k],t1);
                l=k;
                k++;
            }
            if(m==-1){
                strcpy(names[k],t2);
                m=k;
                k++;
            }
            matrix[l][m] = 1;
        }

        for(i=0; i<N; i++) matrix[i][i]=0;

        for(k=0; k<N; k++){
            for(i=0; i<N; i++){
                for(j=0; j<N; j++) if(matrix[i][j] > matrix[i][k] + matrix[k][j] ) matrix[i][j] = matrix[i][k] + matrix[k][j];
            }
        }

        for(i=0; i<N; i++) for(j=0; j<N; j++) {
            if(matrix[i][j]!=10000) matrix[i][j] = 1;
            else matrix[i][j] = 0;
        }

        if(setnum>1) printf("\n");
        printf("Calling circles for data set %d:\n",setnum++);

        for(i=0; i<N; i++) flag[i]=1;

        for(i=0; i<N; i++){
            if(flag[i]==1){
                flag[i]=0;
                printf("%s",names[i]);
                for(j=i+1;j<N;j++){
                    if( matrix[i][j]==1 && matrix[j][i]==1 ){
                        flag[j]=0;
                        printf(", %s",names[j]);
                    }
                }
                printf("\n");
            }
        }


        cases++;
        scanf("%d%d",&N,&M);
    }


    return 0;
}
