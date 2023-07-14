#include <stdio.h>
#include <stdint.h>
#include "stm32f4xx.h"
#include "uart.h"
#include "adc.h"
#include "systick.h"
#include "tim.h"

#define GPIOAEN (1U<<0)
#define PIN5	(1U<<5)

#define LED_PIN	PIN5

static void timer_callback(void);

uint32_t sensor_value;
double voltage;

int main(void){

	RCC->AHB1ENR	|=	GPIOAEN;

	GPIOA->MODER	|=	(1U<<10);
	GPIOA->MODER	&=~	(1U<<11);

	uart2_tx_init();
	tim2_1hz_interrupt_init();

	while(1){
		asm("nop");
	}
}

static void timer_callback(void){
	printf("A second passed ! \n\r");
	GPIOA->ODR	^=	LED_PIN;
}

void TIM2_IRQHandler(void){
	//clear uif
	TIM2->SR &=~SR_UIF;
	timer_callback();
}
