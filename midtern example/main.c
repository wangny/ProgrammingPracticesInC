#include <stdio.h>

int main()
{
    float a,b,x,y;

    scanf("y=%f x %f\n",&a,&b);

    scanf("x= %f",&x);

    y = a*x + b;
    printf("y= %.5f",y);


    return 0;
}
