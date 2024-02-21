#include "stm32f4xx.h"

void UART4_init(void);
void UART4_write(int c);
void delayMs(int);

int main(void) {
    char message[] = "Hello Ruggudboard\r\n";
    int i;
    UART4_init();
    while (1) {
        for (i = 0; i < 17; i++) {
            UART4_write(message[i]); /* send a character */
        }
        delayMs(10); // Leave a gap between messages
    }
}

void UART4_init(void) {
    RCC->AHB1ENR |= 1; // Enable GPIOA clock
    RCC->APB1ENR |= RCC_APB1ENR_UART4EN; // Enable UART4 clock

    // Configure PA0 for UART4 TX
    GPIOA->AFR[0] &= ~0x000F;
    GPIOA->AFR[0] |= 0x0008; // alt8 for UART4
    GPIOA->MODER &= ~0x0003;
    GPIOA->MODER |= 0x0002; // enable alternate function for PA0

    UART4->BRR = 0x0683; // 9600 baud @ 16 MHz
    UART4->CR1 = USART_CR1_TE; // enable Tx, 8-bit data
    UART4->CR2 = 0x0000; // 1 stop bit
    UART4->CR3 = 0x0000; // no flow control
    UART4->CR1 |= USART_CR1_UE; // enable UART4
}

void UART4_write(int ch) {
    while (!(UART4->SR & 0x0080)) {} // wait until Tx buffer empty
    UART4->DR = (ch & 0xFF);
}

void delayMs(int n) {
    int i;
    for (; n > 0; n--) {
        for (i = 0; i < 2000; i++) {
            // Delay
        }
    }
}
