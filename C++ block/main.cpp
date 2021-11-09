#include "function.h"
#include <iostream>

int main()
{
    Block b{4, "@OOX" "OOXX" "XXXX" "XXXX"}; // create a 4x4 pattern
    std::cout << b << std::endl;

    Block c; // default constructor
    c = b;   // using 'copy assignment'
    std::cout << c << std::endl;

    b.clockwise90(); // rotation of 90 degrees clockwise
    std::cout << b << std::endl;

    b.clockwise90(); // rotating again
    std::cout << b << std::endl;


    Block d; // default constructor
    d = Block{4, "0123" "4567" "8910" "1112"}; // move assignment
    std::cout << d << std::endl;

    d.doublesize(); // scaling 4x4 => 8x8
    std::cout << d << std::endl;

    if (equal(c, b)) // checking if two patterns are equivalent under rotation
        std::cout << "EQUAL" << std::endl;
    else
        std::cout << "DIFFERENT" << std::endl;

}
