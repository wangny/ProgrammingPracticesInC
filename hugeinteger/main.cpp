#include<stdio.h>
#include "function.h"
int main()
{

    char c[2], a[42], b[42];
    HugeInteger n3,n4;
    while ( scanf("%s%s%s", &c, &a, &b) != EOF ) {
            if(c[0] == '+'){
                HugeInteger n1(a);
                //n1.output();
                HugeInteger n2(b);
                //n1.output();
                n3 = n1.add(n2);
                n4 = n1.add(b);
                n3.output();printf("\n");
                n4.output();printf("\n");
            }
            else if(c[0] == '-'){

                HugeInteger n1(a);
                HugeInteger n2(b);
                n3 = n1.subtract(n2);
                n4 = n1.subtract(b);
                n3.output();printf("\n");
                n4.output();printf("\n");
            }
            else if (c[0] == '>'){

           HugeInteger n1(a);
           HugeInteger n2(b);
           if(n1.isGreaterThan(n2)) printf("1");
           else printf("0");
           printf("\n");

                }
                else{
            printf("ERROR");
            return 0;
                }
        }
    return 0;
}
