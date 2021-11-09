#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char s[9]={'\0'};
int a[8]={0};
int l;

void move(int row);
int main(void)
{
    int i;

    scanf("%s",s);
    l=strlen(s);

    for(i=0;i<l;i++){
        move(i);
    }

    return 0;
}

void move(int row)
{
    int i,temp=2;
    //printf("'%d'   ",row);

    if(row>=l){
        return;
    }
    for(i=l-1;i>row;i--){
        if(a[i]==a[row]){
            row++;
            move(row);
            row--;
        }
    }
    for(i=l-1;i>=row;i--){
        //printf("%d ",temp);
        if(temp==a[row]){
            temp--;
        }else if(a[i]==temp){
            temp=temp-1;
        }
    }
    if( temp<1 ){
        row++;
        move(row);
        row--;
        return;
    }
    printf("%c:%d->%d\n",s[row],a[row],temp);
    a[row]=temp;
    return;
}
