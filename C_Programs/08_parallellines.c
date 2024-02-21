#include <stdio.h>

int main() {
    float x1, y1, x2, y2, x3, y3, x4, y4;
    float slope1, slope2;

    // Get input for the coordinates of the two points on each line
    printf("Enter coordinates of first point on line 1 (x1 y1): ");
    scanf("%f %f", &x1, &y1);

    printf("Enter coordinates of second point on line 1 (x2 y2): ");
    scanf("%f %f", &x2, &y2);

    printf("Enter coordinates of first point on line 2 (x3 y3): ");
    scanf("%f %f", &x3, &y3);

    printf("Enter coordinates of second point on line 2 (x4 y4): ");
    scanf("%f %f", &x4, &y4);

    // Calculate slopes
    slope1 = (y2 - y1) / (x2 - x1);
    slope2 = (y4 - y3) / (x4 - x3);

    // Check if slopes are equal
    if (slope1 == slope2) {
        printf("The lines are parallel.\n");
    } else {
        printf("The lines are not parallel.\n");
    }

    return 0;
}

