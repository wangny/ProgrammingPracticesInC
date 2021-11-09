#include <stdio.h>
#include <stdlib.h>

using namespace std;

int main()
{
    char a[20];
char* ptra = a;
printf("ptra=%p    a[0]=%p\n",ptra,a);
ptra++;
printf("ptra+1=%p    a[1]=%p\n",ptra,&a[1]);

int b[20];
int* ptrb = b;
printf("ptrb=%p    b[0]=%p\n",ptrb,b);
ptrb++;
printf("ptrb+1=%p    b[1]=%p\n",ptrb,b[1]);
}
