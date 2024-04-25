#pragma once
#include <iostream>
#include <vector>
#include <QTextStream>

using namespace std;

class matrix{
    vector<vector<double>> _elements;
    int _m, _n;

    matrix okaimlennya(int &comp);
    matrix schulz(int &comp);
public:
    matrix(int m,int n, double **mat);
    matrix(int m, int n, QVector<QVector<double>> vec);
    matrix(matrix& mat);
    matrix(int m,int n);

    matrix& randomise();

    int get_m();

    vector<double>& operator[](int index) ;

    friend std::ostream& operator<<(std::ostream& out, const matrix &mat);
    friend QTextStream &operator<<(QTextStream &stream, const matrix &mx);

    matrix operator*( matrix other);
    friend matrix operator*(const double& num, matrix& mat);
    friend matrix operator*(matrix& mat, const double& num);
    matrix operator/(const double& num);
    matrix operator+(const matrix& other);
    matrix operator-(const matrix& other);

    friend double det(matrix matrix_);
    friend double gause_det(matrix matrix_);
    matrix get_transpose();
    double get_square_sqrt_sum();

    matrix reverse(QString method, int &comp);
};
