#include<iostream>
#include<fstream>
#include "Eigen/Dense"
#include "Eigen/Eigenvalues" 
#include "input.hpp"
#include<vector>
#include <assert.h>

using namespace Eigen;
using namespace std;

int main(int argc, char const *argv[])
{
    int size = january.size();
    float janMean = 0;
    float juneMean = 0;
    float varianceX = 0;
    float varianceY = 0;
    float covariance = 0;
    
    for (int i = 0; i < size; i++)
    {
        janMean += january[i];
        juneMean += june[i];        //getting sum of values
    }

    janMean = janMean / size;
    juneMean = juneMean /size;      //getting mean values

    //cout << janMean << " Jan Mean - June Mean " << juneMean << "\n";

    for (int j = 0; j < size; j++)
    {
        january[j] = january[j] - janMean;
        june[j] = june[j] - juneMean;       //normalizing vectors
        
    }

    for (int k = 0; k < size; k++)
    {
        varianceX += january[k] * january[k];
        varianceY += june[k] * june[k];
        covariance += january[k] * june[k];     //calcuting variance and covariance
    }

    //cout << covariance << "\n";
    varianceX = varianceX / (size-1);
    varianceY = varianceY / (size-1);
    covariance = covariance / (size-1);

    MatrixXd m(2,2); //creating 2x2 matrix

    m << varianceX, covariance,
        covariance, varianceY;

    EigenSolver<MatrixXd> solver(m);
    MatrixXd eigenVectors = solver.eigenvectors().real();
    VectorXd eigenValues = solver.eigenvalues().real();
    float tVariance = varianceX + varianceY;
    float PC1 = (eigenValues[0]/tVariance) * 100;
    float PC2 = (eigenValues[1]/tVariance) * 100;
    ofstream o;
    o.open("output.txt");
    o << "The eigenValues are: \n" << eigenValues << "\n";
    o << "An EigenVector matrix is: \n" << eigenVectors << "\n";
    o << "The covariance matrix is: \n" << m << "\n";
    o << "The total variance is: \n" << (tVariance) << "\n";
    o << "The percentage variance of PC1 is: \n" << (PC1) << "%\n";
    o << "The percentage variance of PC2 is: \n" << (PC2) << "%\n";
    o.close();

    return 0;
}
