/*
 * ReadPageI2C_UART.c
 *
 * Created: 10/13/2021 10:38:51 AM
 * Author : Amer Qouneh
 *
 * Program reads a page (64 bytes) from EEPROM 24FC128. 
 * Then, it sends those bytes to serial port as ASCII.
 *
 */ 

#include <avr/io.h>
#include "UART.h"
#include "EEPROMdev.h"

#define EEPROM1_WR 0b10100010	// write EEPROM 1 SLA_W address, lsb = 0 for write
#define EEPROM1_RD 0b10100011	// read EEPROM 1 SLA_R address, lsb = 1 for read

int main(void)
{
	unsigned char buffer[64];
	unsigned char i;
	unsigned char C1, C2;

	USART_init(MyBaud);
	i2c_init();
	i2c_start();
	i2c_write(EEPROM1_WR);   // Slave address EEPROM 1, Write
	i2c_write(0x00);         // high-byte of memory address
	i2c_write(0x00);         // high-byte of memory address
	i2c_start();             // Repeated Start condition
	i2c_write(EEPROM1_RD);   // Slave address EEPROM 1, Read
	
	// Read the first 63 bytes while sending ACK.
	for (i=0; i<63; ++i) {
		buffer[i] = i2c_read(0);
	}
	// Read the last byte (byte 64) and send a NACK (i.e. don't send an ACK).
	buffer[i] = i2c_read(1);
	i2c_stop();
	while(1){
		// Send read bytes to serial port UART as ASCII.
		for (i=0; i<64; ++i) {
			hex2ascii(buffer[i], &C1, &C2);		
			USART_Transmit(C1);
			USART_Transmit(C2);
			USART_Transmit(',');    // Echo back a carriage return to go to beginning of new line
			USART_Transmit(' ');
		}
	}    
}

