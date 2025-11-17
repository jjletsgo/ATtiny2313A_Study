/*
 * max7219.h
 *
 * Created: 2025-11-15 오후 1:02:49
 *  Author: sec
 */ 

#ifndef MAX7219_H
#define MAX7219_H

#include <avr/io.h>
#include <stdint.h>
#include "USI.h"   

// MAX7219 레지스터 주소 정의 (데이터시트 7페이지 Table 2)
#define NoOP         0x00	// cascade된 모듈을 제어할 때 사용함
#define DIGIT0       0x01
#define DIGIT1       0x02
#define DIGIT2       0x03
#define DIGIT3       0x04
#define DIGIT4       0x05
#define DIGIT5       0x06
#define DIGIT6       0x07
#define DIGIT7       0x08
#define DECODE_MODE  0x09	// 디코드 모드는 7-segment 표시용 -> 도트 매트릭스 사용하려면 꺼야함 (0x00)
#define INTENSITY    0x0A	// 16단계의 밝기 조절이 가능 (0x00 ~ 0x0F)
#define SCAN_LIMIT   0x0B	// 활성화할 행의 개수 설정 -> 8x8 도트 매트릭스면 0x07 사용
#define SHUTDOWN     0x0C	// 0x01 설정해야 정상 동작모드로 바뀌고 LED가 켜짐
#define DISPLAY_TEST 0x0F	// test 모드에선 모든 LED가 켜짐 -> 초기화는 항상 0x00

// 도트 매트릭스 사용 시 설정값 아래와 같이 설정하면 됨
	// Decode Mode  : 0x00
	// Intensity    : 0x08 (밝기는 조절 가능)
	// Scan Limit   : 0x07
	// Shutdown     : Normal Operation
	// Display Test : Off
	// Digit 0~7    : 모두 0으로 클리어

void max7219_init(void);
void max7219_init_all(void);
void max7219_write(uint8_t reg, uint8_t data);
void max7219_write_n(uint8_t idx, uint8_t reg, uint8_t data);
void max7219_set_intensity(uint8_t intensity);
void max7219_set_scan_limit(uint8_t limit);
void max7219_set_shutdown(uint8_t enable);
void max7219_set_display_test(uint8_t enable);
void max7219_clear_all(void);
void max7219_set_row(uint8_t row, uint8_t value);

#endif /* MAX7219_H */
