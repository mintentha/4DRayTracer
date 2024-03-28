#pragma once

#include "V4.h"
#include "M33.h"

#include <iostream>

class M44 {
public:
	V4 rows[4];
	M44() {};
	M44(const M44& mat);
	M44(V4 row1, V4 row2, V4 row3, V4 row4);
	M44(float f);
	V4& operator[](int i);
	void SetColumn(int i, V4 colv);
	V4 GetColumn(int i);

	M44& operator=(M44 mat);
	M44& operator+=(M44 mat);
	M44& operator-=(M44 mat);
	M44& operator*=(M44 mat);
	M44& operator*=(float scf);
	M44& operator%=(M44 mat); // Componentwise product

	friend M44 operator+(M44 mat1, M44 mat2);
	friend M44 operator-(M44 mat1, M44 mat2);
	M44 operator*(M44 mat);
	friend M44 operator*(M44 mat1, float scf);
	friend M44 operator*(float scf, M44 mat1);
	friend M44 operator%(M44 mat1, M44 mat2);
	V4 operator*(V4 v);
	M33 SubMatrix(int i, int j);
	M44 Inverted();
	M44 Transposed();
	M44& Invert();
	M44& Transpose();
	float determinant();
	friend std::ostream& operator<<(std::ostream& ostr, M44& mat);
	friend std::istream& operator>>(std::istream& istr, M44& mat);
};