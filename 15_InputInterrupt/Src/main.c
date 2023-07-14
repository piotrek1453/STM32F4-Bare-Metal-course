#include <stdio.h>
#include <stdint.h>
#include "stm32f4xx.h"
#include "uart.h"
#include "adc.h"
#include "systick.h"
#include "tim.h"
#include "exti.h"

#define GPIOAEN (1U<<0)
#define PIN5	(1U<<5)

#define LED_PIN	PIN5

static void exti_callback(void);

int timestamp;
//connect pa5 to pa6
int main(void){

		RCC->AHB1ENR	|=	GPIOAEN;

		GPIOA->MODER	|=	(1U<<10);
		GPIOA->MODER	&=~	(1U<<11);


	pc13_exti_init();
	uart2_tx_init();

	printf("starto desu\n\r");

	while(1){

	}
}

static void exti_callback(void){
	printf("BTN pressed \n\r");
	GPIOA->ODR ^= LED_PIN;
}

void EXTI15_10_IRQHandler(void){
	if((EXTI->PR & LINE13)){
		//clear PR flag
		EXTI->PR |= LINE13;
		//call function
		exti_callback();
	}
}
