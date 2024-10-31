#include <iostream>
#include <vector>
#include <cmath>
#include <functional>
#include <Eigen/Dense>

using namespace std;

vector<double(double)> newtonApprox(double beta, Eigen::MatrixXd gradient, Eigen::MatrixXd hessian, double tol)
{
    // double beta1;
    // double calc0, calc1;

    // calc0 = gradient(beta);
    // calc1 = hessian(beta);

    // if (tol >= fabs(gradient(beta)))
    // {
    //     return beta;
    // }
    
    // beta1 = beta - (calc0 / calc1);

    // return newtonApprox(beta1, gradient, hessian, tol);
}

Eigen::MatrixXd gradient(Eigen::MatrixXd X, Eigen::MatrixXd Y, Eigen::VectorXd B)
{

    Eigen::MatrixXd secondPart = (1.0 / (1.0 + (-X.transpose() * B).array().exp())).matrix();
    Eigen::MatrixXd result = Y - secondPart;

    return result;
}

Eigen::MatrixXd hessian(Eigen::MatrixXd X, Eigen::MatrixXd Y, Eigen::VectorXd B)
{
    Eigen::MatrixXd secondTerm = (1.0 / (1.0 + (-X.transpose() * B).array().exp())).matrix();   // 1/(1+e^XTB)
    Eigen::MatrixXd result = X.transpose() * (-secondTerm) * (-secondTerm) * X;
    return result;
}

int main()
{

    return 0;
}


// vector<double> gradient (inputs)
// {...}

//vector<double<double>> hessian ( inputs )
// vector<double> newt

// BLAS and EIGen

// copy data set over and over and see what happens to eigen values of hessian do it with just two of the X variables (x_1, x_2)