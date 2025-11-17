/*
 * pwm.h
 *
 * Created: 2025-11-15 오후 2:42:18
 *  Author: sec
 */ 

#ifndef PWM_H_
#define PWM_H_

#include <avr/io.h>
#include <stdint.h>

void motor_dc_init(void);
void motor_dc_change(uint8_t pwm);
void motor_dc_stop(void);

#endif /* PWM_H_ */