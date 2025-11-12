/*
 * common.h
 *
 * Created: 2025-11-11 오후 2:24:32
 *  Author: User
 */ 


#ifndef COMMON_H_
#define COMMON_H_
#include <avr/io.h>
#include "spi.h"
#include "max7219.h"
#include "uart.h"




#endif /* COMMON_H_ */


uint16_t combine_bytes(uint8_t high, uint8_t low);