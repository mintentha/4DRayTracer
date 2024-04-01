#pragma once

#define _USE_MATH_DEFINES
#include <iostream>

class V3 {
public:
	float xyz[3];
	float& x = xyz[0];
	float& y = xyz[1];
	float& z = xyz[2];
	V3();
	V3(const V3& v);
	V3(float x, float y, float z);
	V3(float f) : V3(f, f, f) {};
	V3(unsigned int col);
	float& operator[](int i);
	V3& operator=(V3 v);
	V3& operator+=(V3 v);
	V3& operator-=(V3 v);
	V3& operator*=(float scf);
	V3& operator/=(float scf);
	V3& operator^=(V3 v); // cross product
	V3& operator%=(V3 v); // componentwise product
	float operator*(V3 v); // dot product
	V3 operator^(V3 v2);
	bool operator==(V3 v);
	bool operator>(V3 v);
	bool operator<(V3 v);
	bool operator>=(V3 v);
	bool operator<=(V3 v);
	friend V3 operator+(V3 v1, V3 v2);
	friend V3 operator-(V3 v1, V3 v2);
	friend V3 operator*(V3 v1, float scf);
	friend V3 operator/(V3 v1, float scf);
	friend V3 operator%(V3 v1, V3 v2);
	V3 operator-();
	friend V3 operator*(float scf, V3 v);
	friend std::ostream& operator<<(std::ostream& ostr, const V3& v);
	friend std::istream& operator>>(std::istream& istr, V3& v);
	V3& normalize();
	V3 normalized();
	float l2squared();
	float length();
	unsigned int GetColor();
	void SetColor(unsigned int color);
};