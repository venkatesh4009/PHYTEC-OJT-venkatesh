#include <stdio.h>

int main() {
    int totalSeconds, hours, minutes, seconds;

    // Get input from the user
    printf("Enter the total seconds: ");
    scanf("%d", &totalSeconds);

    // Calculate hours, minutes, and remaining seconds
    hours = totalSeconds / 3600;
    minutes = (totalSeconds % 3600) / 60;
    seconds = totalSeconds % 60;

    // Print the result
    printf("Equivalent time: %d hours, %d minutes, %d seconds\n", hours, minutes, seconds);

    return 0;
}

