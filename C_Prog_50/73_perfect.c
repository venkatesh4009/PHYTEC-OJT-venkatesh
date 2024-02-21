#include<stdio.h>
#include<stdlib.h>
int main(int argc,char *argv[])
{
int sum=0, i;
	if(argc == 2)
	{
		int num=atoi(argv[1]);
		for(i=1;i<=num/2;i++)
		{
			if(num%i == 0)
				sum=sum+i;
		}
		if(num == sum)
			printf("Perfect Number\n");
		else
			printf("Not a perfect number\n");

	}
	else
	{
	printf("Invalid arguments\n");
	printf("Please enter ./perfect number\n");
	}
}
