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

	if (rank == 0) {
		int N = 10;
		int destRank = 1;
		int tag = 1;
		MPI_Request reqs;
		MPI_Status status;

		int *sendData = (int *) malloc(N*sizeof(int));

		for (int n = 0; n < N; n++) sendData[n] = 2 * n;

		//Issue a send request
		MPI_Isend(&N, //Pointer to the data we're sending
				1,	//Number of entries to send
				MPI_INT, //Type of each entry
				destRank, //Rank of destination
				tag, //Tags the message with an identifier
				MPI_COMM_WORLD, //Flag to full MPI network
				&reqs + 0);

		tag = 2; //New tag
		//Issue a send request
		MPI_Isend(&N, //Pointer to the data we're sending
				1,	//Number of entries to send
				MPI_INT, //Type of each entry
				destRank, //Rank of destination
				tag, //Tags the message with an identifier
				MPI_COMM_WORLD, //Flag to full MPI network
				&reqs + 1);

		//Wait for the request to compete before proceeding
		MPI_Wait(&reqs, &status);
	}
	else if (rank == 1) {
		int N;
		int sourceRank = 0;
		int tag = 1;
		MPI_Request reqs;
		MPI_Status status;

		MPI_Irecv(&N, //Pointer to where to put data
				1, //Number of entries
				MPI_INT, //Data type
				sourceRank, //Rank of sender
				tag, //Message tag
				MPI_COMM_WORLD,
				&res + 0);
		//Wait for the request to compete before proceeding
		MPI_Wait(&reqs, &status);

		printf("Rank %d received a message from rank %d: value = %d\n", rank, sourceRank, N);
	}

	//All MPI program must end with a finalize
	MPI_Finalize();
	return 0;
}
