#include <stdio.h>

int main() {
    int numRows;

    // Get the number of rows from the user
    printf("Enter the number of rows: ");
    scanf("%d", &numRows);

    // Loop for each row
    for (int i = 1; i <= numRows; i++) {
        // Print leading spaces
        for (int j = 1; j <= numRows - i; j++) {
            printf("   ");
        }

        int currentNum = i;

        // Print numbers in increasing order
        for (int j = 1; j <= i; j++) {
            printf("%3d", currentNum);
            currentNum++;
        }

        // Print numbers in decreasing order
        currentNum -= 2;
        for (int j = 1; j < i; j++) {
            printf("%3d", currentNum);
            currentNum--;
        }

        // Move to the next line after printing a row
        printf("\n");
    }

    return 0;
}

