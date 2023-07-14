#include <stdio.h>
#include <stdint.h>
#include "stm32f4xx.h"
#include "uart.h"
#include "adc.h"

uint32_t sensor_value;
double voltage;

int main(void){

	uart2_rxtx_init();

	pa1_adc_init();

	start_conversion();

	while(1){
		sensor_value = adc_read();
		voltage = (3.3/4095)*sensor_value;
		printf("sensor value: %d \n\r", (int)sensor_value);
	}
}

