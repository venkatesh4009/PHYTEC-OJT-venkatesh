#include <stdio.h>

int main() {
    int n, sum = 0, factorial = 1;

    // Get input for n from the user
    printf("Enter the value of n: ");
    scanf("%d", &n);

    // Calculate the sum of factorials
    for (int i = 1; i <= n; i++) {
        factorial = 1;
        for (int j = 1; j <= i; j++) {
            factorial *= j;
        }
        sum += factorial;
    }

    // Print the result
    printf("Sum of factorials from 1! to %d!: %d\n", n, sum);

    return 0;
}

