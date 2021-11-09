#include <iostream>

using namespace std;

unsigned long long gcd(unsigned long long a, unsigned long long b)
{
    a = a%b;
    if(a==0) return b;
    else return  gcd(b,a);
}


int main()
{
    int n;
    while(cin >> n){

        unsigned long long a=0, b=1;
        while(n>0){
            unsigned long long c,d;
            cin>>c;
            cin>>d;

            a = a*d + c*b;
            b = b*d;

            unsigned long long i = gcd(a,b);
            a=a/i;
            b=b/i;

            n--;
        }
        cout<<a<<"/"<<b<<endl;
    }
    return 0;
}
