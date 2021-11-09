#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define max_lenght 500
#define lenght 100

int big[max_lenght];
int cur[max_lenght];
int ans[max_lenght];
int ans_t[max_lenght];

void mul (int a )
{
    int re[max_lenght];
    int i,tmp;
    int carry = 0;

    for(i=0; i<max_lenght; i++){
        re[i] = 0;

        if(ans[i]>0 || carry>0){
            tmp = a * ans[i] + carry;
            re[i] = tmp%lenght;
            carry = tmp/lenght;
        }
    }

    for(i=0; i<max_lenght; i++) ans[i] = re[i];

}


void mul_t (int a )
{
    int re[max_lenght];
    int i,tmp;
    int carry = 0;

    for(i=0; i<max_lenght; i++){
        re[i] = 0;

        if(ans[i]>0 || carry>0){
            tmp = a * ans[i] + carry;
            re[i] = tmp%lenght;
            carry = tmp/lenght;
        }
    }

    for(i=0; i<max_lenght; i++) ans_t[i] = re[i];

}


void add(int coe)
{
    int carry = 0;
    int i=1;
    ans[0] = ans[0] + coe;
    carry = ans[0] / lenght;
    ans[0] = ans[0] % lenght;
    while(carry>0)
    {
        ans[i] = ans[i] + carry;
        carry = ans[i] / lenght;
        ans[i] = ans[i] % lenght;
        i++;
    }

}


void sub(int coe)
{
    int carry = 0;
    int i=1;

    if(ans[0] >= coe) ans[0] = ans[0] - coe;
    else{
        ans[0] = ans[0] + lenght - coe;
        carry = 1;
    }

    while(carry>0)
    {
        if(ans[i] >= carry){
            ans[i] = ans[i] - carry;
            carry = 0;
        }
        else{
            ans[i] = ans[i] + lenght - coe;
            carry = 1;
        }
        i++;
    }

}


void minus(int coe)
{
    int carry = 0;
    int i = 0;

    add(coe);
    mul_t(coe);

    for(i=0; i<max_lenght; i++){
        if(cur[i] < (ans_t[i] + carry) ){
            cur[i] = lenght + cur[i] - ans_t[i] - carry;
            carry = 1;
        }else{
            cur[i] = cur[i] - ans_t[i] - carry;
            carry = 0;
        }
    }

    add(coe);
    mul(10);
}


void output(int out[max_lenght])
{
     int j;
     for(j=max_lenght-1; j>0; j--){
        if(out[j]>0){
            printf("%d",out[j]);
            j--;
            break;
        }
    }
    for(; j>=0; j--){
        if(out[j]==0) printf("00");
       else if(out[j] < 10) printf("0%d",out[j]);
       else printf("%d",out[j]);
    }
}

int com(void)
{
    int i;
    for(i=max_lenght-1; i>=0; i--){
        if(ans_t[i] > cur[i]) return 1;
        else if(cur[i] > ans_t[i]) return 0;
    }
    return 0;
}


int main()
{
    int n;
    char Y[1001];
    char tmp[3] = {'\0'};
    int i,j,k,l,m;

    scanf("%d",&n);
    while(n>0){

        scanf("%s",Y);

        for(i = strlen(Y)-1 , k=0 ; i>=0; i=i-2,k++ ){
            if(i==0) big[k]= Y[i]-'0';
            else{
                tmp[0] = Y[i-1];
                tmp[1] = Y[i];
                big[k] = atoi(tmp);
            }
        }

        for(i=0; i<max_lenght; i++){
            ans[i]=0;
            ans_t[i]=0;
            cur[i]=0;
        }

        for(i=k-1; i>=0; i-- ){

            for(j=max_lenght-1; j>0; j--){
                if(cur[j]>0)  break;
            }
            for(; j>=0; j--) cur[j+1] = cur[j];
            cur[0] = big[i];

            for(j=0; j<=10; j++){
                add(j);
                mul_t(j);
                sub(j);
                if( com() == 1 ) break;
            }
            minus(j-1);
            printf("%d",j-1);

        }
        printf("\n");

        n--;
        if(n>0) printf("\n");

    }

    return 0;
}
