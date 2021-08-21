#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <time.h>
#define n 100000

int main()
{
	double a[n],b[n], c[n], random_a, random_b;
	float startTime, endTime,execTime;
	int i;
	srand(time(0));

	startTime = omp_get_wtime();
	
		for(i=0;i<n;i++)
		{
			random_a = rand() , random_b = rand();
			a[i] = i * random_a;  	
			b[i] = i * random_b;	
            for(int j=1;j<n;j++)
			c[i] = a[i] + b[i];
		}		
	
	
	endTime = omp_get_wtime();

	execTime = endTime - startTime;
	printf("%f \n",execTime);
	return(0);
}