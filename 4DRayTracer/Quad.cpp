#include "Quad.h"
#include "V3.h"
#include "M33.h"

Quad::Quad(V3 a, V3 b, V3 c, V3 diffuse, V3 specular, float shininess, float reflectivity) {
	abc[0] = a;
	abc[1] = b;
	abc[2] = c;
	normal = (b - a) ^ (c - a);
	normal.normalize();
	this->diffuse = diffuse;
	this->specular = specular;
	this->shininess = shininess;
	this->reflectivity = reflectivity;
}

Quad::Quad(const Quad &quad) {
	a = quad.a;
	b = quad.b;
	c = quad.c;
	normal = quad.normal;
	diffuse = quad.diffuse;
	specular = quad.specular;
	shininess = quad.shininess;
	reflectivity = quad.reflectivity;
}

Quad& Quad::operator=(Quad quad) {
	a = quad.a;
	b = quad.b;
	c = quad.c;
	normal = quad.normal;
	diffuse = quad.diffuse;
	specular = quad.specular;
	shininess = quad.shininess;
	reflectivity = quad.reflectivity;
	return *this;
}

/*
 * Möller–Trumbore method
 */

V3 Quad::intersectionBarycentric(V3 o, V3 dir) {
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
	if ((v < 0.0f) || (v > 1.0f)) {
		return V3(t, u, v);
	}
	t = f * q * tmp2;

	return V3(t, u, v);
}

/*
V3 Quad::intersectionBarycentric(V3 o, V3 dir) {
	dir.normalize();
	M33 Q;
	Q.SetColumn(0, b - a);
	Q.SetColumn(1, c - a);
	Q.SetColumn(2, -dir);
	V3 bct = Q.Inverted() * (o - a);
	// bct = [u, v, t] for p = a(1 - u - v) + bu + cv
	if (bct[0] < 0.0f || bct[0] > 1.0f || bct[1] < 0.0f || bct[1] > 1.0f) {
		return V3(-1.0f);
	}
	return bct;
}
*/

/*
V3 Quad::intersectionBarycentric(V3 o, V3 dir) {
	V3 tuv = M33(-dir, b - a, c - a).Transposed().Inverted() * (o - a);
	if ((tuv[0] < 0) ||
		(tuv[1] < 0.0f || tuv[1] > 1.0f) || 
		(tuv[2] < 0.0f || tuv[2] > 1.0f)) {
		tuv[0] = -1.0f;
	}
	return tuv;
}
*/

V3 Quad::intersection(V3 o, V3 dir, float* time) {
	dir.normalize();
	V3 tuv = intersectionBarycentric(o, dir);
	*time = tuv[0];
	if (*time < 0) {
		return V3(0.0f);
	}

	V3 p = o + *time * dir;

	return p;
}

V3 Quad::getNormal(V3 p) {
	return normal;
}

std::ostream& Quad::print(std::ostream& ostr) {
	return ostr << "QUAD " << a << " " << b << " " << c << " " << diffuse << " " << specular;
}