/*
 * common.c
 *
 * Created: 2025-11-11 오후 2:24:52
 *  Author: User
 */ 
#include "common.h"


uint16_t combine_bytes(uint8_t high, uint8_t low) {
	
	uint16_t result = (uint16_t)high << 8;
	result |= (uint16_t)low;
	return result;
}

