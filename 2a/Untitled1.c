 #include <stdio.h>

 int main (void)
 {
     float x,y,z;
     char A[4] = {'\0'};
     scanf("%3s", A);
     x = 100*(A[0] - 48) + 10*(A[1] - 48) + (A[2] - 48);
     y = 100*(A[2] - 48) + 10*(A[1] - 48) + (A[0] - 48);
     z = (x + y)/2 ;
     printf("%3.1f", z);
     return 0;
 }
