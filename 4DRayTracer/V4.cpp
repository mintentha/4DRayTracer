#include "V4.h"
#include "M44.h"
#include "M33.h"

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

V4& V4::operator^=(V4Cross v23) {
	*this = *this ^ v23;
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

V4 V4::cross(V4 v2, V4 v3) {
	V4 &v1 = *this;
	V4 ret;
	M44 mat(V4(0.0f), v1, v2, v3);
	for (size_t i = 0; i < 4; i++) {
		float det = mat.SubMatrix(0, i).determinant();
		if (i % 2) {
			// top left is 0, 0, should be positive. 0, 1 should be negative, etc.
			det *= -1;
		}
		ret[i] = det;
	}
	return ret;
}

V4Cross operator^(V4 v1, V4 v2) {
	V4Cross ret;
	ret.v1 = v1;
	ret.v2 = v2;
	return ret;
}

V4 operator^(V4Cross v12, V4 v3) {
	V4& v1 = v12.v1;
	V4& v2 = v12.v2;
	return v1.cross(v2, v3);
}

V4 operator^(V4 v1, V4Cross v12) {
	V4& v2 = v12.v1;
	V4& v3 = v12.v2;
	return v1.cross(v2, v3);
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