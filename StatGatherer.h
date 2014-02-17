#ifndef STATGATHERER_H
#define STATGATHERER_H
#include <vector>
#include <algorithm>
#include <functional>
#include <iterator>


class StatGatherer
{
public:
	StatGatherer(){}
	virtual void Inject(std::vector<double> result)=0;
	virtual std::vector<std::vector<double>> Extract()=0;
	virtual StatGatherer* clone() const=0;
	virtual void ResizeSum(unsigned long)=0;
	virtual ~StatGatherer(){}

private:
	//std::vector<double> stats;

};

class MeanStat : public StatGatherer
{
public:
	MeanStat();
	virtual void Inject(std::vector<double> result);
	virtual std::vector<std::vector<double>> Extract();
	virtual StatGatherer* clone() const;
	virtual void ResizeSum(unsigned long resize);
	virtual ~MeanStat(){}

private:
	std::vector<std::vector<double>> stats;
	std::vector<double> sum;
	unsigned long path;

};

#endif