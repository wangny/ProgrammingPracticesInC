#include <iostream>
#include <vector>
#include <stdio.h>
using namespace std;

int main()
{
    int n;
    cin>>n;
    while(n>0){
        int m;
        cin>>m;
        int a[m], b[m], ans[m];
        for(auto i=0; i<m; i++){
            scanf("%1d",&a[i]);
        }
        for(auto i=0; i<m; i++){
            scanf("%1d",&b[i]);
        }
        int c=0;
        for(auto i=m-1; i>=0; i--){
            if( a[i]+b[i]+c >1){
                ans[i] = a[i]+b[i]+c -2;
                c = 1;
            }else{
                ans[i] = a[i]+b[i]+c;
                c=0;
            }
        }
        for(int i=0; i<m; i++){
            cout<<ans[i];
        }
        cout<<endl;
        n--;
    }
    return 0;
}
