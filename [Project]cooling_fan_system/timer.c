#include "LCD.h"

int time_index = -1;
int time_mindex;
int time_sindex;
char time_min[20];
char time_sec[20];

volatile int run_state;	
volatile int rot_state;
volatile int tim_state;

void timer(int* tim_state)
{
   if (*tim_state)
   {
      *tim_state = 0;
      time_index = 180;
   }
   
   if (time_index != -1)
   {
      time_mindex = time_index / 60;
      time_sindex = time_index % 60;
      
      LCD_wBCommand(0x80 | 0x40);
      LCD_wString("TIME LEFT");
      
      LCD_wBCommand(0x80 | 0x4A);
      sprintf(time_min, "%2d", time_mindex);
      LCD_wString(time_min);
      
      LCD_wBCommand(0x80 | 0x4C);
      LCD_wString(":");
      
      LCD_wBCommand(0x80 | 0x4D);
      sprintf(time_sec, "%2d", time_sindex);
      LCD_wString(time_sec);
      
      if (time_index > 0)
      {
         time_index--;
         _delay_ms(1000);
         if (time_index == 0)
         {
            time_index = -1;
            run_state = 0;
            rot_state = 0;
         }
      }
   }
}