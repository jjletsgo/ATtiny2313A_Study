/*
 * GccApplication1.c
 *
 * Created: 2025-11-10 오후 2:01:27
 * Author : User
 #ifndef __AVR_ATtiny2313A__
 #define __AVR_ATtiny2313A__
 #endif
 */ 


#include <avr/io.h>
#ifndef F_CPU
#define F_CPU 16000000
#endif

#include <util/delay.h>
#include "common.h"


int main(void)
{
	USART_Init(68);
	init_max7219();
	while(1) {
		//if(USART_transmit_byte(digit[digit_counter++]));
		max7219_send_cmd(data[digit_counter++],0X01);
		digit_counter %=9; //digit_counter가 0~7을 순환하도록 모듈러 연산
	}
}