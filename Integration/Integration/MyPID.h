#ifndef PID_H
#define PID_H

#define Kp_initial 0.5
#define Ki_initial 0.05
#define Kd_initial 0.01
#define up_lim 255
#define low_lim 0

float Kp, Ki, Kd, prev_error, error, Ts, e_i;

uint8_t getM(float dv, float mv);
void PID_init(float sampleTime);

#endif