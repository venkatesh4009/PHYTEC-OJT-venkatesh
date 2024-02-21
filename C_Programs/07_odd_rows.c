#include <stdio.h>

int main() {
    int numRows;

    // Get the number of rows from the user (odd number)
    do {
        printf("Enter the number of rows (odd): ");
        scanf("%d", &numRows);
    } while (numRows % 2 == 0);

    int currentNumber = 1;
    int spaces = numRows / 2;

    // Loop for each row
    for (int i = 0; i < numRows; i++) {
        // Print leading spaces
        for (int j = 0; j < spaces; j++) {
            printf("   ");
        }

        // Print numbers
        for (int j = 0; j <= i; j++) {
            printf("%3d", currentNumber);
            currentNumber++;
        }

        // Move to the next line
        printf("\n");

        // Adjust spaces for the next row
        if (i < numRows / 2) {
            spaces--;
        } else {
            spaces++;
        }
    }

    return 0;
}

