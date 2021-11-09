#include <stdio.h>
#include <stdlib.h>

typedef struct list{
    int id;
    struct List *next;
    struct List *pre;
}List;

List* add(List* q,int d)
{
    List * p;

    p = (List*)malloc(sizeof(List));
    p->id=d+1;
    p->pre=q;
    p->next=q->next;
    q->next=p;

    return p;
}

void del(List *q)
{
    List *p;
    List *t;
    p=q->next;
    q->next=p->next;
    t=p->next;
    t->pre=q;
    //printf("%d ",p->id);
    free(p);
    return;
}

void del2(List *q)
{
    List *p;
    List *t;
    p=q->pre;
    q->pre=p->pre;
    t=p->pre;
    t->next=q;
    //printf("%d ",p->id);
    free(p);
    return;
}

int main(void)
{
    int N,M;
    int i,j;
    List *head;
    List *cp;

    scanf("%d%d",&N,&M);

    head = (List*)malloc(sizeof(List));
    head->id=1;
    head->next=head;
    cp=head;

    for(i=1;i<N;i++){
        cp=add(cp,i);
    }
    head->pre=cp;

    //printf("done");

    cp=head;
    i=0;
    while((cp->next)!=cp){
        if((i%2)==0){
            for(j=1;j<(M-1);j++){
                cp=cp->next;
            }
            del(cp);
        }else{
            for(j=1;j<(M-1);j++){
                cp=cp->pre;
            }
            del2(cp);
        }
        i++;
    }
    printf("%d\n",cp->id);

    return 0;
}
