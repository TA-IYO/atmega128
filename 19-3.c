#define F_CPU 16000000L
#include <avr/io.h>
#include <stdio.h>
#include <util/delay.h>
#include "UART1.h"
#include "I2C_RTC.h"

FILE OUTPUT = FDEV_SETUP_STREAM(UART1_transmit, NULL, _FDEV_SETUP_WRITE);
FILE INPUT = FDEV_SETUP_STREAM(NULL,UART1_receive, _FDEV_SETUP_READ);

#define MCP23017_ADDRESS	0x20
#define MCP23017_IODIRA		0x00
#define MCP23017_IODIRB		0x01
#define MCP23017_GPPUA		0x0C
#define MCP23017_GPPUB		0x0D
#define MCP23017_GPIOA		0x12
#define MCP23017_GPIOB		0x13

int main(void)
{
	I2C_init();
	UART1_init();
	
	stdout = &OUTPUT;
	stdin = &INPUT;

	I2C_start();
	I2C_transmit(MCP23017_ADDRESS << 1);
	I2C_transmit(MCP23017_IODIRA);
	I2C_transmit(0x00);
	I2C_transmit(0xFF);
	I2C_stop();

	I2C_start();
	I2C_transmit(MCP23017_ADDRESS << 1);
	I2C_transmit(MCP23017_GPPUB);
	I2C_transmit(0);
	I2C_stop();

	while (1)
	{
		I2C_start();
		I2C_transmit(MCP23017_ADDRESS << 1);
		I2C_transmit(MCP23017_GPIOB);
		I2C_stop();
		
		I2C_start();
		I2C_transmit((MCP23017_ADDRESS << 1) + 1);
		uint8_t button_state = I2C_receive_NACK();
		I2C_stop();
		
		printf("%d\r\n", button_state);
		
		I2C_start();
		I2C_transmit(MCP23017_ADDRESS << 1);
		I2C_transmit(MCP23017_GPIOA);
		I2C_transmit(button_state);
		I2C_stop();
		
		_delay_ms(500);

	}
		
	return 0;
}
