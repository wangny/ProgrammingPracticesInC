#include <iostream>
#include <string>

using namespace std;

struct Node
{
        int data;
        Node *next = NULL;
};

int main()
{
    Node *head= new Node;
    head->data = 1;

    int n;
    cin>>n;
    Node *cur=head;
    for(auto i=2; i<=n; i++){
        Node *tmp = new Node;
        tmp->data = i;
        cur->next = tmp;
        cur = tmp;
    }
    Node *tail = cur;

    string str;
    while(cin>>str && str != "Exit"){
        int a,b;
        cin>>a; cin>>b;
        cur = head;
        while(cur->data!=a){
            cur=cur->next;
        }
        Node *des=cur;
        while(des->next->data!=b){
            des=des->next;
        }
        Node *tmp = cur->next;
        cur->next = des->next;
        des->next = head;
        head = tmp;
    }

    cur = head;
    while(cur!=tail){
        cout<<cur->data<<" ";
        cur = cur->next;
    }
    cout<<cur->data<<endl;

    return 0;
}
