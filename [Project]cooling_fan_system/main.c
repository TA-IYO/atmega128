#define F_CPU 16000000UL
#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdio.h>
#include <util/delay.h>
#include "UART0.h"
#include "motor.h"
#include "BTN_LED_VAR_ADC.h"
#include "LCD.h"

volatile int run_state = 0;
volatile int rot_state = 0;
volatile int tim_state = 0;

int read;
char buff[20];
int rot_cnt = 0;
int time_index = -1;
int time_mindex;
int time_sindex;
char time_sec[20];
char time_min[20];

#define mask_adc 11110001

#define EnableMotor1()           PORTE &= ~0x04
#define DisableMotor1()          PORTE |= 0x04
#define ForwardMotor1()          PORTE &= ~0x01
#define BackwardMotor1()         PORTE |= 0x01
#define SpeedMotor1(s)           OCR3B = s

FILE OUTPUT = FDEV_SETUP_STREAM(UART0_transmit, NULL, _FDEV_SETUP_WRITE);
FILE INPUT = FDEV_SETUP_STREAM(NULL, UART0_receive, _FDEV_SETUP_READ);

int main(void)
{
   DDRA = 0xFF;
   DDRB = 0xFF;
   PORTB = 0x00;
   DDRC = 0xFF;
   DDRD = 0x00;
   PORTD = 0x00;
   DDRE = 0x1D;
   PORTE = 0x00;
   DDRF = 0xFE;

   INIT_INT0();
   INIT_INT1();
   INIT_INT2();
   UART0_init();
   ADC_init(0);
   InitializeTimer3();

   stdout = &OUTPUT;
   stdin = &INPUT;
   
   while(1)
   {
      for(;;)
      {
         if(run_state == 0)
         {
            PORTB = 0x00;
            rot_state = 0;
            tim_state = 0;
            time_index = -1;
            SpeedMotor1(0);
            
            LCD_Init();
            LCD_wBCommand(0x80 | 0x00);
            LCD_wString("Waiting for");
            LCD_wBCommand(0x80 | 0x40);
            LCD_wString("START");
         }
         else
            break;
      }
      
      PORTB = (PORTB | 0x01);

      if(rot_state)
         PORTB = (PORTB | 0x10);
      else
         PORTB = (PORTB & 0xEF);

      read = read_ADC();
      LCD_Init();
      LCD_wBCommand(0x80 | 0x00);
      LCD_wString("FAN LEVEL : ");
      LCD_wBCommand(0x80 | 0x0A);
      
      fan_status(read);
      fan_activator(read);
      timer(&tim_state);
      rotator(rot_state, rot_cnt);
   }
   return 0;
}



