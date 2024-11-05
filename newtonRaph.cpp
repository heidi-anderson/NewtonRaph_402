#include <iostream>
#include <vector>
#include <cmath>
#include <Eigen/Dense>

using namespace std;
using namespace Eigen;

MatrixXd theGradient(MatrixXd X, MatrixXd Y, VectorXd B);
MatrixXd theHessian(MatrixXd X, MatrixXd Y, VectorXd B);
VectorXd newtonRaphson(VectorXd B, MatrixXd X, MatrixXd Y, double tol);

VectorXd newtonRaphson(VectorXd B, MatrixXd X, MatrixXd Y, double tol)
{
    MatrixXd gradient;
    MatrixXd hessian;
    MatrixXd betaValues;

    betaValues << B.transpose();

    while(gradient.norm() < tol)
    {
        gradient = theGradient(X, Y, B);
        hessian = theHessian(X, Y, B);


        VectorXd B_new = B - gradient * hessian.inverse(); // newton raphson step
        betaValues << B_new.transpose(); // putting the vector into a matrix

        B = B_new;

        if(B.norm() < tol) // if tolerance is larger than the norm of beta we're good... right?
            break;

    }


    return B;

}

MatrixXd theGradient(MatrixXd X, MatrixXd Y, VectorXd B)
{
    VectorXd regressionLine = X.transpose() * B;
    ArrayXd probs = 1 / (1 + (-regressionLine).array().exp()); 
    MatrixXd result = Y = probs;

    return result;
}

MatrixXd theHessian(MatrixXd X, MatrixXd Y, VectorXd B)
{
    VectorXd regressionLine = X.transpose()*B;
    ArrayXd probs = 1 / (1 + ( -regressionLine).array().exp() );
    VectorXd Dvec = probs * (1 - probs);
    MatrixXd D = Dvec.asDiagonal();
    MatrixXd result = X.transpose()*D*X;
    return result;
}

int main()
{
    // :D

    return 0;
}