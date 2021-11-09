#ifndef FUNCTION_H

#define FUNCTION_H

#include <iostream>

class Node

{

   friend class Josephus;

   public:

          Node( const int &info ) //constructor

      :number( info ), next( NULL ), prev(NULL)

      {

      } //end ListNode constructor

   private:

          Node *next;

          Node *prev;

          int number;

};//end class Node



class Josephus

{

    public:

         Josephus();

         ~Josephus();

         Josephus(const int &);

         int kill();

    private:

        void generatecircularlinkedList(const int &);

        void generateSquare(const int &);

        int sequence[10005];

        int noOfPeople;

        Node *head, *current;

};

#endif // FUNCTION_H


