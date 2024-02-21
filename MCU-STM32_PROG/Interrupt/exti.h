#ifndef EXTI_H
#define EXTI_H

#include <stdio.h>
#include <stdint.h>

#define GPIOCEN      (1U<<2)
#define SYSCFGEN     (1U<<14)
#define LINE13       (1U<<13)

void pc13_exti_init(void);
void exti_callback(void);
void EXTI15_10_IRQHandler(void);
#endif /* EXTI_H */
