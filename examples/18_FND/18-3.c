//don't know why but everything went reverse so i flipped equations.

#define F_CPU 16000000L
#include <avr/io.h>
#include <util/delay.h>

int main(void)
{
	uint8_t numbers[] = {0x3F, 0x06, 0x5B
						,0x4F, 0x66, 0x6D
						,0x7D, 0x27, 0x7F, 0x67};
	
	int i, j;

	DDRD = 0xFF;
	DDRC = 0x0F;
	
	while(1)
	{
		for(i = 0; i < 4; i++)
		{
			PORTC &= 0x00;
			PORTC |= (1 << i);
			
			for(j = 0; j < 10; j++)
			{
				PORTD = ~numbers[j];
				_delay_ms(100);
			}
		}
	}
	
	return 0;
}