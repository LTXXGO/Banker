//
//  Martix.h
//  Martix
//
//  Created by LTXX on 2018/11/15.
//  Copyright © 2018 LTXX. All rights reserved.
//

#ifndef Martix_h
#define Martix_h
#include <iostream>
#include <string>
using namespace std;

template <typename T>
class Martix {
public:
    unsigned int row;
    unsigned int column;
    T ** elem;
    void newElem();
    //构造函数
    Martix(): row(0), column(0) {}
    Martix(Martix<T> const &m);//based on copy
    Martix(unsigned int r, unsigned int c);
    Martix(unsigned int r, unsigned int c, T ** e);
    //析构函数
    ~Martix();
    
    int getRow() { return row; }
    int getColumn() { return column; }
    int size() { return row * column; }
    Martix<T> operator = (Martix<T> m);
    void transpose();//转置
    T caculateDeterminant();//计算行列式
    void input();
    void output(string name);
};

// MARK: - 基于复制的构造函数
template <typename T>
Martix<T>::Martix(Martix<T> const &m) {
    row = m.row;
    column = m.column;
    newElem();
    for(int r = 0; r < row; r++) {
        for(int c = 0; c < column; c++) {
            elem[r][c] = m.elem[r][c];
        }
    }
}

// MARK: - 基于行数和列数的构造函数
template <typename T>
Martix<T>::Martix(unsigned int r, unsigned int c) {
    row = r;
    column = c;
    newElem();
}

// MARK: - 从另一已知矩阵中复制一部分的构造函数
template <typename T>
Martix<T>::Martix(unsigned int r, unsigned int c, T ** e) {
    row = r;
    column = c;
    newElem();
    for(int r = 0; r < row; r++) {
        for(int c = 0; c < column; c++) {
            elem[r][c] = e[r][c];
        }
    }
}

// MARK: - 析构函数
template <typename T>
Martix<T>::~Martix() {
    int max;
    row > column? max = row: max = column;
    for(int i = 0; i < max; i++) {
        delete [] elem[i];
    }
    delete [] elem;
}

// MARK: - 重载 *（乘法）运算法
//用于计算矩阵乘法
template <typename T>
Martix<T> operator * (Martix<T> m1, Martix<T> m2) {
    Martix<T> m(m1.row, m2.column);
    for(int r = 0; r < m.row; r++) {
        for(int c = 0; c < m.column; c++) {
            m.elem[r][c] = m1.elem[r][0] * m2.elem[0][c];
            for(int i = 1; i < m1.column; i++)
                m.elem[r][c] += (m1.elem[r][i] * m2.elem[i][c]);
        }
    }
    return m;
}

// MARK: - 重载 +（加法）运算符
//用于计算矩阵加法
template <typename T>
Martix<T> operator + (Martix<T> m1, Martix<T> m2) {
    Martix<T> m(m1.row, m1.column);
    for(int r = 0; r < m.row; r++) {
        for(int c = 0; c < m.column; c++) {
            m.elem[r][c] = m1.elem[r][c] + m2.elem[r][c];
        }
    }
    return m;
}

// MARK: - 重载 -（减法）运算符
//用于计算矩阵减法
template <typename T>
Martix<T> operator - (Martix<T> m1, Martix<T> m2) {
    Martix<T> m(m1.row, m1.column);
    for(int r = 0; r < m.row; r++) {
        for(int c = 0; c < m.column; c++) {
            m.elem[r][c] = m1.elem[r][c] - m2.elem[r][c];
        }
    }
    return m;
}

// MARK: - 重载 = 运算符
//用于矩阵赋值运算
template <typename T>
Martix<T> Martix<T>::operator = (Martix<T> m) {
    row = m.row;
    column = m.column;
    newElem();
    for(int r = 0; r < m.row; r++) {
        for(int c = 0; c < m.column; c++) {
            elem[r][c] = m.elem[r][c];
        }
    }
    return *this;
}

//MARK: - 为新矩阵申请内存空间
template <typename T>
void Martix<T>::newElem() {
    int max;
    row > column? max = row: max = column;
    elem = new T * [max];
    for(int i = 0; i < max; i++) {
        elem[i] = new T [max];
    }
}

//MARK: - 矩阵转置
template <typename T>
void Martix<T>::transpose() {
    T t;
    int max;
    row < column? max = column: max = row;
    for(int r = 0; r < max; r++) {
        for(int c = 0; c < r + 1; c++) {
            t = elem[r][c];
            elem[r][c] = elem[c][r];
            elem[c][r] = t;
        }
    }
    int ex;
    ex = row;
    row = column;
    column = ex;
}

//MARK: - 计算行列式
template <typename T>
T Martix<T>::caculateDeterminant() {
    T total;
    for(int i = 0; i < column; i ++) {
        
    }
    return total;
}

//MARK: - 输入函数
template <typename T>
void Martix<T>::input() {
    if(row == 0 && column == 0) {
        cout << "Input number of rows: ";
        cin >> row;
        cout << "Input number of column: ";
        cin >> column;
        newElem();
    }
    cout << "Input Martix: \n";
    for(int r = 0; r < row; r++) {
        for(int c = 0; c < column; c++) {
            cin >> elem[r][c];
        }
    }
}

//MARK: - 输出函数
template <typename T>
void Martix<T>::output(string name) {
    cout << "The " << name << " martix is: \n";
    for(int r = 0; r < row; r++) {
        for(int c = 0; c < column; c++) {
            cout << elem[r][c] << " ";
        }
        cout << endl;
    }
}

#endif /* Martix_h */
