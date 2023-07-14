#include "stm32f4xx.h"

#define TIM2EN	(1U<<0)
#define TIM3EN	(1U<<1)
#define CR1_CEN	(1U<<0)
#define OC_TOGGLE ((1U<<4) | (1U<<5))
#define CCER_CC1E	  (1U<<0)
#define GPIOAEN		(1U<<0)
#define AFR5_TIM	(1U<<20)
#define AFR6_TIM	(6U<<25)
#define CCER_CC1S	(1U<<0)

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

void tim2_pa5_output_compare(void){
	//enable clock access to GPIOA
	RCC->AHB1ENR |= GPIOAEN;
	//set pa5 mode to alternate function
	GPIOA->MODER &=~ (1U<<10);
	GPIOA->MODER |=	 (1U<<11);
	//set pa5 alternate function type to TIM2_CH1
	GPIOA->AFR[0] |= AFR5_TIM;
	//enable clock access to tim2
	RCC->APB1ENR |= TIM2EN;
	//set prescaler value
	TIM2->PSC = 1600 - 1;
	//set auto-reload value
	TIM2->ARR = 10000 - 1;
	//set output compare toggle mode
	TIM2->CCMR1 = OC_TOGGLE;
	//enable tim2 channel 1 in compare mode
	TIM2->CCER |= CCER_CC1E;



	//clear counter
	TIM2->CNT = 0;
	//enable timer
	TIM2->CR1 = CR1_CEN;
}

void tim3_pa6_input_capture(void){
	//enable clock access to gpioa
	RCC->AHB1ENR |= GPIOAEN;
	//set pa6 mode to alternate function
	GPIOA->MODER &=~(1U<<12);
	GPIOA->MODER |=	(1U<<13);
	//set pa6 alternate function type to TIM3_CH1 (AF02)
	GPIOA->AFR[0] |= AFR6_TIM;
	//enable clock access to tim3
	RCC->APB1ENR |= TIM3EN;
	//set prescaler
	TIM3->PSC = 16000-1;
	//set ch1 to input capture
	TIM3->CCMR1	|= CCER_CC1S;
	//enable capture on tim3
	TIM3->CCER	|= CCER_CC1E;
	//enable tim3
	TIM3->CR1 = CR1_CEN;
}
