#define  F_CPU 16000000UL

#include <util/delay.h>
#include <avr/io.h>

//#include "oled.h"
#include "i2c.h"


int I2C_Init(void)
{
	TWSR = 0x00;
	TWBR = ((F_CPU / 100000UL) - 16) / 2; // 100kHz
	return (0);
}

void I2C_Start(void)
{
	TWCR = (1 << TWINT) | (1 << TWSTA) | (1 << TWEN);
	while (!(TWCR & (1 << TWINT)));
}

void I2C_Stop(void)
{
	TWCR = (1 << TWINT) | (1 << TWEN) | (1 << TWSTO);
}

void I2C_Write(uint8_t data)
{
	TWDR = data;
	TWCR = (1 << TWINT) | (1 << TWEN);
	while (!(TWCR & (1 << TWINT)));
}