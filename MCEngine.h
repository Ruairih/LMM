#ifndef MCENGINE_H
#define MCENGINE_H

#include "VanillaOption.h"
#include "Parameters.h"
#include "StatGatherer.h"
#include "wrapper.h"
#include "Random3.h"
#include "Arrays.h"

class MCEngine
{
public: 
	MCEngine(const VanillaOption& theOption_, const Wrapper<RandomBase>& randomGen_,double Spot_, const Wrapper<StatGatherer>& stats_, unsigned long iter_, const Wrapper<Parameter>& vol_, const Wrapper<Parameter>& interestr_);
	std::vector<std::vector<double>> GetResult();
	void RunEngine();

private:
	VanillaOption theOption;
	Wrapper<RandomBase> randomGen;
	Wrapper<StatGatherer> stats;
	Wrapper<Parameter> interestr;
	double Spot;
	unsigned long iter;
	Wrapper<Parameter> vol;
};


#endif