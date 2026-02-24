#ifndef UART_H_
#define UART_H_

#define F_CPU 16000000UL
#include <avr/io.h>

void UART_init(unsigned long baud);
void UART_tx(char data);
void UART_print(char *str);
uint8_t UART_rx(char *data);

#endif
