#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <time.h>

#define n 200000

int main()
{
	double a[n],b[n], privatesum, sum=0.0,random_a,random_b;
	float startTime, endTime,execTime;
	int i;
	srand(time(0));
	startTime = omp_get_wtime();
	#pragma omp parallel private (i,privatesum) shared (a,b, sum)
	{	
		privatesum=0;
		#pragma omp for
		for(i=0;i<n;i++)
		{	random_a = rand();
            random_b = rand();
			a[i] = i * random_a;  	
			b[i] = i * random_b;
            for(int j=0;j<n;j++)	
			privatesum = privatesum + a[i] * b[i];
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