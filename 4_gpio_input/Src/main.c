#include "stm32f4xx.h"

#define GPIOAEN		(1U<<0)
#define GPIOCEN		(1U<<2)

#define PIN5		(1U<<5)
#define PIN13		(1U<<13)
#define PIN0		(1U<<0)

#define LED_PIN		PIN13
#define BTN			PIN0

int main(void){

	RCC->AHB1ENR |= GPIOAEN;
	RCC->AHB1ENR |= GPIOCEN;

	GPIOA->MODER &=~(1U<<0);
	GPIOA->MODER &=~(1U<<1);
	GPIOC->MODER |= (1U<<26);
	GPIOC->MODER &=~(1U<<27);


	while(1){
		if(!(GPIOA->IDR & BTN)){
			GPIOC->BSRR = LED_PIN;
		}
		else{
			GPIOC->BSRR = (1U<<29);
		}
	}
}
