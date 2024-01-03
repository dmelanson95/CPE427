
#include <avr/io.h>
#include "MyADC.h"


void ADC_init(void){
	ADCSRA |= (1<<ADEN) | (1<<ADPS2) | (1<<ADPS1) | (1<<ADPS0);   // ADC enable, pre-scalar set to divide clock by 128
	ADMUX |= (1<<REFS0) | (1<<ADLAR);   // Vref is Vcc, left-adjusted
}


unsigned char start_conversion(void){
	ADCSRA |= (1<<ADSC);
	while (!(ADCSRA & (1<<ADIF)));
	ADMUX |= (1<<ADLAR);   // Left adjust result.
	return ADCH;   //Take only the high 8 bits and drop the lower 2 bits. Equivalent to dividing result by 4.
}
