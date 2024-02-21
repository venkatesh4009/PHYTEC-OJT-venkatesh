#include "stm32f4xx.h"
#include"gpio.h"
int main()
{
	RCC->AHB1ENR|=(1<<0);
	RCC->AHB1ENR|=(1<<2);
	GPIO_init();
	while(1)
	{
		if(GPIOC->IDR &=(1<<13))
			GPIOA->BSRR |=~(1<<5);
		else
			GPIOA->BSRR |=(1<<5);
	}
}
