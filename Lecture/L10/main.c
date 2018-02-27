#include "mympi.h"

int main (int argc, char **argv) {

  MPI_Init(&argc,&argv);

  int rank,size;
  MPI_Comm_rank(MPI_COMM_WORLD,&rank);
  MPI_Comm_size(MPI_COMM_WORLD,&size);

  int N;

  if (rank==0) N=199;

  //This is the actual MPI broadcast function
  MPI_Bcast(&N,               //Pointer to data
            1,                //Count (number of entries)
            MPI_INT,          //Data type
            0,                //Root process (the process that broadcasts)
            MPI_COMM_WORLD);

  printf("Rank %d recieved the value N = %d\n",rank,N);

  if (rank==size-1) N=10;

  MPI_Bcast(&N,               //Pointer to data
            1,                //Count (number of entries)
            MPI_INT,          //Data type
            0,                //Root process (the process that broadcasts)
            MPI_COMM_WORLD);

  printf("Rank %d recieved the value N = %d\n",rank,N);

  //MPI's barrier
  MPI_Barrier(MPI_COMM_WORLD);

  //setup a test for the reduction
  float val = 1.0;

  //MPI's reduce function
  MPI_Reduce(&val, //Send buffer
             &sum,  //Receive buffer
             1  //Count (number of entries)
             MPI_INT, //Data type
             MPI_SUM,//Operation - others are MPI_MIN< MPI_MAX:
             MPI_COMM_WORLD)

  float sum = MPI_(val);

  for (int r=0;r<size;r++) {
    if (r==rank) {
      printf("Rank %d has value %f after the reduction.\n", rank, sum);
    }
    myMPI_Barrier(); 
  }

  MPI_Finalize();
  return 0;
}
