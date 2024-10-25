#include <iostream>
#include <vector>
#include <cmath>
#include <functional>
#include <cblas.h>

using namespace std;

double newtonApprox(double beta, function <double(double)> gradient, function <double(double)> hessian, double tol)
{
    double beta1;
    double calc0, calc1;

    calc0 = gradient(beta);
    calc1 = hessian(beta);

    if (tol >= fabs(gradient(beta)))
    {
        return beta;
    }
    
    beta1 = beta - (calc0 / calc1);

    return newtonApprox(beta1, gradient, hessian, tol);
}

double f(double x)
{
    int n; 
    int p;
    return pow(x, 3) + 2;
}

double fp(double x)
{
    return 3 * pow(x, 2);
}

int main()
{

    double ep = 0.001;
    double n = 2;
    double ans;

    ans = newtonApprox(n, f, fp, ep);
    cout << ans << endl;
    return 0;
}


// vector<double> gradient (inputs)
// {...}

//vector<double<double>> hessian ( inputs )
// vector<double> newt

// BLAS and EIGen

// copy data set over and over and see what happens to eigen values of hessian do it with just two of the X variables (x_1, x_2)