/*
 * PID.h
 *
 * Created: 11/2/2023 4:04:56 PM
 * Author : David Melanson
 */ 

#ifndef PID_H
#define PID_H

#define up_lim 500
#define low_lim -500
#define PWM_uplim 255
#define PWM_lowlim 0

float temp_err, prev_error, error, Ts, e_i;


uint8_t getM(float dv, float mv);

#endif
