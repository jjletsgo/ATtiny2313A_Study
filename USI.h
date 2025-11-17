/*
 * USI.h
 *
 * Created: 2025-11-15 오전 10:47:39
 *  Author: sec
 */ 


#ifndef USI_H_
#define USI_H_

#include <avr/io.h>
#include <stdint.h>

// 3-wire 핀맵 : USCK -> PB7 (SCK) / DO -> PB6 (MOSI) / DI -> PB5 (MISO)
// USI는 SS를 제공 X -> 직접 핀 정의해서 사용해야 함

#define USI_SS_PIN    PB4		// 각 Slave에게 데이터를 전송한다고 알려주는 역할 -> SPI 핵심

static inline void usi_spi_ss_low(void)			// 외부 클락 모드 0 -> USICS0 = 0
{
    PORTB &= ~(1 << USI_SS_PIN);
}

static inline void usi_spi_ss_high(void)	// 외부 클락 모드 1 -> USICS0 = 1
{
    PORTB |= (1 << USI_SS_PIN);
}

void usi_spi_init(void);					// 3-wire 마스터 모드 초기화

uint8_t usi_spi_transfer(uint8_t data);		// 1byte 수신, 동시에 1byte 송신

void usi_spi_transfer_buffer(uint8_t *tx, uint8_t *rx, uint8_t len);	//tx 전송하면서 rx에 쓰기 -> 데이터시트 기준


#endif /* USI_H_ */