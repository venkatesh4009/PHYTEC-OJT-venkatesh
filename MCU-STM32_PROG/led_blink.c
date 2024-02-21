#include "stm32f4xx.h"
void delayMs(int n);
int main(void) 
{
RCC->AHB1ENR |= 1; /* enable GPIOA clock */
GPIOA->MODER &= ~(1<<,10); /* clear pin mode */
GPIOA->MODER |=(1<<11; /* set pin to output mode */
while(1) 
{
GPIOA->ODR |= (1<<5); /* turn on LED */
delayMs(500);
GPIOA->ODR &= ~(1<<5); /* turn off LED */
delayMs(500);
}
}
/* 16 MHz SYSCLK */
void delayMs(int n) {
int i;
for (; n > 0; n--)
for (i = 0; i < 3195; i++) ; }
