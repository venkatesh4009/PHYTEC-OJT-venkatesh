#include <stdio.h>

int main() {
    int numRows, numCols;

    // Get the number of rows from the user
    printf("Enter the number of rows: ");
    scanf("%d", &numRows);

    // Get the number of columns from the user
    printf("Enter the number of columns: ");
    scanf("%d", &numCols);

    // Loop for each row
    for (int i = 1; i <= numRows; i++) {
        // Loop for each column
        for (int j = 1; j <= numCols; j++) {
            // Check if it's the first or last row, or the first or last column
            if (i == 1 || i == numRows || j == 1 || j == numCols) {
                printf("* ");
            } else {
                // Print space inside the pattern
                printf("  ");
            }
        }

        // Move to the next line after printing a row
        printf("\n");
    }

    return 0;
}

