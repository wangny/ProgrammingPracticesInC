#include <stdio.h>

int findlcm(int n, int cur);
int x[20];

int main(void)
{
	int n,i,j,a=0,b,gcd=0;
	scanf("%d",&n);
	n = n*2;
	for(i=0;i<n;i++){
		scanf("%d",&x[i]);
	}
	b = findlcm(n,1);
	for(i=1;i<n;i=i+2){
		j = b/x[i];
		x[i] = b;
		x[i-1] = x[i-1]*j;
		a = a+x[i-1];
	}
	i=1;
	while( (i<=a) && (i<=b) ){
        	if( (a%i==0) && (b%i==0) ){
                	gcd=i;}
        i++;
    	}
	a = a/gcd;
	b = b/gcd;
	printf("%d %d\n",a,b);


	return 0;
}

int findlcm(int n,int cur)
{
	int lcm,i=1,done,j;

	done = 0;
	if(cur >= (n-2)){
		done = 1;
		return x[cur];
    }
	while(!done){
        	if( (i%x[cur]==0) && (i%x[cur+2]==0) ){
            		lcm=i;
			break;
            	}
        i++;
    	}
        j = lcm/x[cur+2];
	x[cur+2] = lcm;
	x[cur+1] = x[cur+1]*j;
	cur = cur+2;
	lcm = findlcm(n,cur);

	return lcm;
}
