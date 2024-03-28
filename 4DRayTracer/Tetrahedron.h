#pragma once

#include "V4.h"
#include "Shape.h"

class Tetrahedron : public Shape {
private:
	V4 abcd[4];
	V4 &a = abcd[0];
	V4 &b = abcd[1];
	V4 &c = abcd[2];
	V4 &d = abcd[3];
	V4 normal;
	V4 intersectionBarycentric(V4 o, V4 dir);
public:
	Tetrahedron(V4 a, V4 b, V4 c, V4 d);
	V4 getIntersection(V4 o, V4 dir, float* time);
	V4 getNormal();
	V4 getNormal(V4 p);
};