#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int ans[5][5] = { {1,1,1,1,1}, {0,1,1,1,1}, {0,0,-1,1,1}, {0,0,0,0,1}, {0,0,0,0,0} };
int cur[5][5] = { {1,1,1,1,1}, {0,1,1,1,1}, {0,0,-1,1,1}, {0,0,0,0,1}, {0,0,0,0,0} };
int save[50000][5][5];
int step[50000];

int keep[1666][25];
int keepstep[1666];

int k;
int isfind=12;
int answer;

int compare(int a[5][5], int b[5][5]){

    int i,j;
    for(i=0; i<5; i++) for(j=0; j<5; j++) if(a[i][j]!=b[i][j]) return 0;

    return 1;
}


void findans(int x, int y, int layer){
    int i,j,l,m,n;

    if(layer>6) return;

    for(l=0; l<k; l++) if(compare(cur,keep[l])==1){
        if(layer<keepstep[l]) keepstep[l] = layer;
        else return;
    }
    if(l>=k){
        for(m=0; m<5; m++) for(n=0; n<5; n++) keep[k][m*5+n] = cur[m][n];
        keepstep[k] = layer;
        k++;
    }

    for(i=0; i<5; i++){
        for(j=0; j<5; j++) if(i!=x && j!=y && (abs(i-x)+abs(j-y)==3) ){
            cur[x][y] = cur[i][j];
            cur[i][j] = -1;

            findans(i,j,layer+1);

            cur[i][j] = cur[x][y];
            cur[x][y] = -1;
        }
    }
}


void find(int oldk, int c[5][5]){
    int i,j,l,m,n;
    int x,y;
    int layer = step[oldk];

    int esti=0;
    for(i=0; i<5; i++)for(j=0; j<5; j++)if(c[i][j]!=ans[i][j]){
        esti++;
    }
    if(esti+layer>10) return;

    for(j=0; j<1666; j++) if(compare(c,keep[j])==1){
        if(layer+keepstep[j]<isfind) isfind = layer+keepstep[j];
        return;
    }

    if(layer>=6) return;



    for(i=0; i<5; i++)for(j=0; j<5; j++)if(c[i][j]==-1){
        x = i; y = j;
        break;
    }


    for(i=0; i<5; i++){
        for(j=0; j<5; j++) if( i!=x && j!=y &&(abs(i-x)+abs(j-y)==3) ){
            c[x][y] = c[i][j];
            c[i][j] = -1;

            for(l=0; l<k; l++) if(compare(c,save[l])==1) continue;

            if(l>=k){
                for(m=0; m<5; m++) for(n=0; n<5; n++) save[k][m][n] = c[m][n];
                step[k] = layer+1;
                k++;
            }

            c[i][j] = c[x][y];
            c[x][y] = -1;
        }
    }
}


int main()
{

    int N;
    int i,j,l;
    char c;
    int answer, oldk;

    k=0;
    findans(2,2,0);

    //freopen("10422.in","r",stdin);
    //freopen("myout.out","w",stdout);


    scanf("%d",&N);

    while(N>0){

        for(i=0; i<5; i++){
            for(j=0; j<5; j++){
                scanf("%c",&c);
                if(c=='\n') scanf("%c",&c);

                if(c==' '){
                    save[0][i][j] = -1;


                }else save[0][i][j] = c-'0';
            }
        }

        step[0] = 0;
        k=1; oldk=0;isfind=12;
        while(oldk<k){
            if(isfind<11) break;
            find(oldk,save[oldk]);
            oldk++;
        }


        if(isfind>=11) printf("Unsolvable in less than 11 move(s).\n");
        else printf("Solvable in %d move(s).\n",isfind);

        N--;

    }

    return 0;
}
