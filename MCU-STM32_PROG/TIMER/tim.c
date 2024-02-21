#include"tim.h"
#define TIM2EN       (1U<<0)
#define CR1_CEN			(1U<<0)

void tim2_1hz_init(void)
{
	RCC->APB1ENR|=TIM2EN;

	TIM2->PSC=16000-1;

	TIM2->ARR=1000-1;

	TIM2->CNT=0;

	TIM2->CR1=CR1_CEN;
}
void tim_delay(void)
{
	while(!(TIM2->SR & SR_UIF)){}

	TIM2->SR &=~SR_UIF;
}
