#include <omp.h>
#include <stdlib.h>
#include <stdio.h>
int main(int argc, char argv[]) 
{
	int omp_rank, omp_threads;
	int a[10]={1,1,1,1,1,1,1,1,1,1}; 
	a[0]=1;
	int n =10;
	int i;
	#pragma omp parallel private( i ) shared(a,n)
	{
		#pragma omp for
		for (i=1; i<n; i++) 
		{ 
			omp_rank = omp_get_thread_num();

  			omp_threads = omp_get_num_threads();
			a[i] = 2 * a[i-1]; 
			printf("a[%d] = %d : %d of threads %d\n", i,a[i] ,omp_rank, omp_threads);
		} 

  		
	}
}
