/*
 * main.c
 *
 * Created: 10/26/2023 2:37:17 PM
 *  Author: David Melanson and Corbin Veitch
 */ 
#include <avr/io.h>
#define F_CPU 8000000UL			// 8 MHz Crystal

#include <util/delay.h>
#include <avr/interrupt.h>
#include "PID.h"
#include "MyADC.h"
#include "MyUART.h"
#include "MyPWM.h"
#include "I2C.h"

uint8_t buff[64];
uint8_t control = 0;

void blinkInit();

int main(void) {
	
	DDRD &= ~(1 << PD6); // PD6 as input (SWITCH 4)
	DDRD &= ~(1 << PD7); // PD7 as input (SWITCH 5)

	DDRD |= (1 << PD5); // PD5 as output
	// Check the values of PD6 and PD7 to determine the mode
	if (!(PIND & (1 << PD6)) && !(PIND & (1 << PD7))) {
		// Mode 00: Data Acquisition
		uint8_t curr_page = 0xFF;
		uint16_t curr_val = 1;
		//desired blink value for about .25s blink
		ADC_init();
		i2c_init();
		send_CPE_Enable();				//enables ee board to function
		while(--curr_page){
			if(!(!(PIND & (1 << PD6)) && !(PIND & (1 << PD7)))){break;}
			for(int i = 0; i < 64; i++){
				buff[i] = read_ADC1_reg();			// measured
				buff[++i] = read_ADC2_reg();		// desired
				_delay_ms(50);
			}
			i2c_start();
			i2c_write(EEPROM1_WR);
			i2c_write((uint8_t)(curr_val >> 8)&0xFF);			//high byte memory address
			i2c_write((uint8_t)(curr_val)&0xFF);				//low byte memory address
			//write one page at a time
			for(int i = 0; i < 64; i++) {
				i2c_write(buff[i]);
			}
			i2c_stop();
			curr_val = curr_val+64;							//increment starting memory address each loop32*64
		}
		//TIMSK &= ~0x01;
		PORTD ^= (1 << PD5);
		i2c_start();
		i2c_write(EEPROM1_WR);
		i2c_write(0x00);			//high byte memory address
		i2c_write(0x00);			//low byte memory address
		i2c_write((0xFF-curr_page));
		i2c_stop();
		PORTD |= (CPE_Enable);
		return 0;
	}	
	else if (!(PIND & (1 << PD6)) && (PIND & (1 << PD7))) {
		// Mode 01: Control
		// PC2 is desired value
		// PC1 is measured value
		//desired blink value for about .5s blink
		PWM_init();
		ADC_init();
		CPE_relay_on();
		send_CPE_Enable();
		while(1){
			OCR1A = getM(read_ADC2(), read_ADC1());
			_delay_ms(5);
		}
	}
	//1-0
	else if ((PIND & (1 << PD6)) && !(PIND & (1 << PD7))) {
		uint8_t num_pages;
		uint16_t curr_val = 1;
		// Mode 10: Idle
		UC data, C1, C2;
		char str[25] = {'\n','\r','S','e','n','d','i','n','g',' ','E','E','P','R','O','M',' ','v','a','l','u','e','s','\n','\r'};
		UC p_str[19] = {'P','a','g','e','s',' ','t','o',' ','b','e',' ','r','e','a','d',' ','=', ' '};
		USART_init(MyBaud);
		i2c_init();
		for(uint8_t i = 0; i < 25; i++){
			USART_Transmit(str[i]);
		}
		i2c_start();
		i2c_write(EEPROM1_WR);
		i2c_write(0x00);
		i2c_write(0x00);
		i2c_start();
		i2c_write(EEPROM1_RD);
		num_pages = i2c_read(1);
		i2c_stop();
		hex2ascii(num_pages, &C1, &C2);
		for(uint8_t i = 0; i < 19; i++){
			USART_Transmit(p_str[i]);
		}
		USART_Transmit(C1);
		USART_Transmit(C2);
		USART_Transmit('\n');
		USART_Transmit('\r');
		while(num_pages){
			i2c_start();
			i2c_write(EEPROM1_WR);
			i2c_write((uint8_t)(curr_val >> 8));			//high byte memory address
			i2c_write((uint8_t)(curr_val));					//low byte memory address
			i2c_start();
			i2c_write(EEPROM1_RD);
			for(int i = 0; i < 63; i++) {
				data = i2c_read(0);
				hex2ascii(data, &C1, &C2);
				USART_Transmit(C1);
				USART_Transmit(C2);
				USART_Transmit(',');
			}
			data = i2c_read(1);
			i2c_stop();
			hex2ascii(data, &C1, &C2);
			USART_Transmit(C1);
			USART_Transmit(C2);
			USART_Transmit(',');
			curr_val = curr_val+64;
			num_pages--;
		}
	}
	return 0;
}
