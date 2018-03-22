#include <stdio.h>
#include <stdlib.h>

#include "cuda.h"

//This is my DEVICE function
//__global__ means this function is visible to the host
__global__ void kernelHelloWorld() {
	int thread = threadIdx.x; //Local thread number in a block
	int block = blockIdx.x; //Block number

	printf("Hello World from thread %d of block %d!\n", thread, block);
}

int main(int argc, char** argv) {
	int Nblocks = 10; //Number of blocks
	int Nthreads = 3; //Number of threads per block

	//Run the function "kernelHelloWorld" on the DEVICE
	kernelHelloWorld <<<Nblocks, Nthreads>>> ();

	//Wait for the DEVICE function to complete before moving on
	cudaDeviceSynchronize();

	return 0;
}
