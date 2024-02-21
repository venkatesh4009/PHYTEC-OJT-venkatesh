#include <stdio.h>

int main() {
    int matrix[3][3];
    int sum = 0;

    // Get input for the 3x3 matrix from the user
    printf("Enter the elements of the 3x3 matrix:\n");
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            printf("Element at [%d][%d]: ", i + 1, j + 1);
            scanf("%d", &matrix[i][j]);
        }
    }

    // Calculate the sum of elements in the lower triangle
    for (int i = 1; i < 3; i++) {
        for (int j = 0; j < i; j++) {
            sum += matrix[i][j];
        }
    }

    // Print the result
    printf("Sum of elements in the lower triangle: %d\n", sum);

    return 0;
}

