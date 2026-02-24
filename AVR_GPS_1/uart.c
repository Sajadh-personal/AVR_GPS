#include "uart.h"
#include <stdio.h>
#include <stdlib.h>

void UART_init(unsigned long baud)
{
	unsigned int ubrr = (F_CPU / (16UL * baud)) - 1;

	UBRR0H = (unsigned char)(ubrr >> 8);
	UBRR0L = (unsigned char)ubrr;

	// Enable TX and RX
	UCSR0B = (1 << TXEN0) | (1 << RXEN0);

	// 8-bit data, 1 stop bit, no parity
	UCSR0C = (1 << UCSZ01) | (1 << UCSZ00);
}

void UART_tx(char data)
{
	while (!(UCSR0A & (1 << UDRE0)));   // Wait until buffer empty
	UDR0 = data;
}
#if 1
uint8_t UART_rx(char *data)
{
	while (!(UCSR0A & (1 << RXC0)));    // Wait until data received
	*data = UDR0;
	return 1;
}
#endif
#if 0
uint8_t UART_rx(char *data)
{	
	if (UCSR0A & (1 << RXC0))   // Data received?
	{
		*data = UDR0;          // Read data
		return 1;              // Success
	}

	return 0;                  // No data
	
}
#endif

void UART_print(char *str)
{
	while (*str)
	{
		UART_tx(*str++);
	}
}
