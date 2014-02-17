#ifndef SPECTRAL_H
#define SPECTRAL_H
#include "eigenv.h"
#include "Arrays.h"
#include "MatrixMult.h"

#include<vector>
void specD(float a_temp[], int n, std::vector<double>& eigenvectors);
std::vector<double> corrlArray(float a_temp[], int n, std::vector<double>& eigenvectors, std::vector<double>& PMatrix);


#endif