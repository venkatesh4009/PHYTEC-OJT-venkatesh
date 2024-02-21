#include"stm32f4xx.h"
void uart3_init(void);
void UART6_write(int ch);
char uart3_read(void);

void delayMs(int n) {
int i;
for (; n > 0; n--)
for (i = 0; i < 3195; i++) ;
}

int main(void)
{
	uart3_init();
	char message[] = "CMD+RESET\r\n";
	int i;
	for (i = 0; message[i] != '\0'; i++) {
		UART6_write(message[i]);
	}
	delayMs(1000);
	char messag[] = "CMD+WIFIMODE=1\r\n";
	int j;
	for (j = 0; messag[j] != '\0'; j++) {
		UART6_write(messag[j]);
	}
	delayMs(1000);
	char msg[] = "CMD+CONTOAP=narzo 50 pro 5G,12345678\r\n";
	int k;
	for (k = 0; msg[k] != '\0'; k++) {
		UART6_write(msg[k]);
	}
	delayMs(1000);
	/*char ms[] = "CMD?WIFI\r\n";
	int l;
	for (l = 0; ms[l] != '\0'; l++) {
		UART6_write(ms[l]);
	}
	while (1) {

		}
		uart3_read();
		delayMs(1000);*/
	}







void uart3_init(void)
{
	RCC->AHB1ENR |= 1;
	RCC->APB2ENR |= 0x00000020;
	GPIOA->MODER &= ~0x03C00000;
	GPIOA->MODER |= 0x02800000;
	GPIOA->AFR[1] &= ~0x0FF0;
	GPIOA->AFR[1] |= 0x00088000 ; /* alt8 for UART4 */
	USART6->BRR = 0x01A1; /* 9600 baud @ 16 MHz */
	USART6->CR1 = 0x000C;/* enable Tx, Rx, 8-bit data */
	USART6->CR2 = 0x0000; /* 1 stop bit*/
	USART6->CR3 = 0x0000; /* no flow control */
	USART6->CR1 |= 0x2000; /*enable UART4 */

}



void UART6_write(int ch) {
while (!(USART6->SR & 0x0080)) {} // wait until Tx buffer empty
USART6->DR = (ch & 0xFF);
}
