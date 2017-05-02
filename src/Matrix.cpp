#include "../include/Matrix.h"
#include "../include/Utils.h"
#include <iostream>
#include <cmath>

ll Matrix::getP() const {
    return p;
}

void Matrix::reinit(int m,int n,ll p) {
    rowNum=m;
    colNum=n;
    this->p=p;
    item.resize(m);
    for (int i = 0; i < rowNum; ++i) {
        item[i].resize(n);
        for (int j = 0; j < colNum; ++j) {
            item[i][j]=0;
        }
    }

}

Matrix Matrix::adj() {
    Matrix tmp(rowNum,p);

    for (int i = 0; i <rowNum ; ++i) {
        for (int j = 0; j <colNum ; ++j) {
            tmp.setItem(i, j, (ll) (pow(-1, i + j) * left(i, j).det()));
        }
    }

    return tmp.Trans();
}


Matrix::Matrix(int n,ll p)
{

    rowNum=n;
    colNum=n;
    this->p=p;
    item.resize(n);
    for (int i = 0; i < n; ++i) {
        item[i].resize(n);
        for (int j = 0; j < n; ++j) {
            if(i==j){
                item[i][j]=1;
            } else{
                item[i][j]=0;
            }
        }
    }

}

Matrix Matrix::left(int i,int j){
    Matrix tmp(rowNum-1,p);
    for(int k=0;k<rowNum-1;++k){
        for (int l = 0; l <colNum-1 ; ++l) {
            if(k<i&&l<j){
                tmp.setItem(k,l,getItem(k,l));
            } else if(k<i&&l>=j){
                tmp.setItem(k,l,getItem(k,l+1));
            } else if(k>=i&&l<j){
                tmp.setItem(k,l,getItem(k+1,l));
            } else{
                tmp.setItem(k,l,getItem(k+1,l+1));
            }
        }
    }

    return tmp;
}
Matrix::Matrix(ll* items, int m, int n,ll p)
{
    rowNum=m;
    colNum=n;
    this->p=p;

    item.resize(rowNum);
    for (int i = 0; i < rowNum; ++i) {
        item[i].resize(colNum);
        for (int j = 0; j < colNum; ++j) {
            item[i][j]=items[i*colNum+j]%p;
        }
    }
}

Matrix::Matrix(const Matrix &M)
{
    colNum = M.getColNum();
    rowNum = M.getRowNum();
    this->p = M.p;
    item.resize(rowNum);
    for (int i = 0; i < rowNum; ++i) {
        item[i].resize(colNum);
        for (int j = 0; j <colNum ; ++j) {
            item[i][j]=M.getItem(i,j);
        }
    }
}

Matrix& Matrix::operator=(const Matrix & M)
{
    colNum = M.getColNum();
    rowNum = M.getRowNum();
    p=M.p;

    item.resize(rowNum);
    for (int i = 0; i < rowNum; ++i) {
        item[i].resize(colNum);
        for (int j = 0; j < colNum; ++j) {
            setItem(i,j,getItem(i,j));
        }
    }

    return *this;

}


ll Matrix::getItem(int i, int j) const
{
    return item[i][j];
}
void Matrix::setItem(int i, int j, ll value)
{

    item[i][j] = value%this->p;//如果大于p,会自动转换
}

Matrix Matrix::Trans() const
{
    Matrix tmp = *this;
    tmp.rowNum = this->colNum;
    tmp.colNum = this->rowNum;
    for (int i = 0; i < tmp.rowNum; i++)
    {
        for (int j = 0; j < tmp.colNum; j++)
        {
            tmp.setItem(i, j, getItem(j, i));
        }
    }
    return tmp;
}

int Matrix::getRowNum() const
{
    return rowNum;
}

int Matrix::getColNum() const
{
    return colNum;
}

ostream& operator <<(ostream &os, const Matrix &m)
{
    for (int i = 0; i < m.getRowNum(); i++)
    {
        for (int j = 0; j < m.getColNum(); j++)
            os << m.getItem(i, j) << " ";
        os << "\n";
    }
    os.flush();
    return os;
}

Matrix Matrix::operator +(const Matrix &m)
{
    if (m.getColNum() != colNum || m.getRowNum() != rowNum) return *this;
    Matrix tmp = *this;
    for (int i = 0; i < rowNum; i++)
    {
        for (int j = 0; j < colNum; j++)
        {
            tmp.setItem(i, j, (getItem(i, j) + m.getItem(i, j))%tmp.p);
        }
    }
    return tmp;
}

Matrix Matrix::operator -(const Matrix &m)
{
    if (m.getColNum() != colNum || m.getRowNum() != rowNum) return *this;
    Matrix tmp = *this;
    for (int i = 0; i < rowNum; i++)
    {
        for (int j = 0; j < colNum; j++)
        {
            tmp.setItem(i, j, (getItem(i, j) - m.getItem(i, j))%tmp.p);
        }
    }
    return tmp;
}

Matrix Matrix::operator *(const ll f)
{
    Matrix tmp(rowNum,p);
    for (int i = 0; i < rowNum; i++)
    {
        for (int j = 0; j < colNum; j++)
        {
            tmp.setItem(i, j, getItem(i, j)*f%tmp.p);
        }
    }
    return tmp;
}

Matrix Matrix::operator *(const Matrix &m)
{

    if (colNum != m.getRowNum()||p!=m.p)
    {
        cout << "can not multiply.";
        return *this;
    }

    Matrix tmp(rowNum,m.getColNum(),p);

    for (int i = 0; i <tmp.rowNum ; ++i) {
        for (int j = 0; j <tmp.colNum ; ++j) {
            ll sum = 0;
            for (int k = 0; k < m.getRowNum(); ++k) {
                sum+=getItem(i,k)*m.getItem(k,j)%p;
            }
            while (sum<0){
                sum+=p;
            }
            tmp.setItem(i,j,sum);
        }
    }
    return tmp;

}

Matrix::Matrix(int m, int n, ll p){
    rowNum=m;
    colNum=n;
    this->p=p;
    item.resize(rowNum);
    for (int i = 0; i < rowNum; ++i) {
        item[i].resize(colNum);
        for (int j = 0; j < colNum; ++j) {
            item[i][j]=0;
        }
    }
}


ll Matrix::det()
{
    if(colNum!=rowNum){

        return 0;
    } else if(colNum==0){
        return 0;
    } else if(colNum==1){
        return getItem(0,0);
    } else if(colNum==2){
        return (getItem(0,0)*getItem(1,1)%p-getItem(0,1)*getItem(1,0)%p)%p;
    } else{
        ll num=0;
        int a=1;
        for(int i=0;i<colNum;i++)
        {
            num = (num + a*getItem(0,i)*left(0,i).det()%p)%p;
            a = -a;
        }
        while (num<0){
            num+=p;
        }

        return num;
    }
}

Matrix Matrix::Inverse()
{
    return adj()*Utils::modInv(det(),p);
}
