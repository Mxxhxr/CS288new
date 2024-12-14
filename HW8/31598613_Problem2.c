#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <pthread.h>//

//create the struct
struct threadStruct {
    unsigned long start;
    unsigned long end;
    unsigned long n;
};




long double pi = 0.0;
pthread_mutex_t mutex;

//function for the threads to use
void *calculatePi(void *args) {
    struct threadStruct *arg = (struct threadStruct *)args; //this casts it to threadStruct struct
    long double localSum = 0.0; //using long double bcuz idk how long itll be

    for (unsigned long i = arg->start; i <= arg->end; i++) {
        long double x = ((long double)i - 0.5) / arg->n;
        localSum += 4.0 / (1.0 + x*x);
    }
    pthread_mutex_lock(&mutex);
    pi += localSum;
    pthread_mutex_unlock(&mutex);
}

int main(int argc, char *argv[]) {
    if (argc != 3) { //cli args
        printf("Please provide \"numThreads\" & \"numTerms\"\n");
        return 1;
    
    }
    
    int numThreads = atoi(argv[1]);
    unsigned long numTerms = strtoul(argv[2], NULL, 10); //str to unsigned long

    pthread_t threads[numThreads];
    struct threadStruct thread[numThreads]; //array of structs
    unsigned long termsPerThread = numTerms / numThreads;
    
    pthread_mutex_init(&mutex, NULL);

    //creating the threads
    for (int i = 0; i < numThreads; i++) {
        thread[i].start = i * termsPerThread + 1;
        thread[i].end = (i+1) * termsPerThread;
        thread[i].n = numTerms;

        if (pthread_create(&threads[i], NULL, calculatePi, &thread[i]) != 0) {
            printf("error creating thread\n");
            return 1;
        }
    }

    //now to join the threads tgt
    for (int i = 0; i < numThreads; i++) {
        pthread_join(threads[i], NULL);
    }
    pthread_mutex_destroy(&mutex);

    //fuinnally calculate and print pi
    pi /= numTerms;
    printf("Value of Pi is: %.20Lf\n", pi); //hw doesnt say how many decimals to print

    return 0;
}
