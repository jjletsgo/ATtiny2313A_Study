/*
 * USI.c
 *
 * Created: 2025-11-15 오전 10:47:29
 *  Author: sec
 */ 

// main에서 init -> ss_low -> transfer -> ss high 반드시 이 순서대로 작성해야 함

	// 데이터시트 158쪽 작동 예제 참고
	// USICR, USI Control 레지스터를 작성해야 함
	// USIWM1 = 0, USIWM0 = 1 : 3-wire 모드로 작동, D0/DI/USCK
	// USIWM1 = 1, USIWM0 = 0 : 2-wire 모드로 작동, DI/USCK		-> 아마 안쓸거 같음

	// USICS1 = 1, USICS0 = 0,  USICLK = 1 -> Positive edge에서 USITC를 소프트웨어로 토글
	// USITC  = 1 -> USI 클럭을 소프트웨어에서 생성해줌
	
#include "USI.h"

#define USI_SPI_CLK_STROBE ((1 << USIWM0) | (1 << USICS1) | (1 << USICLK) | (1 << USITC))
	// USITC는 1로 설정하면 동작 후 스스로 0으로 돌아감


void usi_spi_init(void)
{
    DDRB |= (1 << PB6) | (1 << PB7);	// DO : PB6, USCK : PB7
    DDRB &= ~(1 << PB5);				// DI핀 설정

    DDRB |= (1 << USI_SS_PIN);			// SS핀이 필요한 경우 설정
    usi_spi_ss_high();					// 초기에는 Slave 핀을 선택 안함

    USICR = 0;							// 초기에는 0
    USISR = (1 << USIOIF) | (1 << USIPF) | (1 << USIDC);	// 상태 레지스터는 1을 써야 초기화됨
}

uint8_t usi_spi_transfer(uint8_t data)
{
    USIDR = data;						// 전송할 데이터
    USISR = (1 << USIOIF);				// Counter = 0, USIOIF = 0

	while (!(USISR & (1 << USIOIF))) {	// 카운터 16도달 -> Overflow 발생 (4비트이므로) -> USIOIF flag가 1 -> 엣지 16번은 클락 8번이므로 8비트 전송을 의미함
		USICR = USI_SPI_CLK_STROBE;		// USITC가 USCK핀 한번 토글 -> 클록 생성 동시에 카운터 1 증가
	}
	
    return USIDR;
}

void usi_spi_transfer_buffer(uint8_t *tx, uint8_t *rx, uint8_t len)	// Byte 묶음을 한번에 전송해주는 함수
{
    for (uint8_t i = 0; i < len; i++) {
        uint8_t out = tx ? tx[i] : 0xFF;     // tx가 있으면 out에 tx 전송, 없으면 0xFF 더미값 전송
        uint8_t in  = usi_spi_transfer(out); // tx 전송 후 rx 버퍼를 바로 수신

        if (rx) {
            rx[i] = in;						 // rx 값을 저장함
        }
    }
}
