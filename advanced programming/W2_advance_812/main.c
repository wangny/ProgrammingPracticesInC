#include <stdio.h>
#include <stdlib.h>

int compare(const void* a, const void *b)
{
    int c = *(int*)a;
    int d = *(int*)b;
    //if(c == 0) return 1;
    //else if(d==0) return -1;
    return c-d;
}


int main()
{
    int n;
    int purls[50][21];
    int way[50][11];
    int array[50][10];
    int profit;

    int i,j,k,tmp,l;
    int cur,max;
    int casenum = 1;
    int L;
    int ans[100];


    freopen("812.in","r",stdin);
    freopen("myout.out","w",stdout);

    scanf("%d",&n);
    while(n>0){

        profit = 0;

        for(i=0;i<n; i++){
            scanf("%d",&purls[i][0]);
            for(j=1; j<=purls[i][0]; j++) scanf("%d",&purls[i][j]);
            for(j=0; j<=20; j++) array[i][j] = 0;
        }

        for(i=0;i<n; i++){
            max = -1;
            cur = 0;
            for(j=1; j<=purls[i][0]; j++){
                cur = cur + 10 - purls[i][j];
                if(cur > max) max = cur;
            }
            cur = 0;
            way[i][0] = 0;

            if(max<0){
                for(j=1; j<10; j++) way[i][j] = 0;
                way[i][0] = 0;
            }else{
                for(j=1; j<=purls[i][0]; j++){
                    if(cur == max) {
                        way[i][0] ++ ;
                        way[i][ way[i][0] ]= j-1;
                    }
                    cur = cur + 10 - purls[i][j];
                }
            }
            qsort(&way[i][1],way[i][0],sizeof(int), compare );
            if(max>0) profit = profit + max;
        }

        printf("Workyards %d\n",casenum);
        printf("Maximum profit is %d.\n",profit);
        printf("Number of pruls to buy:");

        if(n==1){
            for(i=1; i<=way[0][0]; i++) printf(" %d",way[0][i]);
            printf("\n");

        }else{

            for(i=0; i<n; i++){
                if(way[i][0]>10) way[i][0]=10;

                for(j=1; j<= way[i][0]; j++ ){
                    array[i][j-1] = way[i][j] - way[i][0];
                }
            }

            L=0;
            for(i=0; i<n; i++) L = L + way[i][1];
            //printf(" %d",L);

            for(i=0;i<way[i][0];i++) ans[i]=array[0][i];
            k=i-1;
            for(;i<100;i++) ans[i]=1000;

            for(i=1; i<=n; i++){
                k=10;
                for(j=1;j<way[i][0];j++){
                    if(array[i][j] > ans[9]) break;
                    for(l=0; l<10; l++){
                        ans[k] = array[i] + ans[l];
                        k++;
                    }
                }
                qsort(ans,100,sizeof(int),compare);
            }

            for(i=0; i<10; i++) printf(" %d",ans[i]);

            printf("\n\n");
        }
        casenum++;
        scanf("%d",&n);
    }
    return 0;
}
