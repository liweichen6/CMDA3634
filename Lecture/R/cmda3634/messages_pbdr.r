# File name: messages_rmpi.r
# Description: Round Robin Message Passing (Rmpi)
# Run: Rscript messages_rmpi.r

# Load pbdMPI and initialize the communicator
library(pbdMPI, quiet = TRUE)
init()

# Get rank
myrank <- comm.rank()
# Get from rank
fromrank <- (myrank-1) %% comm.size()
# Get destination rank
torank <- (myrank+1) %% comm.size()

paste("Rank",myrank,"will pass message to rank",torank,".")

# Send a message to the partner
isend(paste("I am rank",myrank),torank)
# Receive the message
recv.msg <- irecv(rank.source=fromrank)
# Wait for messages to complete
wait()

paste("Rank ",myrank," received message '",recv.msg,"'.",sep="")

# Wrap up
finalize()
