/*
 * UART.c
 *
 * Created: 10/13/2021 10:43:02 AM
 *  Author: aq354446
 */ 

#include "UART.h"

static const char asctab[]="0123456789ABCDEF";

void USART_init(UI thebaud){
	UBRRH = (thebaud>>8);
	UBRRL = (UC)(thebaud);
	UCSRB = (1<<RXEN)|(1<<TXEN);
	UCSRC = (1<<URSEL)|(1 << UCSZ0 )|(1 << UCSZ1 );
}

void USART_Transmit(UC data){
	while (!(UCSRA & (1<<UDRE))); // Do nothing until UDR is ready for more data to be written to it
	UDR = data;
}

UC USART_Receive(void){
	while(!(UCSRA & (1<<RXC))); // Do nothing until data have been received and is ready to be read from UDR
	return UDR; // Return the received byte value
}

void USART_Transmit_String(char *msg){
	int k = 0;
	while (msg[k] !=0) {
		USART_Transmit(msg[k]);
		k = k + 1;
	}
}

void hex2ascii(UC inc, UC *c1, UC *c2){
	(*c1)=asctab[(inc>>4)&0x0f];
	(*c2)=asctab[inc& 0x0f];
}

