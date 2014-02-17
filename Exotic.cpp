#include "Exotic.h"

PathDOption::PathDOption(void) 
{}

PathDOption::PathDOption(const Wrapper<Payoff>& thePayoff_, const std::vector<double> Dates_,const std::vector<double> paymentDates_) : thePayoff(thePayoff_), Dates(Dates_), paymentDates(paymentDates_)
{

}

PathDOption::~PathDOption()
{}

PathDOption::PathDOption(const PathDOption& original) : thePayoff(original.thePayoff), Dates(original.Dates), paymentDates(original.Dates)
{

}

const std::vector<double> PathDOption::GetDates() const
{
	return Dates;
}

const std::vector<double> PathDOption::GetPaymentDates() const
{
	return paymentDates;
}

std::vector<double>& PathDOption::GetValue(const std::vector<std::pair<double,double>> Spot, const std::vector<double> payDates) 
{
	//maybe have a single seperate resize function so not resizing every iteration
	payoffVector.resize(payDates.size());

	int index_itr = Spot.size() - payoffVector.size();
	//TODO: Note the spot dates might not be the same as payment dates, need to sort this out.
	for( payoffVector_itr = payoffVector.begin(); payoffVector_itr != payoffVector.end(); payoffVector_itr++, index_itr++)
	{
		*payoffVector_itr = thePayoff->operator()(Spot[index_itr].second);
	}
	return payoffVector;
}

PathDOption& PathDOption::operator=(const PathDOption& original)
{
	thePayoff = original.thePayoff;
	return *this;
}

unsigned long PathDOption::GetSizePaymentDates()
{
	return paymentDates.size();
}

AsianOption::AsianOption(const Wrapper<Payoff>& thePayoff_, const std::vector<double> Dates_,const std::vector<double> paymentDates_) : PathDOption(thePayoff_,Dates_,paymentDates_) ,thePayoff(thePayoff_), Dates(Dates_), paymentDates(paymentDates_)
{

}

AsianOption::~AsianOption()
{}

AsianOption::AsianOption(const AsianOption& original) : PathDOption(original.thePayoff, original.Dates, original.Dates) ,thePayoff(original.thePayoff), Dates(original.Dates), paymentDates(original.Dates)
{

}

std::vector<double>& AsianOption::GetValue(const std::vector<std::pair<double,double>> Spot, const std::vector<double> payDates) 
{
	//maybe have a single seperate resize function so not resizing every iteration
	payoffVector.resize(payDates.size());

	int index_itr = Spot.size() - payoffVector.size();
	double runningSum=0.;
	//TODO: Note the spot dates might not be the same as payment dates, need to sort this out.
	for( int i =0; i < (int)(payDates.size()); i++)
	{
		runningSum += Spot[i].second;
	}
	runningSum /= (payDates.size()); 

	 payoffVector_itr = payoffVector.begin();
	*payoffVector_itr = thePayoff->operator()(runningSum);
	return payoffVector;
}
