/*
 * MyADC.h
 *
 * Created: 9/24/2023 1:25:34 PM
 *  Author: David Melanson
 */ 


#ifndef MYADC_H_
#define MYADC_H_


void ADC_init(void);
unsigned char read_ADC0(void);
float read_ADC1(void);
float read_ADC2(void);
unsigned char read_ADC1_reg(void);
unsigned char read_ADC2_reg(void);
#endif /* MYADC_H_ */