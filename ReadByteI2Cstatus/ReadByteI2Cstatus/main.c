/*
 * ReadByteI2Cstatus.c
 *
 * Created: 10/13/2021 3:01:26 PM
 * Author : aq354446
 */ 

/*
 One can read the status bits and AND them with 0xF8 and display status on a UART terminal.
 If something goes wrong, one can analyze the status code and start debugging.
 For example, if we were expecting a status code of 0x18 but the status was 0x28, then 
 we can debug and figure out why that was so.

*/




#include <avr/io.h>
#include "EEPROMdev.h"


#define F_CPU 8000000UL

#define EEPROM1_WR 0b10100010	// write EEPROM 1 SLA_W address, lsb = 0 for write
#define EEPROM1_RD 0b10100011	// read EEPROM 1 SLA_R address, lsb = 1 for read



unsigned char TWI_Read_Byte(unsigned int addr) {
	unsigned char i = 0 ;
	
	i2c_start();
	while(i2c_readStatus()!= 0x08);

	i2c_write(EEPROM1_WR);   // Slave address EEPROM 1, Write
	while(i2c_readStatus()!= 0x18);
	
	i2c_write((unsigned char)(addr) >> 8);   // Send high-byte of memory address
	while(i2c_readStatus()!= 0x28);
	
	i2c_write((unsigned char)(addr));        // Send low-byte of memory address
	while(i2c_readStatus()!= 0x28);
	
	i2c_start();   // send a Re-start condition
	while(i2c_readStatus()!= 0x10);

	i2c_write(EEPROM1_RD);   // Slave address EEPROM 1, Read
	while(i2c_readStatus()!= 0x40);
	
	i = i2c_read(1);// read 1 byte only
	
	i2c_stop();   // send stop condition
	
	return i;
}


int main(void)
{
    unsigned int address = 0x00;
	unsigned char datum;

    DDRB |= (1<<PB0);   // PB0 is output. Used as monitor.
    PORTB = 0x01;   // Turn off LED on Port B pin 0 by outputting 1
	
	i2c_init();   // initialize TWI module
	datum = TWI_Read_Byte(address);
	
	if (datum == 0xAB)
	{
		PORTB &= ~(1<<PB0); // Turn on PORTB pin 0 by outputting a 0
	}
	return 0;	
}

