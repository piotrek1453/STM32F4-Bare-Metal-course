#include "stm32f4xx.h"

#define GPIOBEN	(1U<<1)
#define I2C1EN	(1U<<21)
#define CR1_PE	(1U<<0)
#define SR2_BUSY (1U<<1)
#define CR1_START (1U<<8)
#define I2C_SB	(1U<<0)
#define SR1_ADDR (1U<<1)
#define SR1_TXE (1U<<7)
#define CR1_ACK (1U<<10)
#define CR1_STOP (1U<<9)
#define SR1_RXNE (1U<<6)
#define SR1_BTF	(1U<<2)
#define SR1_SB	(1U<<0)

#define I2C_100KHZ	80
#define SD_MODE_MAX_RISE_TIME 17

//pb8 scl
//pb9 sda
void I2C1_init(void){
	//enable clk to I2C1
	RCC->AHB1ENR |= GPIOBEN;
	//configure scl and sda lines
	//set pb8 and pb9 mode to af04
	GPIOB->MODER &=~ (1U<<16);
	GPIOB->MODER |=  (1U<<17);

	GPIOB->MODER &=~ (1U<<18);
	GPIOB->MODER |=  (1U<<19);
	//output type to open drain
	GPIOB->OTYPER |= (1U<<8);
	GPIOB->OTYPER |= (1U<<9);
	//enable pb8 pb9 pullup resistors
	GPIOB->PUPDR |= (1U<<16);
	GPIOB->PUPDR &=~(1U<<17);

	GPIOB->PUPDR |= (1U<<18);
	GPIOB->PUPDR &=~(1U<<19);
	//set alternate function to AF04
	GPIOB->AFR[1]&=~(1U<<0);
	GPIOB->AFR[1]&=~(1U<<1);
	GPIOB->AFR[1]|=(1U<<2);
	GPIOB->AFR[1]&=~(1U<<3);
	GPIOB->AFR[1]&=~(1U<<4);
	GPIOB->AFR[1]&=~(1U<<5);
	GPIOB->AFR[1]|=(1U<<6);
	GPIOB->AFR[1]&=~(1U<<7);
	//enable clk to I2C1
	RCC->APB1ENR |= I2C1EN;
	//enter reset mode
	I2C1->CR1 |= (1U<<15);
	//set I2C speed to 16MHz
	I2C1->CR2 |= (1U<<4);
	//set I2C to standard mode
	I2C1->CCR |= I2C_100KHZ;
	//set rise time
	I2C1->TRISE |= SD_MODE_MAX_RISE_TIME;
	//enable I2C1
	I2C1->CR1 |= CR1_PE;
}

void I2C1_byteRead(char saddr, char maddr, char* data){
		volatile int tmp;
		//wait till bus is not busy
		while((I2C1->SR2 & SR2_BUSY)) asm("nop");
		//generate the start
		I2C1->CR1 |= CR1_START;
		//wait until start bit is set
		while(!(I2C1->SR1 & I2C_SB)) asm("nop");
		//transmit slave address+write
		I2C1->DR |= saddr << 1;
		//wait until addr flag is set
		while(!(I2C1->SR1 & SR1_ADDR)) asm("nop");
		//clear addr flag
		tmp = I2C1->SR2;
		//send memory address
		I2C1->DR = maddr;
		//wait until transmitter is empty
		while(!(I2C1->SR1 & SR1_TXE)) asm("nop");
		//generate restart
		I2C1->CR1 |= CR1_START;
		//wait until start flag is set
		while(!(I2C1->SR1 & SR1_SB)) asm("nop");
		//transmit slave address+read
		I2C1->DR |= saddr << 1 | 1;
		//wait until address flag is set
		while(!(I2C1->SR1 & SR1_ADDR)) asm("nop");
		//disable acknowledge
		I2C1->CR1 &=~ CR1_ACK;
		//clear addr flag
		tmp = I2C1->SR2;
		//generate stop after data received
		I2C1->CR1 |= CR1_STOP;
		//wait until RXNE set
		while(!(I2C1->SR1 & SR1_RXNE)) asm("nop");
		//read data from DR
		*data++ = I2C1->DR;
}

void I2C1_burstRead(char saddr, char maddr, int n, char* data){
	volatile int tmp;
	//wait till bus not busy
	while((I2C1->SR2 & SR2_BUSY)) asm("nop");
	//generate start
	I2C1->CR1 |= CR1_START;
	//wait until start flag is set
	while(!(I2C1->SR1 & I2C_SB)) asm("nop");
	//transmit slave address+write
	I2C1->DR = saddr << 1;
	//wait till address flag is set
	while(!(I2C1->SR1 & SR1_ADDR)) asm("nop");
	//clear addr flag
	tmp = I2C1->SR2;
	//wait until transmitter empty
	while(!(I2C1->SR1 & SR1_TXE)) asm("nop");
	//generate restart
	I2C1->CR1 |= CR1_START;
	//wait till start bit set
	while(!(I2C1->SR1 & SR1_SB)) asm("nop");
	//transmit slabe address+read
	tmp = I2C1->SR2;
	//enable acknowledge
	I2C1->CR1 |= CR1_ACK;

	while(n > 0U){
		//if one byte
		if(n == 1U){
			//disable acknowledge
			I2C1->CR1 &=~ CR1_ACK;
			//generate stop
			I2C1->CR1 |= CR1_STOP;
			//wait for RXNE to be set
			while(!(I2C1->SR1 & SR1_RXNE)) asm("nop");
			//read data from DR
			*data++ = I2C1->DR;
			break;
		}
		else{
			//wait til RXNE flag set
			while(!(I2C1->SR1 & SR1_RXNE)) asm("nop");
			//read data from DR
			(*data++) = I2C1->DR;

			--n;
		}
	}
}

void I2C1_burstWrite(char saddr, char maddr, int n, char* data){
	volatile int tmp;
	//wait till bus not busy
	while(!(I2C1->SR1 & SR2_BUSY)) asm("nop");
	//generate start
	I2C1->CR1 |= CR1_START;
	//wait till start flag set
	while(!(I2C1->SR1 & I2C_SB)) asm("nop");
	//transmit slave address
	I2C1->DR = saddr << 1;
	//wait until addr flag set
	while(!(I2C1->SR1 & SR1_ADDR)) asm("nop");
	//clear addr flag
	tmp = I2C1->SR2;
	//wait til DR empty
	while(!(I2C1->SR1 & SR1_TXE)) asm("nop");
	//send memory address
	I2C1->DR = maddr;
	for(int i = 0; i < n; ++i){
		//wait until data register empty
		while(!(I2C1->SR1 & SR1_TXE)) asm("nop");
		//transmit memory address
		I2C1->DR = *data++;
	}
	//wait til transfer finished
	while(!(I2C1->SR1 & SR1_BTF)) asm("nop");
	//generate stop
	I2C1->CR1 |= CR1_STOP;
}

