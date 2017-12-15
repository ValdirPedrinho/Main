#ifndef UTILITIES_H
#define UTILITIES_H

#define kilo_const      1000
#define mega_const      1000000
#define giga_const      1000000000
#define mili_const      0.001
#define micro_const     0.000001
#define nano_const      0.000000001

#ifndef NULL
#define NULL 0
#endif

typedef long long int int_t;
typedef unsigned char uint8_t;

int_t _round(double number);

int_t _ceil(double number);

int_t _pow(int_t base, uint8_t exp);

double _abs(double number);

#endif
