#ifndef BGM_PRODUCT_H
#define BGM_PRODUCT_H

#include "wrapper.h"
#include "Payoff.h"
#include <vector>



class BGMProduct
{
public:
	BGMProduct(){};
	BGMProduct(const BGMProduct& original);
	BGMProduct& operator=(const BGMProduct& original);
	virtual ~BGMProduct();
	virtual const std::vector<double>& GetUnderlyingTimes() const=0;
	virtual const std::vector<double>& GetEvolutionTimes() const=0;
	virtual void Reset()=0;
	virtual std::pair<bool, std::vector<std::pair<double,double>> > DoNextStep(std::vector<std::pair<double,double>> currentForwardRates)=0;
	
};

class EuroSwaption : public BGMProduct
{
public:
	EuroSwaption( const Wrapper<Payoff>& thePayoff_, const std::vector<double> Dates_,const std::vector<double> paymentDates_, double tenorFixed_);
	EuroSwaption(const EuroSwaption& original);
	EuroSwaption& operator=(const EuroSwaption& original);
	virtual ~EuroSwaption();
	virtual const std::vector<double>& GetUnderlyingTimes() const;
	virtual const std::vector<double>& GetEvolutionTimes() const;
	virtual void Reset();
	virtual std::pair<bool, std::vector<std::pair<double,double>> > DoNextStep(std::vector<std::pair<double, double>> currentForwardRates);
private:
	double tenorFixed;
	class pimpl;
	pimpl *swap_impl;
	const std::vector<double> Dates;
	const std::vector<double> paymentDates;
	std::vector<double>::const_iterator paymentDates_itr;
	Wrapper<Payoff> thePayoff;
	const std::vector<double> payoffVector;
	std::vector<double>::iterator payoffVector_itr;
};



#endif