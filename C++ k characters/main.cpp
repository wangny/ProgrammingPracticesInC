#include <iostream>
#include <algorithm>
#include <vector>
#include <map>
#include <set>

using namespace std;

set<vector<char> > ans;
vector<char> tmp;

void solve2(int p,vector<char> s,int t)
{
    if(p>0){
        for(auto i = t ;i<=s.size();i++){
            s.insert(s.begin()+i,'0');
            p--;
            solve2(p,s,i);
            p++;
            s.erase(s.begin()+i);
        }
    }else{
        ans.insert(s);

    }

}

void solve(int num, map<char,int>ma,int p)
{

     if(num>0){

        for(auto m ='A'; m<='K'; m++){
            if(ma[m]>0){

                tmp.push_back(m);
                ma[m]--;
                num--;
                solve(num,ma,p);
                tmp.pop_back();
                num++;
            }
            ma[m]=0;
         }
     }else{
            solve2(p,tmp,0);

     }
}

int main(void)
{
    ios_base::sync_with_stdio(false);

    int n;
    cin>> n;


    while(n>0){
        string str;
        cin>> str;

        int m;
        cin>>m;

        int p;
        cin>>p;

        map<char,int> input;
        for(auto i = 'A';i<='K';i++){
            input[i]=0;
        }
        for(auto i=0; i<str.size(); i++){
            if(input[str[i]] < m) input[str[i]]++;
        }

        ans.clear();
        solve(m,input,p);

        for(auto s : ans){
            for(auto v : s){
                if(v=='0') cout<<"_";
                else cout<<v;
            }
            cout<<"\n";
        }
        cout<<"\n";

        n--;
    }
    return 0;
}
