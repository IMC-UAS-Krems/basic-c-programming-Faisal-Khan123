#include <stdio.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    // initialize random number generator
    srand(time(NULL));
    int minrand = 1;
    int maxrand = 100;

    // WRITE YOUR CODE HERE

    // Checking for correct number of arguments
    if (argc != 3) {
        printf("Incorrect usage. You provided %d arguments. The correct number of arguments is 2\n", argc - 1);
        return 1;
    }

    // Parsing the arguments and validating they are positive integers
    int rows = atoi(argv[2]);
    int cols = atoi(argv[2]);
    if (rows <= 0 || cols <= 0) {
        printf("Incorrect usage. The parameters you provided are not positive integers\n");
        return 1;
    }

    // Dynamically allocating a matrix
    int **matrix = (int **)malloc(rows * sizeof(int *));
    for (int i = 0; i < rows; i++) {
        matrix[i] = (int *)malloc(cols * sizeof(int));
    }

    // Completing the matrix with random integers between 1 and 100
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            matrix[i][j] = (rand() % (maxrand - minrand + 1)) + minrand;
        }
    }

    // Writing the matrix to a file
    FILE *file = fopen("matrix.txt", "w");
    if (!file) {
        perror("Failed to open file for writing");
        for (int i = 0; i < rows; i++) {
            free(matrix[i]);
        }
        free(matrix);
        return 1;
    }

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            fprintf(file, "%d", matrix[i][j]);
            if (j < cols - 1) {
                fprintf(file, " "); // Printing a space between numbers except at the end of a line
            }
        }
        fprintf(file, "\n"); // Printing each row with a newline
    }

    fclose(file);

    // Freeing the allocated memory
    for (int i = 0; i < rows; i++) {
        free(matrix[i]);
    }
    free(matrix);

    return 0;
}



