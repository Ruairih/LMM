#ifndef PAYOFF_H
#define PAYOFF_H

class Payoff
{
public:
	Payoff(){}
	virtual double operator()(double Spot) const=0;
	virtual Payoff* clone() const=0;
	virtual ~Payoff(){}
};

class PayoffCall : public Payoff
{
public:
	PayoffCall(double Strike_);
	virtual double operator()(double Spot) const;
	virtual Payoff* clone() const;
	virtual ~PayoffCall(){}
private:
	double Strike;

};

class PayoffForward : public Payoff
{
public:
	PayoffForward();
	virtual double operator()(double Spot) const;
	virtual Payoff* clone() const;
	virtual ~PayoffForward(){}

};

#endif