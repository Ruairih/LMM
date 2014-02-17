#include "VanillaOption.h"
#include <vector>

VanillaOption::VanillaOption(const Wrapper<Payoff>& thePayoff_, const double Expiry_) : thePayoff(thePayoff_), Expiry(Expiry_)
{

}

VanillaOption::~VanillaOption()
{}

VanillaOption::VanillaOption(const VanillaOption& original) : thePayoff(original.thePayoff)
{
	Expiry = original.Expiry;
}

double VanillaOption::GetExpiry() const
{
	return Expiry;
}

double VanillaOption::GetValue(const double Spot) const
{
	return thePayoff->operator()(Spot);
}

VanillaOption& VanillaOption::operator=(const VanillaOption& original)
{
	thePayoff = original.thePayoff;
	return *this;
}