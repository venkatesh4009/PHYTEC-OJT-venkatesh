#include "stm32f4xx.h"
#include <stdint.h>

#define GPIOAEN     (1U<<0)
#define PA2MOD      (2U<<4)
#define PA2AF       (7U<<8)
#define APB1EN      (1U<<17)
#define USART2_TX   (1U<<3)
#define USART2_RX   (1U<<2) // Added for receiver configuration
#define USART2EN    (1U<<13)
#define SR_TXE      (1U<<7)
#define SR_RXNE     (1U<<5) // Added for receiver checking

#define SYS_FREQ        16000000
#define APB1_CLK        SYS_FREQ

#define UART_BAUDRATE   115200

void uart2_init(void);
void uart2_write(int ch);
int uart2_read(void); // Added for receiver reading

static void uart_set_baudrate(USART_TypeDef *USARTx, uint32_t PeriphClk, uint32_t BaudRate);
static uint16_t compute_uart_bd(uint32_t PeriphClk, uint32_t BaudRate);

int main()
{
    uart2_init();

    while (1)
    {
        // Transmit a character 'y'
        uart2_write('y');

        // Receive a character and echo back
        int received_char = uart2_read();
        if (received_char != -1)
        {
            uart2_write(received_char);
        }
    }

    return 0;
}

void uart2_init(void)
{
    // Configure UART TX pin (PA2)
    RCC->AHB1ENR |= GPIOAEN;
    GPIOA->MODER |= PA2MOD;
    GPIOA->AFR[0] |= PA2AF;

    // Configure UART RX pin (PA3) - Added for receiver
    GPIOA->MODER |= USART2_RX;

    // Enable clock access to USART2
    RCC->APB1ENR |= APB1EN;

    // Configure baud rate
    uart_set_baudrate(USART2, APB1_CLK, UART_BAUDRATE);

    // Configure the transfer direction for both transmitter and receiver
    USART2->CR1 = USART2_TX | USART2_RX;

    // Enable USART2
    USART2->CR1 |= USART2EN;
}

static void uart_set_baudrate(USART_TypeDef *USARTx, uint32_t PeriphClk, uint32_t BaudRate)
{
    USARTx->BRR = compute_uart_bd(PeriphClk, BaudRate);
}

static uint16_t compute_uart_bd(uint32_t PeriphClk, uint32_t BaudRate)
{
    return ((PeriphClk + (BaudRate / 2U)) / BaudRate);
}

void uart2_write(int ch)
{
    // Wait until the transmit data register is empty
    while (!(USART2->SR & SR_TXE))
    {
    }

    // Write to transmit data register
    USART2->DR = (ch & 0xFF);
}

int uart2_read(void)
{
    // Check if data is received
    if (USART2->SR & SR_RXNE)
    {
        // Read the received character from the data register
        return (USART2->DR & 0xFF);
    }

    // No data received
    return -1;
}
