#include "Sphere.h"
#include "V3.h"

Sphere::Sphere(V3 C, float r, V3 diffuse, V3 specular, float shininess, float reflectivity) {
	this->C = C;
	this->r = r;
	this->diffuse = diffuse;
	this->specular = specular;
	this->shininess = shininess;
	this->reflectivity = reflectivity;
}

Sphere::Sphere(const Sphere &sphere) {
	C = sphere.C;
	r = sphere.r;
	diffuse = sphere.diffuse;
	specular = sphere.specular;
	shininess = sphere.shininess;
	reflectivity = sphere.reflectivity;
}

Sphere& Sphere::operator=(Sphere sphere) {
	C = sphere.C;
	r = sphere.r;
	diffuse = sphere.diffuse;
	specular = sphere.specular;
	shininess = sphere.shininess;
	reflectivity = sphere.reflectivity;
	return *this;
}

V3 Sphere::intersection(V3 o, V3 dir, float* time) {
	dir.normalize();
	float b = 2 * dir * (o - C);
	float c = (o - C).l2squared() - r * r;
	float disc = b * b - 4 * c;
	if (disc < 0) {
		*time = -1.0f;
		return V3(0.0f);
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
	return V3(0.0f);
}
V3 Sphere::getNormal(V3 p) {
	// Assume p is on the sphere
	return (p - C).normalize();
}

std::ostream& Sphere::print(std::ostream& ostr) {
	return ostr << "SPHERE " << C << " " << r << " " << diffuse << " " << specular;
}