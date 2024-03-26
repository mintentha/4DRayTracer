#pragma once

#define _USE_MATH_DEFINES
#include <iostream>

#include "V3.h"

class V4 {
public:
	float xyzw[4];
	float& x = xyzw[0];
	float& y = xyzw[1];
	float& z = xyzw[2];
	float& w = xyzw[3];
	V4();
	V4(const V4& v);
	V4(float x, float y, float z, float w);
	V4(float f) : V4(f, f, f, f) {};
	V4(V3 v, float w);
	V4(V3 v) : V4(v, 0.0f) {};
	float& operator[](int i);
	V4& operator=(V4 v);
	V4& operator+=(V4 v);
	V4& operator-=(V4 v);
	V4& operator*=(float scf);
	V4& operator/=(float scf);
	V4& operator%=(V4 v); // componentwise product
	float operator*(V4 v); // dot product
	bool operator==(V4 v);
	bool operator>(V4 v);
	bool operator<(V4 v);
	bool operator>=(V4 v);
	bool operator<=(V4 v);
	friend V4 operator+(V4 v1, V4 v2);
	friend V4 operator-(V4 v1, V4 v2);
	friend V4 operator*(V4 v1, float scf);
	friend V4 operator/(V4 v1, float scf);
	friend V4 operator%(V4 v1, V4 v2);
	V4 operator-();
	friend V4 operator*(float scf, V4 v);
	friend std::ostream& operator<<(std::ostream& ostr, V4& v);
	friend std::istream& operator>>(std::istream& istr, V4& v);
	V4& normalize();
	V4 normalized();
	float l2squared(); // sum of squares
	float length(); // square root of l2squared()
};