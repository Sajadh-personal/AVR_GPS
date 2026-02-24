/*
 * GPS.c
 *
 * Created: 22-Feb-26 5:08:18 PM
 * Author : Administrator
 */ 
#define F_CPU    16000000UL

#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>
#include <string.h>
#include "i2c.h"
#include "oled.h"
#include "uart.h"
#include "gps.h"

extern     GPS_Data     gps_data;
void display_result(int state);

int main(void)
{
	DDRD = 0x00;
	I2C_Init();
	OLED_Init();
	OLED_Clear();
	UART_init(9600);
	char    message[20];
	memset(message, 0x00, 20);
	memset(&gps_data,0x00,sizeof(gps_data));
	//sprintf(message, "GPS_");
	OLED_write(0,0,message);
    /* Replace with your application code */
	char    received_chr;
	int     index=0;
	char    buffer[100];
	int     state=1;
	int     prty =0;
	
    while (1) 
    {
		prty++;
		if(UART_rx(&received_chr))
		{
			if(received_chr == '$')
			{
				index = 0;      // start new sentence
			}

			buffer[index++] = received_chr;

			if(received_chr == '\n')
			{
				buffer[index] = '\0';   // sentence complete
				parse(buffer);
				display_result(state);
				prty++;
				if(prty>199)
				{
					prty=0;
					if(!(PIND &0x10))
					state++;
					if(state>3)
					state =1;
				}
			}
			
		}
	
    }
}

void display_result(int state)
{
	char    message[12];
	static  int    pre_state;
	if (pre_state != state)
	OLED_Clear();
	pre_state = state;
	switch(state)
	{
		case 1 : 
		    //OLED_Clear();
		    //OLED_write(0,110,"1");
			memset(message, 0,sizeof(message));
			sprintf(message,"%c%c:%c%c", gps_data.time[0], gps_data.time[1], gps_data.time[2], gps_data.time[3]);
			OLED_write_big(0,5*6,message);
			
			OLED_write_big(2,40,gps_data.speed);
			OLED_write(3,80,"KMPH");
			
			break;
		case 2: 
		    //OLED_Clear();
		   // OLED_write(0,110,"2");
		    OLED_write(0,0,gps_data.latitude);
		    OLED_write(0,11*6,gps_data.lat_dir);
		    OLED_write(2,0,gps_data.longitude);
		    OLED_write(2,11*6,gps_data.lon_dir);
			break;
		case 3:
		    //OLED_Clear();
		  //  OLED_write(0,110,"3");
		    OLED_write_big(2,10,gps_data.knots);
		    OLED_write(3,90, "Knots" );
			
			break;
	}
}

