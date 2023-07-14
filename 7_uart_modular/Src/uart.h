#ifndef UART_H_
#define UART_H_
#include <stdint.h>

#include "stm32f4xx.h"

void uart2_tx_init(void);
void uart2_write(int ch);

#endif
