#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#include "cuda.h"

int main(int argc, char **argv) {
	//Get vector size from command line argument
	int N = atoi(argv[1]);

	//Seed RNG
	double seed = clock();
	srand48(seed);

	double *h_a, *h_b, *h_c; 

	h_a = (double *) malloc(N*sizeof(double));
	h_b = (double *) malloc(N*sizeof(double));
	h_c = (double *) malloc(N*sizeof(double));
 
 	for (int 
 
}
