#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void)
{
    char output[500]={'/0'};
    char *p,*k;
    char temp;
    int i;

    p=&output[0];

    temp=getchar();

    while( temp!=EOF ){
        if(temp=='/'){
            temp=getchar();
            if(temp=='b'){
                if(p>&output[0]){
                    p--;
                }
                *p='/0';
                for(i=9;i;i--){
                    temp=getchar();
                }
            }else if(temp=='n'){
                *p='\n';
                p++;
                for(i=7;i;i--){
                    temp=getchar();
                }
            }else if(temp=='l'){
                if(*p!='0'){
                    *(p+1)=*p;
                }
                for(i=4;i;i--){
                    temp=getchar();

                }
            }else if(temp=='r'){
                p++;
                if(*p==0){
                    p--;
                }
                for(i=5;i;i--){
                    temp=getchar();
                }

            }
        }else{
            *p=temp;
            p++;
            temp=getchar();
        }
        printf("%s\n",output);
    }

    printf("%s",output);

    return 0;
}
