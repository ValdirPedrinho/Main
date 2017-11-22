#ifndef ADC_CTR_DCA_H
#define ADC_CTR_DCA_H

#include "../Utilities/utilities.h"

struct ADC2Ctr 
{
	double sensor_gain;
	uintMAX_t max_adc;
	double min_input;
	double delta_input;
};

typedef struct ADC2Ctr ADC2Ctr;

void createADC2CtrHandler(ADC2Ctr* adc2ctr, uint8_t bits_ADC, double sensor_gain, double min_input, double max_input);
double runADC2Ctr(ADC2Ctr adc2ctr, uintMAX_t adc_read);

struct Ctr2PWM 
{
	uintMAX_t max_pwm;	
	double min_ctr_output;
	double delta_ctr_output;
};

typedef struct Ctr2PWM Ctr2PWM;

void createCtr2PWMHandler(Ctr2PWM* ctr2PWM, uintMAX_t max_pwm, double min_output, double max_output);
uintMAX_t runCtr2PWM(Ctr2PWM ctr2PWM, double ctr_output);

#endif
