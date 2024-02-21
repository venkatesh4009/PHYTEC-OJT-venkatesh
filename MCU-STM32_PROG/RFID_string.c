#include "stm32f4xx.h"

#define RFID_BUFFER_SIZE 50 // Maximum size of the RFID number buffer

void usart1_init(void);
void usart1_write(int ch);
char usart1_read(void);
void usart1_read_string(char *buffer, int buffer_size);

int main(void)
{
    char rfid_buffer[RFID_BUFFER_SIZE];
    usart1_init();

    while (1) {
        usart1_read_string(rfid_buffer, RFID_BUFFER_SIZE);
        // Process the received RFID number (e.g., send it to a server, compare it with a database, etc.)
        // Implement your RFID processing logic here.



    }
}

void usart1_init(void)
{
    // Same as before...
		RCC->AHB1ENR |= 1;
		RCC->APB2ENR |= 0x00000010;
		GPIOA->MODER &= ~0x003C0000;
		GPIOA->MODER |= 0x00280000;
		GPIOA->AFR[1] &= ~0x0FF0;
		GPIOA->AFR[1] |= 0x0770 ; /* alt8 for UART1 */
		USART1->BRR = 0x0683; /* 9600 baud @ 16 MHz */
		USART1->CR1 = 0x000C;/* enable Tx, Rx, 8-bit data */
		USART1->CR2 = 0x0000; /* 1 stop bit*/
		USART1->CR3 = 0x0000; /* no flow control */
		USART1->CR1 |= 0x2000; /*enable UART1 */

}

void usart1_write(int ch)
{
    // Same as before...
    while (!(USART1->SR & 0x0080)) {} // wait until Tx buffer empty
    USART1->DR = (ch & 0xFF);
}

char usart1_read(void)
{
    while (!(USART1->SR & 0x0020)) {} // wait until char arrives
    return USART1->DR;
}

void usart1_read_string(char *buffer, int buffer_size)
{
    int i = 0;
    char c;

    // Read characters until the buffer is full or the termination character is received
    while (i < buffer_size - 1) { // Leave space for the null terminator
        c = usart1_read();
        usart1_write(c); // Echo back the received character

        if (c == '\r' || c == '\n') { // Termination character received
            buffer[i] = '\0'; // Null-terminate the string
            break;
        } else {
            buffer[i] = c;
            i++;
        }
    }

    // If the buffer is full, ensure null termination
    if (i == buffer_size - 1) {
        buffer[i] = '\0';
    }
}
