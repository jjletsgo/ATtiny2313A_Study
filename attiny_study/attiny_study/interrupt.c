/*
 * interrupt.c
 *
 * Created: 2025-11-17 오후 3:47:15
 *  Author: User
 */ 
#include "interrupt.h"

uint8_t volatile light_flag = 0;

void enable_global_interrupt() 
{
	sei();
}

void disable_global_interrupt()
{
	cli();
}

void init_INT0()
{
	enable_global_interrupt();
	MCUCR |= ( 1 << ISC01); //INT0의 falling edge가 인터럽트 리퀘스트를 생성
	GIMSK |= ( 1 << 6);
}

ISR(INT0_vect) {
	light_flag = 1;
}