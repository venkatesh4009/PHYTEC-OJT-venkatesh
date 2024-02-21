#include <stdio.h>

int main() {
    int matrix[10][10], transpose[10][10];
    int numRows, numCols;

    // Get the number of rows and columns from the user
    printf("Enter the number of rows: ");
    scanf("%d", &numRows);

    printf("Enter the number of columns: ");
    scanf("%d", &numCols);

    // Input the matrix elements from the user
    printf("Enter the elements of the matrix:\n");
    for (int i = 0; i < numRows; i++) {
        for (int j = 0; j < numCols; j++) {
            printf("Element at [%d][%d]: ", i + 1, j + 1);
            scanf("%d", &matrix[i][j]);
        }
    }

    // Find the transpose of the matrix
    for (int i = 0; i < numCols; i++) {
        for (int j = 0; j < numRows; j++) {
            transpose[i][j] = matrix[j][i];
        }
    }

    // Print the transpose matrix
    printf("Transpose Matrix:\n");
    for (int i = 0; i < numCols; i++) {
        for (int j = 0; j < numRows; j++) {
            printf("%d\t", transpose[i][j]);
        }
        printf("\n");
    }

    return 0;
}

