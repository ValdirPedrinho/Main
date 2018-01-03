#include "../../include/TransferFunctions/TF2ndOrdEqDiff.h"

//				 b0 + b1*z^-1 + b2*z^-2		Y(z)
//		H(z) =  ------------------------ = ------
//				  1 + a1*z^-1 + a2*z^-2		U(z)
//
void createTF2ndOrderHandler(TF2nd* tf, double b2, double b1, double b0, double a2, double a1)
{
	tf->y1 = 0.0;
	tf->y2 = 0.0;
	tf->u2 = 0.0;
	tf->u1 = 0.0;
	tf->b2 = b2;
	tf->b1 = b1;
	tf->b0 = b0;
	tf->a2 = a2;
	tf->a1 = a1;
}

double runTF2ndOrder(TF2nd* tf, double u)
{
	double y;
	y = (tf->b0)*u + (tf->b1)*(tf->u1) + (tf->b2)*(tf->u2) - (tf->a1)*(tf->y1) - (tf->a2)*(tf->y2);
	tf->u2 = tf->u1;
	tf->u1 = u;
	tf->y2 = tf->y1;
	tf->y1 = y;
	return y;
}

