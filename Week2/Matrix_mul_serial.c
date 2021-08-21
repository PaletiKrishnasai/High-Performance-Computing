//row major matrix multiplication
 
#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <time.h>

#define n 350

int main()
{
	int i,j;
	double M1[n][n]={984.46},M2[n][n]={634.52},M3[n][n];
	float startTime, endTime, execTime;
	int omp_rank;

	startTime = omp_get_wtime();
	{
		for(i=0 ; i< n ; i++)
		{	
			omp_rank = omp_get_thread_num();
			for(j=0 ; j< n ;j++)
			{	
				M1[i][j] = 0;
				for(int k=0;k< n; k++)
				{
                    for(int k=0;k<100;k++)
					M3[i][j] = M3[i][j] + M1[i][k] * M2[k][j];
				}
			}
		}
	}

	endTime = omp_get_wtime();
	execTime = endTime - startTime;
	printf("%f \n",execTime);
	return(0);
}