//LED:
//pin 13
//port c
#include <stdint.h>

#define PERIPH_BASE 		(0x40000000UL)
#define AHB1PERIPH_OFFSET	(0x00020000UL)
#define AHB1PERIPH_BASE		(PERIPH_BASE + AHB1PERIPH_OFFSET)

#define GPIOA_OFFSET		(0x0000UL)
#define GPIOA_BASE			(AHB1PERIPH_BASE + GPIOA_OFFSET)

#define GPIOC_OFFSET		(0X0800UL)
#define GPIOC_BASE			(AHB1PERIPH_BASE + GPIOC_OFFSET)

#define RCC_OFFSET			(0x3800UL)
#define RCC_BASE			(AHB1PERIPH_BASE + RCC_OFFSET)




#define GPIOAEN			(1U<<0)
#define GPIOCEN			(1U<<2)

#define PIN5			(1U<<5)
#define PIN13			(1U<<13)

#define LED_PIN1		PIN5
#define LED_PIN2		PIN13


#define __IO volatile

typedef struct
{
	__IO uint32_t MODER;
	__IO uint32_t DUMMY[4];
	__IO uint32_t ODR;
} GPIO_TypeDef;

typedef struct
{
	__IO uint32_t DUMMY[12];
	__IO uint32_t AHB1ENR;
} RCC_TypeDef;

#define RCC			((RCC_TypeDef*) RCC_BASE)
#define GPIOA		((GPIO_TypeDef*) GPIOA_BASE)
#define GPIOC		((GPIO_TypeDef*) GPIOC_BASE)

int main(void)
{
	/*enable clock to GPIOA
	 * set PA5 and PC13 as output
	 */
	RCC->AHB1ENR |= GPIOAEN;
	RCC->AHB1ENR |= GPIOCEN;
	GPIOA->MODER |= (1U<<10);
	GPIOA->MODER &=~ (1U<<11);
	GPIOC->MODER |= (1U<<26);
	GPIOC->MODER &=~ (1U<<27);

	while(1){
		GPIOA->ODR ^= LED_PIN1;
		GPIOC->ODR ^= LED_PIN2;
		for(int i = 0;i<100000;++i){}
	}
}
