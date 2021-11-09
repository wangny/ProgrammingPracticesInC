#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
    int x[9]={0};
    char o[101]={'/0'};
    int i,j,l,t=0,no=0;

    scanf("%s",&o);
    l=strlen(o);

    for(i=0;i<l;i++){
        x[o[i]-'0'-1]++;
    }

    for(i=0;i<9;i++){
        //printf("%d",x[i]);
        if(x[i]%2){
            no++;
            t = i;
        }
    }

    if(no>=2){
        printf("NO\n%s\n",o);
    }else{
        j=0;
        for(i=0;i<(l/2);i++){
            while(x[j]<2){
                j++;
            }
            o[i]=j+'0'+1;
            o[l-1-i]=j+'0'+1;
            x[j]=x[j]-2;
        }
        if(t){
            l=l-1;
            o[l/2]=t+'0'+1;
        }

        printf("YES\n%s\n",o);
    }
    return 0;
}
