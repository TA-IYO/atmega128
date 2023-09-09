#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <stdio.h>
#include "UART0.h"
#include "motor.h"

#define mask_run 11111110
#define mask_adc 11110001
#define mask_rot 11101111

ISR(INT0_vect)
{
	_delay_ms(50);
	if(PIND & 0x01) return;
	run_state = (run_state + 1) % 2;
	_delay_ms(50);
}

ISR(INT1_vect)
{
	_delay_ms(50);
	if(PIND & 0x02) return;
	rot_state = (rot_state + 1) % 2;
	_delay_ms(50);
}

ISR(INT2_vect)
{
	_delay_ms(50);
	if(PIND & 0x04) return;
	tim_state = (tim_state + 1) % 2;
	_delay_ms(50);
}


void INIT_INT0(void)
{
	EIMSK |= (1 << INT0);			// INT0 인터럽트 활성화
	EICRA |= (1 << ISC01);			// 하강 에지에서 인터럽트 발생
	sei();							// 전역적으로 인터럽트 허용
}

void INIT_INT1(void)
{
	EIMSK |= (1 << INT1);			// INT1 인터럽트 활성화
	EICRA |= (1 << ISC11);			// 하강 에지에서 인터럽트 발생
	sei();							// 전역적으로 인터럽트 허용
}

void INIT_INT2(void)
{
	EIMSK |= (1 << INT2);			// INT2 인터럽트 활성화
	EICRA |= (1 << ISC21);			// 하강 에지에서 인터럽트 발생
	sei();							// 전역적으로 인터럽트 허용
}

void ADC_init(unsigned char channel)
{
	ADMUX |= (1 << REFS0); 			// AVCC를 기준 전압으로 선택
	
	ADCSRA |= 0x07;					// 분주비 설정
	ADCSRA |= (1 << ADEN);			// ADC 활성화
	ADCSRA |= (1 << ADFR);			// free running 모드

	ADMUX = ((ADMUX & 0xE0) | channel);	// 채널 선택
	ADCSRA |= (1 << ADSC);			// 변환 시작
}

int read_ADC(void)
{
	while(!(ADCSRA & (1 << ADIF)));	// 변환 종료 대기
	
	return ADC;						// 10비트 값을 반환
}