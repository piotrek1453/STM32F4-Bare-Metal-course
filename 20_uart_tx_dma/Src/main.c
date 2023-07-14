#include <stdio.h>
#include <stdint.h>
#include "stm32f4xx.h"
#include "uart.h"

#define GPIOAEN (1U<<0)
#define GPIOA_5	(1U<<5)

#define LED_PIN	GPIOA_5

static void uart_callback(void);

int main(void){

	char message[31]="Hello from STM32 DMA transfer\n\r";

	RCC->AHB1ENR |= GPIOAEN;

	GPIOA->MODER |= (1U<<10);
	GPIOA->MODER &=~(1U<<11);

	uart2_tx_init();
	dma1_stream6_init((uint32_t)message, (uint32_t)&USART2->DR, 31);

	while(1){
		asm("nop");
	}
}

static void dma_callback(void){
	GPIOA->ODR |= LED_PIN;
}

void DMA1_Stream6_IRQHandler(void){
	//check for transfer complete interrupt
	if(DMA1->HISR & HISR_TCIF6){
		//clear flag
		DMA1->HIFCR &=~ HIFCR_CTCIF6;
		//do something
		dma_callback();
	}

}
