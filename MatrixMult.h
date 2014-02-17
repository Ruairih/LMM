
#ifndef MATRIXMULT_H
#define MATRIXMULT_H

#include <vector>
#include "math.h"

template <class T>
std::vector<T> MatrixMult(std::vector<T> first, std::vector<T> second)
{
	std::vector<double> somevector;
	std::vector<double>::iterator vitr;
	std::vector<double>::iterator vitr2;
	auto sizeofMat = sqrt((double)(first.size()));
	//T somethinghere;

	std::vector<double> secondT = MatrixTranspose(second);

	for(int i = 0 ; i <(int) first.size(); i++ )
	{
		int x = i % (int)(sizeofMat);
		int y = i/sizeofMat;
		double tempa=0.;

		for(int j = 0 ; j < (int)sizeofMat; j++)
		{
			double pone = first[(int)(sizeofMat)*y + j];
			double ptwo = secondT[(int)(sizeofMat)*x + j];
			tempa += first[(int)(sizeofMat)*y + j] * secondT[(int)(sizeofMat)*x + j];
		}


		somevector.push_back(tempa);
	}

	return somevector;
}

template <class T>
std::vector<T> MatrixTranspose(std::vector<T> first)
{
	std::vector<double> somevector;
	auto sizeofMat = sqrt((double)(first.size()));
	//T somethinghere;

	for(int i = 0 ; i <(int) first.size(); i++ )
	{
		int x = i % (int)(sizeofMat);
		int y = i/sizeofMat;
		somevector.push_back(first[y + (int)(sizeofMat) * x] );
	}

	return somevector;
}

#endif


