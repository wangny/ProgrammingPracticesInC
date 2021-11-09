#include "function.h"


std::ostream &operator<<(std::ostream & os, Stack & t)
{
    t.print(os);
    return os;
}

Array_stack::Array_stack():max_size{0}
{
    for(auto i=0; i<100; i++)number[i]=0;
}

Array_stack::~Array_stack(){}



void Array_stack::push(const int & d)
{
    number[max_size] = d;
    max_size++;
}

int Array_stack::pop()
{
    if(max_size==0)return 0;
    else{
        max_size--;
        return number[max_size];
    }
}

void Array_stack::print(std::ostream &output)
{
    if(max_size!=0){
        std::cout<<number[max_size-1];
        for(auto i=max_size-2;i>=0;i--){
            std::cout<<" "<<number[i];
        }
    }
}

List_stack::List_stack()
{
    head = NULL;
    tail = NULL;
}

List_stack::~List_stack(){}

void List_stack::push(const int & d)
{
    if(head==NULL){
        head = new ListNode(d);
        tail = head;
    }else{
        ListNode *tmp = new ListNode(d);
        head->prevPtr = tmp;
        tmp->nextPtr = head;
        head = tmp;
    }
}

int List_stack::pop()
{
    if(head!=NULL){
        ListNode *t=head;
        head = head->nextPtr;
        if(head==NULL){
            tail=NULL;
        }else{
            head->prevPtr = NULL;
        }
        return t->data;
    }else return 0;
}

void List_stack::print(std::ostream &output)
{
    if(head!=NULL){
        ListNode *cur=head->nextPtr;
        std::cout<<head->data;
        while(cur!=NULL){
            std::cout<<" "<<cur->data;
            cur = cur->nextPtr;
        }
    }
}
