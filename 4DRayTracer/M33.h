#pragma once

#include "V3.h"

#include <iostream>

class M33 {
public:
	V3 rows[3];
	M33() {};
	M33(const M33& mat);
	M33(V3 row1, V3 row2, V3 row3);
	M33(float f);
	V3& operator[](int i);
	void SetColumn(int i, V3 colv);
	V3 GetColumn(int i);

	M33& operator=(M33 mat);
	M33& operator+=(M33 mat);
	M33& operator-=(M33 mat);
	M33& operator*=(M33 mat);
	M33& operator*=(float scf);
	M33& operator%=(M33 mat); // Componentwise product

	friend M33 operator+(M33 mat1, M33 mat2);
	friend M33 operator-(M33 mat1, M33 mat2);
	M33 operator*(M33 mat);
	friend M33 operator*(M33 mat1, float scf);
	friend M33 operator*(float scf, M33 mat1);
	friend M33 operator%(M33 mat1, M33 mat2);

	V3 operator*(V3 v);
	M33 Inverted();
	M33 Transposed();
	M33& Invert();
	M33& Transpose();
	friend std::ostream& operator<<(std::ostream& ostr, M33& mat);
	friend std::istream& operator>>(std::istream& istr, M33& mat);
};