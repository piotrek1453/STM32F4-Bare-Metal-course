//LED:
//pin 13
//port c

#define PERIPH_BASE 		(0x40000000UL)
#define AHB1PERIPH_OFFSET	(0x00020000UL)
#define AHB1PERIPH_BASE		(PERIPH_BASE + AHB1PERIPH_OFFSET)

#define GPIOA_OFFSET		(0x0000UL)
#define GPIOA_BASE			(AHB1PERIPH_BASE + GPIOA_OFFSET)

#define GPIOC_OFFSET		(0X0800UL)
#define GPIOC_BASE			(AHB1PERIPH_BASE + GPIOC_OFFSET)

#define RCC_OFFSET			(0x3800UL)
#define RCC_BASE			(AHB1PERIPH_BASE + RCC_OFFSET)


#define AHB1ENR_OFFSET		(0x30UL)
#define RCC_AHB1EN_R		(*(volatile unsigned int *)(RCC_BASE + AHB1ENR_OFFSET))

#define MODE_R_OFFSET		(0x00UL)
#define GPIOA_MODE_R		(*(volatile unsigned int *)(GPIOA_BASE + MODE_R_OFFSET))
#define GPIOC_MODE_R		(*(volatile unsigned int *)(GPIOC_BASE + MODE_R_OFFSET))

#define GPIOAEN			(1U<<0)
#define GPIOCEN			(1U<<2)

#define PIN5			(1U<<5)
#define PIN13			(1U<<13)

#define LED_PIN1		PIN5
#define LED_PIN2		PIN13

#define OD_R_OFFSET		(0x14UL)
#define GPIOA_OD_R		(*(volatile unsigned int *)(GPIOA_BASE + OD_R_OFFSET))
#define GPIOC_OD_R		(*(volatile unsigned int *)(GPIOC_BASE + OD_R_OFFSET))


/*
 * (1U<<10)
 * &=~(1U<<11) GPIOA*/
/*
 * (1U<<26)
 * &=~(1U<<27) GPIOC*/


int main(void)
{
	/*enable clock to GPIOA
	 * set PA5 and PC13 as output
	 */

	RCC_AHB1EN_R |= GPIOAEN;
	RCC_AHB1EN_R |= GPIOCEN;

	GPIOA_MODE_R |= (1U<<10);
	GPIOA_MODE_R &=~ (1U<<11);
	GPIOC_MODE_R |= (1U<<26);
	GPIOC_MODE_R &=~ (1U<<27);

	while(1){
		/*set PA5 and PC 13 high
		 *
		 */
		//GPIOA_OD_R |= LED_PIN1;
		//GPIOC_OD_R |= LED_PIN2;
		//toggle led PA5 and PC13
		GPIOA_OD_R ^= LED_PIN1;
		GPIOC_OD_R ^= LED_PIN2;
		for(int i=0; i<200000;++i){}
	}
}
