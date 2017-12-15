#include "../../include/Utilities/utilities.h"

int_t _round(double number)
{
    return (number >= 0) ? (int_t)(number + 0.5) : (int_t)(number - 0.5);
}

int_t _ceil(double number)
{
	int_t aux = number;
	if(number >= 0) {		
		return ((number - ((double) aux)) > 0.0) ? aux + 1 : aux;
	}
	return ((number - ((double) aux)) < 0.0) ? aux - 1 : aux;
}

int_t _pow(int_t base, uint8_t exp)
{
	uint8_t i;
	int_t result = 1;
	for(i=0; i<exp; i++) {
		result *= base;
	}
	return result;
}

double _abs(double number)
{
	return (number >= 0) ? number : -number;
}
