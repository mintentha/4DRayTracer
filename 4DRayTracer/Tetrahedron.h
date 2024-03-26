#pragma once

#include "V4.h"
#include "Shape.h"

class Tetrahedron : public Shape {
private:
	V4 abcd[4];
public:
	Tetrahedron(V4 a, V4 b, V4 c, V4 d);
	V4 getIntersection(V4 o, V4 dir, float* time);
	V4 getNormal();
	V4 getNormal(V4 p);
};