/*
 * tim.h
 *
 *  Created on: 25 cze 2023
 *      Author: Piotr
 */

#ifndef TIM_H_
#define TIM_H_

void tim2_1hz_init(void);
void tim2_1hz_interrupt_init(void);

#define SR_UIF	(1U<<0)

#endif /* TIM_H_ */
