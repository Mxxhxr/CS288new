#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 100

void joinBuckets(unsigned int intEquiv[], unsigned int *buckets[], int counts[], int n);
void radixSort(float arr[], int n);

int main() {
    int count;
    float numbers[MAX_SIZE];

    // get number of elements from user

    printf("Enter number of elements (max 100):\n");
    scanf("%d", &count);
    
    if (count < 1 || count > MAX_SIZE) {
        printf("Invalid number, exiting \n");
        return 1;
    }

    // read floaring point nums
    printf("Enter floating point numbers:\n");
    for (int i = 0; i < count; i++) {
        scanf("%f", &numbers[i]);
    }

    radixSort(numbers, count);

    printf("Sorted numbers:\n");
    for (int i = 0; i < count; i++) {
        printf("%.2f\n", numbers[i]);
    }

    return 0;
}

void radixSort(float arr[], int n) {
    unsigned int max = 0;
    unsigned int *buckets[2];
    unsigned int intEquiv[MAX_SIZE];
    int counts[2];

    buckets[0] = (unsigned int*)malloc(n * sizeof(unsigned int));
    buckets[1] = (unsigned int*)malloc(n * sizeof(unsigned int));

    for (int i = 0; i < n; i++) {
        intEquiv[i] = *(unsigned int*)&arr[i];
        intEquiv[i] ^= (1 << 31); //flips the sign bit for negative numbers
    }

    // radix sort algo
    for (int i = 0; i < 32; i++) {
        counts[0] = 0;
        counts[1] = 0;

        for (int j = 0; j < n; j++) {
            unsigned int bit = (intEquiv[j] >> i) & 1; // learned this in CS350 as well
            buckets[bit][counts[bit]++] = intEquiv[j];
        }
        //placeholder as of now, but will need a helper function. do this tmrw
        joinBuckets(intEquiv, buckets, counts, n);
    }


    for (int i = 0; i < n; i++) {
        intEquiv[i] ^= (1 << 31); //flip thge sign bit back
        arr[i] = *(float*)&intEquiv[i];
    }

    free(buckets[0]);
    free(buckets[1]);
}

//helper function

void joinBuckets(unsigned int intEquiv[], unsigned int *buckets[], int counts[], int n) {
    int index = 0;
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < counts[i]; j++) {
            intEquiv[index++] = buckets[i][j];
        }
    }
}