#include "stm32f4xx.h"
void delayMs(int n);
void I2C1_init(void);
int I2C1_byteWrite(char saddr, char maddr, char data);
int main(void)
{
	I2C1_init();
	I2C1_byteWrite(0x38, 0xAC, 0X33);
    while(1)
    {
    }
}
void I2C1_init(void)
{
	RCC->AHB1ENR |= 2;
	RCC->APB1ENR |=0x00200000;

	GPIOB->AFR[1] &= ~0x000000FF;
	GPIOB->AFR[1] |= 0x00000044;

	GPIOB->MODER &= ~0x000F0000;
	GPIOB->MODER |= 0x000A0000;

	GPIOB->OTYPER |= 0x00000300;

	GPIOB->PUPDR &=~0x000F0000;
	GPIOB->PUPDR |= 0x00050000;


	I2C1->CR1 = 0x8000;
	I2C1->CR1 &= ~0x8000;

	I2C1->CR2 = 0x0010;
	I2C1->CCR = 80;
	I2C1->TRISE =17;
	I2C1->CR1 |= 0x0001;

}
volatile int tmp;
int I2C1_byteWrite(char saddr, char maddr, char data)
{
	while (I2C1->SR2 & 2);
	I2C1->CR1 |= 0x100;
	while (!(I2C1->SR1 & 1));
	I2C1->DR = saddr << 1;
	while (!(I2C1->SR1 & 2));
	tmp = I2C1->SR2;
	while (!(I2C1->SR1 & 0x80));
	I2C1->DR = maddr;
	while (!(I2C1->SR1 & 0x80));
	tmp=I2C1->DR;
	while (!(I2C1->SR1 & 4));
	I2C1->CR1 |= 0x200;
	return 0;
}
