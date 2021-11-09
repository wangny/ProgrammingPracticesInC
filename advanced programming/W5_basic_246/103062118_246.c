#include <stdio.h>
#include <stdlib.h>

typedef struct pile{
    int cards[52];
    int head;
    int tail;
    int num;
}Pile;

Pile p1, p2, p3, p4, p5, p6, p7, hand;
int count;


void change(Pile* p){
    int a,b,c;
    int pick = 1;
    if(p->num<0) return;

    p->cards[p->tail] = hand.cards[hand.head];
    p->tail++; p->num++;
    if(p->tail>51) p->tail = 0;
    hand.head++; hand.num--;
    if(hand.head>51) hand.head = 0;
    count++;

    while(pick==1){
        pick=0;

        if(p->num<3) return;


        a = p->head;
        if(p->head+1>51) b = 0;
        else b = p->head+1;
        if(p->tail-1<0) c = 51;
        else c = p->tail-1;

        if( (p->cards[a]+p->cards[b]+p->cards[c])%10 == 0 ){
            hand.cards[hand.tail] = p->cards[a];
            hand.tail++; if(hand.tail>51) hand.tail = 0;
            hand.cards[hand.tail] = p->cards[b];
            hand.tail++; if(hand.tail>51) hand.tail = 0;
            hand.cards[hand.tail] = p->cards[c];
            hand.tail++; if(hand.tail>51) hand.tail = 0;

            p->tail = c;
            if(b+1>51) p->head = 0;
            else p->head = b+1;

            p->num -=3; hand.num+=3;
            if(p->num<=0) p->num = -1;
            pick=1;
            continue;
        }


        a = p->head;
        if(p->tail-1<0) c = 51;
        else c = p->tail-1;
        if(c-1<0) b = 51;
        else b = c-1;

        if( (p->cards[a]+p->cards[b]+p->cards[c])%10 == 0 ){
            hand.cards[hand.tail] = p->cards[a];
            hand.tail++; if(hand.tail>51) hand.tail = 0;
            hand.cards[hand.tail] = p->cards[b];
            hand.tail++; if(hand.tail>51) hand.tail = 0;
            hand.cards[hand.tail] = p->cards[c];
            hand.tail++; if(hand.tail>51) hand.tail = 0;

            p->tail = b;
            if(a+1>51) p->head = 0;
            else p->head = a+1;

            p->num -=3; hand.num+=3;
            if(p->num<=0) p->num = -1;
            pick=1;
            continue;
        }


        if(p->tail-1<0) c = 51;
        else c = p->tail-1;
        if(c-1<0) b = 51;
        else b = c-1;
        if(b-1<0) a = 51;
        else a = b-1;

        if( (p->cards[a]+p->cards[b]+p->cards[c])%10 == 0 ){
            hand.cards[hand.tail] = p->cards[a];
            hand.tail++; if(hand.tail>51) hand.tail = 0;
            hand.cards[hand.tail] = p->cards[b];
            hand.tail++; if(hand.tail>51) hand.tail = 0;
            hand.cards[hand.tail] = p->cards[c];
            hand.tail++; if(hand.tail>51) hand.tail = 0;

            p->tail = a;

            p->num -=3; hand.num+=3;
            if(p->num<=0) p->num = -1;
            pick=1;
            continue;
        }

    }

}

