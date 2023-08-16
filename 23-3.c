/*
pink                yellow
orange  0 2 1 3     blue 
*/

#define F_CPU 16000000L
#include <avr/io.h>
#include <util/delay.h>

uint8_t step_data[] = {0x01, 0x02, 0x04, 0x08};
int step_index = -1;

uint8_t stepForward(void)
{
	step_index++;
	if(step_index >= 4) step_index = 0;
	
	return step_data[step_index];
}

uint8_t stepBackward(void)
{
	step_index--;
	if(step_index < 0) step_index = 3;
	
	return step_data[step_index];
}

int main(void)
{		
	DDRC = 0x0F;

	while(1)
	{
		for(int i = 0; i < 200; i++)
		{
			PORTC = stepForward();
			
			_delay_ms(5);
		}
		_delay_ms(1000);
		
		for(int i = 0; i < 200; i++)
		{
			PORTC = stepBackward();
			
			_delay_ms(5);
		}
		_delay_ms(1000);
	}
	
	return 0;
}