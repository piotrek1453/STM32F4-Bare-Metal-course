#include "uart.h"

#define GPIOAEN		(1U<<0)
#define UART2EN		(1U<<17)

#define CR1_TE		(1U<<3)
#define CR1_RE		(1U<<2)
#define CR1_UE		(1U<<13)
#define CR1_RXNEIE	(1U<<5)
#define SR_TXE		(1U<<7)

#define SYS_FREQ	16000000
#define APB1_CLK	SYS_FREQ

#define UART_BAUDRATE 115200

static void uart_set_baudrate(USART_TypeDef *USARTx, uint32_t PeriphClk, uint32_t BaudRate);
static uint16_t compute_uart_bd(uint32_t PeriphClk, uint32_t BaudRate);

void uart2_tx_init(void){
	//config uart
	RCC->AHB1ENR |= GPIOAEN;

	//alternate function
	GPIOA->MODER &=~(1U<<4);
	GPIOA->MODER |= (1U<<5);

	//set alternate af07
	GPIOA->AFR[0] |= (1U<<8);
	GPIOA->AFR[0] |= (1U<<9);
	GPIOA->AFR[0] |= (1U<<10);
	GPIOA->AFR[0] &=~(1U<<11);

	//enable apb1
	RCC->APB1ENR = UART2EN;

	//baudrate
	uart_set_baudrate(USART2, APB1_CLK, UART_BAUDRATE);

	//transfer direction
	USART2->CR1 = CR1_TE;

	//enable uart module
	USART2->CR1 |= CR1_UE;
}

void uart2_rxtx_init(void){
	//config uart
	RCC->AHB1ENR |= GPIOAEN;

	//start pa2
	GPIOA->MODER &=~(1U<<4);
	GPIOA->MODER |= (1U<<5);

	//set alternate pa2 tx mode af07
	GPIOA->AFR[0] |= (1U<<8);
	GPIOA->AFR[0] |= (1U<<9);
	GPIOA->AFR[0] |= (1U<<10);
	GPIOA->AFR[0] &=~(1U<<11);

	//start pa3
	GPIOA->MODER &=~(1U<<6);
	GPIOA->MODER |= (1U<<7);

	//set alternate pa3 rx mode af07
	GPIOA->AFR[0] |= (1U<<12);
	GPIOA->AFR[0] |= (1U<<13);
	GPIOA->AFR[0] |= (1U<<14);
	GPIOA->AFR[0] &=~(1U<<15);
	//enable apb1
	RCC->APB1ENR = UART2EN;

	//baudrate
	uart_set_baudrate(USART2, APB1_CLK, UART_BAUDRATE);

	//transfer direction
	USART2->CR1 = (CR1_TE | CR1_RE);

	//enable uart module
	USART2->CR1 |= CR1_UE;
}

void uart2_rx_interrupt_init(void){
	//config uart
	RCC->AHB1ENR |= GPIOAEN;

	//start pa2
	GPIOA->MODER &=~(1U<<4);
	GPIOA->MODER |= (1U<<5);

	//set alternate pa2 tx mode af07
	GPIOA->AFR[0] |= (1U<<8);
	GPIOA->AFR[0] |= (1U<<9);
	GPIOA->AFR[0] |= (1U<<10);
	GPIOA->AFR[0] &=~(1U<<11);

	//start pa3
	GPIOA->MODER &=~(1U<<6);
	GPIOA->MODER |= (1U<<7);

	//set alternate pa3 rx mode af07
	GPIOA->AFR[0] |= (1U<<12);
	GPIOA->AFR[0] |= (1U<<13);
	GPIOA->AFR[0] |= (1U<<14);
	GPIOA->AFR[0] &=~(1U<<15);
	//enable apb1
	RCC->APB1ENR = UART2EN;

	//baudrate
	uart_set_baudrate(USART2, APB1_CLK, UART_BAUDRATE);

	//transfer direction
	USART2->CR1 = (CR1_TE | CR1_RE);
	//enable rx interrupt
	USART2->CR1 |= CR1_RXNEIE;
	//enable  UART2 interrupt in NVIC
	NVIC_EnableIRQ(USART2_IRQn);

	//enable uart module
	USART2->CR1 |= CR1_UE;
}


static uint16_t compute_uart_bd(uint32_t PeriphClk, uint32_t BaudRate){
	return ((PeriphClk+(BaudRate/2U))/BaudRate);
}

static void uart_set_baudrate(USART_TypeDef *USARTx, uint32_t PeriphClk, uint32_t BaudRate){
	USARTx->BRR = compute_uart_bd(PeriphClk,BaudRate);
}

char uart2_read(void){
	//make sure receive reg is not empty
	while(!(USART2->SR & SR_RXNE)){

	}
	return USART2->DR;
}

void uart2_write(int ch){
	//make sure transmit reg is empty
	while(!(USART2->SR & SR_TXE)){

	}
	//if, then write to transmit reg

	USART2->DR	= (ch & 0xFF);
}

int __io_putchar(int ch){
	uart2_write(ch);
	return ch;
}


