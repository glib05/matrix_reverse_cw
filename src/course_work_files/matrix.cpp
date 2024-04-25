#include <cstdlib>
#include <ctime>
#include <string>
#include <iostream>
#include <vector>
#include "matrix.h"
#include <math.h>
#include <QString>
#include <QVector>

using namespace std;


matrix::matrix(int m,int n,double **mat){
    _m = m;
    _n = n;
    for (int i = 0; i < _m; i++){
        vector<double> line;
        for (int j = 0; j < _n; j++)
            line.insert(line.end(), mat[i][j]);
        _elements.insert(_elements.end(), line);
    }
}

matrix::matrix(matrix& mat) {
    _m = mat._m;
    _n = mat._n;
    for (int i = 0; i < _m; i++){
        vector<double> line;
        for (int j = 0; j < _n; j++)
            line.insert(line.end(), mat[i][j]);
        _elements.insert(_elements.end(), line);
    }
}

matrix::matrix(int m, int n) {
    _m = m;
    _n = n;
    for (int i = 0; i < _m; i++){
        vector<double> line;
        for (int j = 0; j < _n; j++)
            line.insert(line.end(), 0);
        _elements.insert(_elements.end(), line);
    }
}

matrix::matrix(int m, int n, QVector<QVector<double>> vec){
    _m = m;
    _n = n;
    for (int i = 0; i < _m; i++){
        vector<double> line;
        for (int j = 0; j < _n; j++)
            line.insert(line.end(), vec[i][j]);
        _elements.insert(_elements.end(), line);
    }
}

matrix& matrix::randomise() {

    for (int i = 0; i <_m; i++)
        for(int j = 0; j < _n; j++)
            _elements[i][j] = (rand()/100.0  - rand()/200.0);
    return *this;
}

int matrix::get_m(){
    return _m;
}

std::ostream& operator<<(std::ostream& out, const matrix &mat){
    for (int i = 0; i<mat._m; i++){
        for (int j = 0; j < mat._n; j++){
            out<<mat._elements[i][j]<<" ";
        }
        out<<"\n";
    }
    return out;
}

QTextStream &operator<<(QTextStream &stream, const matrix &mx) {
    int columnWidth = 11; // Ширина стовпця
    QString horizontalLine = QString("-").repeated(mx._m * columnWidth + mx._m + 1); // Горизонтальна лінія

    for (int i = 0; i < mx._m; i++) {
        stream << horizontalLine << '\n';
        for (int j = 0; j < mx._m; j++) {
            stream << "|" << QString("%1").arg(mx._elements[i][j], columnWidth, ' ');
        }
        stream << "|" << '\n';
    }
    stream << horizontalLine << '\n';
    return stream;
}

vector<double>& matrix::operator[](int index){
    return _elements[index];
}

matrix matrix::operator*(matrix other) {
    if (_n != other._m)
        return matrix(0, 0);

    matrix result(_m, other._n);

    for (int i = 0; i<result._m; i++){
        for (int j =0; j<result._n; j++){
            result[i][j] = 0;
            for (int k = 0; k <_n; k++)
                result[i][j] += (*this)[i][k]*other[k][j];
        }
    }

    return result;
}

matrix operator*(const double &num,  matrix &mat) {
    matrix result(mat._m, mat._n);

    for (int i = 0; i<mat._m; i++)
        for (int j = 0; j < mat._n; j++)
            result[i][j] = num*mat._elements[i][j];

    return result;
}

matrix operator*( matrix &mat, const double &num) {
    matrix result(mat._m, mat._n);

    for (int i = 0; i<mat._m; i++)
        for (int j = 0; j < mat._n; j++)
            result[i][j] = num*mat._elements[i][j];

    return result;
}

matrix matrix::operator/(const double &num) {
    matrix result(_m, _n);

    for (int i = 0; i<_m; i++)
        for (int j = 0; j < _n; j++)
            result[i][j] = _elements[i][j]/num;

    return result;
}

matrix matrix::operator+(const matrix &other) {

    if ((_m != other._m) or (_n != other._n))
        return matrix(0, 0);;

    matrix result(_m,_n);
    for (int i =0; i<_m; i++)
        for (int j = 0; j<_n; j++)
            result[i][j] = (*this)[i][j]+other._elements[i][j];

    return result;
}

matrix matrix::operator-(const matrix &other) {

    if ((_m != other._m) or (_n != other._n))
        return matrix(0, 0);;

    matrix result(_m,_n);
    for (int i =0; i<_m; i++)
        for (int j = 0; j<_n; j++)
            result[i][j] = (*this)[i][j]-other._elements[i][j];

    return result;
}

