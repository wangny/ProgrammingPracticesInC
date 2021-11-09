#include <stdio.h>
#include <stdlib.h>

typedef struct key{
    char data;
    struct Key * next;
}Key;

int main(void)
{
    Key * head, *cp, *tail, *t;
    char c;

    cp=(Key*)malloc(sizeof(Key));
    cp->next=NULL;
    head=cp;
    tail=cp;

    c=getchar();
    while(c != EOF){
        if(c=='@'){
            cp=head;
        }else if(c=='#'){
            cp=tail;
        }else if( c=='%'){
            if(cp->next!=NULL){
                t=cp->next;
                cp->next=t->next;
                //free(t);
            }
        }else{
            t=(Key*)malloc(sizeof(Key));
            t->data=c;
            t->next=cp->next;
            cp->next=t;
            cp=cp->next;
            if(cp->next==NULL){
                tail=cp;
            }
        }
        c=getchar();
    }

    cp=head->next;
    while(cp!=NULL){
        printf("%c",cp->data);
        cp=cp->next;
    }
    printf("\n");
    return 0;
}
