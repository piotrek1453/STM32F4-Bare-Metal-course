#include "exti.h"

#define GPIOCEN	(1U<<2)
#define SYSCFGEN	(1U<<14)


void pc13_exti_init(void){
	//optional:disable global interrupt
	__disable_irq();
	//enable clk for gpioc
	RCC->AHB1ENR |= GPIOCEN;
	//set pc13 as input
	GPIOC->MODER &=~ (1U<<26);
	GPIOC->MODER &=~ (1U<<27);
	//enable clk for SYSCONFIG
	RCC->APB2ENR |= SYSCFGEN;
	//select port C to be connected to EXTI13
	SYSCFG->EXTICR[3] |= (1U<<5);
	//unmask EXTI13
	EXTI->IMR |= (1U<<13);
	//select falling edge trigger
	EXTI->FTSR |= (1U<<13);
	//enable EXTI line in NVIC
	NVIC_EnableIRQ(EXTI15_10_IRQn);
	//enable global interrupt
	__enable_irq();
}
