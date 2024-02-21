#include <stdio.h>

int main() {
    int decimalNumber;

    // Get input for a decimal number from the user
    printf("Enter a decimal number: ");
    scanf("%d", &decimalNumber);

    // Print the binary representation with LSB on the right
    printf("Binary representation with LSB on the right: ");
    for (int i = sizeof(int) * 8 - 1; i >= 0; i--) {
        int bit = (decimalNumber >> i) & 1;
        printf("%d", bit);
    }

    printf("\n");

    return 0;
}

