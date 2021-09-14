/*
Author : Paleti Krishnasai CED18I039
Simulation of N-order moving average FIR filter
	N : order of the filter
	n : instance  
	filter equation : output_signal[n] = (input_signal[n-1] + input_signal[n] + input_signal[n11]) / (N+1)
*/

#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <time.h>
//#include <omp.h>

using namespace std;

#define N 6
#define size 200

int main ()
{
	srand (time(0));
	//float startTime, endTime,execTime;
	long double input_signal[size], output_signal[size], random_input;

	// initialize input signal using random values
	for (int i = 0; i < size; i++)
	{	
		random_input = static_cast <long double> (rand());
		input_signal[i] =random_input;
		//input_signal[i] =i*( static_cast <long double> (rand()));
	}
	//startTime = omp_get_wtime();
	// filter equation
	
		output_signal[0] = (input_signal[0] + input_signal[1]) / (N+1); // edge case 1
		for (int i = 1; i < size-1; i++)
		{
			//for(int k=0;k<size;k++)
			output_signal[i] = (input_signal[i-1] + input_signal[i] + input_signal[i+1]) / (N+1);
			output_signal[i] = output_signal[i]/100000;
		}
		output_signal[size - 1] = (input_signal[size - 2] + input_signal[size - 1]) / (N+1); // edge case 2
	
	for (int i = 0; i < size; i++)
	printf("%Lf\n",output_signal[i]);

	//endTime = omp_get_wtime();
	//execTime = endTime - startTime;
	//cout << execTime << endl;

	return 0;
}