#include "HyperSphere.h"
#include "V4.h"

HyperSphere::HyperSphere(V4 C, float r) {
	this->C = C;
	this->r = r;
}

V4 HyperSphere::getIntersection(V4 o, V4 dir, float *time) {
	dir.normalize();
	// float a = dir.l2squared();
	// a = 1
	float b = 2 * dir * (o - C);
	float c = (o - C).l2squared() - r * r;
	float disc = b * b - 4 * c;
	if (disc < 0) {
		*time = -1.0f;
		return V4(0.0f);
	}
	float t1 = -b - sqrtf(disc);
	float t2 = -b + sqrtf(disc);
	if (t1 > 0) {
		*time = t1;
		return o + dir * t1;
	}
	if (t2 > 0) {
		*time = t2;
		return o + dir * t2;
	}
	*time = -1.0f;
	return V4(0.0f);
}

V4 HyperSphere::getNormal(V4 p) {
	return (p - C).normalized();
}