#include <pthread.h>

void *computation(void *num);

int main()
{
    // create threads
    pthread_t thread1, thread2;
    long value1 = 1, value2 = 2;
    computation((void *)&value1);
    computation((void *)&value2);

    //     // create worker thread 1
    //     pthread_create(&thread1, NULL, computation, (void *)&value1);
    //     pthread_create(&thread2, NULL, computation, (void *)&value2);

    // join the threads
    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);
}

void *computation(void *num)
{
    // casting void * to long type
    long *mynum = (long *)num;

    int sum;
    for (int i = 0; i < 1000000000; i++)
    {
        sum += i * (*mynum);
    }
}
