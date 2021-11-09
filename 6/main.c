#include <stdio.h>

int main(void)
{
    int a[5][5];
    int i,j,x,y,d,n,x9,y9,safe=0,no;

    for(i=0;i<=5;i++){
        for(j=0;j<=5;j++){
            a[i][j]= -1;
        }
    }
    for(i=1;i<4;i++){
        for(j=1;j<4;j++){
            scanf("%d",&a[i][j]);
            if(a[i][j]==1){
                x=i;
                y=j;
            }
            if(a[i][j]==9){
                x9=i;
                y9=i;
            }
        }
    }

    i=x;
    j=y;
    n=2;
    no = 100000;
    while(n<=9 && no){
        if(safe>=10){
            for(x=1;x<4;x++){
                for(y=1;y<4;y++){
                    a[x][y]=0; }
            a[i][j]=1;
            a[x9][y9]=9;
            safe=0;
            x=i;
            y=j;
            n=2;
            printf("(%d,%d)\n",x,y);
            }
        }
        d = rand()%4+1;
        //printf("d=%d ",d);
        //printf("(%d,%d) ",x,y);
        if(d==1 && a[x-1][y]==0){
            x = x-1;
            a[x][y]=n;
            n++;
            safe=0;
        }else if(d==2 && a[x+1][y]==0){
            x = x+1;
            a[x][y]=n;
            n++;
            safe=0;
        }else if(d==3 && a[x][y+1]==0){
            y = y+1;
            a[x][y]=n;
            n++;
            safe=0;
        }else if(d==4 && a[x][y-1]==0){
            y = y-1;
            a[x][y]=n;
            n++;
            safe=0;
        }else{
        safe++;}

        printf("%d\n",n);

        if(n==9){
            if(a[x-1][y]==9 || a[x+1][y]==9 || a[x][y-1]==9 || a[x][y+1]==9){
                printf("YES\n");
                break;
            }
        }

        no--;
        //printf("%d ",no);
    }

    if(!no){
        printf("NO\n");
    }

    return 0;
}
