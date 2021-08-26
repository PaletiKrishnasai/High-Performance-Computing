#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define n 200000

int main()
{
	double a[n],b[n], sum=0.0,random_a,random_b;
	float startTime, endTime,execTime;
	int i;
	srand(time(0));
	startTime = omp_get_wtime();
	{	
		for(i=0;i<n;i++)
		{	random_a = rand();
            random_b = rand();
			a[i] = i * random_a;  	
			b[i] = i * random_b;
            for(int j=0;j<n;j++)	
			sum = sum + a[i] * b[i];
		}		
	}
	endTime = omp_get_wtime();

	execTime = endTime - startTime;
	printf("%f \n",execTime);
	return(0);
}