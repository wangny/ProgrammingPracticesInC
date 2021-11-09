#include "function.h"

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

HugeInteger HugeInteger::add( const HugeInteger & h) const
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

HugeInteger HugeInteger::add( const std::string & s) const
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
   // subtraction operator; HugeInteger - HugeInteger
HugeInteger HugeInteger::subtract( const HugeInteger & h) const
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

    return tmp;
}
   // HugeInteger - string that represents large integer value
HugeInteger HugeInteger::subtract( const std::string & s) const
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

    return tmp;
}

bool HugeInteger::isGreaterThan( const HugeInteger &  a) const
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

void HugeInteger::output() const
{
    for(auto i=noOfDigits-1; i>=0; i--){
        std::cout << integer[i] ;
    }
    //std::cout << "\n";

}
