#include<iostream>
#include<string.h>
#include "function.h"

using namespace std;

int main(){

    Array_stack A_stack;

    List_stack L_stack;

    char command[10];

    int n;

    while(cin>>command){

        if(strcmp(command,"pop")==0){

            n=A_stack.pop();

            n=L_stack.pop();

        }else if(strcmp(command,"push")==0){

            cin >> n;

            A_stack.push(n);

            L_stack.push(n);

        }else if(strcmp(command, "print") == 0){

            cout << A_stack << endl;

            cout << L_stack << endl;

        }

    }

    return 0;

}
