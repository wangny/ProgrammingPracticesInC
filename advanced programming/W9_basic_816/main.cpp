#include <stdio.h>
#include <stdlib.h>

enum dir{S,W,E,N};
enum way{F,R,L};

int maze[10][10][4][4];
int d[10][10];
int Q[10][10][4];

int goalx, goaly;
int get=0;


void ini(){
    int i,j,k,l;
    for(i=0; i<10; i++) for(j=0; j<10; j++) for(k=0; k<4; k++) for(l=0; l<4; l++) maze[i][j][k][l]=0;
    for(i=0; i<10; i++) for(j=0; j<10; j++) d[i][j] = -1;
}


void relax(int x, int y, int o){
    if(d[x][y]+1 > o || d[x][y]==-1) d[x][y] = o+1;

}


void find(int x, int y, int dr){
    int i;

    for(i=0; i<3; i++){
        if(maze[x][y][dr][i]==1){
            if(i==S){
                relax(x,y-1,d[x][y]);
                find(x,y-1,S);
            }else if(i==W){
                relax(x,y,d[x][y]);
                find(x,y-1,S);
            }else if(i==E){
                relax(x,y-1,d[x][y]);
                find(x,y-1,S);
            }else if(i==N){
                relax(x,y-1,d[x][y]);
                find(x,y-1,S);
            }


        }

    }

}

/**node duplication
 s(i, j, k): 目前由入口k 進入node (i, j)， k 屬於 { U, D, L, R }
 一共有9*9*4 nodes
 two-level relaxation: (local + global)*
 不必真的造圖, edges 在程式中用"算的"或"查表"
 作BFS
 依出發點(a, b) 與出發方向，找到一步可以到達的入口s(c, d, e)
 由s(c, d, e) 開始作BFS ，求s(c, d, e) 與所有s(x, y, k) 的最短距離**/



int main()
{
    char name[21]={'\0'};
    int startx,starty,startd;
    int x,y;
    char t,c;

    scanf("%s",name);
    while(name!="END"){

        scanf("%d %d %c %d %d\n",&startx, &starty, &t, &goalx, &goaly );
        if(t=='S') startd = S;
        else if(t=='W') startd = W;
        else if(t=='E') startd = E;
        else if(t=='N') startd = N;

        ini();

        scanf("%d ",&x);
        while(x!=0){
            scanf("%d ",&y);
            scanf("%c",&c);
            while(c!='*'){
                scanf("%c",&t);
                while(t!=' '){
                    if(c=='S'){
                        if(t=='U') maze[x][y][S][0] = 1;
                        else if(t=='L') maze[x][y][S][1] = 1;
                        else if(t=='R') maze[x][y][S][2] = 1;
                        else if(t=='D') maze[x][y][S][3] = 1;
                    }else if(c=='W'){
                        if(t=='U') maze[x][y][W][0] = 1;
                        else if(t=='L') maze[x][y][W][1] = 1;
                        else if(t=='R') maze[x][y][W][2] = 1;
                        else if(t=='D') maze[x][y][W][3] = 1;
                    }else if(c=='E'){
                        if(t=='U') maze[x][y][E][0] = 1;
                        else if(t=='L') maze[x][y][E][1] = 1;
                        else if(t=='R') maze[x][y][E][2] = 1;
                        else if(t=='D') maze[x][y][E][3] = 1;
                    }else if(c=='N'){
                        if(t=='U') maze[x][y][N][0] = 1;
                        else if(t=='L') maze[x][y][N][1] = 1;
                        else if(t=='R') maze[x][y][N][2] = 1;
                        else if(t=='D') maze[x][y][N][3] = 1;
                    }
                    scanf("%c",&t);
                }
                scanf("%c",&c);
            }
            scanf("%d",&x);
        }



        printf("%s\n",name);

        scanf("%s",name);
    }


    return 0;
}
