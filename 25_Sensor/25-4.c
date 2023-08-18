#define F_CPU 16000000L
#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>
#include "UART0.h"

void UART0_init(void);
void UART0_transmit(char data);
unsigned char UART0_receive(void);

FILE OUTPUT = FDEV_SETUP_STREAM(UART0_transmit, NULL, _FDEV_SETUP_WRITE);
FILE INPUT = FDEV_SETUP_STREAM(NULL,UART0_receive, _FDEV_SETUP_READ);

#define PRESCALER 1024

void Timer_init(void)
{
	TCCR1B |= (1 << CS12) | (1 << CS10);
}

uint8_t measure_distance(void)
{
	PORTB &= ~(1 << PB1);
	_delay_us(1);
	PORTB |= (1 << PB1);
	_delay_us(10);
	PORTB &= ~(1 << PB1);
	
	TCNT1 = 0;
	while(!(PINB & 0x01))
		if(TCNT1 > 65000) return 0;
		
	TCNT1 = 0;
	
	while(PINB & 0x01)
	{
		if(TCNT1 > 65000)
		{
			TCNT1 = 0;
			break;
		}
	}
	
	double pulse_width = 1000000.0 * TCNT1 * PRESCALER / F_CPU;
	
	return pulse_width / 58;
}

int main(void)
{
	uint8_t distance;
	
	stdout = &OUTPUT;
	stdin = &INPUT;
	
	UART0_init();
	
	DDRB |= 0x02;
	DDRB &= 0xFE;
	
	Timer_init();
	
	while(1)
	{
		distance = measure_distance();
		
		printf("distance : %d cm\r\n", distance);
		
		_delay_ms(1000);
	}
	
	return 0;
}