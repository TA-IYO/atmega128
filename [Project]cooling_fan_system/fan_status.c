#include "LCD.h"
#define mask_adc 11110001

int read;

void fan_status(read)
{
    if((read > 200) && (read <450))
    {
       LCD_wString("1");
       PORTB = (PORTB &  mask_adc) | 0x08;
    }
    else if((read > 450) && (read < 750))
    {
       LCD_wString("2");
       PORTB = (PORTB &  mask_adc) | 0x0C;
    }
    else if((read > 750) && (read < 1024))
    {
       LCD_wString("3");
       PORTB = (PORTB &  mask_adc) | 0x0E;
    }
    else
    {
       LCD_wString("0");
       PORTB = (PORTB &  mask_adc) | 0x00;
    }
   
   if(rot_state)
   {
      LCD_wBCommand(0x80 | 0x0C);
      LCD_wString("ROT");
   }
   else
   {
      LCD_wBCommand(0x80 | 0x0C);
      LCD_wString("   ");
   }
}
