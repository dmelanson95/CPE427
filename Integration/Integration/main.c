/*
 * main.c
 *
 * Created: 10/26/2023 2:37:17 PM
 *  Author: corbin
 */ 

#define F_CPU 8000000UL			// 8 MHz Crystal

#include <avr/io.h>
#include <util/delay.h>


int main(void) {
	DDRD &= ~(1 << PD6); // PD6 as input (SWITCH 4)
	DDRD &= ~(1 << PD7); // PD7 as input (SWITCH 5)
	

	DDRD |= (1 << PD5); // PD5 as output
	
	
	while (1) {
		// Check the values of PD6 and PD7 to determine the mode
		if (!(PIND & (1 << PD6)) && !(PIND & (1 << PD7))) {
			
			// Mode 00: Data Acquisition
			PORTD ^= (1 << PD5); // Toggle the LED state
			_delay_ms(50);     // Delay for half a second
			
			} 
			
			else if (!(PIND & (1 << PD6)) && (PIND & (1 << PD7))) {
				
				// Mode 01: Control
				PORTD ^= (1 << PD5); // Toggle the LED state
				_delay_ms(500);     // Delay for half a second
			
			}
			
			else if ((PIND & (1 << PD6)) && !(PIND & (1 << PD7))) {
				 
				// Mode 10: Idle
				PORTD ^= (1 << PD5); // Toggle the LED state
				_delay_ms(1000);     // Delay for half a second
			
		}
	}
	
	return 0;
}
