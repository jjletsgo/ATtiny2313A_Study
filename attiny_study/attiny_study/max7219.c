/*
 * max7219.c
 *
 * Created: 2025-11-12 오전 11:54:21
 *  Author: User
 */ 
#include "max7219.h"

void init_max7219()
{
	DDRD |= (1 << LOAD);
	PORTD &= ~( 1<< LOAD);
	max7219_send_cmd(0x0C, 0x01);
	max7219_send_cmd(0x09, 0xFF);
	max7219_send_cmd(0x0B, 0x07);
}

void signal_load()
{
	PORTD |= ( 1<< LOAD);
	PORTD &= ~( 1<< LOAD);
}

void max7219_send_cmd(uint8_t address, uint8_t data)
{
	USART_transmit_byte(address);
	USART_transmit_byte(data);
	signal_load();
}
