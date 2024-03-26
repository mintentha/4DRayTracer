#pragma once
#include "Shape.h"
#include "V3.h"

class Quad : public Shape {
private:
	V3 abc[3];
	V3 &a = abc[0];
	V3 &b = abc[1];
	V3 &c = abc[2];
	V3 normal;
	static constexpr float epsilon = 1e-5;
public:
	Quad(V3 a, V3 b, V3 c, V3 diffuse, V3 specular, float shininess, float reflectivity); // Should be defined CCW
	Quad(V3 a, V3 b, V3 c, V3 d, V3 diffuse, V3 specular, float shininess) : Quad(a, b, c, diffuse, specular, shininess, reflectivity) {};
	Quad(const Quad &quad);

	Quad& operator=(Quad quad);
	V3 intersectionBarycentric(V3 o, V3 dir); // return t, u, v
	V3 intersection(V3 o, V3 dir, float* time);
	V3 getNormal(V3 p);

	std::ostream& print(std::ostream& ostr);
};