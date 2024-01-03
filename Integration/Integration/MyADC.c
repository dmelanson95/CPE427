/*
 * MyADC.c
 *
 * Created: 9/24/2023 1:25:53 PM
 *  Author: David Melanson
 */ 


#include <avr/io.h>
#include "MyADC.h"


void ADC_init(void){
	ADCSRA |= (1<<ADEN) | (1<<ADPS2) | (1<<ADPS1) | (1<<ADPS0);		// ADC enable, pre-scalar set to divide clock by 128
	ADMUX |= ((1 << REFS0) | (1<<ADLAR));											// Vref is Vcc, left-adjuste)d
	ADMUX &= ~((1 << MUX3)|(1<<MUX2));
}

unsigned char read_ADC0(void){
	ADCSRA |= (1<<ADSC);
	while (!(ADCSRA & (1<<ADIF)));
	ADMUX |= (1<<ADLAR);   // Left adjust result.
	return (ADCH);   //Take only the high 8 bits and drop the lower 2 bits. Equivalent to dividing result by 4.
}

float read_ADC1(void){
	ADMUX = ((ADMUX & ~(1 << MUX1)) | (1 << MUX0));
	ADCSRA |= (1<<ADSC);
	while (!(ADCSRA & (1<<ADIF)));
	ADMUX |= (1<<ADLAR);											// Left adjust result.
	return (float)(ADCH);									//Take only the high 8 bits and drop the lower 2 bits. Equivalent to dividing result by 4.
}

float read_ADC2(void){
	ADMUX = (ADMUX & ~(1 << MUX0)) | (1 << MUX1);
	ADCSRA |= (1<<ADSC);
	while (!(ADCSRA & (1<<ADIF)));
	ADMUX |= (1<<ADLAR);											// Left adjust result.
	return (float)(ADCH);										//Take only the high 8 bits and drop the lower 2 bits. Equivalent to dividing result by 4.
}

unsigned char read_ADC1_reg(void){
	ADMUX = ((ADMUX & ~(1 << MUX1)) | (1 << MUX0));
	ADCSRA |= (1<<ADSC);
	while (!(ADCSRA & (1<<ADIF)));
	ADMUX |= (1<<ADLAR);											// Left adjust result.
	return (ADCH);
}

unsigned char read_ADC2_reg(void){
	ADMUX = (ADMUX & ~(1 << MUX0)) | (1 << MUX1);
	ADCSRA |= (1<<ADSC);											//start conversion
	while (!(ADCSRA & (1<<ADIF)));									//wait for ack
	ADMUX |= (1<<ADLAR);											// Left adjust result.
	return (ADCH);										//Take only the high 8 bits and drop the lower 2 bits. Equivalent to dividing result by 4.
}