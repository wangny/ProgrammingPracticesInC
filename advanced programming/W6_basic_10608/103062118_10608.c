#include <stdio.h>
#include <stdlib.h>


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

    for(i=0; i<degree[root]; i++){
        if(color[node[ label[adj[root]+i]  ] ] == 1){
            find(node[ label[adj[root]+i]  ]);
        }
    }
    color[root] = 0;
}


int main()
{
    int S,N,M;
    int i,j,k;
    int a,b;
    int max;



    scanf("%d",&S);
    while(S>0){
        scanf("%d%d",&N,&M);
        for(i=1; i<=N; i++){
            degree[i]=0;
            adj[i] = -1;
        }
        for(i=0; i<1000000; i++){
            node[i] = -1;
            head[i] = -1;
            label[i]=i;
        }


        for(i=0; i<M*2; i=i+2){
            scanf("%d%d",&head[i],&node[i]);
            degree[ head[i] ]++;
            head[i+1] = node[i];
            node[i+1] = head[i];
            degree[ node[i] ]++;
        }

        qsort(label,M*2,sizeof(int),compare);

        for(i=0; i<M*2; i++){

            if(adj[head[label[i]]] <0 ) adj[head[label[i]]]=i;
        }



        max = 0;

        for(i=1; i<=N; i++){
            count=0;
            for(k=1; k<=N; k++) color[k] = 1;
            find(i);
            if(count>max) max = count;

        }

        printf("%d\n",max);
        S--;

    }
    return 0;
}
