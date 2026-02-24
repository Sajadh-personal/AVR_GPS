#include "gps.h"

#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "convert.h"

GPS_Data    gps_data;
char        UTC_time[12];
float       knots;

void parse(char*  nmea)
{
	if (strncmp(nmea, "$GPRMC", 6) == 0 ||
	strncmp(nmea, "$GNRMC", 6) == 0)
	{
		GPS_GetLatLon_Text(nmea, &gps_data);
	}	
}
#if 1
uint8_t GPS_GetLatLon_Text(char *nmea, GPS_Data *gps)
{
	if (strncmp(nmea, "$GPRMC", 6) != 0 &&
	strncmp(nmea, "$GNRMC", 6) != 0)
	return 0;   // Not RMC sentence
	char *token;
	uint8_t field = 0;
	token = strtok(nmea, ",");
	while (token != NULL)
	{
		field++;
		if (field == 2)  		strcpy(UTC_time, token);
		if (field == 4)  		strcpy(gps->latitude, token);
		if (field == 5)  		strcpy(gps->lat_dir, token);
		if (field == 6)  		strcpy(gps->longitude, token);
		if (field == 7)  		strcpy(gps->lon_dir, token);
		if (field == 8)  		strcpy(gps->knots, token);
		token = strtok(NULL, ",");
	}
	
	UTC_to_IST(UTC_time, gps->time);
    knots_to_kmph(gps->knots, gps->speed);
	return 1;   // Success
}
#endif



void knots_to_kmph(char *knots_val, char *kmph_val)
{
	float    knots;
	
	string_to_float(knots_val, &knots);
	knots = knots * 1.852;
	sprintf(kmph_val, "%d", (int)knots);
}

void UTC_to_IST(char *utc_time, char *ist_time)
{
	int hour, min, sec;

	// Extract hh mm ss
	sscanf(utc_time, "%2d%2d%2d", &hour, &min, &sec);

	// Add IST offset
	hour += 5;
	min  += 30;

	// Handle minute overflow
	if (min >= 60)
	{
		min -= 60;
		hour += 1;
	}

	// Handle hour overflow
	if (hour >= 24)
	{
		hour -= 24;
	}

	// Store back to string
	sprintf(ist_time, "%02d%02d%02d", hour, min, sec);
}