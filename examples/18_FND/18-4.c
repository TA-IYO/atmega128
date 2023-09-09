//don't know why but everything went reverse so i flipped equations.

#define F_CPU 16000000L
#include <avr/io.h>
#include <util/delay.h>

#define SEGMENT_DELAY 5
uint8_t numbers[] = {0x3F, 0x06, 0x5B
					,0x4F, 0x66, 0x6D
					,0x7D, 0x27, 0x7F, 0x67};

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
	
	while(1)
	{
		display_digit(1, 0);
		_delay_ms(SEGMENT_DELAY);
		display_digit(2, 4);
		_delay_ms(SEGMENT_DELAY);
		display_digit(3, 1);
		_delay_ms(SEGMENT_DELAY);
		display_digit(4, 9);
		_delay_ms(SEGMENT_DELAY);
	}
	
	return 0;
}