#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "mpi.h"

void myMPI_Bcast(int *N, int root) {
	int rank, size;
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);

	//Every rank other than rank sender receives
	if (rank != root) {
		MPI_Status status;
		int tag = 1;
		int sourceRank = rank - 1; //Receive from previous rank
		if (rank == 0) sourceRank = size - 1; //Careful of rank 0

		MPI_Recv(N, //Pointer to int
				1,
				MPI_INT,
				sourceRank,
				tag,
				MPI_COMM_WORLD,
				&status);
	}

	int prev = root - 1;
	if (root == 0) prev = size - 1;

	if (rank != prev) {
		int tag = 1;
		int destRank = rank + 1;
		if (rank == size - 1) destRank = 0;

		MPI_Send(N,
				1,
				MPI_INT,
				destRank,
				tag,
				MPI_COMM_WORLD);
	}
}

//This acts as a barrier
//No process can leave this function unless all processes have made it here
void myMPI_Barrier() {
	int rank, size;
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);

	int N;

	if (rank == 0) N = 1; //Only rank 0 fills a value
	myMPI_Bcast(&N, 0);

	if (rank = size - 1) N = 10;
	myMPI_Bcast(&N, size - 1);
}

int main(int argc, char **argv) {
	MPI_Init(&argc, &argv);

	int rank, size;
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);

	int N;

	if (rank == 0) N = 199; //Only rank 0 fills a value
	myMPI_Bcast(&N, 0);
	printf("Rank %d received the value N = %d\n", rank, N);

	if (rank = size - 1) N = 10;
	myMPI_Bcast(&N, size - 1);
	printf("Rank %d received the value N = %d\n", rank, N);

	myMPI_Barrier();

	MPI_Finalize();
	return 0;
}
