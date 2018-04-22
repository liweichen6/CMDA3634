#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <time.h>

#include "cuda.h"
#include "functions.c"

/* Q4 Make the search for the secret key parallel on the GPU using CUDA. */

//compute a*b mod p safely
__device__ unsigned int kmodprod(unsigned int a, unsigned int b, unsigned int p) {
    unsigned int za = a;
    unsigned int ab = 0;
    
    while (b > 0) {
        if (b%2 == 1) ab = (ab +  za) % p;
        za = (2 * za) % p;
        b /= 2;
    }
    return ab;
}

 //compute a^b mod p safely
__device__ unsigned int kmodExp(unsigned int a, unsigned int b, unsigned int p) {
    unsigned int z = a;
    unsigned int aExpb = 1;
    
    while (b > 0) {
        if (b%2 == 1) aExpb = kmodprod(aExpb, z, p);
        z = kmodprod(z, z, p);
        b /= 2;
    }
    return aExpb;
}

__global__ void kernelCompare(unsigned int *p, unsigned int *g, unsigned int *h, unsigned int *x) {
  unsigned int threadId = threadIdx.x;
  unsigned int blockId = blockIdx.x;
  unsigned int nBlock = blockDim.x;

  unsigned int id = threadId + blockId * nBlock;

  if (id < *p - 1) {
    if (kmodExp(*g, id + 1, *p) == *h) {
      *x = id + 1;
      printf("Secret key found! x = %u \n", *x);
    }
  }
}

int main (int argc, char **argv) {

  /* Part 2. Start this program by first copying the contents of the main function from 
     your completed decrypt.c main function. */

  //declare storage for an ElGamal cryptosytem
  unsigned int n, p, g, h, x;
  unsigned int Nints;

  //get the secret key from the user
  printf("Enter the secret key (0 if unknown): "); fflush(stdout);
  char stat = scanf("%u",&x);

  printf("Reading file.\n");

  /* Q3 Complete this function. Read in the public key data from public_key.txt
    and the cyphertexts from messages.txt. */
  FILE *pkey = fopen("public_key.txt", "r");
  FILE *mes = fopen("message.txt", "r");

  fscanf(pkey, "%u%u%u%u", &n, &p, &g, &h);
  fscanf(mes, "%u", &Nints);

  unsigned int *Zmessage = (unsigned int *) malloc(Nints * sizeof(unsigned int));
  unsigned int *a = (unsigned int *) malloc(Nints * sizeof(unsigned int));

  for (unsigned int i = 0; i < Nints; i++) {
    fscanf(mes, "%u %u\n", &Zmessage[i], &a[i]);
  }

  fclose(pkey);
  fclose(mes);

  // find the secret key
  if (x==0 || modExp(g,x,p)!=h) {
    printf("Finding the secret key...\n");
    double startTime = clock();
    
    unsigned int *d_p, *d_g, *d_h, *d_x;
    
    cudaMalloc(&d_p, sizeof(unsigned int));
    cudaMalloc(&d_g, sizeof(unsigned int));
    cudaMalloc(&d_h, sizeof(unsigned int));
    cudaMalloc(&d_x, sizeof(unsigned int));
    
    cudaMemcpy(d_p, &p, sizeof(unsigned int), cudaMemcpyHostToDevice);
    cudaMemcpy(d_g, &g, sizeof(unsigned int), cudaMemcpyHostToDevice);
    cudaMemcpy(d_h, &h, sizeof(unsigned int), cudaMemcpyHostToDevice);

    int Nthreads = 1024;
    int Nblocks = (p + Nthreads - 2)/Nthreads;
    kernelCompare<<<Nblocks, Nthreads>>>(d_p, d_g, d_h, d_x);

    cudaDeviceSynchronize();
    cudaMemcpy(&x, d_x, sizeof(unsigned int), cudaMemcpyDeviceToHost);

    cudaFree(d_p);
    cudaFree(d_g);
    cudaFree(d_h);
    cudaFree(d_x);
    
    double endTime = clock();

    double totalTime = (endTime-startTime)/CLOCKS_PER_SEC;
    double work = (double) p;
    double throughput = work/totalTime;

    printf("Searching all keys took %g seconds, throughput was %g values tested per second.\n", totalTime, throughput);
  }

  /* Q3 After finding the secret key, decrypt the message */
  int bufferSize = 1024;
  unsigned char *message = (unsigned char *) malloc(bufferSize * sizeof(unsigned char));

  ElGamalDecrypt(Zmessage, a, Nints, p, x);
  convertZToString(Zmessage, Nints, message, Nints * (n - 1) / 8);
  printf("%s\n", message);
  
  return 0;
}
