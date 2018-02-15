#include "mympi.h"

//Compute the global sum of all the values in val across all MPI ranks
float MPI_Reduction(float val) {
	float sum = 0;
	float recvBuffer; //Space for incoming values
	int rank, size;
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);

	//Start with all ranks active
	int Nactive = size;

	while (Nactive > 1) {
		if (rank >= (Nactive + 1) / 2) {
			//MPI_Send to rank - Nactive / 2
			int destRank = rank - Nactive / 2;
			int tag = Nactive;

			MPI_Send(&val, 1, MPI_FLOAT, destRank, tag, MPI_COMM_WORLD);
		}
		if (rank < (Nactive + 1) / 2) {
			//MPI_Recv from rank + Nactive / 2
			int sourceRank = rank + Nactive / 2;
			int tag = Nactive;
			MPI_Status status;

			MPI_Recv(&recvBuffer, 1, MPI_FLOAT, sourceRank, tag, MPI_COMM_WORLD, status);

			//Add the received value to the sum
			sum += recvBuffer;
		}

		//Only half the ranks are active next time
		Nactive = (Nactive + 1) / 2;
	}
}
