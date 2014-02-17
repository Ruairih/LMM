#include "BGMProduct.h"


BGMProduct::~BGMProduct()
{}

BGMProduct::BGMProduct(const BGMProduct& original)
{

}


EuroSwaption::EuroSwaption(const Wrapper<Payoff>& thePayoff_, const std::vector<double> Dates_,const std::vector<double> paymentDates_, double tenorFixed_) : thePayoff(thePayoff_), Dates(Dates_), paymentDates(paymentDates_), tenorFixed(tenorFixed_)
{

}

EuroSwaption::~EuroSwaption()
{}

EuroSwaption::EuroSwaption(const EuroSwaption& original) : thePayoff(original.thePayoff), Dates(original.Dates), paymentDates(original.Dates)
{

}

const std::vector<double>& EuroSwaption::GetUnderlyingTimes() const
{
	return paymentDates;
}

const std::vector<double>& EuroSwaption::GetEvolutionTimes() const
{
	return payoffVector;
}

void EuroSwaption::Reset()
{
	
}


std::pair<bool, std::vector<std::pair<double,double>> > EuroSwaption::DoNextStep(std::vector<std::pair<double, double>> currentForwardRates)
{
	std::pair<bool, std::vector<std::pair<double,double>> > nextStep;
	double intrinsicValue;
	nextStep.first=0;
	
	std::pair<double,double> test;

	test = std::make_pair(paymentDates[0],intrinsicValue);

	//nextStep.second.push_back( (paymentDates[0],intrinsicValue) );
	nextStep.second.push_back( test );
	return nextStep;
}


