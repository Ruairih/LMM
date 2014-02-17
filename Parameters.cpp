#include "Parameters.h"
ConstantParameter::ConstantParameter(const std::vector<double> parameters_) : parameters(parameters_)
{

}

double ConstantParameter::DoIntegral(const double time1, const double time2) const
{
	return parameters[0]* (time2-time1);
}

double ConstantParameter::DoSquareIntegral(const double time1, const double time2) const
{
	return parameters[0]*parameters[0]* (time2-time1);
}

double ConstantParameter::Mean(const double time1, const double time2) const
{
	return parameters[0];
}

double ConstantParameter::RootMeanSquare(const double time1, const double time2) const
{
	return sqrt(parameters[0]*parameters[0]);
}

Parameter* ConstantParameter::clone() const
{
	return new ConstantParameter(*this);
}


OneDParameter::OneDParameter( std::vector< std::pair<double,double>> parameters_) : parameters(parameters_)
{

}

double OneDParameter::DoIntegral(const double time1, const double time2) const
{
	std::vector< std::pair<double,double>>::const_iterator tnow_itr;
	tnow_itr = parameters.begin();

	if((*tnow_itr).first <= time1){
		
		while((*tnow_itr).first <= time1)
		{
			tnow_itr++;
		}	

		tnow_itr--;
	}
	else
	{

	}


	double integral=0;

	if(time1 < parameters[0].first)
	{
		integral += parameters[0].second * parameters[0].second *( parameters[0].first - time1);
	}

	for(;tnow_itr!=parameters.end();tnow_itr++)
	{

		if(*(tnow_itr) != parameters.back())
		{
			if((*(tnow_itr+1)).first <= time2)
			{
			integral += (*tnow_itr).second * ( (*(tnow_itr+1)).first - ((*(tnow_itr)).first ));
			}
			else
			{
				if( ((*(tnow_itr)).first ) <= time2)
				{
					integral += (*tnow_itr).second * ( time2 - ((*(tnow_itr)).first ));
					break;
				}
				else
				{
					integral += (*tnow_itr).second * (*tnow_itr).second * ( time2 - time1 );
					break;
				}
			}
		}
		else
		{
			if( ((*(tnow_itr)).first ) <= time2)
			{
				integral += (*tnow_itr).second * ( time2 - ((*(tnow_itr)).first ));
				break;
			}
			else
			{
				integral += (*tnow_itr).second * (*tnow_itr).second * ( time2 - time1 );
				break;
			}
		}

	}
	return integral;

}

double OneDParameter::DoSquareIntegral(const double time1, const double time2) const
{
	std::vector< std::pair<double,double>>::const_iterator tnow_itr;
	tnow_itr = parameters.begin();


	if((*tnow_itr).first <= time1){
		
		while((*tnow_itr).first <= time1)
		{
			tnow_itr++;
		}	

		tnow_itr--;
	}
	else
	{

	}

	double integral=0;


	if(time1 < parameters[0].first)
	{
		integral += parameters[0].second * parameters[0].second *( parameters[0].first - time1);
	}



	for(;tnow_itr!=parameters.end();tnow_itr++)
	{

		if(*(tnow_itr) != parameters.back())
		{

			if((*(tnow_itr+1)).first <= time2)
			{
				integral += (*tnow_itr).second * (*tnow_itr).second * ( (*(tnow_itr+1)).first - ((*(tnow_itr)).first ));
			}
			else
			{
				if( ((*(tnow_itr)).first ) <= time2)
				{
					integral += (*tnow_itr).second * (*tnow_itr).second * ( time2 - ((*(tnow_itr)).first ));
					break;
				}
				else
				{
					integral += (*tnow_itr).second * (*tnow_itr).second * ( time2 - time1 );
					break;
				}

			}
		}
		else
		{
			if( ((*(tnow_itr)).first ) <= time2)
				{
					integral += (*tnow_itr).second * (*tnow_itr).second * ( time2 - ((*(tnow_itr)).first ));
					break;
				}
				else
				{
					integral += (*tnow_itr).second * (*tnow_itr).second * ( time2 - time1 );
					break;
				}
		}
	}
	return integral;

}

double OneDParameter::Mean(const double time1, const double time2) const
{
	return 0;//parameters[0];
}

double OneDParameter::RootMeanSquare(const double time1, const double time2) const
{
	return 0.;//sqrt(parameters[0]*parameters[0]);
}

Parameter* OneDParameter::clone() const
{
	return new OneDParameter(*this);
}