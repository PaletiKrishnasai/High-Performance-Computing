/*
Author : Paleti Krishnasai CED18I039

Parallelize the following sequence and write openMP and estimate parallelization fraction for
the sequence’s larger number 100000. Write your comments on each problem.

2. Sequence 1*sin a, 3*sin b, 6*sin c, 10*sin d, 15*sin a, 21*sin b, 28*sin c, 36*sin d, 45*sin a, ..
    Where a, b, c, d follows following sequence 0, 30, 60 and 90 respectively.
*/

// g++ -O0 -fopenmp Q2.cpp -o Q2

#include <bits/stdc++.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <math.h>
#include <time.h>
#include <omp.h>
using namespace std;
#define n 1000001
double sequence[n];
double sin_values[4] = {0,0.5,0.866025404,1};

int main()
{
    float startTime, endTime,execTime;
    int i;
    srand(time(0));
	startTime = omp_get_wtime();
	#pragma omp parallel private (i)
    {
        #pragma omp for
        for(i=0;i<100000;i++)
        {
            
            sequence[i] =  0; //0.5*((i*i)+i) * sin[a]
            i++;
            sequence[i] = 0.5*((i*i)+i) * 0.5;
            i++;
            sequence[i] = 0.5*((i*i)+i) * 0.866025404;
            i++;
            sequence[i] = 0.5*((i*i)+i) * 1;
        }
    }
    endTime = omp_get_wtime();
	execTime = endTime - startTime;
    for(i=0;i<100000;i++)
    cout<<sequence[i]<<endl;
    cout<<"time "<<execTime<<endl;
    return(0); 
}