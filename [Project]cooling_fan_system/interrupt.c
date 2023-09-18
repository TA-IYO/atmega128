#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

int run_state;
int rot_state;
int tim_state;

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
