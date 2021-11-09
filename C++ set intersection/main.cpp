#include <iostream>
#include <set>
#include <vector>
#include <algorithm>

using namespace std;

int main()
{
    ///重要! 讓input不須同時符合stdio , iostream
    ios_base::sync_with_stdio(false);

    int n;
    while( cin>>n && n!= 0){
        vector<int> first;
        while(n>0){
            int i;
            cin>> i;
            first.push_back(i);
            n--;
        }
        sort(first.begin(),first.end());

        int m;
        cin>> m;
        vector<int> second;
        while(m>0){
            int i;
            cin>> i;
            second.push_back(i);
            m--;
        }
        sort(second.begin(),second.end());

        vector<int> ans;
        int i = 0, j=0;
        while( i<first.size() && j<second.size() ){
            if(first[i]==second[j]){
                ans.push_back(first[i]);
                i++; j++;
            }else if(first[i] < second[j]){
                i++;
            }else{
                j++;
            }

        }

        if(ans.empty()){
            cout<<"empty"<<endl;
        }else{
            cout<<ans[0];
            for(auto s=1; s<ans.size();s++){
                cout<<" "<<ans[s];
            }
            cout<<endl;
        }
    }

    return 0;
}
