#include "Payoff.h"

PayoffCall::PayoffCall(double Strike_) : Strike(Strike_)
{}

double PayoffCall::operator()(double Spot) const
{
	return (Spot - Strike) > 0 ? (Spot - Strike) : 0 ;
}

Payoff* PayoffCall::clone() const
{
	//Note could use copy constructor instead? Perhaps would be faster
	//return new PayoffCall(Strike);
	return new PayoffCall(*this);
}

PayoffForward::PayoffForward()
{}

double PayoffForward::operator()(double Spot) const
{
	return Spot;
}

Payoff* PayoffForward::clone() const
{
	//Note could use copy constructor instead? Perhaps would be faster
	//return new PayoffCall(Strike);
	return new PayoffForward(*this);
}