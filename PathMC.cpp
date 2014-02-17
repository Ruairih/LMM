#include "PathMC.h"



PathMC::PathMC(const AsianOption& theOption_, const Wrapper<RandomBase>& randomGen_, double Spot_, const Wrapper<StatGatherer>& stats_, unsigned long iter_, const Wrapper<Parameter>& vol_, const Wrapper<Parameter>& interestr_, int divisions_) : theOption(theOption_), randomGen(randomGen_), Spot(Spot_), stats(stats_), iter(iter_), vol(vol_), interestr(interestr_), divisions(((theOption.GetDates()).size())), Dates(theOption.GetDates())
{
	stats->ResizeSum( theOption.GetSizePaymentDates() );
}

std::vector<std::vector<double> > PathMC::GetResult()
{
	return stats->Extract();
}

void PathMC::RunEngine()
{
	unsigned long i=0;
	MJArray VArray(divisions);
	randomGen->ResetDimensionality(VArray.size());
	onePath.resize(VArray.size());

	while (i < iter)
	{
		//Recalcualting the parameters each iteration, fix this!
		randomGen->GetGaussians(VArray);

		double drift1 = interestr->DoIntegral(0,Dates.front());
		double vol1 = vol->DoSquareIntegral(0,Dates.front());
		onePath[0].second = (Spot * exp(drift1 * Dates[0] - .5 * vol1 * vol1 * Dates[0] + vol1 * sqrt(Dates[0]) * VArray[0]));
		onePath[0].first = Dates[0];

		for(Dates_itr = Dates.begin()+1; Dates_itr != Dates.end(); Dates_itr++)
		{
			int index = Dates_itr - Dates.begin();
			double drift = interestr->DoIntegral(Dates[index-1],Dates[index]);
			double insvol = vol->DoSquareIntegral(Dates[index-1],Dates[index]);
			double test = *Dates_itr - *(Dates_itr-1);
			double test2 = drift * (*Dates_itr - *(Dates_itr-1)) -.5 * insvol * insvol * (*Dates_itr - *(Dates_itr-1));
			double test3 = insvol * sqrt( (*Dates_itr - *(Dates_itr-1) ));
			double test4 = VArray[index];
			onePath[index].second = (onePath[index-1].second * exp(drift * (*Dates_itr - *(Dates_itr-1)) -.5 * insvol * insvol * (*Dates_itr - *(Dates_itr-1)) + insvol * sqrt( (*Dates_itr - *(Dates_itr-1) )) * VArray[index])); 
			onePath[index].first = *Dates_itr;
			double randout1 =  VArray[0];
			double randout2 =  VArray[1];
			double randout3 =  VArray[2];
			double randout4 =  VArray[3];

		}

		stats->Inject( (theOption.GetValue(onePath, Dates)) );
		//stats->Inject(onePath[1]);
		i++;
	}
	
	MakeDiscountFactors();
	
	std::vector<std::vector<double>> undiscountedResults = stats->Extract();
	std::vector<std::pair<double,double>> discountedCashFlows;
	std::vector<std::pair <double,double>> discountedCashFlows2(discountFactors.size());
	std::transform(discountFactors.begin(), discountFactors.end(), undiscountedResults.begin(),std::back_inserter(discountedCashFlows), [] (std::pair<double,double>p, std::vector<double> e){ return std::make_pair(p.first,e[0] * p.second);});
//	std::transform(discountFactors.begin(), discountFactors.end(), (stats->Extract()).begin(), (discountedCashFlows.begin()).second, std::multiplies<double>());
	
}

void PathMC::MakeDiscountFactors()
{
	if(*Dates.begin() < 0.00001 && *Dates.begin() > -.00001)
		discountFactors.push_back(std::pair<double,double>(0., 1.));

	for(Dates_itr=Dates.begin(); Dates_itr!=Dates.end()-1;Dates_itr++)
	{
		double rate = 1;
		rate *= exp(-interestr->DoIntegral(*Dates_itr,*(Dates_itr+1)));

		discountFactors.push_back(std::pair<double,double>(*(Dates_itr+1), rate));
	}
	
}


/**********************************************************************************************************************/



FullPathMC::FullPathMC(const AsianOption& theOption_, const Wrapper<RandomBase>& randomGen_, double Spot_, const Wrapper<StatGatherer>& stats_, unsigned long iter_, const Wrapper<Parameter>& vol_, const Wrapper<Parameter>& interestr_, int divisions_) : theOption(theOption_), randomGen(randomGen_), Spot(Spot_), stats(stats_), iter(iter_), vol(vol_), interestr(interestr_), divisions(((theOption.GetDates()).size())), Dates(theOption.GetDates())
{
	stats->ResizeSum( theOption.GetSizePaymentDates() );
}

