#include <stdio.h>
#include <stdlib.h>

int label[4000];
int head[4000]; /*use label*/
int end[4000]; /*use label*/
int no[4000];

int degree[50];
int adj[50];

int color[2000];
int ans[2000];

int dump;

int compare(const void *a, const void *b){
    int c = *(int*)a;
    int d = *(int*)b;

    if( head[c] > head[d] ) return 1;
    else if( head[c] < head[d] ) return -1;
    else return (no[c] - no[d]);
}

int count,k,start,get;

void find(int root, int n){
    int i;

    for(i=0; i<degree[root]; i++){
        if(color[no[ label[adj[root]+i]  ] ] == 1){
            count++;
            ans[n] = no[ label[adj[root]+i]];
            color[no[ label[adj[root]+i]  ] ] = 0;
            find(end[ label[adj[root]+i]  ], n+1);
            if(count>=k/2 && (end[ label[adj[root]+i]  ]==start || get==1 ) ) {get=1;break;}
            color[no[ label[adj[root]+i]  ] ] = 1;
            if(count>=k/2-1) dump++;
            count--;
            if(dump>50) break;
        }
    }
}


int main()
{
    int x,y,z;
    int node;
    int i,j,l;


    freopen("302.in","r",stdin);
    freopen("myout.out","w",stdout);

    head[0] = 0; end[0] = 0; no[0] =0;


    scanf("%d%d",&x,&y);
    while(x!=0 && y!=0){

        k=0; node = 0;

        for(i=0;i<50; i++) degree[i]=0;

        while(x!=0 && y!=0){

            scanf("%d",&z);

            no[z] = z;
            head[z] = x;
            end[z] = y;
            k++;
            degree[x]++;
            degree[y]++;

            if(x>node) node = x;
            if(y>node) node = y;

            scanf("%d%d",&x,&y);
        }

        for(i=1; i<=k; i++){
            no[k+i] = no[i];
            head[k+i] = end[i];
            end[k+i] = head[i];
        }
        k=k*2;

        for(i=0; i<=k; i++) label[i]  = i;

        qsort(label,k+1,sizeof(int),compare);

        for(i=0; i<=50; i++)adj[i] = -1;

        for(i=1; i<=k; i++){
            if( adj[head[label[i] ] ] < 0  ) adj[head[label[i] ] ] = i;
        }

        for(i=1; i<=k; i++){
            printf("%d %d %d\n",head[label[i]],end[label[i]],no[label[i]]);
        }
        for(i=1; i<=node; i++) printf(" %d",adj[i]);
        printf("\n");
        for(i=1; i<=node; i++) printf(" %d",degree[i]);
        printf("\n");

        for(i=0; i<2000; i++) ans[i]=0;

        get = 0;

        for(i=1; i<=k/2; i++){

            count=0;    dump=0;
            for(j=1; j<=k/2; j++) color[j] = 1;


            if(head[i]<end[i]){
                start = head[i];
                find(head[i],0);
                if(get==1){
                    printf("%d",ans[0]);
                    for(l=1; l<k/2; l++) printf(" %d",ans[l]);
                    printf("\n\n");
                    break;
                }
                for(j=1; j<=k/2; j++) color[j] = 1;
                start = end[i];
                find(end[i],0);
                if(get==1){
                    printf("%d",ans[0]);
                    for(l=1; l<k/2; l++) printf(" %d",ans[l]);
                    printf("\n\n");
                    break;
                }
            }else{
                start = end[i];
                find(end[i],0);
                if(get==1){
                    printf("%d",ans[0]);
                    for(l=1; l<k/2; l++) printf(" %d",ans[l]);
                    printf("\n\n");
                    break;
                }
                for(j=1; j<=k/2; j++) color[j] = 1;
                start = head[i];
                find(head[i],0);
                if(get==1){
                    printf("%d",ans[0]);
                    for(l=1; l<k/2; l++) printf(" %d",ans[l]);
                    printf("\n\n");
                    break;
                }
            }
        }

        if(get==0) printf("Round trip does not exist.\n\n");

        scanf("%d%d",&x,&y);
    }

    return 0;
}
