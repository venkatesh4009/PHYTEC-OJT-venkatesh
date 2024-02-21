#include <stdio.h>
#include <stdbool.h>

int main() {
    int start, end;

    // Get input for two numbers from the user
    printf("Enter the start number: ");
    scanf("%d", &start);

    printf("Enter the end number: ");
    scanf("%d", &end);

    // Print prime numbers between the two numbers
    printf("Prime numbers between %d and %d are:\n", start, end);
    for (int i = start; i <= end; i++) {
        if (i > 1) {
            bool isPrime = true;
            for (int j = 2; j * j <= i; j++) {
                if (i % j == 0) {
                    isPrime = false;
                    break;
                }
            }
            if (isPrime) {
                printf("%d\n", i);
            }
        }
    }

    return 0;
}

