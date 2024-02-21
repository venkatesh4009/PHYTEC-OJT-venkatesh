#include "stm32f4xx.h"

#define TIM2EN		(1U << 0)
#define CR1_CEN		(1U << 0)
#define CCER_CC1E	(1U << 0)
#define CCER_CC1P	(1U << 1)
#define CCER_CC1NP	(1U << 3)
#define CCER_CC1E	(1U << 0)
#define CCER_CC1P	(1U << 1)
#define CCER_CC1NP	(1U << 3)
#define SR_CC1IF	(1U << 1)

#define GPIOAEN		(1U << 0)
#define AFR5_TIM	(0x05 << 20)

void tim2_pa5_input_capture(void);

int main()
{
	tim2_pa5_input_capture();

	while(1)
	{
		char timestamp;

		/* Wait until edge is captured */
		while (!(TIM2->SR & SR_CC1IF)) {}

		/* Read captured value */
		timestamp = TIM2->CCR1;
		// Do something with the captured timestamp.
	}
}

void tim2_pa5_input_capture(void)
{
	/* Enable clock access to GPIOA */
	RCC->AHB1ENR |= GPIOAEN;

	/* Set PA5 mode to alternate function */
	GPIOA->MODER |= (1U << 10);
	GPIOA->MODER &= ~(1U << 11);

	/* Set PA5 alternate function type to TIM2_CH1 (AF05) */
	GPIOA->AFR[0] |= AFR5_TIM;

	/* Enable clock access to TIM2 */
	RCC->APB1ENR |= TIM2EN;

	/* Set Prescaler */
	TIM2->PSC = 16000 - 1; // 16,000,000 / 16,000 = 1000 Hz

	/* Set CH1 to input capture mode CCMR1 */
	TIM2->CCMR1 &= ~0x03; // Reset CC1S bits (capture mode)
	TIM2->CCMR1 |= 0x01;  // CC1S bits set to 01 (CC1 channel is configured as input, IC1 is mapped on TI1)

	/* Configure the input capture filter CCMR1 */
	TIM2->CCMR1 &= ~(0x0F << 4); // Reset IC1F bits (input capture filter)
	TIM2->CCMR1 |= (0x04 << 4);  // Set IC1F bits to filter with 4 sample clocks

	/* Set CH1 to capture at rising edge CCER */
	TIM2->CCER &= ~(CCER_CC1P | CCER_CC1NP); // Set both CC1P and CC1NP bits to 0 (capture at rising edge)

	/* Enable input capture for CH1 */
	TIM2->CCER |= CCER_CC1E;

	/* Enable TIM2 */
	TIM2->CR1 = CR1_CEN;
}
