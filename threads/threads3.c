#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

// the following variables in global scope so shared by all threads
long *array, nthreads, length, s;

// thread function
void *scalar_multiply(void *id)
{
    // cast generic pointer to type lng
    long *myid = (long *)id;

    // calculate the chunk of the array that each thread will process
    long chunk = length / nthreads;
    // calculate the start index of the array
    long start = (*myid) * chunk;
    // calculate the end index of the array
    long end = start + chunk;

    // perform scalar multiplication
    for (int i = 0; i < end; i++)
    {
        array[i] *= s;
    }
}

int main(int atgc, char *argv[])
{
    pthread_t *thread_array;
    long *thread_ids;

    // parse command line arguments
    nthreads = strtol(argv[1], NULL, 10);
    length = strtol(argv[2], NULL, 10);
    s = strtol(argv[3], NULL, 10);

    // allocate memory for the array
    thread_array = malloc(nthreads * sizeof(pthread_t));
    array = (long *)malloc(length * sizeof(long));
    thread_ids = malloc(nthreads * sizeof(long));

    // initialize the array
    for (int i = 0; i < length; i++)
    {
        array[i] = i;
    }
    for (int i = 0; i < nthreads; i++)
    {
        pthread_create(&thread_array[i], NULL, scalar_multiply, (void *)&thread_ids[i]);
    }

    // join the threads
    for (int i = 0; i < nthreads; i++)
    {
        pthread_join(thread_array[i], NULL);
    }
}