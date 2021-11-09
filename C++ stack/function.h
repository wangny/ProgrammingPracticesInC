#ifndef FUNCTION_H
#define FUNCTION_H
#include <iostream>

class ListNode

{

    friend class List_stack; //make List_stack a friend

public:

    ListNode( const int &info ) //constructor
    : data( info ), nextPtr( NULL ), prevPtr( NULL )
    { } //end ListNode constructor

private:

    int data; //data
    ListNode *nextPtr; // next node in list
    ListNode *prevPtr;

}; //end class ListNode


class Stack{

    friend std::ostream &operator<<(std::ostream &, Stack &);

    public:
        virtual ~Stack() {};
        virtual void push(const int &) = 0;
        virtual int pop() = 0;
        virtual void print(std::ostream &output)=0;
};

class Array_stack : public Stack{

    public:

        Array_stack();
        virtual ~Array_stack();
        void push(const int &);
        int pop();
        void print(std::ostream &output);

    private:

        int number[100];
        int max_size;

};

class List_stack : public Stack{

    public:

        List_stack();
        virtual ~List_stack();
        void push(const int &);
        int pop();
        void print(std::ostream &output);

    private:

        ListNode *head;
        ListNode *tail;

};

#endif // FUNCTION_H
