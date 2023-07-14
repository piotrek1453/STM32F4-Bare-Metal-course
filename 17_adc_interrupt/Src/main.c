#include <stdio.h>
#include <stdint.h>
#include "stm32f4xx.h"
#include "uart.h"
#include "adc.h"

static void adc_callback(void);

uint32_t sensor_value;
double voltage;

int main(void){

	uart2_rxtx_init();

	pa1_adc_interrupt_init();

	start_conversion();

	while(1){

	}
}

static void adc_callback(void){
	sensor_value=ADC1->DR;
	printf("sensor value: %u\n\r", (int)sensor_value);
}

void ADC_IRQHandler(void){
	//check for EOC in SR
	if(ADC1->SR && SR_EOC){
		//clear EOC
		ADC1->SR &=~ SR_EOC;
		adc_callback();
	}
}
