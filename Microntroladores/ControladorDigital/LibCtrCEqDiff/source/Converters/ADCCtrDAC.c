#include "../../include/Converters/ADCCtrDAC.h"

void createADC2CtrHandler(ADC2Ctr* adc2ctr, uint8_t bits_ADC, double sensor_gain, double min_analog_input, double max_analog_input)
{
    adc2ctr->max_adc = _pow(2,bits_ADC) -1;
    adc2ctr->min_analog_input = min_analog_input/sensor_gain;
    adc2ctr->delta_analog_input = (max_analog_input - min_analog_input)/sensor_gain;
}

double runADC2Ctr(ADC2Ctr adc2ctr, int_t adc_read)
{
    adc_read = (adc_read < 0) ? 0 : adc_read;
    adc_read = (adc_read > adc2ctr.max_adc) ? adc2ctr.max_adc : adc_read;

    double aux = (adc2ctr.delta_analog_input)*((double) adc_read);
    aux /= ((double) adc2ctr.max_adc);
    aux += adc2ctr.min_analog_input;
    return aux;
}

void createCtr2PWMHandler(Ctr2PWM* ctr2PWM, int_t max_pwm, double min_ctr_output, double max_ctr_output)
{
    ctr2PWM->max_pwm = max_pwm;
    ctr2PWM->min_ctr_output = min_ctr_output;
    ctr2PWM->max_ctr_output = max_ctr_output;
    ctr2PWM->delta_ctr_output = max_ctr_output - min_ctr_output;
}

int_t runCtr2PWM(Ctr2PWM ctr2PWM, double ctr_output)
{
    if(ctr_output < ctr2PWM.min_ctr_output)
    {
        return 0;
    }
    if(ctr_output > ctr2PWM.max_ctr_output)
    {
        return ctr2PWM.max_pwm;
    }
    double aux = ctr_output - ctr2PWM.min_ctr_output;
    aux *= ((double) ctr2PWM.max_pwm);
    aux /= (ctr2PWM.delta_ctr_output);
    return _round(aux);
}
