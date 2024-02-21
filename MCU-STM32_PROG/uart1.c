#include "stm32f4xx_hal.h"

UART_HandleTypeDef huart2; // Change the handle according to your setup

int main(void) {
    HAL_Init();
    // Initialize UART with desired settings (baud rate, etc.)
    // ...

    while (1) {
        // Receive data over UART
        char receivedData[50]; // Assuming the received data won't exceed this size
        HAL_UART_Receive(&huart2, (uint8_t*)receivedData, sizeof(receivedData)-1, HAL_MAX_DELAY);

        // Process received data (e.g., print it via UART)
        HAL_UART_Transmit(&huart2, (uint8_t*)receivedData, sizeof(receivedData)-1, HAL_MAX_DELAY);

        HAL_Delay(100); // Wait before receiving the next message
    }
}
