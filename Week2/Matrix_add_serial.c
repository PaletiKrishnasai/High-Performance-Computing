#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <time.h>

#define size 400

int main()
{
	long double M1[size][size]={1075.75},M2[size][size]={1594.97},M3[size][size];
	float startTime,endTime,execTime;
	int i,j;
	int omp_rank;

	startTime = omp_get_wtime();
	{
		omp_rank = omp_get_thread_num();
		for(i=0;i<250;i++)
		{
			for(j=0;j<250;j++)
			{
                for(int k=0;k<100000;k++)
				    M3[i][j] = M1[i][j] + M2[i][j];
			}
		}
	}
	endTime = omp_get_wtime();

	execTime = endTime-startTime;
	printf("%f \n",execTime);
	return(0);
}