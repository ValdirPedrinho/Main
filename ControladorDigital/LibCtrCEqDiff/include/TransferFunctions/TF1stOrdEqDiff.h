#ifndef TF_1st_ORDER_EQ_DIFF_H
#define TF_1st_ORDER_EQ_DIFF_H

#include "../Utilities/utilities.h"

///			    b0 + b1*z^-1     Y(z)
///		H(z) = -------------- = ------
///			     1 + a1*z^-1	 U(z)
///
struct TF1stOrder
{
	double b1;
	double b0;
	double a1;
	double y1;
	double u1;
};

typedef struct TF1stOrder TF1st;

void createTF1stOrderHandler(TF1st* tf, double b1, double b0, double a1);

double runTF1stOrder(TF1st* tf, double u);

#endif
