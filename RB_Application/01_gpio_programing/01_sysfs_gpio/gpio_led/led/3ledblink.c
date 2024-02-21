#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define GPIO_EN  "/sys/class/gpio/export"
#define GPIO_DIR_PC13 "/sys/class/gpio/PC13/direction"
#define GPIO_Val_PC13 "/sys/class/gpio/PC13/value"
#define GPIO_DIR_PC17 "/sys/class/gpio/PC17/direction"
#define GPIO_Val_PC17 "/sys/class/gpio/PC17/value"
#define GPIO_DIR_PC19 "/sys/class/gpio/PC19/direction"
#define GPIO_Val_PC19 "/sys/class/gpio/PC19/value"

int main()
{
    int gpio_fd[3]; // File descriptors for the three GPIO pins
    char gpio_buf[30];
    int gpio_num[] = {77, 81, 83};
    int count = 10;

    // Enable and configure GPIO pins
    for (int i = 0; i < 3; i++)
    {
        gpio_fd[i] = open(GPIO_EN, O_WRONLY);
        if (gpio_fd[i] < 0)
        {
            printf("Unable to open the file %s\n", GPIO_EN);
            exit(0);
        }
        sprintf(gpio_buf, "%d", gpio_num[i]);
        write(gpio_fd[i], gpio_buf, strlen(gpio_buf));
        close(gpio_fd[i]);

        switch (gpio_num[i])
        {
            case 77:
                gpio_fd[i] = open(GPIO_DIR_PC13, O_WRONLY);
                break;
            case 81:
                gpio_fd[i] = open(GPIO_DIR_PC17, O_WRONLY);
                break;
            case 83:
                gpio_fd[i] = open(GPIO_DIR_PC19, O_WRONLY);
                break;
            default:
                printf("Invalid GPIO pin\n");
                exit(1);
        }

        if (gpio_fd[i] < 0)
        {
            printf("Unable to open the file for GPIO pin %d", gpio_num[i]);
            exit(0);
        }
        write(gpio_fd[i], "out", 3);
        close(gpio_fd[i]);
    }

    // Open the files for writing
    gpio_fd[0] = open(GPIO_Val_PC13, O_WRONLY);
    gpio_fd[1] = open(GPIO_Val_PC17, O_WRONLY);
    gpio_fd[2] = open(GPIO_Val_PC19, O_WRONLY);

    int led_states[3] = {0, 0, 0};

    if (gpio_fd[0] < 0 || gpio_fd[1] < 0 || gpio_fd[2] < 0)
    {
        printf("Unable to open the GPIO files");
        exit(0);
    }

    printf("Toggling the GPIO_PINs\n");

    while (count--)
    {
        for (int i = 0; i < 3; i++)
        {
            led_states[i] = 1 - led_states[i]; // Toggle LED state
            sprintf(gpio_buf, "%d", led_states[i]);

            switch (gpio_num[i])
            {
                case 77:
                    gpio_fd[i] = open(GPIO_Val_PC13, O_WRONLY);
                    sleep(1);
                    break;
                    
                case 81:
                    gpio_fd[i] = open(GPIO_Val_PC17, O_WRONLY);
                    sleep(2);
                    break;
                    
                case 83:
                    gpio_fd[i] = open(GPIO_Val_PC19, O_WRONLY);
                    sleep(3);
                    break;
                default:
                    printf("Invalid GPIO pin\n");
                    exit(1);
            }

            if (gpio_fd[i] < 0)
            {
                printf("Unable to open the file for GPIO pin %d", gpio_num[i]);
                exit(0);
            }

            write(gpio_fd[i], gpio_buf, 1);
            close(gpio_fd[i]);
        }
        
    }

    // Close the files
    close(gpio_fd[0]);
    close(gpio_fd[1]);
    close(gpio_fd[2]);

    return 0;
}
