#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int degree[30000];
int adj[30000];
int node[1000000];  /*use label*/
int head[1000000];  /*use label*/
int label[1000000];
int color[1000000]; /*1 : unvisited, 0 : visited, -1 : visiting*/

int count;

int compare(const void*a, const void*b){
    int c = *(int*)a;
    int d = *(int*)b;

    if(head[c]<head[d]) return -1;
    else if(head[c]>head[d]) return 1;
    else return node[c]-node[d];

}

void find(int root){
    int i ,t;

    color[root] = -1;
    count = count+1;
    //printf("=>%d ",root);
    for(i=0; i<degree[root]; i++){
        if(color[node[ label[adj[root]+i]  ] ] == 1){
            find(node[ label[adj[root]+i]  ]);
        }
    }
    color[root] = 0;
}


int main()
{
    int S;
    char N[201]={'\0'};
    char tmp[4]={'\0'};
    int i,j,k,t;
    int critical;
    char nouse;

    //freopen("315.in","r",stdin);


    scanf("%d%c",&S,&nouse);
    while(S>0){

        for(i=1; i<=S; i++){
            degree[i]=0;
            adj[i] = -1;
        }
        for(i=0; i<1000000; i++){
            node[i] = -1;
            head[i] = -1;
            label[i]=i;
        }

        gets(N);
        k=0;
        while( N[0]>'0' ){
            j=0;
            for(i=0; i<4; i++) tmp[i]='\0';
            while(N[j]!=' '){
                tmp[j] = N[j];
                j++;
            }
            t = atoi(tmp);

            while(j<strlen(N) ){
                i=0;
                j++;
                for(i=0; i<4; i++) tmp[i]='\0';

                while(j<strlen(N) && N[j]!=' '){
                    tmp[i] = N[j];
                    j++; i++;
               }
               //printf("%d\n",atoi(tmp) );

               head[k] = t;
               node[k] = atoi(tmp);
               k++;
               degree[t]++;
               head[k] =atoi(tmp);
               node[k] = t;
               k++;
               degree[atoi(tmp)]++;

            }
            gets(N);
        }

        qsort(label,k,sizeof(int),compare);

       //for(i=0; i<k; i++) printf("%d %d\n",head[label[i]],node[label[i]]);

        for(i=0; i<k; i++){
            if(adj[head[label[i]]] <0 ) adj[head[label[i]]]=i;
        }

        critical = 0;

        for(i=1; i<=S; i++){
            count=0;
            for(j=1; j<=S; j++) color[j] = 1;
            color[i] = 0;

            if(i==S) find(1);
            else find(i+1);
            //printf("\n");
            if(count<S-1)  critical++;
        }

        printf("%d\n",critical);

        scanf("%d%c",&S,&nouse);
    }
    return 0;
}
