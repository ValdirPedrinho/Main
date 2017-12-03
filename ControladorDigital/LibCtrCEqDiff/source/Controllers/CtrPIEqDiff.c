#include "../../include/Controllers/CtrPIEqDiff.h"

void createPIHandler(CtrPI* cPI, ADC2Ctr* adc2Ctr, Ctr2PWM* ctr2PWM, double k, double tau, double freq_sampling, double min_output, double max_output)
{
	double b0 = k + 1.0/(2*tau*freq_sampling);
	double b1 = 1.0/(2*tau*freq_sampling) - k;
	createTF1stOrderHandler(&(cPI->ctr), b1, b0, -1.0);
	
	double Th = k*tau;
	double Ts = 1.0/freq_sampling;
	b0 = (0.002*Th + Ts)/(2*Th + Ts);
	b1 = (Ts - 0.002*Th)/(2*Th + Ts);
	double a1 = (Ts - 2*Th)/(2*Th + Ts);
	createTF1stOrderHandler(&(cPI->refFilter), b1, b0, a1);

	cPI->min_output = min_output;
	cPI->max_output = max_output;
	
	cPI->adc2Ctr = adc2Ctr;
	cPI->ctr2PWM = ctr2PWM;
}

double runPI(CtrPI* cPI, double ref, double feedback)
{
	double aux = runTF1stOrder(&(cPI->refFilter), ref);
	double e =  aux - feedback;
	double y = runTF1stOrder(&(cPI->ctr), e);
	if(y > cPI->max_output) 
	{
		(cPI->ctr).y1 = cPI->max_output;
		return cPI->max_output;	
	}
	if(y < cPI->min_output)
	{
		(cPI->ctr).y1 = cPI->min_output;
		return cPI->min_output;
	}
	return y;
}

uintMAX_t runPIfromADC2PWM(CtrPI* cPI, double ref, uintMAX_t feedback) 
{
	if((cPI->adc2Ctr == NULL) || (cPI->ctr2PWM == NULL)) {
		return 0;
	}
	return runCtr2PWM(*(cPI->ctr2PWM), runPI(cPI, ref, runADC2Ctr(*(cPI->adc2Ctr), feedback)));
}
