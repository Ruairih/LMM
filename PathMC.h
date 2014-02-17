#ifndef PATHMC_H
#define PATHMC_H

#include "wrapper.h"
#include "VanillaOption.h"
#include "Parameters.h"
#include "StatGatherer.h"
#include "wrapper.h"
#include "Random3.h"
#include "Arrays.h"
#include "Exotic.h"
#include <algorithm>
#include <functional>
#include <iterator>
#include "Spectral.h"

class PathMC{
public:
	PathMC(const AsianOption& theOption_, const Wrapper<RandomBase>& randomGen_,double Spot_, const Wrapper<StatGatherer>& stats_, unsigned long iter_, const Wrapper<Parameter>& vol_, const Wrapper<Parameter>& interestr_, int divisions_);
	std::vector<std::vector<double>> GetResult();
	void RunEngine();
	void MakeDiscountFactors();

private:
	AsianOption theOption;
	Wrapper<RandomBase> randomGen;
	Wrapper<StatGatherer> stats;
	Wrapper<Parameter> interestr;
	double Spot;
	unsigned long iter;
	Wrapper<Parameter> vol;
	int divisions;
	const std::vector<double> Dates;
	std::vector<double>::const_iterator Dates_itr;
	std::vector<std::pair<double,double>> onePath;
	std::vector<std::pair<double, double>> discountFactors;
};

class FullPathMC{
public:
	FullPathMC(const AsianOption& theOption_, const Wrapper<RandomBase>& randomGen_,double Spot_, const Wrapper<StatGatherer>& stats_, unsigned long iter_, const Wrapper<Parameter>& vol_, const Wrapper<Parameter>& interestr_, int divisions_);
	std::vector<std::vector<double>> GetResult();
	void RunEngine();
	void MakeDiscountFactors();
	void MakeCovarianceMatrix(std::vector<double> Dates, int rank);
	~FullPathMC();

private:
	AsianOption theOption;
	Wrapper<RandomBase> randomGen;
	Wrapper<StatGatherer> stats;
	Wrapper<Parameter> interestr;
	double Spot;
	unsigned long iter;
	Wrapper<Parameter> vol;
	int divisions;
	const std::vector<double> Dates;
	std::vector<double>::const_iterator Dates_itr;
	std::vector<double>::const_iterator Dates_itr2;
	std::vector<std::pair<double,double>> onePath;
	std::vector<std::pair<double, double>> discountFactors;
	float *a_cov;
};




#endif