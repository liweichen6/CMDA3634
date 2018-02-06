#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include "mpi.h"

int main(int argc, char** argv) {
	//Every MPI program must start with an initialize
	//Always do this first
	MPI_Init(&argc, &argv);

	int rank, size;
	MPI_Comm_rank(MPI_COMM_WORLD, //This tells MPI to get the rank of this process globally 
			&rank); //Store the result in rank
	MPI_Comm_size(MPI_COMM_WORLD, //This tells MPI to get the size of this process globally 
			&size); //Store the result in size

	if (rank < 5) printf("Hello World from rank %d of %d!\n", rank, size);
	else printf("Hello again from rank %d of %d!\n", rank, size);

	//All MPI program must end with a finalize
	MPI_Finalize();
	return 0;
}
