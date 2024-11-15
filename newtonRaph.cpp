#include <iostream>
#include <vector>
#include <cmath>
#include <Eigen/Dense>
#include <fstream>
#include <sstream>

using namespace std;
using namespace Eigen;

MatrixXd theGradient(MatrixXd X, VectorXd Y, VectorXd B);
MatrixXd theHessian(MatrixXd X, VectorXd Y, VectorXd B);
VectorXd newtonRaphson(VectorXd B, MatrixXd X, VectorXd Y, double tol);

VectorXd newtonRaphson(VectorXd B, MatrixXd X, VectorXd Y, double tol)
{
    MatrixXd gradient;
    MatrixXd hessian;
    MatrixXd betaValues;

    betaValues << B.transpose();

    while(gradient.norm() < tol)
    {
        gradient = theGradient(X, Y, B);
        hessian = theHessian(X, Y, B);


        VectorXd B = B - gradient * hessian.inverse(); // newton raphson step
        betaValues << B.transpose(); // putting the vector into a matrix

        if(B.norm() < tol) // if tolerance is larger than the norm of beta we're good... right?
            break;

    }
    
    return B;

}

MatrixXd theGradient(MatrixXd X, VectorXd Y, VectorXd B)
{
    VectorXd regressionLine = X.transpose() * B;
    ArrayXd probs = 1 / (1 + (-regressionLine).array().exp()); 
    MatrixXd result = Y = probs;

    return result;
}

MatrixXd theHessian(MatrixXd X, VectorXd Y, VectorXd B)
{
    VectorXd regressionLine = X.transpose()*B;
    ArrayXd probs = 1 / (1 + ( -regressionLine).array().exp() );
    VectorXd Dvec = probs * (1 - probs);
    MatrixXd D = Dvec.asDiagonal();
    MatrixXd result = X.transpose()*D*X;
    return result;
}

bool getData(const string& filename, MatrixXd& X, VectorXd& Y, VectorXd& B)
{
    ifstream file(filename);

    if(!file.is_open())
    {
        cout << "Couldn't open csv file" << endl;
        return false;
    }

    vector<vector<double>> rawData;
    string line;

    bool isHeader = true;
    while(getline(file, line))
    {
        if (isHeader)
        {
            isHeader = false; // skip the first row 
            continue;
        }
        stringstream lineStream(line);
        string cell;
        vector<double> row;

        while(getline(lineStream, cell, ','))
            row.push_back(stod(cell));
        rawData.push_back(row);
    }

    file.close();

    int rows = rawData.size();
    int cols = rawData[0].size();

    X.resize(rows - 1, cols);
    for(int i = 0; i < rows - 1; ++i)
    {
        for(int j = 0; j < cols; ++j)
        {
            X(i,j) = rawData[i][j];
        }
    }

    for(int k = 0; k < cols; ++k)
        Y(k) = rawData[rows - 1][k];
    Y.resize(rows - 1);

    for(int l = 0; l < cols; ++l)
        B(l) = l + 1;
    B.resize(cols);
    return true;
}

int main()
{
    MatrixXd X;
    VectorXd Y;
    VectorXd B;

    string filename = "SyntheticLRdata.csv";
    getData(filename, X, Y, B);
    newtonRaphson( B, X, Y, 0.1);

    return 0;
}