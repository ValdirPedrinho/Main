#include "../../include/Converters/ADCCtrDAC.h"

void createADC2CtrHandler(ADC2Ctr* adc2ctr, uint8_t bits_ADC, double sensor_gain, double min_input, double max_input)
{
	adc2ctr->max_adc = (uintMAX_t) _pow(2,bits_ADC) -1;
	adc2ctr->sensor_gain = sensor_gain;
	adc2ctr->min_input = _abs(min_input);
	adc2ctr->delta_input = max_input - min_input;
}

double runADC2Ctr(ADC2Ctr adc2ctr, uintMAX_t adc_read)
{
	double aux = (adc2ctr.delta_input)*((double) adc_read);
	aux /= ((double) adc2ctr.max_adc);
	aux += adc2ctr.min_input;
	aux /= adc2ctr.sensor_gain;
	return aux;
}

void createCtr2PWMHandler(Ctr2PWM* ctr2PWM, uintMAX_t max_pwm, double min_ctr_output, double max_ctr_output)
{
	ctr2PWM->max_pwm = max_pwm;	
	ctr2PWM->min_ctr_output = min_ctr_output;
	ctr2PWM->delta_ctr_output = max_ctr_output - min_ctr_output;
}

uintMAX_t runCtr2PWM(Ctr2PWM ctr2PWM, double ctr_output)
{
	double aux = ctr_output - ctr2PWM.min_ctr_output;
	aux *= ((double) ctr2PWM.max_pwm);
	aux /= (ctr2PWM.delta_ctr_output);
	return  (uintMAX_t) _round(aux);
}
