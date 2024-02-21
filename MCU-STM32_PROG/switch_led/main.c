#include "stm32f4xx.h"
#include"gpio.h"
#include"delay.h"
#define GPIOA_EN (1<<0)
#define PA5_MOD (0X01 << 10)
int main()
{
	RCC->AHB1ENR |= GPIOA_EN;
	GPIOA->MODER |= PA5_MOD;
	while(1)
	{
		led_on();
		delayms(500);
		led_off();
		delayms(500);
	}
	return 0;
}
