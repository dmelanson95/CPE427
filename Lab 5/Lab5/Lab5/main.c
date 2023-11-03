/*
 * PWMTimer1Lab.c
 * Updated to main.c in Lab5
 *
 * Created: 10/21/2021 8:48:09 AM
 * Updated: 10/19/2023
 * Original Code by : Example from slides: Brainiac Intervention3b-CPE2
 * Utilized by David Melanson, Corbin Veitch
 */ 


#define F_CPU 8000000UL			// 8 MHz Crystal
#include <avr/io.h>
#include <util/delay.h>

#define duty_cycle25 63
#define duty_cycle50 127
#define duty_cycle75 191
#define CPE_Relay (1<<PC4)
#define CPE_Enable (1<<PD5)

void send_CPE_Relay();
void send_CPE_Enable();

int main(void){
	
	DDRB |= (1<<DDB1);			//  1. Set PB1 to Output

	TCCR1A  = (1 << WGM10);		//  2. Set Phase Correct PWM Mode 8bit
	TCCR1A |= (1 << COM1A1);	//  3. Set None-Inverting Mode
	TCCR1B  = (1 << CS10);		//  4. (No) Pre-Scaler

	OCR1A = 255;
	
	while(1){};
}

void send_CPE_Relay(){
	_delay_ms(1000);
	DDRC |= CPE_Relay;
	PORTC |= CPE_Relay;
	_delay_ms(2000);
	PORTC &= !(CPE_Relay);
}

void send_CPE_Enable(){
	_delay_ms(1000);
	DDRD |= CPE_Enable;
	PORTD |= CPE_Enable;
}

