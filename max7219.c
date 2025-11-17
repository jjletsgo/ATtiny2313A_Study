/*
 * max7219.c
 *
 * Created: 2025-11-15 오후 1:02:41
 *  Author: sec
 */ 

#include "max7219.h"
#define MAX7219_NUM 4

void max7219_write(uint8_t reg, uint8_t data)		// USI 레지스터에 max7219 데이터 저장, USI 사용시 16비트를 2번에 나눠서 전송
{
	usi_spi_ss_low();          // 프레임 시작 
	usi_spi_transfer(reg);     // 데이터 시트 6페이지 테이블 1 -> D11~D8에 주소 저장
	usi_spi_transfer(data);    // 데이터 시트 6페이지 테이블 1 -> D7~D0에 데이터 저장
	usi_spi_ss_high();         // 프레임 끝 (CS HIGH → latch)
}

void max7219_write_n(uint8_t idx, uint8_t reg, uint8_t data)
{
	if (idx >= MAX7219_NUM) return;
	
	usi_spi_ss_low();

	for (int i = MAX7219_NUM - 1; i >= 0; i--) {	// 제일 먼 칩부터 차례대로 밀어 넣음
		if (i == idx) {								// 이 칩만 실제로 레지스터/데이터 전송
			usi_spi_transfer(reg);
			usi_spi_transfer(data);
			} else {
			usi_spi_transfer(NoOP);		// 나머지는 NO-OP
			usi_spi_transfer(0x00);
		}
	}
	usi_spi_ss_high();
}

void max7219_set_intensity(uint8_t intensity)
{
	if (intensity > 0x0F) intensity = 0x0F;		// 최대값 클램프
	max7219_write(INTENSITY, intensity);
}

void max7219_set_scan_limit(uint8_t limit)
{
	if (limit > 0x07) limit = 0x07;		// 최대값 클램프
	max7219_write(SCAN_LIMIT, limit);
}

void max7219_set_shutdown(uint8_t enable)
{
	if (enable) {
		max7219_write(SHUTDOWN, 0x00);	// Shutdown 모드
		} else {
		max7219_write(SHUTDOWN, 0x01);	// 정상 동작 모드
	}
}

void max7219_set_display_test(uint8_t enable)
{
	if (enable) {
		max7219_write(DISPLAY_TEST, 0x01);
		} else {
		max7219_write(DISPLAY_TEST, 0x00);
	}
}

void max7219_clear_all(void)	// 전체 행 초기화
{
	for (uint8_t row = 0; row < 8; row++) {
		max7219_write(DIGIT0 + row, 0x00);
	}
}

void max7219_set_row(uint8_t row, uint8_t value)
{
	if (row > 7) return;
	max7219_write(DIGIT0 + row, value);
}

void max7219_init(void)		// 단일 MAX7219 초기화
{
	usi_spi_init();		// USI 3-wire로 초기화
	max7219_set_display_test(0);	// Display test 모드 끔
	max7219_write(DECODE_MODE, 0x00);
	max7219_set_scan_limit(0x07);
	max7219_set_intensity(0x08);
	max7219_set_shutdown(0);
	max7219_clear_all();
}

void max7219_init_all(void)		// Cascade MAX7219 초기화
{
	usi_spi_init();

	for (uint8_t dev = 0; dev < MAX7219_NUM; dev++) {
		max7219_write_n(dev, DISPLAY_TEST, 0x00); 
		max7219_write_n(dev, DECODE_MODE, 0x00);  
		max7219_write_n(dev, SCAN_LIMIT, 0x07);   
		max7219_write_n(dev, INTENSITY, 0x08);   
		max7219_write_n(dev, SHUTDOWN, 0x01);     

		for (uint8_t row = 0; row < 8; row++) {
			max7219_write_n(dev, DIGIT0 + row, 0x00);
		}
	}
}