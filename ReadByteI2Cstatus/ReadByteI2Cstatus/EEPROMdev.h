/*
 * EEPROMdev.h
 *
 * Created: 10/13/2021 11:46:19 AM
 *  Author: Amer Qouneh
 */ 


#ifndef EEPROMDEV_H_
#define EEPROMDEV_H_

#include <avr/io.h>

void i2c_init(void);
void i2c_start(void);
void i2c_write(unsigned char data);
unsigned char i2c_read(unsigned char isLast);
unsigned char i2c_readStatus(void);
void i2c_stop();

#endif /* EEPROMDEV_H_ */