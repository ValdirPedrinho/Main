#include "../../include/Utilities/utilities.h"

intMAX_t _round(double number)
{
    return (number >= 0) ? (intMAX_t)(number + 0.5) : (intMAX_t)(number - 0.5);
}

intMAX_t _ceil(double number)
{
	intMAX_t aux = number;
	if(number >= 0) {		
		return ((number - ((double) aux)) > 0.0) ? aux + 1 : aux;
	}
	return ((number - ((double) aux)) < 0.0) ? aux - 1 : aux;
}

intMAX_t _pow(intMAX_t base, uint8_t exp)
{
	uint8_t i;
	intMAX_t result = 1;
	for(i=0; i<exp; i++) {
		result *= base;
	}
	return result;
}

double _abs(double number)
{
	return (number >= 0) ? number : -number;
}
