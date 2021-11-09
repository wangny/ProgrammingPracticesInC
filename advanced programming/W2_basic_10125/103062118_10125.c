#include <stdio.h>
#include <stdlib.h>

int X[1000001];
int instruct[1000001];
int k;

int compareset(const void*a, const void* b)
{
    int c = *(int*)a;
    int d = *(int*)b;

    if(c>d) return 1;
    else if (c==d) return 0;
    else return -1;
}

int comparex(const void*a, const void* b)
{
    int c = *(int*)a;
    int d = *(int*)b;

    if( X[c] > X[d] ) return 1;
    else if (X[c]==X[d]) return 0;
    else return -1;
}


int binary_search1(int y)
{
    int U = k-1;
    int L = 0;

    while(U>L+1){
        if ( X[ instruct[(U+L)/2] ] > y ) U = (U+L)/2;
        else L = (U+L)/2;
    }

    return U;
}

int binary_search2(int y)
{
    int U = k-1;
    int L = 0;

    while(U>L+1){
        if ( X[ instruct[(U+L)/2] ] >= y ) U = (U+L)/2;
        else L = (U+L)/2;
    }

    return L;
}


int main()
{
    int n;
    int set[1001];
    int a[1000001];
    int b[1000001];
    int Y;
	int	left, right;
    int i,j,l;
    int solve;

    /*freopen("10125.in","r",stdin);*/

    scanf("%d",&n);

    while(n>0){
        solve = 0;

        for(i=0; i<n; i++) scanf("%d",&set[i]);

        qsort(set,n,sizeof(int),compareset);

        k = 0;
        for(i=0;i<n-1;i++){
            for(j=i+1; j<n; j++){
              X[k] = set[i]+set[j];
              a[k] = set[i];
              b[k] = set[j];
              instruct[k] = k;
              k++;
            }
        }

        qsort(instruct,k,sizeof(int),comparex);

        for(i=n-1; i>=0; i--){
            for(j=0; j<n; j++){
                if(i==j) continue;

                Y = set[i] - set[j];

                right = binary_search1(Y);
                left = binary_search2(Y);

                for(l=left+1; l<right; l++){

                    if(set[i]!=a[instruct[l]] && set[i]!=b[instruct[l] ] && set[j]!=a[instruct[l]] && set[j]!=b[instruct[l]]){
                        printf("%d\n",set[i]);
                        solve = 1;
                        break;
                    }
                }
                if(solve) break;
            }
            if(solve) break;
        }
        if(solve==0) printf("no solution\n");

        scanf("%d",&n);
    }

    return 0;
}
