#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void change(int n);
void recursion(int row);

char s[17]={'\0'};
char a,b;
int c,l;
int i=0;

int main(void)
{
    scanf("%c%c",&a,&b);
    scanf("%s",s);
    scanf("%d",&c);

    l=strlen(s);
    c=l-c;

    recursion(0);

    return 0;
}

void recursion(int row)
{
    int j;

    //printf("%d",i);
    if(row==l){
        if(i==c){
        printf("%s\n",s);
        }
        i++;
        return;
    }else{
        for(j=0;j<2;j++){
            if(j){
                change(row);
                i++;
            }
            row++;
            recursion(row);
            change(row);
            i--;
            row--;
        }
    }
}

void change(int n)
{
    if(s[n]==a){
        s[n]=b;
    }else if(s[n]==b){
        s[n]=a;
    }
}
