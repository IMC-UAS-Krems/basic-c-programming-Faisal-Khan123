#include <stdio.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    // Initializing random number generator
    srand(time(NULL));
    int minrand = 1;
    int maxrand = 100;

    // Checking the number of arguments
    if (argc != 3) {
        printf("Incorrect usage. You provided %d arguments. The correct number of arguments is 2\n", argc - 1);
        return 1;
    }

    // Converting arguments to integers
    int rows = atoi(argv[1]);
    int cols = atoi(argv[2]);

    // Checking if arguments are positive integers
    if (rows <= 0 || cols <= 0) {
        printf("Incorrect usage. The parameters you provided are not positive integers\n");
        return 1;
    }

    // Dynamically allocating memory for the matrix
    int **matrix = (int **)malloc(rows * sizeof(int *));
    for (int i = 0; i < rows; i++) {
        matrix[i] = (int *)malloc(cols * sizeof(int));
    }

    // Populating the matrix with random integers between 1 and 100
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            matrix[i][j] = minrand + rand() % (maxrand - minrand + 1);
        }
    }

    // Creating and writing the matrix to "matrix.txt"
    FILE *file = fopen("matrix.txt", "w");
    if (file == NULL) {
        perror("Error opening file");
        for (int i = 0; i < rows; i++) {
            free(matrix[i]);
        }
        free(matrix);
        return 1;
    } else {
        printf("File opened successfully.\n");
    }

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            fprintf(file, "%d", matrix[i][j]);
            if (j < cols - 1) {
                fprintf(file, " "); // Printing a space between numbers except at the end of a line
            }
        }
        // Printing a newline only if it is not the last row
        if (i < rows - 1) {
            fprintf(file, "\n");
        }
    }

    fclose(file);

    // Printing a confirmation message
    printf("Matrix of size %d x %d was successfully created in 'matrix.txt'.\n", rows, cols);

    // Freeing dynamically allocated memory
    for (int i = 0; i < rows; i++) {
        free(matrix[i]);
    }
    free(matrix);

    return 0;
}
