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
	USART_Async_Init(103);
	while(1){
		
		USART_Transmit_Max_8bit_Data(5);
		_delay_ms(1000);
	}
}