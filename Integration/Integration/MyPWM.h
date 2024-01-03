/*
 * MyPWM.h
 *
 * Created: 11/21/2023 1:25:34 PM
 *  Author: David Melanson
 */ 


#ifndef _MYPWM_H
#define _MYPWM_H

#define duty_cycle25 63
#define duty_cycle50 127
#define duty_cycle75 191
#define CPE_Relay (1<<PB2)
#define CPE_Enable (1<<PD5)

void PWM_init();
void CPE_relay_off();
void CPE_relay_on();
void send_CPE_Enable();

#endif