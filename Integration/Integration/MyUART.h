/*
 * MyUART.h
 *
 * Created: 11/9/2023 3:34:19 PM
 *  Author: David Melanson
 */ 

#ifndef MYUART_H_INCLUDED
#define MYUART_H_INCLUDED

typedef unsigned char UC;
typedef unsigned int UI;
static const char asctab[]="0123456789ABCDEF";


#define BAUD 9600
#define MyBaud F_CPU/BAUD/16 - 1

void USART_init(UI thebaud);
void USART_Transmit(UC data);
UC USART_Receive(void);
void USART_Transmit_String(char *msg);
void hex2ascii(UC inc, UC *c1, UC *c2);

#endif





