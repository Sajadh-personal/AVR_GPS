#ifndef    _GPS_H_
#define    _GPS_H_


#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct
{
	char time[12];        // hhmmss.sss
	char fix;
	char latitude[16];
	char lat_dir[2];
	char longitude[16];
	char lon_dir[2];
	char speed[10];       // speed in knots (text)
	char knots[10];
} GPS_Data;

void    parse(char*  nmea_data);
uint8_t GPS_GetLatLon_Text(char *nmea, GPS_Data *gps);
void UTC_to_IST(char *utc_time, char *ist_time);
void knots_to_kmph(char *knots, char *kmph);
#endif