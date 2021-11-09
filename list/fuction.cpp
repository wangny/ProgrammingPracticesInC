#include <iostream>
#include "function.h"

    OWList::OWList()
    {
        firstPtr=NULL;
        lastPtr=NULL;
    }

    //destructor
    OWList::~OWList()
    {
        ListNode* curptr = firstPtr;
        while(curptr != lastPtr){
            ListNode *t = curptr;
            delete t;
            curptr = curptr->nextPtr;
        }
    }

    //insert node at front of list
    void OWList::insertAtFront( const int &value )
    {
        if (isEmpty() ){
            ListNode *t = new ListNode(value);
            firstPtr = t;
            lastPtr = firstPtr;
        }else{
            ListNode *t = new ListNode(value);
            t->nextPtr = firstPtr;
            firstPtr = t;


        }
    }

    //remove node from front of list


    void OWList::removeFromFront()
    {
        if(!isEmpty()){
            ListNode * curptr=firstPtr;
            firstPtr = firstPtr->nextPtr;
            delete curptr;
        }
    }

    //is List empty?

    bool OWList::isEmpty() const
    {
        return  firstPtr == nullptr ;
    }

    //display contents of List

    void OWList::print() const
    {
        ListNode *curptr = firstPtr;
        //std::cout<<firstPtr->nextPtr<<" "<<lastPtr<<std::endl;
        while(curptr != lastPtr){
            std::cout << curptr->data << " ";
            curptr = curptr->nextPtr;
        }
        std::cout<< curptr->data;
    }


    //insert node at back of list

    void TWList::insertAtBack( const int &value )
    {
        if (isEmpty() ){
            ListNode  *t=new ListNode(value);
            lastPtr = t;
            firstPtr = lastPtr;
        }else{
            ListNode  *t=new ListNode(value);
            lastPtr->nextPtr = t;
            lastPtr = t;
        }
    }

    //delete node from back of list

    void TWList::removeFromBack()
    {
       if(!isEmpty()){
            ListNode *curptr = firstPtr;
            while(curptr->nextPtr != lastPtr){
                curptr = curptr->nextPtr;
            }
            delete curptr->nextPtr;
            curptr->nextPtr=NULL;
            lastPtr=curptr;
       }
    }


