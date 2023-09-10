#include <avr/io.h>
#include <util/delay.h>

#define EnableMotor1()			PORTE &= ~0x04
#define DisableMotor1()			PORTE |= 0x04

#define ForwardMotor1()			PORTE &= ~0x01
#define BackwardMotor1()		PORTE |= 0x01

#define SpeedMotor1(s)			OCR3B = s

#define ON0						0x01
#define ON1						0x02
#define ON2						0x04
#define ON3						0x03

uint8_t step_data[] = {0x10, 0x30, 0x20, 0x60, 0x40, 0xc0, 0x80, 0x90};
int step_index = -1;			// 현재 상태
int read;
int rot_state, rot_cnt;
uint8_t stepForward(void);
uint8_t stepBackward(void);

void InitializeTimer3(void)
{
	// 8비트 고속 PWM 모드
	TCCR3A |= (1 << WGM30);
	TCCR3B |= (1 << WGM32);
	
	// 비반전 모드
	// TOP : 0xFF, 비교일치값 : OCR3B 레지스터
	TCCR3A |= (1 << COM3B1);
	
	// 분주비 64
	TCCR3B |= (1 << CS31) | (1 << CS30);
	
	OCR3B = 0;
}

uint8_t stepForward(void)			// 시계방향 회전
{
	step_index++;
	if(step_index >= 8) step_index = 0;

	return step_data[step_index];
}

uint8_t stepBackward(void)		// 반시계방향 회전
{
	step_index--;
	if(step_index < 0) step_index = 7;
	
	return step_data[step_index];
}

void fan_activator(read)
{
   EnableMotor1();
   ForwardMotor1();
   SpeedMotor1(read/8);
}

void rotator(rot_state, rot_cnt)
{
   if(rot_state)
   {
      if (rot_cnt >= 0)
      {
         for(int i = 0; i < 500; i++)
         PORTF = stepForward();
         _delay_ms(1);
         rot_cnt++;
         if(rot_cnt == 1)
         rot_cnt = -1;
      }
      else
      {
         for(int i = 0; i < 500; i++)
         PORTF = stepBackward();
         _delay_ms(1);
         rot_cnt--;
         if(rot_cnt == -2)
         rot_cnt = 0;
      }
   }
}