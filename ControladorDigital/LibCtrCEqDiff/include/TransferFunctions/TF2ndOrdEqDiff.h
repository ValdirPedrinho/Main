#ifndef TF_2nd_ORDER_EQ_DIFF_H
#define TF_2nd_ORDER_EQ_DIFF_H

#include "../Utilities/utilities.h"

///				 b0 + b1*z^-1 + b2*z^-2		Y(z)
///		H(z) =  ------------------------ = ------
///				  1 + a1*z^-1 + a2*z^-2		U(z)
///
struct TF2ndOrder
{
	double b2;			/// coefficient of z^-2 on numerator of transfer function
	double b1;			/// coefficient of z^-1 on numerator of transfer function
	double b0;			/// coefficient of z^0 on numerator of transfer function
	double a2;			/// coefficient of z^-2 on denominator of transfer function
	double a1;			/// coefficient of z^-1 on denominator of transfer function
	double y2;			/// output at two steps back
	double y1;			/// output at one step back
	double u2;			/// input at two steps back
	double u1;			/// input at one step back
};

typedef struct TF2ndOrder TF2nd;

//				 b0 + b1*z^-1 + b2*z^-2		Y(z)
//		H(z) =  ------------------------ = ------
//				  1 + a1*z^-1 + a2*z^-2		U(z)
//
/**
 * @brief Initializes a data structure of a first order transfer function
 * 
 * The coefficients of transfer function are saved as integers (to fixed
 * point operation). The "precision" parameter is used to convert 
 * coefficients from double point to fixed point. How much bigger value 
 * of "precision", more loyal will be the data struct of transfer function.
 * 
 * @param tf data struct of transfer function
 * @param precision ???????????????????????????????????????????
 * @param b2 coefficient of z^-2 on numerator of transfer function
 * @param b1 coefficient of z^-1 on numerator of transfer function
 * @param b0 coefficient of z^0 on numerator of transfer function
 * @param a2 coefficient of z^-2 on denominator of transfer function
 * @param a1 coefficient of z^-1 on denominator of transfer function
 * */
void createTF2ndOrderHandler(TF2nd* tf, double b2, double b1, double b0, double a2, double a1);

/**
 * @brief Calculus of response of a transfer function for "u" input
 * 
 * @param tf data struct of transfer function
 * @param u input
 * */
double runTF2ndOrder(TF2nd* tf, double u);

#endif
