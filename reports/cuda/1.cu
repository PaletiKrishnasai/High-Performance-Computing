#include <stdio.h>
#include <stdlib.h>
#include<stdlib.h>
#include<time.h>
#include<math.h>
 
#define n_size 100000
 
__global__ void add(float *a, float *b, float *c) {
 int index=threadIdx.x+blockIdx.x*blockDim.x;
 c[index]=a[index]+b[index];
}
 
void random_init(float a[],int ch)
{
   srand(time(NULL));
   if(ch==0)
   {
       for(int i=0;i<n_size;i++)
       {
           a[i]=((float)rand()/(float)(RAND_MAX)) * 5.0;
       }
   }
   else
   {
       for(int i=0;i<n_size;i++)
       {
             a[i]=(i+1);
       }
   }
  
}
 
int main() {
  
float a[n_size], b[n_size],c[n_size];
cudaEvent_t start, end;
 
// host copies of variables a, b & c
float *d_a, *d_b, *d_c;
 
// device copies of variables a, b & c
int size = n_size*sizeof(float);
 
// Allocate space for device copies of a, b, c
cudaMalloc((void **)&d_a, size);
cudaMalloc((void **)&d_b, size);
cudaMalloc((void **)&d_c, size);
 
// Create Event for time
cudaEventCreate(&start);
cudaEventCreate(&end);
 
 
// Setup input values 
random_init(a,0);
random_init(b,0);
 
 
 
// Copy inputs to device
cudaMemcpy(d_a, &a, size, cudaMemcpyHostToDevice);
cudaMemcpy(d_b, &b, size, cudaMemcpyHostToDevice);
int Thread[]={1,2,4,6,8,10,12,16,20,32,64,128,150};
int thread_arr_size=13;
 
for(int i=0;i<thread_arr_size;i++)
{
       int Threads=Thread[i];
       cudaEventRecord(start);
 
       // Launch add() kernel on GPU
       add<<<n_size/Threads,Threads>>>(d_a, d_b, d_c);
 
       cudaEventRecord(end);
       cudaEventSynchronize(end);
 
       float time = 0;
       cudaEventElapsedTime(&time, start, end);
 
       // Copy result back to host
       cudaError err = cudaMemcpy(&c, d_c, size, cudaMemcpyDeviceToHost);
       if(err!=cudaSuccess) {
           printf("CUDA error copying to Host: %s\n", cudaGetErrorString(err));
       }
           int flag=0;
       for(int i=0;i<n_size;i++)
       {
           if(c[i]!=(a[i]+b[i]))
           { 
               flag=1;
           break;
           }
       }
       if(flag==0)
       {
           printf("Program Executed as Expected\n");
           printf("Time Taken by the program for %d Threads=%f\n",Threads,time);
       }
       else
       {
           printf("Vector Addition hasnt been done properly,Mismatch in Values!!!\n");
       }
      
 
}
 
// Cleanup
cudaFree(d_a);
cudaFree(d_b);
cudaFree(d_c);
return 0;
}
 
