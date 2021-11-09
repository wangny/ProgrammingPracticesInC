#include <stdio.h>
#include <stdlib.h>


int chain[16][16];
int visit[16];
int ans, curans;
int N;

int been[16];
int cycle(int o, int e){
    int i;
    been[e]=1;
    for(i=1; i<=N; i++){
        if(chain[e][i]==1 && i!=o && been[i]==1) return 1;
        if(chain[e][i]==1 && i!=o) return cycle(e,i);
    }

    return 0;
}




int check(){
    int i,j,l;
    int head=0;
    int count=0;

    for(i=1; i<=N; i++){
        if(chain[i][0]>2) return 0;
        else if(chain[i][0]==1) head++;
        else if(chain[i][0]==0) count++;
    }

    if(head%2) return 0;

    for(i=1; i<=N; i++){
        if(chain[i][0]<1) continue;

        for(j=1; j<=N; j++){
            for(l=0; l<16; l++) been[l]=0;
            been[i] = 1;
            if(chain[i][j]==1) if(cycle(i,j)==1) return 0;
        }
    }

    return head/2 + count;
}


void dfs(int num){
    int j;

    if(num>N) return;
    if(visit[num]) return;

    visit[num]=1;
    for(j=1; j<=N; j++){
        if(chain[num][j]==1){
            chain[j][num] = 0;
            chain[j][0]--;
        }
    }
    chain[num][0]=-1;
    curans++;
    if(check()>0 && check() < curans+1 ) if(curans<ans) ans = curans;

    dfs(num+1);

    visit[num]=0;
    chain[num][0]=0;
    for(j=1; j<=N; j++){
        if(chain[num][j]==1){
            chain[j][num] = 1;
            chain[j][0]++;
            chain[num][0]++;
        }
    }
    curans--;
    if(check()>0 && check() < curans+1 ) if(curans<ans) ans = curans;
    dfs(num+1);

}


int main()
{
    int set=1;
    int x,y;
    int i,j;

    //freopen("818.in","r",stdin);
    //freopen("out.out","w",stdout);


    scanf("%d",&N);

    while(N!=0){

        for(i=0; i<16; i++) for(j=0; j<16; j++) chain[i][j] = 0;

        scanf("%d%d",&x,&y);
        while(x!=-1){
            if(chain[x][y]==0){
                chain[x][y] = 1;
                chain[y][x] = 1;
                chain[x][0]++;
                chain[y][0]++;
            }
            scanf("%d%d",&x,&y);
        }

        for(i=0; i<16; i++) visit[i]=0;
        ans=N; curans=0;
        if(check()==1) ans=0;
        else dfs(1);

        printf("Set %d: Minimum links to open is %d\n",set,ans);
        set++;
        scanf("%d",&N);
    }



    return 0;
}
