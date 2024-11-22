#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 100

void joinBuckets(int intEquiv[], int *buckets[], int counts[], int n);
void radixSort(int arr[], int n);

int main() {
    int count;
    int numbers[MAX_SIZE];

    // get number of elements from user

    // printf("Enter number of elements (max 100):\n");
    printf("\n");
    scanf("%d", &count);
    
    if (count < 1 || count > MAX_SIZE) {
        printf("Invalid number, exiting \n");
        return 1;
    }

    // read floaring point nums
    // printf("Enter integer numbers:\n");
    printf("\n");
    for (int i = 0; i < count; i++) {
        scanf("%d", &numbers[i]);
    }

    radixSort(numbers, count);

    //print out sorted numbers
    printf("\n");
    for (int i = 0; i < count; i++) {
        printf("%d\n", numbers[i]);
    }

    return 0;
}

void radixSort(int arr[], int n) {
    int *buckets[16];
    int counts[16];
    int positive[MAX_SIZE];
    int negative[MAX_SIZE];
    int posCount = 0;
    int negCount = 0;

    for (int i = 0; i < 16; i++) {
        buckets[i] = (int*)malloc(n * sizeof(int));
        counts[i] = 0;
    }

    //splitting the positive and negative numbers
    for (int i = 0; i < n; i++) {
        if (arr[i] < 0) {
            negative[negCount++] = arr[i];
        } 
        else {
            positive[posCount++] = arr[i];
        }
    }



    for (int p = 0; p < sizeof(int) * 8; p += 4) {
        for (int i = 0; i < 16; i++) {
            counts[i] = 0;
        }

        for (int i = 0; i < posCount; i++) {
            int bucketIndex = (positive[i] >> p) & 0xF; // Get the current 4 bits
            buckets[bucketIndex][counts[bucketIndex]++] = positive[i];
        }

        //join back into the positive array
        int index = 0;
        for (int l = 0; l < 16; l++) {
            for (int m = 0; m < counts[l]; m++) {
                positive[index++] = buckets[l][m];
            }
        }
    }


    //sorting the negative numbers
    for (int i = 0; i < negCount; i++) {
        negative[i] = -negative[i];
    }

    for (int p = 0; p < sizeof(int) * 8; p += 4) {
        for (int q = 0; q < 16; q++) {
            counts[q] = 0;
        }

        for (int r = 0; r < negCount; r++) {
            int bit = (negative[r] >> p) & 0xF;
        }

        int index = 0;
        for (int l = 0; l < 16; l++) {
            for (int m = 0; m < counts[l]; m++) {
                negative[index++] = buckets[l][m];
            }
        }
    }

    //copying nthe sorted neg nums in reverse into the array
    for (int i = 0; i < negCount; i++) {
        arr[i] = -negative[negCount - i - 1]; //flipping the sign bit back to normal
    }

    //copying the positive numbers into the array
    for (int i = 0; i < posCount; i++) {
        arr[i + negCount] = positive[i];
    }


    for (int i = 0; i < 16; i++) {
        free(buckets[i]);
    }
}
