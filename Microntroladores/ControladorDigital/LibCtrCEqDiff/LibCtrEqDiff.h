#ifndef LIB_CTR_EQ_DIFF_H
#define LIB_CTR_EQ_DIFF_H

#include "include/Controllers/CtrsEqDiff.h"
#include "include/Converters/ADCCtrDAC.h"

/**
 * ADC:
 * void createADC2CtrHandler(ADC2Ctr* adc2ctr, uint8_t bits_ADC, double sensor_gain, double min_analog_input, double max_analog_input);
 * 
 * PWM:
 * void createCtr2PWMHandler(Ctr2PWM* ctr2PWM, int_t max_pwm, double min_output, double max_output);
 * 
 * Butterworth2nd:
 * createButterworth2nd(Butterworth2nd* filter, double fc, double freq_sampling);
 * 
 * PI:
 * void createRefFilterPI(RefFilterPI* refFilter, double k, double tau, double freq_sampling);
 * void createPIHandler(CtrPI* cPI, RefFilterPI* refFilter, Butterworth2nd* fbFilter, ADC2Ctr* adc2Ctr, Ctr2PWM* ctr2PWM, double k, double tau, double freq_sampling, double min_output, double max_output);
 * double runPI(CtrPI* cPI, double ref, double feedback);
 * int_t runPI2PWM(CtrPI* cPI, double ref, double feedback);
 * 
 * 
 * */

#endif
