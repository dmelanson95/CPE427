/*
 * PID.c
 *
 * Created: 11/2/2023 2:24:04 PM
 * Author : David Melanson
 */ 

#include <avr/io.h>
#include "PID.h"

float Kp = 1;
float Ki = 0.5;
float Kd = 0.1;

/*
void PID_init(float sampleTime){
	Kp = Kp_initial;
	Ki = Ki_initial;
	Kd = Kd_initial;
	error = 0;
	e_i = 0;
}
*/

uint8_t getM(float dv, float mv){
	//dv is desired value that comes from pin pin 24 PC1, ADC1
	//mv is measured value that comes from pin 23 - PC0, ADC0
	error = dv - mv;
	temp_err = error-prev_error;
	e_i = e_i + error;
	if (e_i > up_lim){
		e_i = up_lim;
	}
	else if (e_i < low_lim){
		e_i = low_lim;
	}
	float temp_m = Kp*error+Ki*e_i+Kd*temp_err;
	if (temp_m > PWM_uplim){
		temp_m = PWM_uplim;
	}
	else if (temp_m < PWM_lowlim){
		temp_m = PWM_lowlim;
	}
	prev_error = error;
	return (uint8_t)temp_m;
}



