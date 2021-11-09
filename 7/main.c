#include <stdio.h>
#define MAXNV 5
int DONE = 0;
int values[MAXNV];
int numbers[MAXNV];
int temp[MAXNV];
void show(int nv);
void change(int amount, int cur, int nv);
int main(void)
{
    int nv, i;
    int money;
    scanf("%d", &nv);
    for (i=0; i<nv; i++) {
        scanf("%d", &values[i]);
        numbers[i] = 0;
        temp[i] = 0;
    }
    scanf("%d", &money);
    change(money, 0, nv);
    show(nv);
    return 0;
}
void show(int nv)
{
    int i;
    printf("(%d", numbers[0]);
    for (i=1; i<nv; i++) {
        printf(",%d", numbers[i]);
    }
    printf(")\n");
}
void change(int amount, int cur, int nv)
{
    int i=0,j=amount,x=100,x1=0,k;

    if(cur<nv){
        i=0;
        while(j>= (values[cur]*i) ){
            j = j-(values[cur]*i);
            temp[cur] = temp[cur]+i;
            cur++;
            change(j,cur,nv);
            cur--;
            i = 1;
        }
        if(j==0){
            for(k=0;k<nv;k++){
                x1 = x1 + temp[k];
            }
            if(x>x1){
                for(k=0;k<nv;k++){
                    numbers[k] = temp[k];
                }
                temp[cur] = 0;
                x = x1;
            }
            return;
        }else{
        j = amount;
        temp [cur] =0;
        return;
        }
    }

}
