#include "stm32f4xx.h"

#define GPIOAEN		(1U<<0)
#define GPIOCEN		(1U<<2)
#define PIN5		(1U<<5)
#define PIN13		(1U<<13)
#define LED_PIN1		PIN5
#define LED_PIN2		PIN13

int main(void){

	RCC->AHB1ENR |= GPIOAEN;
	RCC->AHB1ENR |= GPIOCEN;

	GPIOA->MODER |= (1U<<10);
	GPIOA->MODER &=~(1U<<11);
	GPIOC->MODER |= (1U<<26);
	GPIOC->MODER &=~(1U<<27);

	while(1){
		GPIOA->BSRR = LED_PIN1;
		GPIOC->BSRR = LED_PIN2;
		for(int i=0;i<100000;++i){}

		GPIOA->BSRR = (1U<<21);
		GPIOC->BSRR = (1U<<29);
		for(int i=0;i<100000;++i){}
	}
}
