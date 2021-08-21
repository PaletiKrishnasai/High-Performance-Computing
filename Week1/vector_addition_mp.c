#include <stdio.h>
#include<time.h>
#include <omp.h>
#include<stdlib.h>
#define n 100000
#define m 100000
int main()
{
double a[n],b[n], c[n];
float startTime, endTime,execTime;
int i,k;
int omp_rank;
float rtime[20];
int thread[]={1,2,4,6,8,10,12,16,20,32,64,128,150};
int thread_arr_size=13;
for(k=0;k<thread_arr_size;k++)
{
omp_set_num_threads(thread[k]);
startTime = omp_get_wtime();
#pragma omp parallel private (i) shared (a,b,c)
{
#pragma omp for
for(i=0;i<n;i++)
{
omp_rank = omp_get_thread_num();
a[i] = i * 10.236 ; // Use Random function and assign a[i]
b[i] = i * 152.123; // Use Random function and assign b[i]
for(int j=0;j<m;j++)
c[i] = a[i] + b[i];

// printf("The value of a[%d] = %lf and b[%d] = %lf and result c[%d] =%lf done by worker Thread ID = %d\n", i, a[i], i, b[i], i, c[i], omp_rank);

}
}
endTime = omp_get_wtime();

execTime = endTime - startTime;
rtime[k]=execTime;
}
for (k=0;k<thread_arr_size;k++)
printf("\nThread=%d\t rtime=%f\n",thread[k],rtime[k]);
return(0);
}