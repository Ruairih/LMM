#include "MCEngine.h"

MCEngine::MCEngine(const VanillaOption& theOption_, const Wrapper<RandomBase>& randomGen_,double Spot_, const Wrapper<StatGatherer>& stats_, unsigned long iter_, const Wrapper<Parameter>& vol_, const Wrapper<Parameter>& interestr_) : theOption(theOption_), randomGen(randomGen_), Spot(Spot_), stats(stats_), iter(iter_), vol(vol_), interestr(interestr_)
{
	
}

std::vector<std::vector<double> > MCEngine::GetResult()
{
	return stats->Extract();
}

void MCEngine::RunEngine()
{
	unsigned long i=0;
	MJArray VArray(1);

	while (i < iter)
	{
		randomGen->GetGaussians(VArray);
		double temp4 =  vol->Mean(1,2) * sqrt(theOption.GetExpiry()) * VArray[0];
		double temp3 = - .5 * vol->Mean(1,2) * theOption.GetExpiry();
		double temp2 = theOption.GetExpiry() * interestr->Mean(1,2);
		double temp1 = Spot* exp(theOption.GetExpiry() * interestr->Mean(1,2)  - .5 * vol->Mean(1,2) * vol->Mean(1,2)* theOption.GetExpiry() + vol->Mean(1,2) * sqrt(theOption.GetExpiry()) * VArray[0]);
//		stats->Inject(theOption.GetValue(Spot* exp(theOption.GetExpiry() * interestr->Mean(1,2)  - .5 * vol->Mean(1,2) * vol->Mean(1,2) * theOption.GetExpiry() + vol->Mean(1,2) * sqrt(theOption.GetExpiry()) * VArray[0])));
		i++;
	}
}
