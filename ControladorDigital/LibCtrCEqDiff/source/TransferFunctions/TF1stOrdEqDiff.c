#include "../../include/TransferFunctions/TF1stOrdEqDiff.h"

//			    b0 + b1*z^-1     Y(z)
//		H(z) = -------------- = ------
//			     1 + a1*z^-1	 U(z)
//
void createTF1stOrderHandler(TF1st* tf, double b1, double b0, double a1)
{
	tf->y1 = 0;
	tf->u1 = 0;
	tf->b1 = b1;
	tf->b0 = b0;
	tf->a1 = a1;
}

double runTF1stOrder(TF1st* tf, double u)
{
	double y;
	y = (tf->b0)*u + (tf->b1)*(tf->u1) - (tf->a1)*(tf->y1);
	tf->u1 = u;
	tf->y1 = y;
	return y;
}
