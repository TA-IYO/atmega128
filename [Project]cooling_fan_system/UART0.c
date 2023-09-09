#include <avr/io.h>
#include <avr/sfr_defs.h>

void UART0_init(void)
{
	UBRR0H = 0x00;	// 9,600 보율 설정
	UBRR0L = 207;
	
	UCSR0A |= _BV(U2X0);	// 2배속 모드
	// 비동기, 8비트 데이터, 패러티 없음, 1비트 정지 비트 모드
	UCSR0C |= 0x06;
	
	UCSR0B |= _BV(RXEN0);	// 송수신 가능
	UCSR0B |= _BV(TXEN0);
}

void UART0_transmit(char data)
{
	while( !(UCSR0A & (1 << UDRE0)) );	// 송신 가능 대기
	UDR0 = data;						// 데이터 전송
}

unsigned char UART0_receive(void)
{
	while( !(UCSR0A & (1 << RXC0)) );	// 데이터 수신 대기
	return UDR0;						// 데이터 수신
}

void UART0_print_string(char *str)
{
	for(int i = 0; str[i]; i++)
	UART0_transmit(str[i]);
}

void UART0_print_1_byte_number(uint8_t n)
{
	char numString[4] = "0";
	sprintf(numString,"%d",n);
	UART0_print_string(numString);
}

void UART0_print_float(float f)
{
	char numString[20] = "0";
	sprintf(numString,"%f",f);
	UART0_print_string(numString);
}