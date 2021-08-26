#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <time.h>

#define n 100000

int main()
{
	double a[n], random_a;
	double sum=0;
	float startTime, endTime,execTime;
	int i;
    srand(time(0));
	startTime = omp_get_wtime();
	#pragma omp parallel private (i) shared (a) reduction(+:sum)
	{
		#pragma omp for
		for(i=0;i<n;i++)
		{
			random_a = rand();
			a[i] = i * random_a; 
			for(int j=1;j<n;j++)
			sum = sum + a[i];
		}		
	
	}
	endTime = omp_get_wtime();
	execTime = endTime - startTime;
	printf("%f \n",execTime);
	return(0);
}