int compare(int s[60]){
    int i=8,j;

    if(hand.num!=s[0]) return 0;
    for(j=0; j<hand.num; j++){
        if(s[i]!=hand.cards[(hand.head+j)%52]) return 0;
        i++;
    }
    if(p1.num!=s[1]) return 0;
    for(j=0; j<p1.num; j++){
        if(s[i]!=p1.cards[(p1.head+j)%52]) return 0;
        i++;
    }
    if(p2.num!=s[2]) return 0;
    for(j=0; j<p2.num; j++){
        if(s[i]!=p2.cards[(p2.head+j)%52]) return 0;
        i++;
    }
    if(p3.num!=s[3]) return 0;
    for(j=0; j<p3.num; j++){
        if(s[i]!=p3.cards[(p3.head+j)%52]) return 0;
        i++;
    }
    if(p4.num!=s[4]) return 0;
    for(j=0; j<p4.num; j++){
        if(s[i]!=p4.cards[(p4.head+j)%52]) return 0;
        i++;
    }
    if(p5.num!=s[5]) return 0;
    for(j=0; j<p5.num; j++){
        if(s[i]!=p5.cards[(p5.head+j)%52]) return 0;
        i++;
    }
    if(p6.num!=s[6]) return 0;
    for(j=0; j<p6.num; j++){
        if(s[i]!=p6.cards[(p6.head+j)%52]) return 0;
        i++;
    }
    if(p7.num!=s[7]) return 0;
    for(j=0; j<p7.num; j++){
        if(s[i]!=p7.cards[(p7.head+j)%52]) return 0;
        i++;
    }

    return 1;
}

void initial(){
    int i;
    for(i=0; i<52; i++){
        p1.cards[i] = 0;
        p2.cards[i] = 0;
        p3.cards[i] = 0;
        p4.cards[i] = 0;
        p5.cards[i] = 0;
        p6.cards[i] = 0;
        p7.cards[i] = 0;
    }
    p1.head = 0;  p1.tail = 0;  p1.num = 0;
    p2.head = 0;  p2.tail = 0;  p2.num = 0;
    p3.head = 0;  p3.tail = 0;  p3.num = 0;
    p4.head = 0;  p4.tail = 0;  p4.num = 0;
    p5.head = 0;  p5.tail = 0;  p5.num = 0;
    p6.head = 0;  p6.tail = 0;  p6.num = 0;
    p7.head = 0;  p7.tail = 0;  p7.num = 0;
}

void save_cur(int* save){
    int j,i=8;
    save[0] = hand.num;
    save[1] = p1.num;
    save[2] = p2.num;
    save[3] = p3.num;
    save[4] = p4.num;
    save[5] = p5.num;
    save[6] = p6.num;
    save[7] = p7.num;
    for(j=hand.head; j!=hand.tail; j++){
        save[i] = hand.cards[j]; i++;
        if(j>50) j=-1;
    }
    for(j=p1.head; j!=p1.tail; j++){
        save[i] = p1.cards[j]; i++;
        if(j>50) j=-1;
    }
    for(j=p2.head; j!=p2.tail; j++){
        save[i] = p2.cards[j]; i++;
        if(j>50) j=-1;
    }
    for(j=p3.head; j!=p3.tail; j++){
        save[i] = p3.cards[j]; i++;
        if(j>50) j=-1;
    }
    for(j=p4.head; j!=p4.tail; j++){
        save[i] = p4.cards[j]; i++;
        if(j>50) j=-1;
    }
    for(j=p5.head; j!=p5.tail; j++){
        save[i] = p5.cards[j]; i++;
        if(j>50) j=-1;
    }
    for(j=p6.head; j!=p6.tail; j++){
        save[i] = p6.cards[j]; i++;
        if(j>50) j=-1;
    }
    for(j=p7.head; j!=p7.tail; j++){
        save[i] = p7.cards[j]; i++;
        if(j>50) j=-1;
    }
}

