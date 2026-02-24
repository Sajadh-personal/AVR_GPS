#ifndef _OLED_H_
#define _OLED_H_


#define F_CPU 16000000UL

#include <util/delay.h>
#include <avr/io.h>
#include "i2c.h"
#include "oled.h"

#define    OLED_ADDR    0x3c

void OLED_Command(uint8_t cmd);
void OLED_Init(void);
void OLED_Data(uint8_t data);
void OLED_Clear(void);
void OLED_char_print(char*  chr_ptr);
void OLED_write(int page, int col, char* msg);
void OLED_write_big(int page, int col, char* msg);
void OLED_big_number(int page, int col, char *chr_ptr);

#endif