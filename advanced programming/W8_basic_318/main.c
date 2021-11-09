#include <stdio.h>
#include <stdlib.h>

int matrix[501][501];
int Q[501], d[501];
int n;

int find_min_d(){

    int min_d = 10000000, node = 1;
    int i;

    for (i=2; i<=n; i++){
        if (d[i]< min_d && Q[i]==1 && d[i]!=-1){
            min_d = d[i];
            node = i;
        }
    }
    return node;
}


void relax(int u, int v){
    if( (d[v] > (d[u]+matrix[u][v])) || d[v]==-1 ){
        d[v] = d[u]+matrix[u][v];
    }
}

void Dijk(){
    int i,j;
    int min,t,node;

    for(i=1; i<=n; i++){

        node = find_min_d();
        Q[node]=0;
        for(j=1; j<=n; j++){
            if(matrix[node][j]!=-1) relax(node,j);
        }
    }
}


int main()
{
    int m;
    int x,y,w;
    double PATH_MAX, tmp, node_max,large, small;
    int node;
    int i,j;
    int count=1;

    scanf("%d%d",&n,&m);

    while(n!=0){

        for(i=1; i<501; i++){
            Q[i] = 1;
            d[i] = -1;
            for(j=1; j<501; j++){
                matrix[i][j] = -1;
            }
        }

        for(i=0; i<m; i++){
            scanf("%d%d%d",&x,&y,&w);
            matrix[x][y] = w;
            matrix[y][x] = w;
        }

        d[1] = 0;

        Dijk();

        PATH_MAX = 0;
        for(i=1; i<=n; i++){
            for(j=1; j<=n; j++){
                if(matrix[i][j]!=-1){
                    if(d[i]>=d[j]){
                        large = d[i];
                        small = d[j];
                    }else{
                        large = d[j];
                        small = d[i];
                    }
                    tmp = (matrix[i][j]-(large-small))/2 + large;
                    if (tmp > PATH_MAX){
                        PATH_MAX = tmp;
                        if (i< j) x=i, y=j;
                        else x=j, y=i;
                    }
                }
            }
        }

        node_max=0;
        for(i=1; i<=n; i++) if(d[i]>node_max){
            node_max = d[i];
            node = i;
        }

        printf("System #%d\n", count++);
        if (node_max>=PATH_MAX) printf("The last domino falls after %.1f seconds, at key domino %d.\n\n", node_max, node);
        else printf("The last domino falls after %.1f seconds, between key dominoes %d and %d.\n\n", PATH_MAX, x,y);


        scanf("%d%d",&n,&m);
    }

}