void output(){
    int i;
    printf("\ncount %d\nhand: ",count);
    for(i=0; i<hand.num; i++)printf("%d ",hand.cards[(hand.head+i)%52]);
    printf("\np1: ");
    for(i=0; i<p1.num; i++)printf("%d ",p1.cards[(p1.head+i)%52]);
    printf("\np2: ");
    for(i=0; i<p2.num; i++)printf("%d ",p2.cards[(p2.head+i)%52]);
    printf("\np3: ");
    for(i=0; i<p3.num; i++)printf("%d ",p3.cards[(p3.head+i)%52]);
    printf("\np4: ");
    for(i=0; i<p4.num; i++)printf("%d ",p4.cards[(p4.head+i)%52]);
    printf("\np5: ");
    for(i=0; i<p5.num; i++)printf("%d ",p5.cards[(p5.head+i)%52]);
    printf("\np6: ");
    for(i=0; i<p6.num; i++)printf("%d ",p6.cards[(p6.head+i)%52]);
    printf("\np7: ");
    for(i=0; i<p7.num; i++)printf("%d ",p7.cards[(p7.head+i)%52]);
}


int main()
{
    int save[60];
    int ini[60];
    int find[1000][60];
    int loop_period;
    int period,save_step;
    int phase;
    int i,j,k;


    scanf("%d",&ini[8]);
    while(ini[8]!=0){
        ini[0] = 52;
        hand.cards[0] = ini[8];
        for(i=9; i<60; i++) {
            scanf("%d",&ini[i]);
            hand.cards[i-8] = ini[i];
        }
        hand.head = 0;
        hand.tail = 0;
        hand.num = 52;
        initial();
        phase = 0;
        period = 1;
        count = 0;
        save_step = 0;

        while(1){

            phase++; if(phase>7)phase=1;
            if(phase==1 && p1.num>=0) change(&p1);
            else if(phase==2 && p2.num>=0) change(&p2);
            else if(phase==3 && p3.num>=0) change(&p3);
            else if(phase==4 && p4.num>=0) change(&p4);
            else if(phase==5 && p5.num>=0) change(&p5);
            else if(phase==6 && p6.num>=0) change(&p6);
            else if(phase==7 && p7.num>=0) change(&p7);
            else continue;

            if(hand.num<=0){
                printf("Loss: %d\n",count);
                break;
            }else if(count!=1 && compare(save)==1){

                loop_period = count - save_step;
                initial();
                for(i=8; i<60; i++) {
                    hand.cards[i-8] = ini[i];
                }
                hand.num = 52; hand.head = 0; hand.tail=0;
                k=1; phase=0; count=0;
                while(count<loop_period){
                    phase++; if(phase>7)phase=1;
                    if(phase==1 && p1.num>=0) change(&p1);
                    else if(phase==2 && p2.num>=0) change(&p2);
                    else if(phase==3 && p3.num>=0) change(&p3);
                    else if(phase==4 && p4.num>=0) change(&p4);
                    else if(phase==5 && p5.num>=0) change(&p5);
                    else if(phase==6 && p6.num>=0) change(&p6);
                    else if(phase==7 && p7.num>=0) change(&p7);
                    else continue;
                    save_cur(find[k]);
                   k++;
                   if(k>=loop_period)k=0;
                }

                while(1){

                    phase++; if(phase>7)phase=1;
                    if(phase==1 && p1.num>=0) change(&p1);
                    else if(phase==2 && p2.num>=0) change(&p2);
                    else if(phase==3 && p3.num>=0) change(&p3);
                    else if(phase==4 && p4.num>=0) change(&p4);
                    else if(phase==5 && p5.num>=0) change(&p5);
                    else if(phase==6 && p6.num>=0) change(&p6);
                    else if(phase==7 && p7.num>=0) change(&p7);
                    else continue;

                    if(compare(find[ count%loop_period ]) ) break;
                    save_cur(find[k]);
                    k++;
                    if(k>=loop_period)k=0;
                }


                printf("Draw: %d\n",count);
                break;

            }else if(p1.num<0 && p2.num<0 && p3.num<0 && p4.num<0 && p5.num<0 && p6.num<0 && p7.num<0){
                printf("Win : %d\n",count); break;
            }

            if(count-save_step == period){
                save_cur(save);
                save_step = count;
                period = period*2;
            }


        }
        scanf("%d",&ini[8]);
    }
    return 0;
}
