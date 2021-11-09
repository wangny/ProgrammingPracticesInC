#include "function.h"
#include <sstream>

HugeInteger::HugeInteger()
{
   for (auto i=0;i<42;i++) {
        integer[i]=0;
   }
   noOfDigits=0;
}

HugeInteger::HugeInteger( const std::string & s )
{
    for(auto i=0;i<s.size();i++ ){
        integer[i]= s[s.size()-1-i]-'0';
    }
    for(auto i=s.size();i<42;i++){
        integer[i]=0;
    }
    noOfDigits=s.size();
}

HugeInteger HugeInteger::operator+ (const HugeInteger& h)const
{
    HugeInteger tmp;
    int carry=0;

    if(noOfDigits>=h.noOfDigits){
        for(auto i=0;i<noOfDigits;i++){
            tmp.integer[i] = integer[i] + h.integer[i] + carry;
            carry=0;
            if( tmp.integer[i] >= 10){
                carry = 1;
                tmp.integer[i]=tmp.integer[i] - 10;
            }else{
                carry=0;
            }
        }
        if(carry==1){
            tmp.integer[noOfDigits] = 1;
            tmp.noOfDigits=noOfDigits+1;
        }else tmp.noOfDigits=noOfDigits;

    }else if(noOfDigits<h.noOfDigits){
        for(auto i=0;i<h.noOfDigits;i++){
            tmp.integer[i]=integer[i]+h.integer[i]+carry;
            if(tmp.integer[i]>=10){
                carry = 1;
                tmp.integer[i]=tmp.integer[i] - 10;
            }else carry=0;
        }
        if(carry==1){
            tmp.integer[h.noOfDigits]=1;
            tmp.noOfDigits=h.noOfDigits+1;
        }else
            tmp.noOfDigits=h.noOfDigits;
    }
    return tmp;
}

HugeInteger HugeInteger::operator+ (const std::string& s)const
{
    HugeInteger tmp;
    int carry=0;

    if(s.size()>=noOfDigits){
        for(auto i=0;i<s.size() ;i++){
            tmp.integer[i]= integer[i] + s[s.size()-1-i]-'0' + carry;
            if(tmp.integer[i]>=10){
                carry = 1;
                tmp.integer[i]=tmp.integer[i] - 10;
            }else carry=0;
        }
        if(carry==1){
            tmp.integer[s.size()]=1;
            tmp.noOfDigits=s.size()+1;
        }else tmp.noOfDigits=s.size();

    }else {
        for(auto i=0;i<s.size();i++){
            tmp.integer[i]= integer[i]+ s[s.size()-1-i]-'0' + carry;
            if(tmp.integer[i]>=10){
                carry = 1;
                tmp.integer[i]=tmp.integer[i] - 10;
            }else carry=0;
        }
        for(auto i=s.size();i<noOfDigits ;i++){
            tmp.integer[i]= integer[i]+ carry;
            if(tmp.integer[i]>=10){
                carry = 1;
                tmp.integer[i]=tmp.integer[i] - 10;
            }else carry=0;
        }
        if(carry==1){
            tmp.integer[noOfDigits]=1;
            tmp.noOfDigits=noOfDigits+1;
        }else tmp.noOfDigits=noOfDigits;
    }

    return tmp;
}

HugeInteger HugeInteger::operator- (const HugeInteger& h)const
{
     HugeInteger tmp;
     int carry=0;

    for(auto i=0;i<noOfDigits;i++){
            if( (integer[i]+carry) <h.integer[i]){
                tmp.integer[i]= integer[i] +10 - h.integer[i] + carry;
                carry=-1;
            }else{
                tmp.integer[i] = integer[i] - h.integer[i] + carry;
                carry = 0;
            }
    }
    tmp.noOfDigits=noOfDigits;
    for(auto i=noOfDigits-1;i>=0;i--){
        if(tmp.integer[i]==0)tmp.noOfDigits--;
        else break;
    }
    if(tmp.noOfDigits<=0){
        tmp.noOfDigits=1;
        tmp.integer[0]=0;
    }

    return tmp;
}

HugeInteger HugeInteger::operator- (const std::string& s)const
{
    HugeInteger tmp;
    int carry=0;
    for(auto i=0;i<s.size();i++){
            if( (integer[i]+carry) < s[s.size()-i-1]-'0'){
                tmp.integer[i]= integer[i] +10 - s[s.size()-i-1]+'0' + carry;
                carry= -1;
            }else{
                tmp.integer[i] = integer[i] - s[s.size()-i-1]+'0' + carry;
                carry = 0;
            }
    }
    for(auto i=s.size();i<noOfDigits ;i++){
            tmp.integer[i]= integer[i] + carry;
            if(tmp.integer[i]<0){
                carry = -1;
                tmp.integer[i]=tmp.integer[i] + 10;
            }else carry=0;
    }

    tmp.noOfDigits=noOfDigits;
    for(auto i=noOfDigits-1;i>=0;i--){
        if(tmp.integer[i]==0)tmp.noOfDigits--;
        else break;
    }
    if(tmp.noOfDigits<=0){
        tmp.noOfDigits=1;
        tmp.integer[0]=0;
    }

    return tmp;

}

