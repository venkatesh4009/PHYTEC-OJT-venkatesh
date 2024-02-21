#include"stm32f4xx.h"
int main()
void delayms(void)
{
	RCC-> AHB1ENR |=(1<<0);
	RCC-> AHB1ENR |=(1<<2);
	GPIOA->MODER |=(1<<10);
	while(1)
		{
			if(GPIOC->IDR &=(1<<13))
				GPIOA->BSRR |= ~(1<<5);
				delayms(500);
			else
				GPIOA->BSRR |=(1<<5);
		}
}
