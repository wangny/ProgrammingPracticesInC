#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
    char s[11]={'\0'};
    char inputs[30][7]={'\0'};
    char name[150000][11]={'\0'};
    int i=0,j=0,n=0,k=0;
    int find=0;

    scanf("%s",s);
    while(strcmp(s,"END")!=0){
        find=0;
        for(i=0;i<j;i++){
            if(strcmp(inputs[i],s)==0){
                n=i;
                find=1;

                if(i==(j-1)){
                    scanf("%s",s);
                    strcpy(name[k],s);

                    k++;
                }else{
                    scanf("%s",s);
                }

                break;
            }
        }
        if(!find){
            strcpy(inputs[j], s);
            n=j;
            j++;

            scanf("%s",s);
            k=0;
            strcpy(name[k],s);

            k++;
        }


        scanf("%s",s);
    }

    j--;
    printf("%s %s",inputs[j],name[0]);
    for(i=1;i<k;i++){
        printf(" %s",name[i]);
    }

    printf("\n");

    return 0;
}
