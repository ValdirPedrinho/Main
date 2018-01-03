#ifndef CTR_PI_EQ_DIFF_H
#define CTR_PI_EQ_DIFF_H

#include "../TransferFunctions/TF1stOrdEqDiff.h"
#include "../Converters/ADCCtrDAC.h"
#include "../Filters/Butterworth2nd.h"

typedef TF1st  RefFilterPI;

struct controllerPI
{
	TF1st ctr;
	RefFilterPI* refFilter;
	Butterworth2nd* fbFilter;
	ADC2Ctr* adc2Ctr;
	Ctr2PWM* ctr2PWM;
	double ref;
	double fb;
	double min_output;
	double max_output;
};

typedef struct controllerPI CtrPI;


void createRefFilterPI(RefFilterPI* refFilter, double k, double tau, double freq_sampling);
void createPIHandler(CtrPI* cPI, RefFilterPI* refFilter, Butterworth2nd* fbFilter, ADC2Ctr* adc2Ctr, Ctr2PWM* ctr2PWM, double k, double tau, double freq_sampling, double min_output, double max_output);

double run_minimal_PI(CtrPI* cPI, double ref, double feedback);
double runPI(CtrPI* cPI, double ref, double feedback);
int_t runPI2PWM(CtrPI* cPI, double ref, double feedback);

#endif
