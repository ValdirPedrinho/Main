#include "../../include/Controllers/CtrPIEqDiff.h"

void createRefFilterPI(RefFilterPI* refFilter, double k, double tau, double freq_sampling)
{
    double Th = k*tau;
    double Ts = 1.0/freq_sampling;
    double b0 = (0.02*Th + Ts)/(2*Th + Ts);
    double b1 = (Ts - 0.02*Th)/(2*Th + Ts);
    double a1 = (Ts - 2*Th)/(2*Th + Ts);
    createTF1stOrderHandler(refFilter, b1, b0, a1);
}

void createPIHandler(CtrPI* cPI, RefFilterPI* refFilter, Butterworth2nd* fbFilter, ADC2Ctr* adc2Ctr, Ctr2PWM* ctr2PWM, double k, double tau, double freq_sampling, double min_output, double max_output)
{
    double b0 = k + 1.0/(2*tau*freq_sampling);
    double b1 = 1.0/(2*tau*freq_sampling) - k;
    createTF1stOrderHandler(&(cPI->ctr), b1, b0, -1.0);

    cPI->min_output = min_output;
    cPI->max_output = max_output;

    cPI->adc2Ctr = adc2Ctr;
    cPI->ctr2PWM = ctr2PWM;
    cPI->refFilter = refFilter;
    cPI->fbFilter = fbFilter;
}

double run_minimal_PI(CtrPI* cPI, double ref, double feedback)
{
    double y = runTF1stOrder(&(cPI->ctr), ref - feedback);
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

double runPI(CtrPI* cPI, double ref, double feedback)
{
    if(cPI->refFilter != NULL)
    {
        ref = runTF1stOrder(cPI->refFilter, ref);
    }
    if(cPI->adc2Ctr != NULL)
    {
        feedback = runADC2Ctr(*(cPI->adc2Ctr), feedback);
    }
    if(cPI->fbFilter != NULL)
    {
        feedback = runButterworth2nd(cPI->fbFilter, feedback);
    }
    return run_minimal_PI(cPI, ref, feedback);
}

int_t runPI2PWM(CtrPI* cPI, double ref, double feedback)
{
    return runCtr2PWM(*(cPI->ctr2PWM), runPI(cPI, ref, feedback));
}
