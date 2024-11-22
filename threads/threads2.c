#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

// see the order of the execution of the threads
//  to make the threads dynmaic by specify from CLI

// implement thread function

void *helloworld(void *id)
{
    /// case the generic pointer to type long
    long *myid = (long *)id;
    printf("Im a thread: %d\n", *myid);
    return NULL;
}

int main(int argc, char *argv[])
{
    pthread_t *pthread_array;
    long *thread_ids;
    long nthreads;

    // strtol => convert string to long
    // strtol(start, end, base)
    nthreads = strtol(argv[1], NULL, 10);

    pthread_array = malloc(nthreads * sizeof(pthread_t));
    thread_ids = malloc(nthreads * sizeof(long));

    for (int i = 0; i < nthreads; i++)
    {
        thread_ids[i] = i;
        pthread_create(&pthread_array[i], NULL, helloworld, (void *)&thread_ids[i]);
    }

    // join the threads
    for (int i = 0; i < nthreads; i++)
    {
        pthread_join(pthread_array[i], NULL);
    }
}