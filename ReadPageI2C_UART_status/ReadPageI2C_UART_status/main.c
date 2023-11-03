/*
 * ReadPageI2C_UART_status.c
 *
 * Created: 10/13/2021 3:54:46 PM
 * Author : Amer Qouneh
 */ 

#include <avr/io.h>

#include "UART.h"
#include "EEPROMdev.h"

#define EEPROM1_WR 0b10100010	// write EEPROM 1 SLA_W address, lsb = 0 for write
#define EEPROM1_RD 0b10100011	// read EEPROM 1 SLA_R address, lsb = 1 for read

unsigned char buffer[64];


unsigned char TWI_Read_Page(unsigned int addr) {
	
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
	
	
	// Read the first 63 bytes while sending ACK.
	for (i=0; i<63; ++i) {
		buffer[i] = i2c_read(0);
		while(i2c_readStatus()!= 0x50);

	}
	// Read the last byte (byte 64) and send a NACK (i.e. don't send an ACK).
	buffer[i] = i2c_read(1);
	while(i2c_readStatus()!= 0x58);
	
	i2c_stop();	

	return 0;
}



int main(void)
{
	unsigned char i;
	unsigned char C1, C2;
	unsigned int startingAddress = 0x00;

	USART_init(MyBaud);
	i2c_init();	
	
	TWI_Read_Page(startingAddress);	
	
	// Send read bytes to serial port UART as ASCII.
	for (i=0; i<64; ++i) {
		hex2ascii(buffer[i], &C1, &C2);
		USART_Transmit(C1);
		USART_Transmit(C2);
		//USART_Transmit('\t');
		USART_Transmit('\n');    // Echo back a new line
		USART_Transmit('\r');    // Echo back a carriage return to go to beginning of new line
	}
}

