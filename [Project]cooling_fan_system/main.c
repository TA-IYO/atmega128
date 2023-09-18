#define F_CPU 16000000UL
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdio.h>
#include "UART0.h"
#include "LCD.h"
#include "interrupt.h"
#include "adc.h"
#include "motor.h"
#include "timer.h"
#include "fan_status.h"
#include "rot_status.h"

volatile int run_state = 0;
volatile int rot_state = 0;
volatile int tim_state = 0;

int read;
int rot_cnt = 0;
int time_index;
int fan_led;

#define mask_adc 11110001
#define EnableMotor1()           PORTE &= ~0x04
#define DisableMotor1()          PORTE |= 0x04
#define ForwardMotor1()          PORTE &= ~0x01
#define BackwardMotor1()         PORTE |= 0x01
#define SpeedMotor1(s)           OCR3B = s

int fan_status(int read, int fan_led);
int rot_status(int rot_state, int rot_led);
void fan_activator(int read);
void INIT_INT0(void);
void INIT_INT1(void);
void INIT_INT2(void);
void LCD_IDLE(void);
void LCD_RUN(void);

FILE OUTPUT = FDEV_SETUP_STREAM(UART0_transmit, NULL, _FDEV_SETUP_WRITE);
FILE INPUT = FDEV_SETUP_STREAM(NULL, UART0_receive, _FDEV_SETUP_READ);

int main(void)
{
   DDRA =	0xFF;
   DDRB =	0xFF;
   PORTB =			0x00;
   DDRC =	0xFF;
   DDRD =	0x00;
   PORTD =			0x00;
   DDRE =	0x1D;
   PORTE =			0x00;
   DDRF =	0xFE;

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
            LCD_IDLE();
			PORTB = 0x00;
            rot_state = 0;
            tim_state = 0;
            time_index = -1;
            SpeedMotor1(0);
			
printf("IDLE\r\n");
         }
         else
            break;
      }
      
printf("BTN 1 PUSHED\r\n");
	  
      read = read_ADC();
	  LCD_RUN();
      fan_activator(read);
	  PORTB = (PORTB | 0x01);
      PORTB = rot_status(rot_state, PORTB);
      
printf("FAN is activated at %d power\r\n", read);

      
	  fan_led = PORTB;
      PORTB = fan_status(read, fan_led);
      timer(&tim_state);
      rotator(rot_state, rot_cnt);
   }
   return 0;
}