std::vector<std::vector<double> > FullPathMC::GetResult()
{
	return stats->Extract();
}

void FullPathMC::RunEngine()
{
	unsigned long i=0;
	MJArray VArray(divisions), UArray(divisions);
	randomGen->ResetDimensionality(VArray.size());
	randomGen->ResetDimensionality(UArray.size());
	onePath.resize(VArray.size());
	MakeCovarianceMatrix(Dates,Dates.size());





	while (i < iter)
	{
		//Recalcualting the parameters each iteration, fix this!
		randomGen->GetGaussians(VArray);
		

		double drift1 = interestr->DoIntegral(0,Dates.front());
		double vol1 = vol->DoSquareIntegral(0,Dates.front());

		for(int p=0; p < divisions; p++)
		{
			UArray[p]=0.;
		}

	//	std::cout<<"\n";
		for(int z =0 ; z< divisions * divisions; z++)
		{
	//		std::cout << "   " << a_cov[z];
		}
	//	std::cout<<"\n";

		for(int j =0 ; j < divisions; j++)
		{
			UArray[0] += a_cov[j] * VArray[j];
		//	std::cout << VArray[j] << " ";
		}
		//std::cout << UArray[0];
		onePath[0].second = (Spot * exp(drift1 * Dates[0] - .5 * vol1 * vol1 * Dates[0] + vol1 * sqrt(Dates[0]) * UArray[0]));
		onePath[0].first = Dates[0];

		for(Dates_itr = Dates.begin()+1; Dates_itr != Dates.end(); Dates_itr++)
		{
			int index = Dates_itr - Dates.begin();
			for(int k =0; k < divisions; k++)
			{	
				UArray[index] += a_cov[divisions*index + k] * VArray[k];
	//			std::cout << a_cov[divisions*index + k] << " " << VArray[k] << "\n";
			}

			double drift = interestr->DoIntegral(0,Dates[index]);
			double insvol = vol->DoSquareIntegral(0,Dates[index]);
			double test = *Dates_itr - *(Dates_itr-1);
			double test2 = drift * (*Dates_itr - *(Dates_itr-1)) -.5 * insvol * insvol * (*Dates_itr - *(Dates_itr-1));
			double test3 = insvol * sqrt( (*Dates_itr - *(Dates_itr-1) ));
			double test4 = UArray[index];
			onePath[index].second = (Spot * exp(drift * (*Dates_itr) -.5 * insvol * insvol * (*Dates_itr ) + insvol * sqrt( (*Dates_itr)) * UArray[index])); 
			onePath[index].first = *Dates_itr;
			double randout1 =  VArray[0];
			double randout2 =  VArray[1];
			double randout3 =  VArray[2];
			double randout4 =  VArray[3];

		}

		stats->Inject( (theOption.GetValue(onePath, Dates)) );
		//stats->Inject(onePath[1]);
		i++;
	}
	
	MakeDiscountFactors();
	
	std::vector<std::vector<double>> undiscountedResults = stats->Extract();
	std::vector<std::pair<double,double>> discountedCashFlows;
	std::vector<std::pair <double,double>> discountedCashFlows2(discountFactors.size());
	std::transform(discountFactors.begin(), discountFactors.end(), undiscountedResults.begin(),std::back_inserter(discountedCashFlows), [] (std::pair<double,double>p, std::vector<double> e){ return std::make_pair(p.first,e[0] * p.second);});
//	std::transform(discountFactors.begin(), discountFactors.end(), (stats->Extract()).begin(), (discountedCashFlows.begin()).second, std::multiplies<double>());
	
}

void FullPathMC::MakeDiscountFactors()
{
	if(*Dates.begin() < 0.00001 && *Dates.begin() > -.00001)
		discountFactors.push_back(std::pair<double,double>(0., 1.));

	for(Dates_itr=Dates.begin(); Dates_itr!=Dates.end()-1;Dates_itr++)
	{
		double rate = 1;
		rate *= exp(-interestr->DoIntegral(*Dates_itr,*(Dates_itr+1)));

		discountFactors.push_back(std::pair<double,double>(*(Dates_itr+1), rate));
	}
	
}

void FullPathMC::MakeCovarianceMatrix(std::vector<double> Dates, int rank)
{
	
a_cov = new float [rank*rank];

	int index;
	for(Dates_itr = Dates.begin(), index =0; Dates_itr != Dates.end(); Dates_itr++)
	{
		for(Dates_itr2 = Dates.begin(); Dates_itr2 != Dates.end(); Dates_itr2++, index++)
		{
		a_cov[index] = std::min(*Dates_itr, *Dates_itr2);
//		std::cout <<"index : " <<index << "  " << *(a_cov + index) << " ";
		}
	}
}

FullPathMC::~FullPathMC()
{

	//note: should this have some [] type form?
	delete [] a_cov;
}