#include "Spectral.h"
#include<iostream>

void specD(float a_temp[], int n, std::vector<double>& eigenvectors, std::vector<double>& PMatrix)
{
	float **v = matrix(1,n,1,n);
	int rot;
	float *d = vector(1,n);
	float **a = convert_matrix(&a_temp[0],1,n,1,n);

	printf("Matrix:\n");
    for (int i1 = 1; i1 <= n; i1++) {
        for (int j1 = 1; j1 <= n; j1++) {
            printf("  %+13.6e", a[i1][j1]);
        }
        printf("\n");
    }
    printf("\n");

	jacobi(a,n,d,v,&rot);
	


	/*printf("Eigenvectors:\n");
    for (int i1 = 1; i1 <= n; i1++) {
        for (int j1 = 1; j1 <= n; j1++) {
            printf("  %+13.6e", v[j1][i1]);
			a_temp[i1+n*(j1-1) -1] = v[j1][i1];
        }
        printf("\n");
    }*/



	// Original way
		printf("Eigenvectors:\n");
    for (int i1 = 1; i1 <= n; i1++) {
        for (int j1 = 1; j1 <= n; j1++) {
            printf("  %+13.6e", v[j1][i1]);
			a_temp[j1+n*(i1-1) -1] = v[j1][i1];
			PMatrix.push_back(v[j1][i1]);
        }
        printf("\n");
    }
	
	//   why is this here? 
	/*for (int i1 = 1; i1 <= n; i1++) {
        for (int j1 = 1; j1 <= n; j1++) {
            printf("i %d j %d  %+13.6e", j1,i1,a_temp[j1+n*(i1-1) -1]);
			a_temp[j1+n*(i1-1) -1] = a[i1][j1];
        }
        printf("\n");
    }*/
	

	printf("Eigenvalues:\n");
    for (int i1 = 1; i1 <= n; i1++) {
        printf("  Number %d:%+14.6e\n", i1, d[i1]);
		eigenvectors.push_back(d[i1]);
    }
    printf("\n");
	
	free_convert_matrix(a, 1, n, 1, n);
    free_matrix(v, 1, n, 1, n);
    free_vector(d, 1, n);

}

std::vector<double> corrlArray(float a_temp[], int n, std::vector<double>& eigenvectors, std::vector<double>& PMatrix)
{
	specD(&a_temp[0],n, eigenvectors, PMatrix);
	//std::vector<double> Ptranspose(a_temp, a_temp + sizeof(a_temp)/sizeof(float));
	//std::vector<double> Pvector = MatrixTranspose(Ptranspose);
	std::vector<double> Pvector = MatrixTranspose(PMatrix);
	std::vector<double> eigenVMatrix(n*n);

	for(int i = 0 ; i < n * n ; i++)
	{
		eigenVMatrix[i]=0.;
	}

	for(int i = 0; i < n; i++)
	{
		eigenVMatrix[i*n+i] = sqrt(eigenvectors[i]);
	}

	//double eigenVMatrix1[3] = {eigenvectors[0],0,0};
	//std::vector<double> DMatrix(eigenVMatrix1, eigenVMatrix1 + sizeof(eigenVMatrix1) / sizeof(double)); 
	//double eigenVMatrix2[3] = {0,eigenvectors[1],0};
	//std::vector<double> secondrow(eigenVMatrix2, eigenVMatrix2 + sizeof(eigenVMatrix2) / sizeof(double));
	//double eigenVMatrix3[3] = {0,0,eigenvectors[2]};
	//std::vector<double> thirdrow(eigenVMatrix3, eigenVMatrix3 + sizeof(eigenVMatrix3) / sizeof(double));
	
	//DMatrix.insert(DMatrix.end(), secondrow.begin(), secondrow.end() );
	//DMatrix.insert(DMatrix.end(), thirdrow.begin(), thirdrow.end() );



	return MatrixMult(Pvector, eigenVMatrix);

}