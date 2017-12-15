#include "../../include/Filters/Butterworth2nd.h"

void createButterworth2nd(Butterworth2nd* filter, double fc, double freq_sampling)
{
    createTF2ndOrderHandler(filter, 1.0, 1.0, 1.0, -1.0, -1.0);
}

double runButterworth2nd(Butterworth2nd* filter, double u)
{
    return runTF2ndOrder(filter, u);
}
