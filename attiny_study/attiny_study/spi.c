/*
 * spi.c
 *
 * Created: 2025-11-11 오후 1:40:18
 *  Author: User
 */

 #include "spi.h"

uint8_t segment_mode = 0;
uint8_t digit_counter = 1;
uint8_t data_counter = 0;
// 00000110 00000011
// 00000111 00000011  순 되는거 확인함

//자릿수 선택.(0,1,2,3,,,7)
uint8_t digit[8] = {0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08};

// 출력할 데이터 선택. 0,1,2,,,,9,-,E,H,L,P,blank
uint8_t data[16] = {0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F};

void USART_Init( uint16_t baud )//baud에는 UBRR에 적을 데이터 넣어주면 됨.
 //115200 hz : 68(0b1000100), 4Mhz : 1  , 8Mhz : 0
{
	UBRRH = 0;
	UBRRL = 0;
	/* Setting the XCK port pin as output, enables master mode. */
	XCK_DDR |= (1<<XCK); //XCK의 방향을 출력으로 설정
	DDRD |= (1 << DDD1);
	DDRD &= ~(1 << DDD0);
	/* Set MSPI mode of operation and SPI data mode 0. */
	UCSRC |= (1<<UMSEL1)|(1<<UMSEL0); //USART IN MSPIM 활성화 및 클럭 극성 설정
	UCSRC &= ~( (1 << UDORD) | (1 << UCPHA) | ( 1 << UCPOL));
	/* Enable receiver and transmitter. */
	UCSRB = (1<<RXEN)|(1<<TXEN); // UDRIE 활성화
	/* Set baud rate. */
	/* IMPORTANT: The Baud Rate must be set after the transmitter is enabled
	*/
	UBRRH = (uint8_t)(baud>>8);
	UBRRL = (uint8_t) baud;
}




uint8_t USART_transmit_byte(uint8_t data)
{
	while ( !( UCSRA & (1<<UDRE)) ); //UDRE가 0인동안 무한루프타며 대기
	/* Put data into buffer, sends the data */
	UDR = data;
	return 0;
}

//7-segment를 카운트 모드로 설정한다.
void set_count_mode(void)
{
	segment_mode = COUNT_MODE; 
}

