/*
 * systick.h
 *
 *  Created on: 17 cze 2023
 *      Author: Piotr
 */

#ifndef SYSTICK_H_
#define SYSTICK_H_

void systickDelayMs(int delay);
void systick_1hz_interrupt(void);

#endif /* SYSTICK_H_ */
