#include "function.h"

Josephus::Josephus()
{
    head = NULL;
    current = NULL;
}

Josephus::~Josephus()
{
    /*current = head;
    while(current->next != NULL){
        Node *tmp = current;
        current = current->next;
        delete tmp;
    }
    delete current;*/
}

Josephus::Josephus(const int & n)
{
    noOfPeople = n;
    generatecircularlinkedList(n);
}

int Josephus::kill()
{
    generateSquare(noOfPeople);
    int k=1;

    while(noOfPeople > 1 ){

        int kiln=sequence[k];
        if(kiln%noOfPeople!=0){
            kiln=kiln%noOfPeople;
        }else{
            kiln=noOfPeople;
        }
        for(auto i=1 ; i<kiln ; i++){
            current = current->next;
        }
        //std::cout<<current->next->number<<std::endl;
        current->next = current->next->next;
        current->next->prev = current;

        noOfPeople--;
        k++;
    }
    return current->number;
}

void Josephus::generatecircularlinkedList(const int &n)
{
    head = new Node(1);
    current = head;
    for(auto i = 2; i<=n ; i++ ){
        Node *tmp = new Node(i);
        current->next = tmp;
        tmp->prev = current;
        current = tmp;
    }
    current->next = head;
    head->prev = current;
}

void Josephus::generateSquare(const int & n)
{
    for (auto i=1; i<=n; i++){
        sequence[i] = i*i;
    }
}




