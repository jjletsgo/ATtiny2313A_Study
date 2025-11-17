/*
 * pwm.c
 *
 * Created: 2025-11-15 오후 2:42:07
 *  Author: sec
 */ 
#include <avr/io.h>
#include "pwm.h"
#include <stdint.h>

void motor_dc_init(void)
{
	DDRB |= (1 << PB3);        // PB3 = OC1A
	TCCR1A = 0;
	TCCR1B = 0;

	// Fast PWM 8bit 모드, TOP=0xFF
	TCCR1A |= (1 << WGM10);          // WGM10 = 1
	TCCR1B |= (1 << WGM12);          // WGM12 = 1

	// OC1A 비반전 모드
	TCCR1A |= (1 << COM1A1);

	// 분주비 64
	TCCR1B |= (1 << CS11) | (1 << CS10);

	OCR1A = 0;   // 듀티 0% 시작
}

void motor_dc_change(uint8_t pwm)
{
	OCR1A = pwm;		// Timer1은 16bit지만 8bit 모드라 하위 8bit만 사용
}

void motor_dc_stop(void)
{
	TCCR1A &= ~(1 << COM1A1);
	PORTB  &= ~(1 << PB3); 
}
