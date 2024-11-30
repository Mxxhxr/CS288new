#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

#define FROM_MASTER 1
#define FROM_WORKER 2

int main(int argc, char *argv[])
{
    int numtasks, numworkers, taskid, rows;
    double a[N][N], b[N], [N], c[N][N];
    // the idea is that the root process will intitiliaze thje matrices and send the data to worker processes
    // the worker porocesses will compute and send the result back to the root process.

    MPI_Init(&argc, &argv);
    MPI_Status status;
    MPI_Comm_rank(MPI_COMM_WORLD, &taskid);
    MPI_Comm_size(MPI_COMM_WORLD, &numtasks);

    // caluclaute the number fo worker tasks
    numworkers = numtasks - 1;
    // calculate the number of rows that each process will work
    rows = N / numworkers;

    if (taskid == 0)
    { // if root process
        // init the matrices
        for (int i = 0; i < N; i++)
        {
            for (int j = 0; j < N; j++)
            {
                a[i][j] = i + j;
                b[i][j] = i * j;
            }
        }
        for (int dest = 1; dest <= numworkers; dest++)
        {
            MPI_Send(&a[(dest - 1) * rows][0], rows * N, MPI_DOUBLE, dest, FROM_MASTER, MPI_COMM_WORLD);
            MPI_Send(&b, N * N, MPI_DOUBLE, dest, FROM_MASTER, MPI_COMM_WORLD);
        }
    }

    if (taskid > 0)
    {
        // recieve the data from root/master process
        for (int src = 1; src <= numworkers; src++)
        {
            MPI_Recv(&a, rows * N, MPI_DOUBLE, 0, FROM_MASTER, MPI_COMM_WORLD, &status);
            MPI_Recv(&b, N * N, MPI_DOUBLE, 0, FROM_MASTER, MPI_COMM_WORLD, &status);
        }
    }
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < N; j++)
        {
            for (int k = 0; k < N; k++)
            {
                c[i][j] += a[i][k] * b[j][k];
            }
        }
    }

    MPI_Send(&c, rows * N, MPI_DOUBLE, 0, FROM_WORKER, MPI_COMM_WORLD);
    MPI_Finalize();
}