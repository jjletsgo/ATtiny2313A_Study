/*
 * spi.h
 *
 * Created: 2025-11-11 오전 5:43:19
 *  Author: User
 */ 

#include "common.h"

#ifndef SPI_H_
#define SPI_H_
#define XCK 2
#define COUNT_MODE 1




#endif /* SPI_H_ */


uint8_t extern digit_counter;
uint8_t extern data_counter;
//자릿수 선택.(0,1,2,3,,,7)
 uint8_t extern digit[8];
// 출력할 데이터 선택. 0,1,2,,,,9,-,E,H,L,P,blank
uint8_t extern data[16];

void USART_Init(uint16_t baud);
uint8_t USART_transmit_byte(uint8_t data);
void set_count_mode(void);