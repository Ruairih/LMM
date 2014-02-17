#include "IncludeFile.h"


//using namespace std;

int main()
{
	double tmp, Spot=100.;
	RandomParkMiller generator(1);
	generator.ResetDimensionality(1);

	PayoffCall callTest(100), callTest2(100);
	PayoffForward forward;
	Wrapper<Payoff> wrappedCall(callTest), wrappedCall2(callTest2);
	//PayoffCall test2 = *wrappedCall;

	std::vector<double> pr;
	std::vector<double> pv;

	pr.push_back(.0001);
	pv.push_back(.1);
	ConstantParameter intpara(pr);
	ConstantParameter volpara(pv);

	std::vector<std::pair<double,double>> parametersr;
	std::vector<std::pair<double,double>> parametersv;
	
	parametersr.push_back( std::make_pair(.1,.000001));
	parametersr.push_back( std::make_pair(.2,.000001));	
	parametersr.push_back( std::make_pair(.3,.000001));
	parametersr.push_back( std::make_pair(.4,.000001));
	parametersr.push_back( std::make_pair(.5,.000001));
	parametersr.push_back( std::make_pair(.6,.000001));
	parametersr.push_back( std::make_pair(.8,.000001));
	parametersr.push_back( std::make_pair(.9,.000001));
	parametersr.push_back( std::make_pair(1.,.000001));

	parametersv.push_back(std::make_pair(0.1,.316227766));
	parametersv.push_back(std::make_pair(0.2,.316227766));
	parametersv.push_back(std::make_pair(0.3,.316227766));
	parametersv.push_back(std::make_pair(0.4,.316227766));
	parametersv.push_back(std::make_pair(0.5,.316227766));
	parametersv.push_back(std::make_pair(0.6,.316227766));
	parametersv.push_back(std::make_pair(0.7,.316227766));
	parametersv.push_back(std::make_pair(0.8,.316227766));
	parametersv.push_back(std::make_pair(0.9,.316227766));
	parametersv.push_back(std::make_pair(1.0,.316227766));

	OneDParameter interestrate(parametersr);
	OneDParameter volp(parametersv);
	//cout << interestrate.Mean(1,2);
	//cout << wrappedCall->operator()(110);
	wrappedCall = wrappedCall2;
	std::cout << "\n" << CallBS(intpara,volpara,1,100,100) << "\n";
	MeanStat collectMean;

	VanillaOption callOption(callTest,1.0);
	std::vector<double> DatesV;
	std::vector<double> DatesPay;
	DatesV.push_back(.1);
	DatesV.push_back(.3);
	DatesV.push_back(.5);
	DatesV.push_back(1.);
	DatesPay.push_back(1.);
	//DatesV.push_	double integral=0;back(.6);
	//DatesV.push_back(1.);

	
	PathDOption pathy(callTest,DatesV,DatesPay);
	AsianOption asian(forward,DatesV,DatesPay);
	//MCEngine MCRun(callOption, generator, Spot, collectMean, 10000000, volp,interestrate);
	//MCRun.RunEngine();

	FullPathMC MCRun(asian, generator, Spot, collectMean, 20000, volp,interestrate, 2);
	MCRun.RunEngine();
	
	auto outputMean = MCRun.GetResult();
	
	//auto something = *outputMean;
	//cout << "\n" << "Result:" << MCRun.GetResult();
	//auto another = something.Extract();
	//cout << "\n val = " << another[0][0];
	
	
	//float a_temp[] = {1.0, 1.0, -1.0, 1.0,0.,2.,-1.,2.,3.};
	//float a_temp[] = {1.0, 1.0, -1.0, 1.0};
	float a_temp[] = {1.0, 1.0, 1.0, 1.0,2.,2.,1.,2.,3.};
	int testsize = sizeof(a_temp)/sizeof(float);
	std::vector<double> eigenvalues;
	std::vector<double> PMatrix;


//	std::vector<double> samplet = corrlArray(&a_temp[0],3, eigenvalues);
	std::vector<double> samplet = corrlArray(a_temp,3, eigenvalues, PMatrix);
//	specD(&a_temp[0],3, eigenvalues);
//	std::vector<double> Ptranspose(a_temp, a_temp + sizeof(a_temp)/sizeof(float));
//	std::vector<double> Pvector = MatrixTranspose(Ptranspose);

/*	double eigenVMatrix1[3] = {eigenvalues[0],0,0};
	std::vector<double> DMatrix(eigenVMatrix1, eigenVMatrix1 + sizeof(eigenVMatrix1) / sizeof(double)); 
	double eigenVMatrix2[3] = {0,eigenvalues[1],0};
	std::vector<double> secondrow(eigenVMatrix2, eigenVMatrix2 + sizeof(eigenVMatrix2) / sizeof(double));
	double eigenVMatrix3[3] = {0,0,eigenvalues[2]};
	std::vector<double> thirdrow(eigenVMatrix3, eigenVMatrix3 + sizeof(eigenVMatrix3) / sizeof(double));
	
	DMatrix.insert(DMatrix.end(), secondrow.begin(), secondrow.end() );
	DMatrix.insert(DMatrix.end(), thirdrow.begin(), thirdrow.end() );
	std::vector<double> sampleV;
    sampleV = MatrixMult(DMatrix,DMatrix);

	std::vector<double> outputfirst = MatrixMult(DMatrix,Ptranspose);
	std::vector<double> outputifnal = MatrixMult(Pvector, outputfirst);
	*/

	int i=0;
	std::cout << "\n";
	std::vector<std::vector<double>>::iterator sampling;
	for(sampling=outputMean.begin();sampling!=outputMean.end();sampling++)
	{
		std::vector<double>::iterator test = sampling->begin();
		std::cout << *test << "\n";
		
	}

	std::cin >> tmp;

}