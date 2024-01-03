/*
 * PID.c
 *
 * Created: 11/2/2023 2:24:04 PM
 * Author : David Melanson
 */ 

#include <avr/io.h>


#define Kp_initial 0.5
#define Ki_initial 0.05
#define Kd_initial 0.01
#define up_lim 255
#define low_lim 0

float Kp, Ki, Kd, prev_error, error, Ts, e_i;

uint8_t getM(float dv, float mv);
void PID_init(float sampleTime);

void PID_init(float sampleTime){
	Kp = Kp_initial;
	Ki = Ki_initial;
	Kd = Kd_initial;
	error = 0;
	Ts = sampleTime;
	e_i = 0;
}

uint8_t getM(float dv, float mv){
	//dv is desired value that comes from pin pin 24 PC1, ADC1
	//mv is measured value that comes from pin 23 - PC0, ADC0
	error = dv - mv;
	float temp_err = error-prev_error;
	e_i = e_i + error;
	if (e_i > up_lim){
		e_i = up_lim;
	}
	else if (e_i < low_lim){
		e_i = low_lim;
	}
	float temp_m = Kp*error+Ki*e_i+Kd*temp_err;
	if (temp_m > up_lim){
		temp_m = up_lim;
	}
	else if (temp_m < low_lim){
		temp_m = low_lim;
	}
	prev_error = error;
	return (uint8_t)temp_m;
}



