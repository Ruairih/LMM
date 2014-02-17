#ifndef EXOTIC_OPTION_H
#define EXOTIC_OPTION_H

#include "wrapper.h"
#include "Payoff.h"
#include <vector>

class PathDOption
{
public:
	PathDOption(void);
	PathDOption( const Wrapper<Payoff>& thePayoff_, const std::vector<double> Dates_,const std::vector<double> paymentDates_);
	PathDOption(const PathDOption& original);
	PathDOption& operator=(const PathDOption& original);
	virtual ~PathDOption();
	virtual const std::vector<double> GetDates() const;
	virtual const std::vector<double> GetPaymentDates() const;
	virtual std::vector<double>& GetValue(const std::vector<std::pair<double,double>> Spot, const std::vector<double> payDates) ;
	virtual unsigned long GetSizePaymentDates();

private:
	const std::vector<double> Dates;
	std::vector<double> paymentDates;
	std::vector<double>::const_iterator paymentDates_itr;
	Wrapper<Payoff> thePayoff;
	std::vector<double> payoffVector;
	std::vector<double>::iterator payoffVector_itr;
};

class AsianOption : public PathDOption
{
public:
	AsianOption( const Wrapper<Payoff>& thePayoff_, const std::vector<double> Dates_,const std::vector<double> paymentDates_);
	AsianOption(const AsianOption& original);
	AsianOption& operator=(const PathDOption& original);
	virtual ~AsianOption();
	virtual std::vector<double>& GetValue(const std::vector<std::pair<double,double>> Spot, const std::vector<double> payDates) ;

private:
	const std::vector<double> Dates;
	std::vector<double> paymentDates;
	std::vector<double>::const_iterator paymentDates_itr;
	Wrapper<Payoff> thePayoff;
	std::vector<double> payoffVector;
	std::vector<double>::iterator payoffVector_itr;
};



#endif