#ifndef TF_2nd_ORDER_EQ_DIFF_H
#define TF_2nd_ORDER_EQ_DIFF_H

#include "../Utilities/utilities.h"

///				 b0 + b1*z^-1 + b2*z^-2		Y(z)
///		H(z) =  ------------------------ = ------
///				  1 + a1*z^-1 + a2*z^-2		U(z)
///
struct TF2ndOrder
{
	double b2;
	double b1;
	double b0;
	double a2;
	double a1;
	double y2;
	double y1;
	double u2;
	double u1;
};

typedef struct TF2ndOrder TF2nd;

void createTF2ndOrderHandler(TF2nd* tf, double b2, double b1, double b0, double a2, double a1);

double runTF2ndOrder(TF2nd* tf, double u);

#endif
