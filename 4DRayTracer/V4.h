#pragma once

#define _USE_MATH_DEFINES
#include <iostream>

#include "V3.h"

class V4Cross;

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
	V4& operator^=(V4Cross v23);
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
	friend V4Cross operator^(V4 v1, V4 v2);
	friend V4 operator^(V4Cross v12, V4 v3);
	friend V4 operator^(V4 v1, V4Cross v23);
	friend std::ostream& operator<<(std::ostream& ostr, const V4& v);
	friend std::istream& operator>>(std::istream& istr, V4& v);
	V4 cross(V4 v2, V4 v3);	// takes the "cross product" (not technically a cross product, but generates an orthogonal vector through the same process)
	V4& normalize();
	V4 normalized();
	float l2squared(); // sum of squares
	float length(); // square root of l2squared()
};

class V4Cross {
private:
	V4 v1;
	V4 v2;
public:
	friend V4Cross operator^(V4 v1, V4 v2);
	friend V4 operator^(V4Cross v12, V4 v3);
	friend V4 operator^(V4 v1, V4Cross v23);
};