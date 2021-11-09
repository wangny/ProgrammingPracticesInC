#include <iostream>

using namespace std;

struct Node{
    int pre;
    int nex;
};

int main()
{
    int n;
    cin>>n;
    Node lis[n];
    for(auto i = 0; i<n; i++){
        if(i == n-1){
            lis[i].nex = -1;
            lis[i].pre = i-1;
        }else if(i==0){
            lis[i].pre = -1;
            lis[i].nex = i+1;
        }else{
            lis[i].pre = i-1;
            lis[i].nex = i+1;
        }
    }
    int head=0;

    string str;
    while(cin>>str && str!="Exit"){
        int a,b;
        cin >>a; cin>>b;
        a = a-1; b = b-1;

        int tmp = lis[b].pre;
        lis[b].pre = a;
        lis[tmp].nex= head;
        lis[head].pre = tmp;
        head = lis[a].nex;
        lis[a].nex = b;
    }

    cout<<head+1;
    int cur=lis[head].nex;
    while(cur>=0){
        cout<<" "<<cur+1;
        cur = lis[cur].nex;
    }
    cout<<endl;

    return 0;
};
