#ifndef PARAMETERS_H
#define PARAMETERS_H
#include "wrapper.h"
#include <vector>
#include <iostream>

class Parameter
{
public:
	Parameter(){};
	virtual double DoIntegral(const double time1, const double time2) const=0;
	virtual double DoSquareIntegral(const double time1, const double time2) const=0;
	virtual double Mean(const double time1, const double time2) const=0;
	virtual double RootMeanSquare(const double time1, const double time2) const=0;
	virtual Parameter* clone() const=0;
	virtual ~Parameter(){};

private:
	
};

class ConstantParameter : public Parameter
{
public:
	ConstantParameter(const std::vector<double> parameters);
	virtual double DoIntegral(const double time1, const double time2) const;
	virtual double DoSquareIntegral(const double time1, const double time2) const;
	virtual double Mean(const double time1, const double time2) const;
	virtual double RootMeanSquare(const double time1, const double time2) const;
	virtual Parameter* clone() const;
	virtual ~ConstantParameter(){}

private:
	std::vector<double> parameters;

};

class OneDParameter : public Parameter
{
public:
	OneDParameter(  std::vector<  std::pair<double,double>> parameters);
	virtual double DoIntegral(const double time1, const double time2) const;
	virtual double DoSquareIntegral(const double time1, const double time2) const;
	virtual double Mean(const double time1, const double time2) const;
	virtual double RootMeanSquare(const double time1, const double time2) const;
	virtual Parameter* clone() const;
	virtual ~OneDParameter(){}

private:
	 std::vector< std::pair<double, double>> parameters;
};


#endif