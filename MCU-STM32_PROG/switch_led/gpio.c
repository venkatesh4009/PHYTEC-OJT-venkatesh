#include"stm32f4xx.h"

void led_on(void)
{
	GPIOA->ODR|=(1<<5);
}
void led_off(void)
{
	GPIOA->ODR&=~(1<<5);
}
