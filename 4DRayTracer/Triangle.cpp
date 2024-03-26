#include "Triangle.h"
#include "V3.h"

#include <iostream>

Triangle::Triangle(V3 a, V3 b, V3 c, V3 diffuse, V3 specular, float shininess, float reflectivity) {
	abc[0] = a;
	abc[1] = b;
	abc[2] = c;
	normal = (b - a) ^ (c - a);

	this->diffuse = diffuse;
	this->specular = specular;
	this->shininess = shininess;
	this->reflectivity = reflectivity;
}

Triangle::Triangle(const Triangle &tri) {
	a = tri.a;
	b = tri.b;
	c = tri.c;
	normal = tri.normal;
	diffuse = tri.diffuse;
	specular = tri.specular;
	shininess = tri.shininess;
	reflectivity = tri.reflectivity;
}

Triangle& Triangle::operator=(Triangle tri) {
	a = tri.a;
	b = tri.b;
	c = tri.c;
	normal = tri.normal;
	diffuse = tri.diffuse;
	specular = tri.specular;
	shininess = tri.shininess;
	reflectivity = tri.reflectivity;
	return *this;
}

V3 Triangle::intersectionBarycentric(V3 o, V3 dir) {
	float t = -1.0f;
	float u = 0.0f;
	float v = 0.0f;
	dir.normalize();

	V3 p = b - a;
	V3 q = c - a;
	V3 tmp1 = dir ^ q;
	float dot1 = tmp1 * p;
	if (fabsf(dot1) < epsilon) {
		return V3(t, u, v);
	}
	float f = 1.0f / dot1;
	V3 s = o - a;
	u = f * s * tmp1;
	if ((u < 0.0f) || (u > 1.0f)) {
		return V3(t, u, v);
	}
	V3 tmp2 = s ^ p;
	v = f * dir * tmp2;
	if ((v < 0.0f) || (u + v > 1.0f)) {
		return V3(t, u, v);
	}
	t = f * q * tmp2;

	// This actually is set up to return u, v such that P = a(1 - u - v) + bu + cv
	// I believe
	return V3(t, u, v);
}

V3 Triangle::intersection(V3 o, V3 dir, float* time) {
	dir.normalize();
	V3 tuv = intersectionBarycentric(o, dir);
	*time = tuv[0];
	if (*time < 0) {
		return V3(0.0f);
	}
	
	// V3 p = b * tuv[1] + c * tuv[2] + a * (1.0f - tuv[1] - tuv[2])
	V3 p = o + *time * dir; // Neither of these expressions feel any more efficient than the other

	return p;
}

V3 Triangle::getNormal() {
	return normal;
}

V3 Triangle::getNormal(V3 p) {
	return getNormal();
}

std::ostream& Triangle::print(std::ostream& ostr) {
	return ostr << "TRIANGLE " << a << " " << b << " " << c << " " << diffuse << " " << specular;
}