#include <stdio.h>
#include <string.h>

// Function to swap characters at positions i and j in a string
void swap(char *a, char *b) {
    char temp = *a;
    *a = *b;
    *b = temp;
}

int main() {
    char inputString[100];

    // Get the string from the user
    printf("Enter a string: ");
    scanf("%s", inputString);

    int length = strlen(inputString);

    // Print all combinations of the input string
    printf("All combinations of the string are:\n");

    for (int i = 0; i < length; i++) {
        for (int j = i; j < length; j++) {
            // Swap characters at positions i and j
            swap(&inputString[i], &inputString[j]);
            printf("%s\n", inputString);
            // Undo the swap to backtrack
            swap(&inputString[i], &inputString[j]);
        }
    }

    return 0;
}

