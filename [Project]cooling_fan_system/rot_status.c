#include "LCD.h"

int rot_state;
int rot_led = 0;

int rot_status(int rot_state)
{
    if(rot_state)
          {
             rot_led = (rot_led | 0x10);
             LCD_wBCommand(0x80 | 0x0C);
             LCD_wString("ROT");
          }
          else
          {
             rot_led = (rot_led & 0xEF);
             LCD_wBCommand(0x80 | 0x0C);
             LCD_wString("   ");
          }
}