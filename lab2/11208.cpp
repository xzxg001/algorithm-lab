#include<stdio.h>
#include<math.h>
int n;
int fib[40];
int cci[15010];
double x=log10(1.0/sqrt(5.0));
double y=log10((1.0+sqrt(5.0))/2.0);
int main()
{
	int i;
	fib[0]=0;
	fib[1]=1;
	cci[0]=0;
	cci[1]=1;
	for(i=2;i<40;i++)
	   fib[i]=fib[i-1]+fib[i-2];
	for(i=2;i<=15000;i++)
	{
		cci[i]=cci[i-1]+cci[i-2];
		if(cci[i]>=10000)//只需要后四位 
		 cci[i]%=10000; 
	}
	while(scanf("%d",&n)!=EOF)
	{
		if(n<40)
		{
			printf("%d\n",fib[n]);
			continue;
		}
		  
		double res;
		 res=x+n*y;
		 res-=(int)res;
		 res=pow(10,res)*1000;
		 printf("%d...%0.4d\n",(int)res,cci[n%15000]);//1500是一个循环周期 
	}                                     //输出时可能不足四位，注意补 0 
return 0; 
}