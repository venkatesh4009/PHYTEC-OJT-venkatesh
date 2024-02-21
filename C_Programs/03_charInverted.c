#include <stdio.h>

int main() {
    int numRows;

    // Get the number of rows from the user
    printf("Enter the number of rows: ");
    scanf("%d", &numRows);

    // Loop for each row
    for (int i = numRows; i >= 1; i--) {
        char currentChar = 'A';

        // Loop to print letters 'a' to 'e' in each row
        for (int j = 1; j <= i; j++) {
            printf("%c", currentChar);
            currentChar++;
        }

        // Move to the next line after printing letters in a row
        printf("\n");
    }

    return 0;
}

