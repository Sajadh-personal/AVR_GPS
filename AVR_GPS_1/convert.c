#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include "convert.h"

void string_to_float(char *str, float *flt)
{
	float result = 0.0;
	float fraction = 0.0;
	float divisor = 1.0;
	uint8_t sign = 0;

	// Check sign
	if (*str == '-')
	{
		sign = 1;
		str++;
	}

	// Integer part
	while (*str && *str != '.')
	{
		if (*str >= '0' && *str <= '9')
		{
			result = result * 10.0 + (*str - '0');
		}
		str++;
	}

	// Fraction part
	if (*str == '.')
	{
		str++;
		while (*str && (*str >= '0' && *str <= '9'))
		{
			fraction = fraction * 10.0 + (*str - '0');
			divisor *= 10.0;
			str++;
		}
	}

	result += (fraction / divisor);

	if (sign)
	result = -result;

	*flt = result;
}