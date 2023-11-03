/*
 * UART.h
 *
 * Created: 10/13/2021 10:39:38 AM
 *  Author: Amer Qouneh
 */ 


#ifndef UART_H_
#define UART_H_


#include <avr/io.h>

typedef unsigned char UC;
typedef unsigned int UI;

#define F_CPU 8000000L
#define BAUD 9600
#define MyBaud F_CPU/BAUD/16 - 1

void USART_init(UI thebaud);
void USART_Transmit(UC data);
UC USART_Receive(void);
void USART_Transmit_String(char *msg);
void hex2ascii(UC inc, UC *c1, UC *c2);

#endif /* UART_H_ */