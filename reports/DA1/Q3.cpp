/*
Author : Paleti Krishnasai CED18I039

Parallelize the following sequence and write openMP and estimate parallelization fraction for
the sequence’s larger number 100000. Write your comments on each problem.

3. Sequence 8,4√2,4,2√2 - using pow()
*/

// g++ -O0 -fopenmp Q3.cpp -o Q3

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
            sequence[i] =256*pow(0.707106781,i); 
        }
    }
    endTime = omp_get_wtime();
	execTime = endTime - startTime;
    for(i=0;i<100000;i++)
    cout<<sequence[i]<<endl;
    cout<<"time "<<execTime<<endl;
    return(0); 
}