//don't know why but everything went reverse so i flipped equations.

#define F_CPU 16000000L
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#define SEGMENT_DELAY			5
#define MILLIS_PER_OVERFLOW		16
#define MICROS_PER_OVERFLOW		384

uint8_t numbers[] = {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x27, 0x7F, 0x67};

volatile uint32_t millis = 0;
volatile uint32_t micros = 0;

ISR(TIMER0_OVF_vect)
{
	micros += MICROS_PER_OVERFLOW;
	millis += MILLIS_PER_OVERFLOW;
	
	millis += (micros / 1000);
	micros %= 1000;
}

void display_digit(int position, int number)
{
	PORTC &= 0x00;
	PORTC |= (1 << (position - 1));
	
	PORTD = ~numbers[number];
}

int main(void)
{		
	DDRD = 0xFF; 
	DDRC = 0x0F;

	TCCR0 |= (1 << CS02) | (1 << CS01) | (1 << CS00);
	TIMSK |= (1 << TOIE0);
	sei();
		
	while(1)
	{
		int temp = millis / 1000;
		
		int minutes = (temp / 60) % 60;
		int seconds = temp % 60;
		                                               
		display_digit(1, minutes / 10);
		_delay_ms(SEGMENT_DELAY);
		display_digit(2, minutes % 10);
		_delay_ms(SEGMENT_DELAY);
		display_digit(3, seconds / 10);
		_delay_ms(SEGMENT_DELAY);
		display_digit(4, seconds % 10);
		_delay_ms(SEGMENT_DELAY);
	}
	
	return 0;
}