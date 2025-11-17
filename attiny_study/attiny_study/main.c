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
	init_INT0();
	DDRB |= (1 << 2);
	
	while(1) {
		cli();
		if(get_light_flag_atomic()) {
			PINB |= (1 << 2); //PB2를 toggle
			
			light_flag = 0; 
		}
		sei();
	}
}