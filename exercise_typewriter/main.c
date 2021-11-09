#include <stdio.h>
#include <ctype.h>

int main(void)
{
    int x[26]={0};
    char ch;
    int i,j,k;

    //ch = getchar();

    while( (ch=getchar()) != EOF){
        if(ch >= 97){
            i = ch - 97;
        }else if(ch>=65){
            i = ch - 65;
        }
        x[i] = x[i] + 1;
        //ch = getchar();
    }

    i = 1;
    j = 0;
    k = 0;

    while(i<26){
        if( x[i] > x[j] ){
            j = i;
        }
        i++;
    }

    i = 0;

    while(x[k]==0){
        k++;
    }

    while(i<26){
        if ( 0 < x[i] && x[i] < x[k] ){
            k = i;
            }
        i++;
    }

    printf("max: %c,%d\n",j+'a',x[j]);
    printf("min: %c,%d\n",k+'a',x[k]);

    return 0;
}
