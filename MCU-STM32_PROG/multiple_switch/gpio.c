#include"stm32f4xx.h"
#include"gpio.h"
void GPIO_init(void)
{
	GPIOA->MODER |=(1<<10);
}
