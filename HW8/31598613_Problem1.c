// #include "../../../../usr/lib/x86_64-linux-gnu/openmpi/include/mpi.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mpi.h>

int main(int argc, char** argv) {
    int rank, size;
    MPI_Init(&argc, &argv);

    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    size_t readNum, writeNum;
    char fname[100];
    int *buffer = NULL;
    int numInts = 0;

    if (rank == 0) {
        printf("Enter the file name:\n");
        scanf("%s", fname);

        FILE *f = fopen(fname, "rb");
        if (f == NULL) {
            printf("An error occurred trying to open the file.\n");
            MPI_Abort(MPI_COMM_WORLD, 1);
        }

        fseek(f, 0, SEEK_END);
        long fsize = ftell(f);
        rewind(f);

        numInts = fsize / sizeof(int);
        printf("Contains %d integers\n", numInts);

        buffer = (int*)malloc(numInts * sizeof(int));
        if (buffer == NULL) {
            printf("An error occurred trying to allocate memory.\n");
            fclose(f);
            MPI_Abort(MPI_COMM_WORLD, 1);
        }

        readNum = fread(buffer, sizeof(int), numInts, f);
        if (readNum != numInts) {
            printf("An error occurred reading the file.\n");
            fclose(f);
            free(buffer);
            MPI_Abort(MPI_COMM_WORLD, 1);
        }
        fclose(f);
    }

    MPI_Bcast(&numInts, 1, MPI_INT, 0, MPI_COMM_WORLD);

    int chunkSize = numInts / size;
    int *localBuff = (int*)malloc(chunkSize * sizeof(int));
    if (localBuff == NULL) {
        free(buffer);
        MPI_Abort(MPI_COMM_WORLD, 1);
    }

    MPI_Scatter(buffer, chunkSize, MPI_INT, localBuff, chunkSize, MPI_INT, 0, MPI_COMM_WORLD);

    int localCounter[1000] = {0};
    for (int i = 0; i < chunkSize; i++) {
        localCounter[localBuff[i]]++;
    }

    int globalCounter[1000] = {0};
    MPI_Reduce(localCounter, globalCounter, 1000, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);

    if (rank == 0) {
        for (int i = 0; i < numInts; i++) {
            buffer[i] = 0;
        }

        int indx = 0;
        for (int i = 0; i < 1000; i++) {
            for (int count = 0; count < globalCounter[i]; count++) {
                buffer[indx++] = i;
            }
        }

        FILE *f = fopen(fname, "wb");
        if (f == NULL) {
            free(buffer);
            free(localBuff);
            MPI_Abort(MPI_COMM_WORLD, 1);
        }

        writeNum = fwrite(buffer, sizeof(int), numInts, f);
        if (writeNum != numInts) {
            fclose(f);
            free(buffer);
            free(localBuff);
            MPI_Abort(MPI_COMM_WORLD, 1);
        }

        fclose(f);
        free(buffer);
    }

    free(localBuff);
    MPI_Finalize();
    return 0;
}
