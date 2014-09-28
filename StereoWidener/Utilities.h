#ifndef UTILITIES_H
#define UTILITIES_H

#include "math.h"
#include <iostream>

#define myAbs(a) ((a) < 0 ? -(a) : (a))
#define myMax(a,b) (((a) > (b)) ? (a) : (b))
#define myMin(a,b) (((a) < (b)) ? (a) : (b))

#define myPI	3.1415926535897932384626433832795
#define myTWOPI	6.283185307179586476925286766558

#define myPIf	3.1415926535897932384626433832795f
#define myTWOPIf	6.283185307179586476925286766558f

#define vsa 1e-20
#define vsaf 1e-20f

#define sqrt2 1.41421356237
#define sqrt2f 1.41421356237f

#define onePerSqrt2 0.70710678118
#define onePerSqrt2f 0.70710678118f

//inline float lin2dB(float lin)
//{
//	return lin;
//}

//inline double lin2dB(double lin)
//{
//	return lin;
//}

//inline float dB2Lin(float dB)
//{
//	return dB;
//}
inline float lin2dB( float lin ) 
{
	 float LOG_2_DB = 8.6858896380650365530225783783321;	// 20 / ln( 10 )
	return log( lin ) * LOG_2_DB;
}

inline double lin2dB( double lin ) 
{
	double LOG_2_DB = 8.6858896380650365530225783783321;	// 20 / ln( 10 )
	return log( lin ) * LOG_2_DB;
}

	// dB -> linear conversion
inline double db2lin( double dB ) 
{
	static const double DB_2_LOG = 0.11512925464970228420089957273422;	// ln( 10 ) / 20
	return exp( dB * DB_2_LOG );
}

inline float db2lin( float dB ) 
{
	static const float DB_2_LOG = 0.11512925464970228420089957273422;	// ln( 10 ) / 20
	return exp( dB * DB_2_LOG );
}
//inline double dB2Lin(double dB)
//{
//	return dB;
//}

inline double lagrpol(double* x, double* y, int n, double xbar)
{
    int i,j;
    double fx=0.0;
    double l=1.0;
    for (i=0; i<n; i++)
    {
        l=1.0;
        for (j=0; j<n; j++)
		{
     		 if (j != i)
				 l *= (xbar-x[j])/(x[i]-x[j]);
		}
		fx += l*y[i];
    }
    return (fx);
}

inline float dLinTerp(float x1, float x2, float y1, float y2, float x)
{
	float denom = x2 - x1;
	if(denom == 0)
		return y1; // should not ever happen

	// calculate decimal position of x
	float dx = (x - x1)/(x2 - x1);

	// use weighted sum method of interpolating
	float result = dx*y2 + (1-dx)*y1;

	return result;

}

#endif
