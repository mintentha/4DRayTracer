#pragma once
#include "Shape.h"
#include "V3.h"

class Sphere : public Shape {
private:
	V3 C;
	float r;
public:
	Sphere(V3 C, float r, V3 diffuse, V3 specular, float shininess, float reflectivity);
	Sphere(const Sphere &sphere);

	Sphere& operator=(Sphere sphere);
	V3 intersection(V3 o, V3 dir, float *time);
	V3 getNormal(V3 p);

	std::ostream& print(std::ostream& ostr);
};
