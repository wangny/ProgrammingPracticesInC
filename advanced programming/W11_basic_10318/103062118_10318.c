#include <stdio.h>
#include <stdlib.h>

int panel[5][5];
int pattern[3][3];
int ans[100][26], k, l;
int get = 0;
int R,W;

void find(int r, int w){
    int i,j;


    get = 1;
    for(i=0; i<R; i++) for(j=0; j<W; j++) if(panel[i][j]==0) get = 0;
    if(get==1){
        for(i=0; i<=k; i++) ans[l+1][i] = ans[l][i];
        l++;
        return;
    }

    if(r>=R || w>=W){
        return;
    }

    for(i=0; i<r-1; i++){
        for(j=0; j<W; j++) if(panel[i][j]==0) return;
    }


    for(i=0; i<3; i++){
        for(j=0; j<3; j++) if(pattern[i][j]==1){
            if( (r-1+i)>=0 && (w-1+j)>=0 && (r-1+i)<5 && (w-1+j)<5 ){
                if( panel[r-1+i][w-1+j]==1 )  panel[r-1+i][w-1+j]= 0;
                else  if( panel[r-1+i][w-1+j]==0 )  panel[r-1+i][w-1+j]= 1;
            }
        }
    }
    k++;
    ans[l][k] = r*W + w +1;
    ans[l][0]++;


    if(w==W-1) find(r+1,0);
    else find(r,w+1);


    for(i=0; i<3; i++){
        for(j=0; j<3; j++) if(pattern[i][j]==1){
            if( (r-1+i)>=0 && (w-1+j)>=0 && (r-1+i)<5 && (w-1+j)<5 ){
                if( panel[r-1+i][w-1+j]==1 )  panel[r-1+i][w-1+j]= 0;
                else  if( panel[r-1+i][w-1+j]==0 )  panel[r-1+i][w-1+j]= 1;
            }
        }
    }
    k--;
    ans[l][0]--;

    if(w==W-1) find(r+1,0);
    else find(r,w+1);

}

int main()
{
    int casenum = 1;
    char c;

    int i,j,m;



    scanf("%d%d\n",&R,&W);

    while(R!=0 || W!=0){

        for(i=0; i<3; i++){
            for(j=0; j<3; j++){
               scanf("%c",&c);
               if(c=='\n') scanf("%c",&c);

               if(c == '*') pattern[i][j] = 1;
               else if (c == '.') pattern[i][j] = 0;
            }
        }

        for(i=0; i<100; i++) for(j=0; j<26; j++) ans[i][j] = 0;
        for(i=0; i<5; i++) for(j=0; j<5; j++) panel[i][j] = 0;

        k=0; l=0;
        if(R!=0&&W!=0)find(0,0);

        printf("Case #%d\n",casenum);
        if(l==0) printf("Impossible.");
        else{
            j=25; m=0;
            for(i=0; i<l; i++) if(ans[i][0]<j){
                m = i;
                j = ans[i][0];
            }
            printf("%d",ans[m][1]);
            for(i=2; i<=ans[m][0]; i++) printf(" %d",ans[m][i]);
        }
        printf("\n");

        scanf("%d%d",&R,&W);
        casenum++;
    }

    return 0;
}
