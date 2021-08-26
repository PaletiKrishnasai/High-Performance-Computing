#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <time.h>

#define n 100000

int main()
{
	double a[n], random_a;
	double sum=0, privatesum;
	float startTime, endTime,execTime;
	int i;
    srand(time(0));
	startTime = omp_get_wtime();
	#pragma omp parallel private (i,privatesum) shared (a, sum) 
	{
		privatesum=0;
		#pragma omp  for 
		for(i=0;i<n;i++)
		{
			random_a = rand();
			a[i] = i * random_a; 
            for(int j=1;j<n;j++) 	
			privatesum = privatesum + a[i];
		}
		#pragma omp critical		
		{
			sum = sum + privatesum;
		}

	}
	endTime = omp_get_wtime();

	execTime = endTime - startTime;
	printf("%f \n",execTime);
	return(0);
}