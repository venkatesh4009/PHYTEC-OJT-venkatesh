#include"stm32f4xx.h"
#define  PERIPR_BASE                                (0X40000000UL)
#define  AHB1PERIPR_OFFSET                          (0X00020000UL)
#define  AHB1PERIPR_BASE                            (PERIPR_BASE + AHB1PERIPR_OFFSET)
#define  GPIOA_OFFSET                               (0X0000UL)
#define  GPIOA_BASE                                 (AHB1PERIPR_BASE +GPIOA_OFFSET)
#define  RCC_OFFSET                                 (0X3800UL)
#define  RCC_BASE                                   (AHB1PERIPR_BASE + RCC_OFFSET)
#define  AHB1EN_R_OFFSET                            (0X30UL)
#define  RCC_AHB1EN_R                               (*(volatile unsigned int *)(RCC_BASE + AHB1EN_R_OFFSET))
#define  MOD_R_OFFSET                               (0X00UL)
#define  GPIOA_MOD_R                                (*(volatile unsigned int *)(GPIOA_BASE + MOD_R_OFFSET))
#define  OD_R_OFFSET                                (0X14UL)
#define  GPIOA_OD_R                                 (*(volatile unsigned int *)(GPIOA_BASE + OD_R_OFFSET))
#define  GPIOAEN                                    (1U<<0)
#define  PINS                                       (1U<<5)
#define  LED_PIN                                     PIN5
int main()
{
	RCC_AHB1EN_R |=1;
	GPIOA_MOD_R |=(1U<<10);
	GPIOA_MOD_R &=~(1U<<11);
	while(1)
	{
		GPIOA_OD_R |=(1<<5);
		for( int i=0;i<1000;i++)
			for(int j=0;j<4000;j++);
		GPIOA_OD_R &=~(1<<5);
		for( int i=0;i<1000;i++)
			for(int j=0;j<4000;j++);

	}
	return 0;
}

