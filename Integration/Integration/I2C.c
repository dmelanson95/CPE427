/*
* I2C.c
* Written by David Melanson
* Functions taken from file provided by Amer Quoneh
*/

#include "I2C.h"
#include <avr/io.h>

void i2c_write(unsigned char data)
{
  TWDR = data;
  TWCR = (1<< TWINT)|(1<<TWEN);
  while ((TWCR & (1 <<TWINT)) == 0);
}

void i2c_start(void)
{
  TWCR = (1 << TWINT) | (1 << TWSTA) | (1 << TWEN);
  while ((TWCR & (1 << TWINT)) == 0);
}

void i2c_stop()
{
  TWCR = (1<< TWINT)|(1<<TWEN)|(1<<TWSTO);
}

void i2c_init(void)
{
  TWSR=0x00;			
  TWBR=0x47;   // check what value needs to be for 8 MHz crystal			
  TWCR=0x04;			
}

unsigned char i2c_read(unsigned char isLast)
{
  if (isLast == 0)		
    TWCR = (1<< TWINT)|(1<<TWEN)|(1<<TWEA);   // if want to read more than 1 byte
  else				
    TWCR = (1<< TWINT)|(1<<TWEN);   // if want to read only 1 byte
  while ((TWCR & (1 <<TWINT)) == 0);
  return TWDR;
}