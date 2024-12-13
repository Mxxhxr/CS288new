// #include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv) {
    char fname[100];
    printf("Enter the file name:\n");
    scanf("%s", fname);

    //opening the file
    FILE *f = fopen(fname, "rb");
    if (f == NULL) {
        printf("An error occured trying to open the file.\n");
        return 1;
    }

    //getting the length of the file
    fseek(f, 0, SEEK_END); //moves to the end of the file
    long fsize = ftell(f); //returns the end position of the file aka getting the size
    rewind(f); //moves the f pointer back to the begenning of the file

    // get the # of ints
    int numInts = fsize / sizeof(int);
    printf("%d", numInts);

    return 0;
}
