#include "exti.h"
#include "stm32f4xx.h"
#define LED         (1<<5)

void pc13_exti_init(void)
{
    /* Disable global interrupts */
    __disable_irq();

    /* Enable clock access for GPIOC */
    RCC->AHB1ENR |= GPIOCEN;

    /* Set PC13 as input */
    GPIOC->MODER &= ~(1U << 26);
    GPIOC->MODER &= ~(1U << 27);

    /* Enable clock access to SYSCFG */
    RCC->APB2ENR |= SYSCFGEN;

    /* Select PORTC for EXTI13 */
    SYSCFG->EXTICR[3] |= (1U << 5);

    /* Unmask EXTI13 */
    EXTI->IMR |= LINE13;

    /* Select falling edge trigger */
    EXTI->FTSR |= LINE13;

    /* Enable EXTI13 line in NVIC */
    NVIC_EnableIRQ(EXTI15_10_IRQn);

    /* Enable global interrupts */
    __enable_irq();

void exti_callback(void)
{
    printf("BTN Pressed...\n\r");
    GPIOA->ODR ^= LED;
}

void EXTI15_10_IRQHandler(void)
{
    if ((EXTI->PR & LINE13) != 0)
    {
        /* Clear PR flag */
        EXTI->PR |= LINE13;

        // Do something...
        exti_callback();
    }
}
