#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 100 //max size cant be more than 100

int main() {
    int n1, n2;
    FILE *f1 = fopen("matrix1.bin", "rb");
    FILE *f2 = fopen("matrix2.bin", "rb");

    if (f1 == NULL || f2 == NULL) {
        printf("Error opening file(s)\n");
        return 1;
    }

    fread(&n1, sizeof(n1), 1, f1);
    fread(&n2, sizeof(n2), 1, f2);
    if (n1 > MAX_SIZE || n2 > MAX_SIZE) {
        printf("The matrix(s) is too large\n");
        fclose(f1);
        fclose(f2);
        return 1;
    }
    if (n1 != n2) {
        printf("The matrices are not the same size\n");
        return 1;
    }

    int matrix1[n1][n1][n1];
    int matrix2[n2][n2][n2];
    long long result_matrix[n1][n1][n1];

    fread(matrix1, sizeof(int), n1*n1*n1, f1);
    fread(matrix2, sizeof(int), n2*n2*n2, f2);

    fclose(f1);
    fclose(f2);


    for (int i = 0; i < n1; i++) {
        for (int j = 0; j < n1; j++) {
            for (int k = 0; k < n1; k++) {
                result_matrix[i][j][k] = (long long)matrix1[i][j][k] * (long long)matrix2[i][j][k];
            }
        }
    }

    FILE *fout = fopen("result.bin", "wb");
    if (fout == NULL) {
        printf("Error opening file\n");
        return 1;
    }
    fwrite(&n1, sizeof(n1), 1, fout); //write dimension
    fwrite(result_matrix, sizeof(long long), n1*n1*n1, fout); 
    fclose(fout);

    return 0;
}

