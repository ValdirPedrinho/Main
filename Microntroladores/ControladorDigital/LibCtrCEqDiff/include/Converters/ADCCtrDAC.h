#ifndef ADC_CTR_DCA_H
#define ADC_CTR_DCA_H

#include "../Utilities/utilities.h"

struct ADC2Ctr
{
	int_t max_adc;
	double min_analog_input;
	double delta_analog_input;
};

typedef struct ADC2Ctr ADC2Ctr;

void createADC2CtrHandler(ADC2Ctr* adc2ctr, uint8_t bits_ADC, double sensor_gain, double min_analog_input, double max_analog_input);
double runADC2Ctr(ADC2Ctr adc2ctr, int_t adc_read);

struct Ctr2PWM
{
	int_t max_pwm;
	double min_ctr_output;
	double max_ctr_output;
	double delta_ctr_output;
};

typedef struct Ctr2PWM Ctr2PWM;

void createCtr2PWMHandler(Ctr2PWM* ctr2PWM, int_t max_pwm, double min_output, double max_output);
int_t runCtr2PWM(Ctr2PWM ctr2PWM, double ctr_output);

#endif
