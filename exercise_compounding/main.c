#include <stdio.h>

int main(void)
{
    char input;
    int y1,y2,a;
    float i=1.006,j;

    scanf("%d %c %f",&y1,&input,&j);
    scanf("%d %c %d",&y2,&input,&a);

    while(1){

        y1 = y1+1;
        while (y1<=y2){
            j = j*i;
        }
        if (input=='D'){
            j = j + a;
        }else if(input == 'W'){
            j = j - a;
        }else{
            break;
        }
        scanf("%d %c %d",&y2,&input,&a);
    }

    printf("%.2f\n",j);

    return 0;
}