double det(matrix matrix_){
    double determinant = 0;

    matrix submatrix(matrix_._m-1, matrix_._n-1);
    if (matrix_._m == 1)
        return matrix_[0][0];
    if (matrix_._m == 2)
        return ((matrix_[0][0] * matrix_[1][1]) - (matrix_[1][0] * matrix_[0][1]));
    else {
        for (int x = 0; x < matrix_._m; x++) {
            int subi = 0;
            for (int i = 1; i < matrix_._m; i++) {
                int subj = 0;
                for (int j = 0; j < matrix_._m; j++) {
                    if (j == x)
                        continue;
                    submatrix[subi][subj] = matrix_[i][j];
                    subj++;
                }
                subi++;
            }
            determinant = determinant + (pow(-1, x) * matrix_[0][x] * det(submatrix));
        }
    }
    return determinant;
}

double gause_det(matrix matrix_) {
    double determinant = 1;
    matrix copy_matrix = matrix_;

    for (int i = 0; i < matrix_._m; ++i){
        for (int j = i+1; j < matrix_._m; ++j){
            double store = copy_matrix[j][i];
            for (int k = i; k < matrix_._n; ++k) {
                copy_matrix[j][k] -= (copy_matrix[i][k]*store)/copy_matrix[i][i];
            }
        }
        determinant *= copy_matrix[i][i];
    }

    return determinant;
}

matrix matrix::get_transpose() {
    matrix result(_n,_m);
    for (int i =0; i<_m; i++)
        for (int j = 0; j<_n; j++)
            result[j][i] = (*this)[i][j];
    return result;
}

double matrix::get_square_sqrt_sum() {
    double suma = 0;
    for (int i = 0; i <_m; i++)
        for (int j = 0; j <_n; j++)
            suma += (*this)[i][j]*(*this)[i][j];
    return sqrt(suma);
}

matrix matrix::okaimlennya(int &comp) {
    comp++;
    if (_n != _m)
        return matrix(0, 0);

    if (_n == 1){
        matrix reversed(1, 1);
        reversed[0][0] = 1 / (*this)[0][0];
        return reversed;
    }

    matrix prev(_m-1, _n-1);
    for (int i = 0; i<_m-1; i++)
        for (int j = 0; j<_n-1; j++) {
            double d = (*this)[i][j];
            prev[i][j] = d;
            comp++;
        }

    matrix prev_reversed(_m - 1, _n - 1);
    prev_reversed = prev.okaimlennya(comp);

    matrix v(1, _n-1);
    for (int i = 0; i<_n-1; i++) {
        v[0][i] = (*this)[_m - 1][i];
        comp++;
    }

    matrix u(_m-1, 1);
    for (int i = 0; i<_n-1; i++) {
        u[i][0] = (*this)[i][_n - 1];
        comp++;
    }

    double a = (*this)[_m-1][_n-1] - (v * prev_reversed * u)[0][0];
    comp+=_m*_m*_m;

    matrix r = (-1/a) * prev_reversed * u;
    matrix q = (-1/a) * v * prev_reversed;
    matrix b = prev_reversed - (prev_reversed * u) *  q;
    comp+=4*_m*_m*_m;

    matrix reversed(_m, _n);

    for (int i = 0 ; i <_m-1; i++) {
        reversed[_m-1][i] = q[0][i];
        reversed[i][_m-1] = r[i][0];
        for (int j = 0; j < _n - 1; j++) {
            reversed[i][j] = b[i][j];
            comp++;
        }
    }
    reversed[_m-1][ _n-1] = 1/a;

    return reversed;
}

matrix matrix::schulz(int &comp) {

    const double epsilon = 1e-9;

    if (_m!=_n)
        return matrix(0,0);

    matrix ct = this->get_transpose();
    comp+=_m*_m;
    matrix c1 = (*this) * ct;
    comp+=_m*_m*_m;

    double strange_suma = c1.get_square_sqrt_sum();
    comp+=_m*_m;

    matrix reversed = ct / strange_suma;
    comp+=_m*_m;

    matrix E(_m,_n);
    for (int i = 0; i < _m; i++)
        E[i][i] = 1;
    comp += _m;

    matrix psi = E - (*this)*reversed;
    comp+=_m*_m*_m;

    while (strange_suma > epsilon){
        strange_suma = psi.get_square_sqrt_sum();
        comp+=_m*_m;

        reversed = (reversed)*(E+psi);
        comp+=_m*_m*_m;

        psi = E - ((*this)*reversed);
        comp+=_m*_m*_m;

        comp++;
    }

    return reversed;
}

matrix matrix::reverse(QString method, int &comp) {
    if (method == "schulz")
        return this->schulz(comp);
    else if (method == "okaimlennya")
        return this->okaimlennya(comp);
    else
        return *this;
}








