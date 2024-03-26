#include "V4.h"

V4::V4() {
	V4(0.0f);
}

V4::V4(float x, float y, float z, float w) {
	xyzw[0] = x;
	xyzw[1] = y;
	xyzw[2] = z;
	xyzw[3] = w;
}

V4::V4(const V4& v) {
	xyzw[0] = v.x;
	xyzw[1] = v.y;
	xyzw[2] = v.z;
	xyzw[3] = v.w;
}

V4::V4(V3 v, float w) {
	xyzw[0] = v.x;
	xyzw[1] = v.y;
	xyzw[2] = v.z;
	xyzw[3] = w;
}

float& V4::operator[](int i) {

	return xyzw[i];

}

V4& V4::operator=(V4 v) {
	x = v.x;
	y = v.y;
	z = v.z;
	w = v.w;
	return *this;
}

V4& V4::operator+=(V4 v) {
	x += v.x;
	y += v.y;
	z += v.z;
	w += v.w;
	return *this;
}

V4& V4::operator-=(V4 v) {
	x -= v.x;
	y -= v.y;
	z -= v.z;
	w -= v.w;
	return *this;
}

V4& V4::operator*=(float scf) {
	x *= scf;
	y *= scf;
	z *= scf;
	w *= scf;
	return *this;
}

V4& V4::operator/=(float scf) {
	x /= scf;
	y /= scf;
	z /= scf;
	w /= scf;
	return *this;
}

V4& V4::operator%=(V4 v) {
	x *= v.x;
	y *= v.y;
	z *= v.z;
	w *= v.w;
	return *this;
}

bool V4::operator==(V4 v) {
	return (x == v.x && y == v.y && z == v.z && w == v.w);
}

bool V4::operator>=(V4 v) {
	return (x >= v.x && y >= v.y && z >= v.z && w >= v.w);
}

bool V4::operator<=(V4 v) {
	return (x <= v.x && y <= v.y && z <= v.z && w <= v.w);
}

bool V4::operator>(V4 v) {
	return (x > v.x && y > v.y && z > v.z && w > v.w);
}

bool V4::operator<(V4 v) {
	return (x < v.x && y < v.y && z < v.z && w < v.w);
}

V4 operator+(V4 v1, V4 v2) {
	return v1 += v2;
}

V4 operator-(V4 v1, V4 v2) {
	return v1 -= v2;
}

V4 operator*(V4 v1, float scf) {
	return v1 *= scf;
}

V4 operator/(V4 v1, float scf) {
	return v1 /= scf;
}

V4 operator%(V4 v1, V4 v2) {
	return v1 %= v2;
}

float V4::operator*(V4 v) {
	return x * v.x + y * v.y + z * v.z + w * v.w;
}

V4 V4::operator-() {
	return V4(-x, -y, -z, -w);
}

V4 operator*(float scf, V4 v) {
	return v * scf;
}

std::ostream& operator<<(std::ostream& ostr, V4& v) {

	return ostr << v[0] << " " << v[1] << " " << v[2] << " " << v[3];

}

std::istream& operator>>(std::istream& istr, V4& v) {
	return istr >> v[0] >> v[1] >> v[2] >> v[3];
}

V4& V4::normalize() {
	float l = length();
	if (l == 0) {
		return *this;
	}
	return *this /= l;
}

V4 V4::normalized() {
	return V4(*this).normalize();
}


float V4::l2squared() {
	return *this * *this;
}

float V4::length() {
	return sqrtf(l2squared());
}