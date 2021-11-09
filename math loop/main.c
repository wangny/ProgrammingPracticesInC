#include <stdio.h>

void sortA(void);
void sortB(void);
int A[6]={0}, B[6]={0};
int x,i,j,td,temp,a=0,b=0;

int main()
{
    char s[10]={'\0'};
    int d[100]={0};
    int k,DONE=1;

    i=0;
    while( (s[i]=getchar()) != EOF ){
        i++;
    }
    i--;
    x = i;
    for(i=0;i<x;i++){
        A[i] = s[i]-'0';
        //printf("%d",A[i]);
        B[i] = s[i]-'0';
    }

    k=0;
    while(DONE){
        sortA();
        sortB();
        td = a - b;
        for(i=0;i<k;i++){
            if(td==d[i]){
                DONE = 0;
            }
        }
        d[k] = td;
        for(i=0;td;i++){
            A[i] = td%10;
            B[i] = td%10;
            td = td/10;
        }
        x=i;
        k++;
    }
    printf("%d\n",k);

    return 0;
}

void sortA (void){
    for(i=x-1;i>=0;i--){
        for(j=0;j<i;j++){
            if(A[j]<A[j+1]){
                temp = A[j];
                A[j] = A[j+1];
                A[j+1] = temp;
            }
        }
    }
    a=0;
    for(i=x-1,j=1;i>=0;i--,j=j*10){
        a = a+j*A[i];
    }
    return;
}

void sortB(void){
    for(i=x-1;i>=0;i--){
        for(j=0;j<i;j++){
            if(B[j]>B[j+1]){
                temp = B[j];
                B[j] = B[j+1];
                B[j+1] = temp;
            }
        }
    }
    b=0;
    for(i=x-1,j=1;i>=0;i--,j=j*10){
        b = b+j*B[i];
    }
    return;
}
