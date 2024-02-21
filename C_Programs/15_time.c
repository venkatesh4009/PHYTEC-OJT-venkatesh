#include <stdio.h>
#include <time.h>

int main() {
    time_t t;
    struct tm *indianTime, *londonTime, *americanTime;

    // Get the current time in Indian Standard Time (IST)
    time(&t);
    indianTime = localtime(&t);

    // Convert to London time (GMT)
    t -= 5 * 3600;  // London is 5 hours behind IST
    londonTime = localtime(&t);

    // Convert to American time (EST)
    t -= 5 * 3600;  // Eastern Standard Time (EST) is 5 hours behind GMT
    americanTime = localtime(&t);

    // Display the times with AM/PM
    printf("Indian Time: %02d:%02d %s\n", indianTime->tm_hour % 12,
           indianTime->tm_min, indianTime->tm_hour < 12 ? "AM" : "PM");

    printf("London Time: %02d:%02d %s\n", londonTime->tm_hour % 12,
           londonTime->tm_min, londonTime->tm_hour < 12 ? "AM" : "PM");

    printf("American Time: %02d:%02d %s\n", americanTime->tm_hour % 12,
           americanTime->tm_min, americanTime->tm_hour < 12 ? "AM" : "PM");

    return 0;
}

