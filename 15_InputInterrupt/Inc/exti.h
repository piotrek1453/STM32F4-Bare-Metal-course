/*
 * exti.h
 *
 *  Created on: 30 cze 2023
 *      Author: Piotr
 */

#ifndef EXTI_H_
#define EXTI_H_


#include "stm32f4xx.h"

void pc13_exti_init(void);

#define LINE13	(1U<<13)

#endif /* EXTI_H_ */
