#include "stm32f4xx.h"

#define TIM2EN	(1U<<0)
#define CR1_CEN	(1U<<0)
#define DIER_UIE (1U<<0)

void tim2_1hz_init(void){
	//enable clock access to tim2
	RCC->APB1ENR |= TIM2EN;
	//set prescaler value
	TIM2->PSC = 1600 - 1;
	//set auto-reload value
	TIM2->ARR = 10000 - 1;
	//clear counter
	TIM2->CNT = 0;
	//enable timer
	TIM2->CR1 = CR1_CEN;
}

void tim2_1hz_interrupt_init(void){
	//enable clock access to tim2
	RCC->APB1ENR |= TIM2EN;
	//set prescaler value
	TIM2->PSC = 1600 - 1;
	//set auto-reload value
	TIM2->ARR = 10000 - 1;
	//clear counter
	TIM2->CNT = 0;
	//enable timer
	TIM2->CR1 = CR1_CEN;
	//enable interrupt for TIM2
	TIM2->DIER |= DIER_UIE;
	//enable TIM2 interrupt in NVIC
	NVIC_EnableIRQ(TIM2_IRQn);
}
