#include <iostream>
#include <vector>
#include <stdio.h>

using namespace std;

int main()
{
    int n,i=1;
    scanf("%d",&n);
    string c;
    getline(cin,c);
    while(i<=n){
        vector<int> a;
        int ans=1;
        getline(cin,c);
        for(int j=0; j<=c.size(); j++){
        //for(int i=0; i<c.size(); i++){
            if (c[j]=='(') a.push_back(1);
            else if (c[j]=='<') a.push_back(2);
            else if (c[j]=='{') a.push_back(3);
            else if (c[j]=='[') a.push_back(4);
            else if (c[j]==')'){
                if(a.back() == 1) a.pop_back();
                else{
                    ans=0; break;
                }
            }else if (c[j]=='>'){
                if(a.back() == 2) a.pop_back();
                else{
                    ans=0; break;
                }
            }else if (c[j]=='}'){
                if(a.back() == 3) a.pop_back();
                else{
                    ans=0; break;
                }
            }else if (c[j]==']'){
                if(a.back() == 4) a.pop_back();
                else{
                    ans=0; break;
                }
            }
        }
        if(a.empty()==false) ans = 0;

        cout<<"Case"<<" "<<i<<":"<<" ";
        if(ans==1) cout<<"Yes"<<endl;
        else if(ans==0) cout<<"No"<<endl;

        i++;
    }
    return 0;
}
