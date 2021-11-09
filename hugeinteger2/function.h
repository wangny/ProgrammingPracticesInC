#ifndef HUGEINTEGER_H
#define HUGEINTEGER_H
#include <iostream>
#include <string>
class HugeInteger
{
    friend std::ostream &operator<<( std::ostream &, const HugeInteger & );
public:
    HugeInteger();

    HugeInteger( const std::string &);

    HugeInteger operator+ (const HugeInteger&) const;

    HugeInteger operator+ (const std::string&) const;

    HugeInteger operator- (const HugeInteger&) const;

    HugeInteger operator- (const std::string&) const;

    HugeInteger operator* (const HugeInteger&) const;

    HugeInteger operator* (const std::string&) const;

    HugeInteger operator/ (const HugeInteger&) const;

    HugeInteger operator/ (const std::string&) const;

    bool operator> (const HugeInteger&) const;

    //std::ostream& operator<< (std::ostream&, const HugeInteger&);

private:
   int integer[42];
   int noOfDigits;
 };
#endif
