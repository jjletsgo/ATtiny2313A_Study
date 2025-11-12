/*
 * uart.c
 *
 * Created: 2025-11-12 오후 1:13:20
 *  Author: User
 */ 
#include "uart.h"

void USART_Async_Init( uint16_t baud ) //UMSEL1:0은 기본값이 00으로, USART-Asynchronous 모드임.
//보드레이트 9600으로하려면 103을 전달해주면된다.
{
	/* Set baud rate */
	UBRRH = (unsigned char)(baud>>8);
	UBRRL = (unsigned char)baud;
	/* Enable receiver and transmitter */
	UCSRB = (1<<RXEN)|(1<<TXEN);
	/* Set frame format: 8data, 2stop bit */
	UCSRC = (1<<USBS)|(3<<UCSZ0);
}

void USART_Transmit_Max_9bit_Data( uint16_t data )
{
	/* Wait for empty transmit buffer */
	while ( !( UCSRA & (1<<UDRE))); //UDRE가 1되면 전체가 0되며 탈출
	
	/* Copy 9th bit to TXB8 */
	UCSRB &= ~(1<<TXB8); //TXB8을 0으로 clear
	if ( data & 0x0100 ) // data의 9번째 비트 검사
	UCSRB |= (1<<TXB8); // data의 9번째 비트가 1이면 TXB8을 1로 set (data의 9번째 비트를 TXB8 비트에 write 하는 과정임)
	/* Put data into buffer, sends the data */
	UDR = (uint8_t)data; //data의 하위 8비트를 UDR(8비트 송,수신 버퍼)에 저장
}

void USART_Transmit_Max_8bit_Data( uint8_t data )
{
	/* Wait for empty transmit buffer */
	while ( !( UCSRA & (1<<UDRE)) )
	;
	/* Put data into buffer, sends the data */
	UDR = data;
}