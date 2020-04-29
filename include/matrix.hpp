// Copyright 2018 Your Name <your_email>

#ifndef INCLUDE_MATRIX_HPP_
#define INCLUDE_MATRIX_HPP_
#pragma once
#include <iostream>
#include <cmath>
#include<type_traits>
#include<limits>

template<typename T>
class Matrix {
    T** ptr;
    int Rows;
    int Cols;
    static_assert(std::is_arithmetic<T>::value, "Non arithmetic type");
    
public:
    Matrix(int Rows, int Cols) {
        this->Rows = Rows;
        this->Cols = Cols;
        ptr = new T * [Rows];
        for (int i = 0; i < Rows; i++) {
            ptr[i] = new T[Cols];
        }
        for (int i = 0; i < Rows; i++) {
            for (int j = 0; j < Cols; j++) {
                ptr[i][j] = 0;
            }
        }
    }
    Matrix() {
        ptr = nullptr;
        Rows = 0;
        Cols = 0;
    }
    ~Matrix() {
        if (ptr != NULL) {
            for (int i = 0; i < Rows; i++) {
                delete []ptr[i];
            }
            delete[]ptr;
        }
    }
    T* operator[](int index) {
        return ptr[index];
    }
    void print() {
        for (int i = 0; i < Rows; i++) {
        for (int j = 0; j < Cols; j++) {
                std::cout << ptr[i][j] << ' ';
            }
            std::cout << std::endl;
        }
    }
    Matrix<T>& operator=(Matrix<T>& M1) {
        if (ptr == M1.ptr) return *this;
        Rows = M1.Rows;
        Cols = M1.Cols;
        if (ptr == nullptr) {
            ptr = new T* [Rows];
            for (int i = 0; i < Rows; i++) {
                ptr[i] = new T[Cols];
            }
            for (int i = 0; i < Rows; i++) {
                for (int j = 0; j < Cols; j++) {
                    ptr[i][j] = M1.ptr[i][j];
                }
            }
        } else {
            for (int i = 0; i < Rows; i++) {
                delete[]ptr[i];
            }
            delete[]ptr;
            ptr = new T* [Rows];
            for (int i = 0; i < Rows; i++) {
                ptr[i] = new T[Cols];
            }
            for (int i = 0; i < Rows; i++) {
                for (int j = 0; j < Cols; j++) {
                    ptr[i][j] = M1.ptr[i][j];
                }
            }
        }
        return *this;
    }
    bool operator==(const Matrix<T>& op2) const {
        if (typeid(*this) == typeid(op2)
            && (typeid(op2) == typeid(static_cast<float>)
        || typeid(op2) == typeid(static_cast<float>))) {
            if (Rows == op2.Rows && Cols == op2.Cols) {
                for (int i = 0; i < Rows; i++) {
                    for (int j = 0; j < Cols; j++) {
                        if (fabs(ptr[i][j] - op2.ptr[i][j])
                            >= 16 * DBL_EPSILON * fmax(fabs(ptr[i][j]),
                           fabs(op2.ptr[i][j]))) return false;
                    }
                    return true;
                }
            } else {
            return false;
            }
       }
        if (Rows == op2.Rows && Cols == op2.Cols) {
            for (int i = 0; i < Rows; i++) {
                for (int j = 0; j < Cols; j++) {
                    if (ptr[i][j] != op2.ptr[i][j]) return false;
                }
                return true;
            }
        }
        return false;
    }
    bool operator!=(const Matrix<T>& op2)const {
        if (*this == op2) return false;
        return true;
    }
    Matrix(const Matrix <T>& matr) {
        Rows = matr.Rows;
        Cols = matr.Cols;
        ptr = new T * [Rows];
        for (int i = 0; i < Rows; i++) {
            ptr[i] = new T[Cols];
        }
        for (int i = 0; i < Rows; i++) {
            for (int j = 0; j < Cols; j++) {
                ptr[i][j] = matr.ptr[i][j];
            }
        }
    }
    Matrix<T> operator+(const Matrix<T>& M1) {
        Matrix result;
        if (Rows == M1.Rows && Cols == M1.Cols) {
            result = Matrix(M1.Rows, M1.Cols);
            for (int i = 0; i < M1.Rows; i++) {
                for (int j = 0; j < M1.Cols; j++) {
                    result.ptr[i][j] = ptr[i][j] + M1.ptr[i][j];
                }
            }
        } else {
            result = Matrix(0, 0);
        }
        return result;
    }
    Matrix<T> operator-(const Matrix<T>& M1) {
        Matrix result;
        if (Rows == M1.Rows && Cols == M1.Cols) {
            result = Matrix(M1.Rows, M1.Cols);
            for (int i = 0; i < M1.Rows; i++) {
                for (int j = 0; j < M1.Cols; j++) {
                    result.ptr[i][j] = ptr[i][j] - M1.ptr[i][j];
                }
            }
        } else {
            result = Matrix(0, 0);
        }
        return result;
    }
    Matrix<T> operator*(const Matrix<T>& M2) {
        T buffer = 0;
        int counter = -1;
        Matrix M;
        if (Cols == M2.Rows) {
            M = Matrix(Rows, M2.Cols);
            for (int i = 0; i < Rows; i++) {
                for (int k = 0; k < M2.Cols; k++) {
                    for (int j = 0; j < Cols; j++) {
                        buffer += ptr[i][j] * M2.ptr[j][k];
                        if (counter == -1) {
                            counter = k;
                        }
                    }
                    if (std::fabs(buffer)
                        <= std::numeric_limits<T>::epsilon() * 1E10) {
                        buffer = 0.;
                    }
                    M.ptr[i][counter] = buffer;
                    buffer = 0;
                    counter = -1;
                }
            }
            return M;
        } else {
            M = Matrix(0, 0);
            return M;
        }
    }
    size_t cols() const
    {
        size_t c = Cols;
        return c;
    }
    size_t rows() const
    {
        size_t r = Rows;
        return r;
    }
    int get_rows() const {
        return Rows;
    }
    int get_columns() const {
        return Cols;
    }
    Matrix Inverse() const {
    if (Rows != Cols) {
            Matrix<T> error;
            return error;
        }
        Matrix<T> Turn(Rows, 2 * Cols);
        for (int i = 0; i < Rows; i++) {
            for (int j = 0; j < Cols; j++) {
                Turn[i][j] = ptr[i][j];
            }
        }
        for (int i = 0; i < Rows; i++) {
            for (int j = Cols; j < 2 * Cols; j++) {
                if (i == j - Cols) Turn[i][j] = 1;
            }
        }
        double l = 0;
        double n = 0;
        for (int j = 0; j < 2 * Cols; j++) {
            for (int i = 0; i < Rows; i++) {
                if (i == j) {
                    if (Turn[i][j] == 0) {
                        int r = i;
                        while (Turn[r][j] == 0) {
                            r++;
                        }
                        for (int q = 0; q < 2 * Cols; q++) {
                            double k = Turn[i][q];
                            Turn[i][q] = Turn[r][q];
                            Turn[r][q] = k;
                        }
                    }
                    l = Turn[i][j];
                    for (int k = 0; k < 2 * Cols; k++) {
                            if (Turn[i][k] != 0) {
                            Turn[i][k] = Turn[i][k] / l;
                        }
                    }
                }
                if (i > j) {
                    n = Turn[i][j] / Turn[j][j];
                    for (int k = 0; k < 2 * Cols; k++) {
                        Turn[i][k] -= Turn[j][k] * n;
                    }
                }
            }
        }
        for (int j = Cols - 1; j >= 0; j--) {
            for (int i = Rows - 1; i >= 0; i--) {
                if (i < j) {
                    if (Turn[j][j] != 0) {
                        n = Turn[i][j] / Turn[j][j];
                        for (int k = 0; k < 2 * Cols; k++) {
                            Turn[i][k] -= Turn[j][k] * n;
                        }
                    }
                }
            }
        }
        Matrix<T> result(Rows, Cols);
        for (int i = 0; i < Rows; i++) {
            for (int j = 0; j < Cols; j++) {
                result[i][j] = Turn[i][j + Cols];
            }
        }
        return result;
    }
};
#endif // INCLUDE_MATRIX_HPP_
