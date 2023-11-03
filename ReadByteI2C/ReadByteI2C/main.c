/*
 * ReadByteI2C.c
 *
 * Created: 9/5/2021
 * Author : Amer Qouneh
 * See Logic Analyzer output image for this program. Addresses and data are visible.
 * Similar to Mazidi's Program 18-4. However, this is modified for ATmega8 instead of ATmega32.
 * Slave address is that of 24FC128 EEPROM used on CPE 427 board.
 * Continuously reads one byte of data from EEPROM.

 */ 


/*
 * Similar to Program 18-4 
 *  Author: Naimi
 */ 


#include <avr/io.h>
#define F_CPU 8000000UL
#include <util/delay.h>

#define EEPROM1_WR 0b10100010	// write EEPROM 1 SLA_W address, lsb = 0 for write
#define EEPROM1_RD 0b10100011	// read EEPROM 1 SLA_R address, lsb = 1 for read

		

void i2c_init(void)
{
  TWSR=0x00;   // Prescalar set to 0
  // SCL frequency = 8 MHz/(16+2(71)(4^0)) = 8MHz/(16+142(1)) = 50.632 kHz
  TWBR=0x47;   // 0x47 = 71 decimal. This sets SCL clock to about 50kHz. 			
  TWCR=0x04;   // Enable TWI module by writing 1 to TWEN		
}
//**********************************************************
void i2c_start(void)
{
  TWCR = (1 << TWINT) | (1 << TWSTA) | (1 << TWEN);
  while ((TWCR & (1 << TWINT)) == 0);
}
//**********************************************************
void i2c_write(unsigned char data)
{
  TWDR = data ;
  TWCR = (1<< TWINT)|(1<<TWEN);
  while ((TWCR & (1 <<TWINT)) == 0);
}
//**********************************************************
unsigned char i2c_read(unsigned char isLast)
{
  if (isLast == 0)		
    TWCR = (1<< TWINT)|(1<<TWEN)|(1<<TWEA);   // if want to read more than 1 byte
  else				
    TWCR = (1<< TWINT)|(1<<TWEN);   // if want to read only 1 byte
  while ((TWCR & (1 <<TWINT)) == 0);
  return TWDR  ;
}
//**********************************************************
void i2c_stop()
{
  TWCR = (1<< TWINT)|(1<<TWEN)|(1<<TWSTO);
}
//**********************************************************


// Program keeps reading from EEPROM to make viewing signals on logic analyzer easier.
int main(void)
{
  unsigned char i = 0 ;
  DDRB |= (1<<PB0);   // PB0 is output. Used as monitor.
  PORTB = 0x01;   // Turn off LED on Port B pin 0 by outputting 1
  			
  i2c_init();   // initialize TWI module
  
  while(1) {
	i2c_start();   // send start condition			
	i2c_write(EEPROM1_WR);   // Slave address EEPROM 1, Write
	  
	i2c_write(0x00);   // high-byte of memory address	
	i2c_write(0x01);   // low-byte of memory address
	
	i2c_start();   // send a Re-start condition  

	i2c_write(EEPROM1_RD);   // Slave address EEPROM 1, Read
  	
	i = i2c_read(1);// read 1 byte only
	i2c_stop();   // send stop condition
	
	// Check if read value is the expected one	
	if (i == 0xAB)
	{
		PORTB &= ~(1<<PB0); // Turn on PORTB pin 0 by outputting a 0
	}		
  }
}

int main101(void) {
	i2c_init();   // initialize TWI module
	
	i2c_start();				// send start condition
	i2c_write(EEPROM1_WR);		// Slave address EEPROM 1, Write
	
	i2c_write(0b00000000);		// high-byte of memory address
	i2c_write(0b00000001);		// low-byte of memory address
	
	//i2c_write(0b11110000);	// Write the value 0b11110000 i.e. 0xF0
	i2c_write(0xAB);			// value to be written to memory
	i2c_stop();
	return 0;
}






// Program reads from EEPROM once.
int main100 (void)
{
	unsigned char i = 0 ;
	DDRB |= (1<<PB0);   // PB0 is output. Used as monitor.
	PORTB = 0x01;   // Turn on LED on Port B pin 0 by outputting 1
	
	i2c_init();   // initialize TWI module
	
	i2c_start();   // send start condition
	i2c_write(EEPROM1_WR);   // Slave address EEPROM 1, Write
	
	i2c_write(0x00);   // high-byte of memory address
	i2c_write(0x01);   // low-byte of memory address
	//i2c_write(0xAB);   // value to be written to memory
	
	i2c_start();   // send a Re-start condition

	i2c_write(EEPROM1_RD);   // Slave address EEPROM 1, Read
	
	i = i2c_read(1);// read 1 byte only
	i2c_stop();   // send stop condition
	
	// Check if read value is the expected one
	if (i == 0xAB)
	{
		while(1){
			PORTB ^= (1<<PB0); // Turn on PORTB pin 0 by outputting a 0
			_delay_ms(500);
		}
	}
	return 0;
}

