#include "stm32f4xx.h"

#define GPIOAEN			(1U << 0)

#define ADC1EN			(1U << 8)

#define ADC_CH1			(1U << 0)

#define ADC_SEQ_LEN_1	0x00

#define CR2_ADON		(1U << 0)

#define CR2_SWSTART		(1U << 30)

#define SR_EOC			(1U << 1)



void pa1_adc_init(void);

void start_conversion(void);

void delayMs(int n);

uint32_t adc_read(void);

uint32_t adcValue;





int main()

{

	pa1_adc_init();

	start_conversion();

	while (1)

    {

        adcValue = adc_read();

        delayMs(500);

    }

}



void pa1_adc_init(void)

{

    /**Configure the ADC GPIO pin **/

    // Enable clock access to GPIOA

    RCC->AHB1ENR |= GPIOAEN;

    // Set the mode of PA1 to analog

    GPIOA->MODER |= (1U << 2);

    GPIOA->MODER |= (1U << 3);

    /**Configure the ADC module**/

    // Enable clock access to ADC

    RCC->APB2ENR |= ADC1EN;

    // Set ADC channel 1 for conversion

    ADC1->SQR3 = ADC_CH1;

    // Set conversion sequence length to 1

    ADC1->SQR1 = ADC_SEQ_LEN_1;

    // Enable ADC

    ADC1->CR2 |= CR2_ADON;

}



void start_conversion(void)

{

	ADC1->CR2 |= 2;

    // Start ADC conversion

    ADC1->CR2 |= CR2_SWSTART;

}



uint32_t adc_read(void)

{

    // Wait for conversion to be complete

    while (!(ADC1->SR & SR_EOC));

    // Read converted result

    return (ADC1->DR);

}



void delayMs(int n)

{

	int i;

	for (;n  > 0; n--)

	for (i = 0; i < 3195; i++) ;
}

