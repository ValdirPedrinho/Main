#ifndef UTILITIES_H
#define UTILITIES_H

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

#ifndef int32_t
#define int32_t long long int
#endif

#ifndef uint32_t
#define uint32_t unsigned long long int
#endif

#ifndef uint8_t
#define uint8_t unsigned char
#endif

typedef int32_t intMAX_t;
typedef uint32_t uintMAX_t;

intMAX_t _round(double number);

intMAX_t _ceil(double number);

intMAX_t _pow(intMAX_t base, uint8_t exp);

double _abs(double number);

#define kilo_const      1000
#define mega_const      1000000
#define giga_const      1000000000
#define mili_const      0.001
#define micro_const     0.000001
#define nano_const      0.000000001

#endif
