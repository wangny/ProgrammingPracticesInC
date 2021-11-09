#include <stdio.h>
#include <stdlib.h>

typedef struct book{
    int id;
    struct Book *next;
    struct Book *pre;
}Book;

typedef enum{
    move,Remove,on,under,Exit
}commend;

Book* insert(Book *p, int d)
{
    Book *q = (Book*)malloc(sizeof(Book));

    q->next=p->next;
    q->pre=p;
    p->next=q;
    q->id=d;

    return q;
}

int read(void)
{
    char s[7]={'\0'};
    scanf("%s",s);
    if(strcmp(s,"move")==0) return move;
    if(strcmp(s,"remove")==0) return Remove;
    if(strcmp(s,"on")==0) return on;
    if(strcmp(s,"under")==0) return under;
    if(strcmp(s,"exit")==0) return Exit;
}

int main(void)
{
    int n;
    Book *head, *cp,*a, *b;
    int i,c,A,B;

    scanf("%d",&n);

    head=(Book*)malloc(sizeof(Book));
    head->next=NULL;
    head->pre=NULL;
    cp=head;

    for(i=0;i<n;i++){
        cp=insert(cp,i);
        //printf("%d ",i);
    }
   // printf("\n");

    while( (c=read())!= Exit ){


        if(c==move){
            cp=head;
            scanf("%d",&A);
             while(cp->id!=A ){
                cp=cp->next;
                if(cp==NULL) break;
            }
            a=cp;

            c=read();

            scanf("%d",&B);
            cp=head;
            while(cp->id!=B ){
                cp=cp->next;
                if(cp==NULL)break;
            }
            b=cp;

            if(A==B || A>=n || B>=n || A<0 || B<0 || a==NULL || b==NULL){
                continue;
            }

            if(c==on ){

                if(a->next==NULL){
                    cp=a->pre;
                    cp->next=a->next;
                }else{
                    cp=a->next;
                    cp->pre=a->pre;
                    cp=a->pre;
                    cp->next=a->next;
                }


                if(b->next==NULL){
                    b->next=a;
                    a->pre=b;
                    a->next=NULL;
                }else{
                    a->next=b->next;
                    a->pre=b;
                    cp=b->next;
                    cp->pre=a;
                    b->next=a;
                }
            }else if(c==under ){

                if(a->next==NULL){
                    cp=a->pre;
                    cp->next=a->next;
                }else{
                    cp=a->next;
                    cp->pre=a->pre;
                    cp=a->pre;
                    cp->next=a->next;
                }

                a->pre=b->pre;
                a->next=b;
                cp=b->pre;
                cp->next=a;
                b->pre=a;
            }
        }else if(c==Remove){
            scanf("%d",&A);
            cp=head;
            while(cp->id!=A ){
                cp=cp->next;
                if(cp==NULL) break;
            }
            a=cp;

            if(A<n && A>=0 && a!=NULL){

                if(a->next==NULL){
                    cp=a->pre;
                    cp->next=NULL;
                }else{
                    cp=a->next;
                    cp->pre=a->pre;
                    cp=a->pre;
                    cp->next=a->next;
                }
                free(a);
            }
        }
    }

    cp=head->next;
    while(cp!=NULL){
        printf("%d ",cp->id);
        cp=cp->next;
    }
    printf("\n");


    return 0;
}