HugeInteger HugeInteger::operator* (const HugeInteger& h)const
{
    HugeInteger tmp;
    std::string s;

    if(h.noOfDigits==1 && h.integer[0]==0){
        tmp=h;
        return tmp;
    }else if(noOfDigits==1 && integer[0]==0){
        tmp=*this;
        return tmp;
    }

    for(auto i=0;i<h.noOfDigits;i++){
        for(auto j=0;j<noOfDigits;j++){
            auto t = h.integer[i]*integer[j];
            s.clear();
            s.push_back(t/10+'0');
            s.push_back(t%10+'0');
            for(auto k=1;k<=i+j;k++){
                s.push_back('0');
            }
            tmp = tmp + s;

        }
    }
    for(auto i=41; i>=0;i--){
        if(tmp.integer[i]>0){
            tmp.noOfDigits=i+1;
            break;
        }
    }

    return tmp;
}

HugeInteger HugeInteger::operator* (const std::string& s)const
{
    HugeInteger tmp;
    std::string l;

    if(s.size()==1 && s[0]=='0'){
        tmp=s;
        return tmp;
    }else if(noOfDigits==1 && integer[0]==0){
        tmp=*this;
        return tmp;
    }


    for(auto i=0;i<s.size();i++){
        for(auto j=0;j<noOfDigits;j++){
            auto t = (s[s.size()-1-i]-'0')*integer[j];
            l.clear();
            l.push_back(t/10+'0');
            l.push_back(t%10+'0');
            for(auto k=1;k<=i+j;k++){
                l.push_back('0');
            }
            tmp=tmp+l;
        }
    }
    for(auto i=41; i>=0;i--){
        if(tmp.integer[i]!=0){
            tmp.noOfDigits=i+1;
            break;
        }
    }
    return tmp;
}

HugeInteger HugeInteger::operator/ (const HugeInteger&h)const
{
    HugeInteger tmp;
    std::string ans;
    int cont=noOfDigits-h.noOfDigits;

    if(h.noOfDigits==1 && h.integer[0]==0){
        tmp=h;
        return tmp;
    }else if(noOfDigits==1 && integer[0]==0){
        tmp=*this;
        return tmp;
    }

    for(auto i=noOfDigits-1, j=0; i>=noOfDigits-h.noOfDigits; i--,j++){
        tmp.integer[h.noOfDigits-1-j]=integer[i];
    }
    tmp.noOfDigits=h.noOfDigits;

    while(cont>=0){
        for(auto i=9;i>=0;i--){
            std::string c;
            c.push_back(i+'0');

            if(!(h*c>tmp)){
                tmp=tmp-(h*c);
                ans.push_back(i+'0');
                //std::cout<<"ans "<<ans<<std::endl;
                break;
            }
            if(i==0)ans.push_back('0');
        }

        for(auto i=tmp.noOfDigits-1;i>=0;i--){
            tmp.integer[i+1]=tmp.integer[i];
        }

        cont--;
        tmp.integer[0]=integer[cont];
        //std::cout<<"tmp "<<tmp<<std::endl;
        if(tmp.integer[tmp.noOfDigits]!=0)tmp.noOfDigits=tmp.noOfDigits+1;
    }

    HugeInteger x (ans);
    for(auto i=41; i>=0;i--){
        if(x.integer[i]!=0){
            x.noOfDigits=i+1;
            break;
        }
    }

    return x;
}

HugeInteger HugeInteger::operator/ (const std::string& l)const
{
    HugeInteger tmp;
    HugeInteger h (l);
    std::string ans;
    int cont=noOfDigits-h.noOfDigits;

    if(l.size()==1 && l[0]=='0'){
        tmp=l;
        return tmp;
    }else if(noOfDigits==1 && integer[0]==0){
        tmp=*this;
        return tmp;
    }

    for(auto i=noOfDigits-1, j=0; i>=noOfDigits-h.noOfDigits; i--,j++){
        tmp.integer[h.noOfDigits-1-j]=integer[i];
    }
    tmp.noOfDigits=h.noOfDigits;

    while(cont>=0){
    for(auto i=9;i>=0;i--){
        std::string c;
        c.push_back(i+'0');

        if(!(h*c>tmp)){
            tmp=tmp-(h*c);
            ans.push_back(i+'0');
            //std::cout<<"ans "<<ans<<std::endl;
            break;
        }
        //if(i==0)ans.push_back('0');

    }
    for(auto i=tmp.noOfDigits-1;i>=0;i--){
        tmp.integer[i+1]=tmp.integer[i];
    }
    cont--;
    tmp.integer[0]=integer[cont];
    if(tmp.integer[tmp.noOfDigits]!=0)tmp.noOfDigits=tmp.noOfDigits+1;
    }

    HugeInteger x (ans);
    for(auto i=41; i>=0;i--){
        if(x.integer[i]!=0){
            x.noOfDigits=i+1;
            break;
        }
    }

    return x;
}

bool HugeInteger::operator> (const HugeInteger& a)const
{
    if(noOfDigits > a.noOfDigits)
        return true;
    else if(noOfDigits < a.noOfDigits)
        return false;
    else
    {
        for(int i = 41 ; i >= 0 ; i--)
        {
            if(integer[i] > a.integer[i])
                return true;
            else if(integer[i] == a.integer[i])
                continue;
            else
                break;
        }
        return false;
    }
}

std::ostream& operator<< (std::ostream& os,const HugeInteger& h)
{
    for(auto i = h.noOfDigits-1 ; i>=0 ; i--){
        os << h.integer[i];
    }
    return os;
}
