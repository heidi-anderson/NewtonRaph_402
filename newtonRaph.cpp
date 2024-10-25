#include <iostream>
#include <vector>
#include <cmath>
#include <functional>

using namespace std;

//vector<double> newtonRaphson(function<double(double)> gradient, function<double(double)> hessian, vector<double> X);
//
//vector<double> newtonRaphson(function<double(double)> gradient, function<double(double)> hessian, vector<double> X)
//{
//    int len = X.size();
//
//    int i;
//    int j;
//    int max_j = 1000; // can change this to be whatever 
//    double x;
//    double delta;
//    double tolerance = 1e-6; // same with this
//    vector<double> roots = X; // initial guesses
//
//    for (i = 0; i < len; ++i)
//    {
//        x = X[i];
//        j = 0;
//        while (j < max_j)
//        {
//            if (fabs(gradient(x)) < tolerance) // while absolute value of gradient is less than tolerance
//                break; // solution found within tolerance
//            if (hessian(x) == 0)
//                break; // cant divide by 0
//
//            delta = gradient(x) / hessian(x);
//
//            x = x - delta;
//
//            if (fabs(delta) < tolerance)
//                break; // if change is less than tolerance, stop
//
//            ++j;
//
//        }
//        
//        if (j == max_j)
//            cout << "Maximum iterations reached at X[" << i << "]" << endl;
//
//        roots[i] = x; // store computed root
//    }
//
//    return roots;
//}


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