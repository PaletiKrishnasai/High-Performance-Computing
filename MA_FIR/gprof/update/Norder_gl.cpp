/*
Author : Paleti Krishnasai CED18I039
Simulation of N-order moving average FIR filter
	N : order of the filter
	n : instance  
	filter equation : output_signal[n] = (input_signal[n-1] + input_signal[n] + input_signal[n1+1]) / (N+1)
*/

// g++ Norder_gl.cpp -O0 -fopenmp -lGL -lGLU -lglut -lGLEW -o Norder_gl


#include <bits/stdc++.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <GL/glut.h>
#include <math.h>
#include <time.h>
#include <omp.h>

using namespace std;

#define N 6 // filter order
#define size 200000 // size of 1-D signal

long double input_signal[size], output_signal[size]; // store in heap

void changeViewPort(int w, int h) 
{
	if(w>=h)
		glViewport(w/2-h/2, 0, h, h);
	else
		glViewport(0, h/2-w/2, w, w);
}

void myinit(void)
{
	glClearColor(0.8,0.8,0.8,0.0);
	glMatrixMode(GL_PROJECTION);
	gluOrtho2D (0.0,200000.0,0.0,10000.0);
	glMatrixMode(GL_MODELVIEW);
}

void filter()
{
    myinit();
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    float startTime, endTime,execTime;
	long double random_input;

	// initialize input signal using random values
	for (int i = 0; i < size; i++)
	{	
		random_input = static_cast <long double> (rand());
		input_signal[i] =random_input;
	}
	startTime = omp_get_wtime();
	// filter equation
	
		output_signal[0] = (input_signal[0] + input_signal[1]) / (N+1); // edge case 1
		for (int i = 1; i < size-1; i++)
		{
			output_signal[i] = (input_signal[i-1] + input_signal[i] + input_signal[i+1]) / (N+1);
                glColor3f(0,0,0);
                glPointSize(3);
                glBegin(GL_POINTS);
                glVertex2f(i,(output_signal[i])/100000);
                glEnd();
                glFlush();
                glutSwapBuffers();
		}
		output_signal[size - 1] = (input_signal[size - 2] + input_signal[size - 1]) / (N+1); // edge case 2

    endTime = omp_get_wtime();
	execTime = endTime - startTime;
	cout << execTime << endl;
    glutLeaveMainLoop();
}


int main (int argc,char** argv)
{
	srand (time(0));

    glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_SINGLE);
	glutInitWindowSize(1000, 1000);
    glutInitWindowPosition(200, 200);
   
    
    glutCreateWindow("CED18I039"); 
    glutDisplayFunc(filter);
    
    
    glutReshapeFunc(changeViewPort);
    GLenum err = glewInit();
	if (GLEW_OK != err) {
		fprintf(stderr, "GLEW error");
		return 1;
	}
	glutMainLoop();


	return 0;
}