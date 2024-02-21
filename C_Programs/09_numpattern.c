#include <stdio.h>

int main() {
    int numRows;

    // Get the number of rows from the user
    printf("Enter the number of rows: ");
    scanf("%d", &numRows);

    // Outer loop for rows
    for (int i = 1; i <= numRows; i++) {
        // Inner loop for printing numbers
        for (int j = 1; j <= 2 * i - 1; j++) {
            printf("%d", j);
        }

        printf("\n");
    }

    return 0;
}

