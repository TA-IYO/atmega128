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

void ADC_init(unsigned char channel)
{
	ADMUX |= (1 << REFS0);
	ADCSRA |= 0x07;
	ADCSRA |= (1 << ADEN);
	ADCSRA |= (1 << ADFR);
	ADMUX |= ((ADMUX & 0xE0) | channel);
	ADCSRA |= (1 << ADSC);
}

int read_ADC(void)
{
	while(!(ADCSRA & (1 << ADIF)));
	
	return ADC;
}

int main(void)
{
	int read;
	
	stdout = &OUTPUT;
	stdin = &INPUT;
	
	UART0_init();
	ADC_init(5);
	
	while(1)
	{
		read = read_ADC();

		printf("%d\r\n", read);
		
		_delay_ms(1000);
	}
	return 0;
}