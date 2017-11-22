#ifndef CTR_PI_EQ_DIFF_H
#define CTR_PI_EQ_DIFF_H

#include "../TransferFunctions/TF1stOrdEqDiff.h"
#include "../Converters/ADCCtrDAC.h"

struct controllerPI 
{
	TF1st ctr;
	TF1st refFilter;
	ADC2Ctr* adc2Ctr;
	Ctr2PWM* ctr2PWM;
	double min_output;
	double max_output;
};

typedef struct controllerPI CtrPI;

void createPIHandler(CtrPI* cPI, ADC2Ctr* adc2Ctr, Ctr2PWM* ctr2PWM, double k, double tau, double freq_sampling, double min_output, double max_output);
double runPI(CtrPI* cPI, double ref, double feedback);
uintMAX_t runPIfromADC2PWM(CtrPI* cPI, double ref, uintMAX_t feedback);
double getMinOutputPI(CtrPI cPI);
double getMaxOutputPI(CtrPI cPI);

#endif
