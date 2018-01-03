#include "../../include/Filters/Butterworth2nd.h"

void createButterworth2nd(Butterworth2nd* filter, double fc, double freq_sampling)
{
	double Ts = 1.0/freq_sampling;
	double T2s = pow(Ts,2);
	double w_nd = 2*(tan(pi_const*fc*Ts))/Ts;
	double w2_nd = pow(w_nd,2);
	double w_nd2csi = sqrt(2)*w_nd;
	double h = 4.0 + 2.0*w_nd2csi*Ts + w2_nd*T2s;
	double b0 = (w2_nd*T2s)/h;
	double b1 = (2.0*w2_nd*T2s)/h;
	double b2 = (w2_nd*T2s)/h;
	double a1 = (2.0*w2_nd*T2s-8.0)/h;
	double a2 = (4.0-2*w_nd2csi*Ts+w2_nd*T2s)/h;
    createTF2ndOrderHandler(filter, b2, b1, b0, a2, a1);
}

double runButterworth2nd(Butterworth2nd* filter, double u)
{
    return runTF2ndOrder(filter, u);
}
