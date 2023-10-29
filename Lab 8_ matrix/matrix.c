#include <stdio.h>
#include <stdlib.h>

int **allocateMatrix(int numRows, int numCols)
{
   int **matrix = (int **)malloc(numRows * sizeof(int *));
   for (int i = 0; i < numRows; i++) {
      matrix[i] = (int *)malloc(numCols * sizeof(int));
    }
    return matrix;
}

void freeMatrix(int **matrix, int numRows, int numCols)
{
   for (int i = 0; i < numRows; i++) {
        free(matrix[i]);
    }
    free(matrix);
}

void readMatrix(FILE *fp, int **matrix, int numRows, int numCols)
{
    for (int i = 0; i < numRows; i++) {
        for (int j = 0; j < numCols; j++) {
            if (fscanf(fp, "%d", &matrix[i][j]) != 1) {
                fprintf(stderr, "error\n");
                return;
            }
        }
    }
}

void printMatrix(int **matrix, int numRows, int numCols)
{  
    for (int i = 0; i < numRows; i++) {
        for (int j = 0; j < numCols; j++) {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }
   
}

int rangeRow(int **matrix, int numRows, int numCols, int r)
{

    int min = matrix[r][0];
    int max = matrix[r][0];

    for (int j = 1; j < numCols; j++) {
        if (matrix[r][j] < min) {
            min = matrix[r][j];
        }
        if (matrix[r][j] > max) {
            max = matrix[r][j];
        }
    }

    return max - min;
}

void printCorners(int **matrix, int numRows, int numCols)
{
   if (matrix == NULL || numRows <= 0 || numCols <= 0) {
        fprintf(stderr, "Invalid input parameters for printCorners.\n");
        return;
    }

    printf("%d          %d\n", matrix[0][0], matrix[0][numCols - 1]);
    printf("%d          %d\n", matrix[numRows - 1][0], matrix[numRows - 1][numCols - 1]);
}

int sumSubMatrix(int **matrix, int startRow, int endRow, int startCol, int endCol)
{
     int sum = 0;

    for (int i = startRow; i <= endRow; i++) {
        for (int j = startCol; j <= endCol; j++) {
            sum += matrix[i][j];
        }
    }

    return sum;
}
