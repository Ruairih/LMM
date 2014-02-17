#include "StatGatherer.h"

MeanStat::MeanStat() : path(0)
{}

void MeanStat::Inject(std::vector<double> result)
{
	std::transform(result.begin(), result.end(), sum.begin(), sum.begin(), std::plus<double>());
	path++;

}

void MeanStat::ResizeSum(unsigned long resize)
{
	sum.resize(resize);
	//stats.resize(resize);
}

std::vector<std::vector<double>> MeanStat::Extract()
{
	//stats.resize(2);
	//stats[0].resize(2);
	std::vector<double>::iterator sum_itr;

	std::transform(sum.begin(), sum.end(), sum.begin(), std::bind1st(std::multiplies<double>(), 1./path));
	
	//stats.push_back(sum);
	for(sum_itr = sum.begin(); sum_itr != sum.end(); sum_itr++)
	{
		std::vector<double> tempv;
		tempv.push_back(*sum_itr);
		stats.push_back(tempv);
	}

	return stats;
}

StatGatherer* MeanStat::clone() const
{
	return new MeanStat(*this);

}