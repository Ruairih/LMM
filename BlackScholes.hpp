#include "wrapper.h"
#include "Parameters.h"
#include "Random3.h"
#include "Normals.h"

double CallBS(const Wrapper<Parameter>& r, const Wrapper<Parameter>& sig, double Expiry,double Spot, double Strike)
{
	double d1,d2;

	d1=1./(sig->Mean(1,2)*sqrt(Expiry)) * ( log(Spot/Strike) + (r->Mean(1,2) + .5 * sig->Mean(1,2) * sig->Mean(1,2) ) * Expiry);
	d2=1./(sig->Mean(1,2)*sqrt(Expiry)) * ( log(Spot/Strike) + (r->Mean(1,2) - .5 * sig->Mean(1,2) * sig->Mean(1,2) ) * Expiry);
	double ans = CumulativeNormal(d1) * Spot - CumulativeNormal(d2) * Strike * exp(-r->Mean(1,2) * Expiry);

	return ans;
}