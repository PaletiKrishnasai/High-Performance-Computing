#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <bits/stdc++.h>

#define N 1000

using namespace std;

double a[N][N], b[N][N], c[N][N];
int main()
{
    srand(time(0));

	for(int i=0; i<N; i+=1) 
    {
		for(int j=0; j<N; j+=1) 
        {
			a[i][j] = rand();
			b[i][j] = rand();
		}
	}
    int blocks;
    for(int i=1;i<10;i++)
    {
        blocks = pow(2,i);

        float startTime, endTime, execTime;

        startTime = omp_get_wtime();

        #pragma omp for
        for(int jj=0; jj<N; jj+=blocks) {
            for(int kk=0; kk<N; kk+=blocks) {
                for(int i=0; i<N; i+=1) {
                    for(int j=jj; j<min(jj+blocks, N); j+=1) {
                        double r = 0;
                        for(int k=kk; k<min(kk+blocks, N); k+=1) {
                            r += a[i][k] * b[k][j];
                        }
                        c[i][j] += r;
                    }
                }
            }
        }

        endTime = omp_get_wtime();
        execTime = endTime - startTime;
        cout << "Exec time for " << blocks << " blocks is: " << execTime << endl;
    }
	return 0;
}