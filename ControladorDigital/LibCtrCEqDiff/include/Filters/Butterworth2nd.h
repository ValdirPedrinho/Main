#ifndef BUTTERWORTH2ND_H
#define BUTTERWORTH2ND_H

#include "../TransferFunctions/TF2ndOrdEqDiff.h"

typedef TF2nd  Butterworth2nd;

/// Falta implementar corretamente
void createButterworth2nd(Butterworth2nd* filter, double fc, double freq_sampling);
double runButterworth2nd(Butterworth2nd* filter, double u);

#endif
