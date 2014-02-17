#ifndef VANILLA_OPTION_H
#define VANILLA_OPTION_H

#include "wrapper.h"
#include "Payoff.h"

class VanillaOption
{
public:
	VanillaOption( const Wrapper<Payoff>& thePayoff_, const double Expiry_);
	VanillaOption(const VanillaOption& original);
	VanillaOption& operator=(const VanillaOption& original);
	~VanillaOption();
	double GetExpiry() const;
	double GetValue(const double Spot) const;

private:
	double Expiry;
	Wrapper<Payoff> thePayoff; 
};




#endif