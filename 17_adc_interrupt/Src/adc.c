#include "stm32f4xx.h"
#include "adc.h"
#include <stdint.h>

#define GPIOAEN	(1U<<0)
#define ADC1EN	(1U<<8)
#define ADC_CH1		(1U<<0)
#define ADC_SEQ_LEN_1	0x00
#define CR2_ADON	(1U<<0)
#define CR2_SWSTART (1U<<30)
#define CR2_CONT	(1U<<1)
#define CR1_EOCIE	(1U<<5)


void pa1_adc_init(void){
	//enable clock access to gpioa
	RCC->AHB1ENR |= GPIOAEN;

	//set PA1 mode to adc
	GPIOA->MODER |= (1U<<2);
	GPIOA->MODER |= (1U<<3);

	//enable clock access to adc
	RCC->APB2ENR |= ADC1EN;
	//configure adc params

	//conversion sequence start
	ADC1->SQR3 = ADC_CH1;

	//conversion sequence length
	ADC1->SQR1 = ADC_SEQ_LEN_1;

	//enable adc
	ADC1->CR2 |= CR2_ADON;
}

void pa1_adc_interrupt_init(void){
	//enable clock access to gpioa
	RCC->AHB1ENR |= GPIOAEN;

	//set PA1 mode to adc
	GPIOA->MODER |= (1U<<2);
	GPIOA->MODER |= (1U<<3);

	//enable clock access to adc
	RCC->APB2ENR |= ADC1EN;
	//configure adc params

	//enable EOC interrupt
	ADC1->CR1 |= CR1_EOCIE;

	//enable ADC interrupt in NVIC
	NVIC_EnableIRQ(ADC_IRQn);
	//conversion sequence start
	ADC1->SQR3 = ADC_CH1;

	//conversion sequence length
	ADC1->SQR1 = ADC_SEQ_LEN_1;


	//enable adc
	ADC1->CR2 |= CR2_ADON;
}

void start_conversion(void){
	//enable cont conversion
	ADC1->CR2 |= CR2_CONT;

	ADC1->CR2 |= CR2_SWSTART;
}

uint32_t adc_read(void){
	//wait for conversion to complete
	while(!(ADC1->SR & SR_EOC)){}
	//read converted result
	return ADC1->DR;
}
