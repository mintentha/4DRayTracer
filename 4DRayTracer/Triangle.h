#pragma once
#include "Shape.h"
#include "V3.h"

class Triangle : public Shape {
private:
	V3 abc[3];
	V3 &a = abc[0];
	V3 &b = abc[1];
	V3 &c = abc[2];
	V3 normal;

	static constexpr float epsilon = 1e-5;
public:
	Triangle(V3 a, V3 b, V3 d, V3 diffuse, V3 specular, float shininess, float reflectivity); // Should be defined CCW
	Triangle(const Triangle &tri);

	Triangle& operator=(Triangle tri);
	V3 intersectionBarycentric(V3 o, V3 dir); // return t, u, v
	V3 intersection(V3 o, V3 dir, float* time);
	V3 getNormal();
	V3 getNormal(V3 p);

	std::ostream& print(std::ostream& ostr);
};