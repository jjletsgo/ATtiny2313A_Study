/*
 * uart.h
 *
 * Created: 2025-11-12 오후 1:13:37
 *  Author: User
 */ 


#ifndef UART_H_
#define UART_H_
#include "common.h"




#endif /* UART_H_ */

void USART_Async_Init( uint16_t baud );
void USART_Transmit_Max_9bit_Data( uint16_t data );
void USART_Transmit_Max_8bit_Data( uint8_t data );