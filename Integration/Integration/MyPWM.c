/*
 * PWMTimer1Lab.c
 * Updated to main.c in Lab5
 *
 * Created: 10/21/2021 8:48:09 AM
 * Updated: 10/19/2023
 * Original Code by : Example from slides: Brainiac Intervention3b-CPE2
 * Utilized by David Melanson, Corbin Veitch
 */ 


//#define F_CPU 8000000UL			// 8 MHz Crystal
#include <avr/io.h>
#include <util/delay.h>
#include "MyPWM.h"

void PWM_init(){
	//also inits PB2 relay pin as output
	DDRB |= (1<<PB2) | (1<<DDB1);				//  1. Set PB1 and 2 to Output
	
	TCCR1A  = (1 << WGM10);						//  2. Set Phase Correct PWM Mode 8bit
	TCCR1A |= (1 << COM1A1);					//  3. Set None-Inverting Mode
	TCCR1B |= ((1 << CS11) | (1 << CS10));		//  4. Pre-Scaler of 64

	OCR1A = 255;								// Value for OCR1A resulting in ~500Hz
	//start at 100% duty cycle for 20 ms to start quickly
	_delay_ms(20);
}

void CPE_relay_on(){
	PORTB |= (CPE_Relay);		//set relay - PB2 high
}

void CPE_relay_off(){
	PORTB &= !(CPE_Relay);
}

void send_CPE_Enable(){
	//sets enable pin as output and sets high
	DDRD |= CPE_Enable;
	PORTD |= CPE_Enable;
}

