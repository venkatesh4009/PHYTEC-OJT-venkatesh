#include"stm32f4xx.h"

void usart1_init(void);
void USART1_write(int ch);
void delayMs(int n);

void delayMs(int n)
{
	int i;
	for (; n > 0; n--)
	for (i = 0; i < 3195; i++);
}

int main()
{
	usart1_init();

	int i;
	char msg1[] ="CMD+RESET\r\n";

	for (i = 0; msg1[i] !='\0'; i++)
		USART1_write(msg1[i]);

	delayMs(1000);

	char msg2[] ="CMD+WIFIMODE=1\r\n";
	for (i = 0; msg2[i] != '\0'; i++)
		USART1_write(msg2[i]);

	delayMs(1000);

	char msg3[] ="CMD+CONTOAP=narzo 50 pro 5G,12345678\r\n";
	for (i = 0; msg3[i] != '\0'; i++)
		USART1_write(msg3[i]);

	delayMs(1000);

	return 0;
}




void usart1_init(void)
{
	RCC->AHB1ENR |= 1;
	RCC->APB2ENR |= 0x00000010;
	GPIOA->MODER &= ~0x003C0000;
	GPIOA->MODER |= 0x00280000;
	GPIOA->AFR[1] &= ~0x0FF0;
	GPIOA->AFR[1] |= 0x0770 ; /* alt8 for UART1 */
	USART1->BRR = 0x01A1; /* 9600 baud @ 16 MHz */
	USART1->CR1 = 0x000C;/* enable Tx, Rx, 8-bit data */
	USART1->CR2 = 0x0000; /* 1 stop bit*/
	USART1->CR3 = 0x0000; /* no flow control */
	USART1->CR1 |= 0x2000; /*enable UART1 */

}



void USART1_write(int ch)
{
	while (!(USART1->SR & 0x0080)) {} // wait until Tx buffer empty
	USART1->DR = (ch & 0xFF);
}
