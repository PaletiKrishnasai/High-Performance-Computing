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
	int omp_rank;
	srand(time(0));

	startTime = omp_get_wtime();
	#pragma omp parallel private (i) shared (a,b,c)
	{
		#pragma omp for	
		for(i=0;i<n;i++)
		{
			random_a = rand() , random_b = rand();
			omp_rank = omp_get_thread_num();
			a[i] = i * random_a;  	
			b[i] = i * random_b;	
            for(int j=1;j<n;j++)
			c[i] = a[i] + b[i];
			//printf("The value of a[%d] = %lf and b[%d] = %lf and result c[%d] = %lf  Thread rank = %d\n", i, a[i], i, b[i], i, c[i], omp_rank);
		}		
	
	}
	endTime = omp_get_wtime();

	execTime = endTime - startTime;
	printf("%f \n",execTime);
	return(0);
}