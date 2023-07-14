/*
 * i2c.h
 *
 *  Created on: 4 lip 2023
 *      Author: Piotr
 */

#ifndef I2C_H_
#define I2C_H_

void I2C1_init(void);
void I2C1_byteRead(char saddr, char maddr, char* data);
void I2C1_burstRead(char saddr, char maddr, int n, char* data);
void I2C1_burstWrite(char saddr, char maddr, int n, char* data);



#endif /* I2C_H_ */