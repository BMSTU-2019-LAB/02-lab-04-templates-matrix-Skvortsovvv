// Copyright 2018 Your Name <your_email>

#ifndef INCLUDE_MATRIX_HPP_
#define INCLUDE_MATRIX_HPP_

#include <iostream>

template<typename T>
class Matrix {
	T** ptr;
	int Rows;
	int Cols;
public:
	Matrix(int Rows, int Cols) {
		this->Rows = Rows;
		this->Cols = Cols;
		ptr =(T**) new T * [Rows];
		for (int i = 0; i < Rows; i++) {
			ptr[i] =(T*) new T[Cols];
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
				delete ptr[i];
			}
			delete[]ptr;
		}
	}
	T* operator[](int index) {
		return ptr[index];
	}
	Matrix(const Matrix <T>& matr) { // Copying
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
	friend Matrix<T>& operator+(Matrix<T> M1, Matrix<T> M2);
	friend Matrix<T>& operator-(Matrix<T> M1, Matrix<T> M2);
	friend Matrix<T>& operator*(Matrix<T> M1, Matrix<T> M2);


};
template <typename T>
Matrix<T>& operator+(Matrix<T> M1, Matrix<T> M2) {
	if (M1.Cols == M2.Cols && M1.Rows == M2.Rows) {
		int r = M1.Rows;
		int c = M1.Col;
		Matrix M(M1.Rows, M1.Cols);
		for (int i = 0; i < Rows; i++) {
			for (int j = 0; j < Cols; j++) {
				M.ptr[i][j] = M1.ptr[i][j] + M2.ptr[i][j];
			}
		}
		return M;
	}
	else {
		Matrix M(0, 0);
		return M;
	}
}

template<typename T>
Matrix<T>& operator-(Matrix<T> M1, Matrix<T> M2) {
	if (M1.Cols == M2.Cols && M1.Rows == M2.Rows) {
		Matrix M(M1.Rows, M1.Cols);
		for (int i = 0; i < Rows; i++) {
			for (int j = 0; j < Cols; j++) {
				M.ptr[i][j] = M1.ptr[i][j] - M2.ptr[i][j];
			}
		}
		return M;
	}
	else {
		Matrix M(0, 0);
		return M;
	}
}
template<typename T>
Matrix<T>& operator*(Matrix<T> M1, Matrix<T> M2) {
	T buffer = 0;
	int counter = -1;
	if (M1.Cols == M2.Rows) {
		Matrix M(M1.Rows, M2.Cols);
		for (int i = 0; i < M1.Rows; i++) {
			for (int k = 0; k < M2.Cols; k++) {
				for (int j = 0; j < M1.Cols; j++) {
					buffer += M1.ptr[i][j] * M2.ptr[j][k];
					if (counter == -1) {
						counter = k;
					}
				}
				M.ptr[i][counter] = buffer;
				buffer = 0;
				counter = -1;
			}
			
		 }
		return M;
	}
	else {
		Matrix M(0, 0);
		return M;
	}
}


#endif // INCLUDE_MATRIX_HPP_
