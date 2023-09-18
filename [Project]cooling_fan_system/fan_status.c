#define F_CPU 16000000UL
#include "LCD.h"

#define mask_adc 11110001

int read;
int fan_led;

int fan_status(int read, int fan_led)
{
		if((read > 200) && (read <450))
		{
			LCD_wBCommand(0x80 | 0x0A);
			LCD_wString("1");
			fan_led = (fan_led &  mask_adc) | 0x08;
		}
		else if((read > 450) && (read < 750))
		{
			LCD_wBCommand(0x80 | 0x0A);
			LCD_wString("2");
			fan_led = (fan_led &  mask_adc) | 0x0C;
		}
		else if((read > 750) && (read < 1024))
		{
			LCD_wBCommand(0x80 | 0x0A);
			LCD_wString("3");
			fan_led = (fan_led &  mask_adc) | 0x0E;
		}
		else
		{
			LCD_wBCommand(0x80 | 0x0A);
			LCD_wString("0");
			fan_led = (fan_led &  mask_adc) | 0x00;
		}
	return fan_led;
}
