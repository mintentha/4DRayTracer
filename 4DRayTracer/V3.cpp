#include "V3.h"
#include <math.h>

V3::V3() {
	V3(0.0f);
}

V3::V3(float x, float y, float z) {
	xyz[0] = x;
	xyz[1] = y;
	xyz[2] = z;
}

V3::V3(const V3& v) {
	xyz[0] = v.x;
	xyz[1] = v.y;
	xyz[2] = v.z;
}

V3::V3(unsigned int col) {
	this->SetColor(col);
}

float& V3::operator[](int i) {

	return xyz[i];

}

V3& V3::operator=(V3 v) {
	x = v.x;
	y = v.y;
	z = v.z;
	return *this;
}

V3& V3::operator+=(V3 v) {
	x += v.x;
	y += v.y;
	z += v.z;
	return *this;
}

V3& V3::operator-=(V3 v) {
	x -= v.x;
	y -= v.y;
	z -= v.z;
	return *this;
}

V3& V3::operator*=(float scf) {
	x *= scf;
	y *= scf;
	z *= scf;
	return *this;
}

V3& V3::operator/=(float scf) {
	x /= scf;
	y /= scf;
	z /= scf;
	return *this;
}

V3& V3::operator^=(V3 v) {
	return *this = *this ^ v;
}

V3& V3::operator%=(V3 v) {
	x *= v.x;
	y *= v.y;
	z *= v.z;
	return *this;
}

bool V3::operator==(V3 v) {
	return (x == v.x && y == v.y && z == v.z);
}

bool V3::operator>=(V3 v) {
	return (x >= v.x && y >= v.y && z >= v.z);
}

bool V3::operator<=(V3 v) {
	return (x <= v.x && y <= v.y && z <= v.z);
}

bool V3::operator>(V3 v) {
	return (x > v.x && y > v.y && z > v.z);
}

bool V3::operator<(V3 v) {
	return (x < v.x && y < v.y && z < v.z);
}

V3 operator+(V3 v1, V3 v2) {
	return v1 += v2;
}

V3 operator-(V3 v1, V3 v2) {
	return v1 -= v2;
}

V3 operator*(V3 v1, float scf) {
	return v1 *= scf;
}

V3 operator/(V3 v1, float scf) {
	return v1 /= scf;
}

V3 V3::operator^(V3 v) {
	return V3(
		y * v.z - z * v.y,
		z * v.x - x * v.z,
		x * v.y - y * v.x
	);
}

V3 operator%(V3 v1, V3 v2) {
	return v1 %= v2;
}

float V3::operator*(V3 v) {
	return x * v.x + y * v.y + z * v.z;
}

V3 V3::operator-() {
	return V3(-x, -y, -z);
}

V3 operator*(float scf, V3 v) {
	return v * scf;
}

std::ostream& operator<<(std::ostream& ostr, V3& v) {

	return ostr << v[0] << " " << v[1] << " " << v[2];

}

std::istream& operator>>(std::istream& istr, V3& v) {
	return istr >> v[0] >> v[1] >> v[2];
}

V3 &V3::normalize() {
	float l = length();
	if (l == 0) {
		return *this;
	}
	return *this /= l;
}

V3 V3::normalized() {
	return V3(*this).normalize();
}


float V3::l2squared() {
	return *this * *this;
}

float V3::length() {
	return sqrtf(l2squared());
}

unsigned int V3::GetColor() {
	unsigned int ret;
	unsigned char* rgba = (unsigned char*) &ret;
	for (int ci = 0; ci < 3; ci++) {
		if (xyz[ci] < 0.0f)
			rgba[ci] = 0;
		else if (xyz[ci] >= 1.0f)
			rgba[ci] = 255;
		else
			rgba[ci] = (unsigned char) (xyz[ci] * 255.0f);
	}
	rgba[3] = 0xFF;
	return ret;
}

void V3::SetColor(unsigned int color) {
	unsigned char* rgba = (unsigned char*)&color;
	for (int ci = 0; ci < 3; ci++) {
		xyz[ci] = (float) rgba[ci] / 255.0f;
	}
}