#ifndef MODNUM_INCLUDE_MATRIX_H
#define MODNUM_INCLUDE_MATRIX_H

#include <vector>


typedef long long ll;
using namespace std;
class Matrix
{

private:
    vector< vector<ll> > item;       //以vector的形式存储元素
    int rowNum;        //矩阵行数
    int colNum;        //矩阵列数
    ll p;           //求mod的p

public:
    Matrix()= default;
    Matrix(int n,ll p);
    Matrix(int m, int n, ll p);
    Matrix(const Matrix & /*M*/);
    Matrix(ll* items, int m, int n,ll p);
    ~Matrix()= default;
    int getRowNum() const;
    int getColNum() const;
    ll getP() const;
    Matrix Trans() const;
    ll getItem(int i, int j) const;
    void setItem(int i, int j, ll value);

    Matrix Inverse();
    ll det();
    Matrix left(int i,int j);           //去除一行一列后的矩阵
    Matrix adj();                       //伴随矩阵
    void reinit(int m,int n,ll p);

    Matrix operator +(const Matrix &m);
    Matrix operator -(const Matrix &m);
    Matrix operator * (const Matrix &m);
    Matrix operator *(const ll f);
    Matrix& operator=(const Matrix& m);
    friend ostream& operator <<(ostream &os, const Matrix &m);

};

#endif
