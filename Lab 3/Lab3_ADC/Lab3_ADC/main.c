/*
 * ADCtest.c
 *
 * Created: 9/24/2023 1:19:14 PM
 * Author : Amer Qouneh
 */ 

#include <avr/io.h>

#define F_CPU 8000000L

#include "MyUART.h"
#include "MyADC.h"
#include <util/delay.h>

void EEPROM_write(UI address, UC data);
unsigned char EEPROM_read(UI address);

int main(void)
{
	
	UC arr[511];
	UC run = 1;
	UC C1, C2;
	DDRB = 0x01;
	PORTB |= 0x01;
	USART_init(MyBaud);
	
	ADC_init();

	while (run)
	{
		ADCSRA|=(1<<ADSC);
		while((ADCSRA&(1<<ADIF))==0);
		
		// Returned ADC_value is one quarter of the actual value. 
		// Multiply by 4 to know the actual value.
		// Example, 0.5V converts to ADC_value of: (0.5*1024)/5 = 102.4 
		// 102.4/4 = 25.6 in decimal. That's roughly 0x19 in hex. 
		int i = 0;
		UI addr = 0x0000;
		PORTB = 0x01;
		
		//read adc values every 2 ms to get a full period of sinewave with f=1Hz
		while(i < 512){
			arr[i] = start_conversion();
			i++;
			_delay_ms(2);
		}
		
		//reset variables
		i = 0;
		addr = 0x0000;
		PORTB ^=0x01;
		
		//write values to EEPROM
		while(i < 512) {
			EEPROM_write(addr, arr[i]);
			i++;
			addr++;
		}
		
		//reset variables
		i = 0;
		addr = 0;
		
		//read values from EEPROM and write to putty
		while(i < 512){
			UC data = EEPROM_read(addr);
			hex2ascii(data, &C1, &C2);
			USART_Transmit('\n');
			USART_Transmit('\r');
			USART_Transmit(C1);
			USART_Transmit(C2);
			PORTB ^= 0x01;
			i++;
			addr++;
		}
		PORTB = 0x01;
		run = 0;
	}
	return 0 ;
}



void EEPROM_write(UI address, UC data)
{
	/* Wait for completion of previous write */
	while(EECR & (1<<EEWE))
	;
	/* Set up address and data registers */
	EEAR = address;
	EEDR = data;
	/* Write logical one to EEMWE */
	EECR |= (1<<EEMWE);
	/* Start eeprom write by setting EEWE */
	EECR |= (1<<EEWE);
}

unsigned char EEPROM_read(UI address)
{
	/* Wait for completion of previous write */
	while(EECR & (1<<EEWE))
	;
	/* Set up address register */
	EEAR = address;
	/* Start eeprom read by writing EERE */
	EECR |= (1<<EERE);
	/* Return data from data register */
	return EEDR;
}


