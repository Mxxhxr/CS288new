#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
// uses MPI compiler mpicc filename
// run by mpirun -n 4(procceses)
int main(int argc, char *argv[])
{
    // initiliaze the MPI environment
    MPI_Init(&argc, &argv);

    int rank;
    // get the rank for each process aka ID
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    // MPI_COMM_rank refers to the group of the processes in our program

    // get the # of processes
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    // print the rank and size
    printf("I'm %d of %d\n", rank, size);

    // exit the MPI environment
    MPI_Finalize();
}