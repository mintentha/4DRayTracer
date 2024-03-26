#pragma once

#include "V4.h"
#include "Shape.h"

class HyperSphere : public Shape {
private:
	V4 C;
	float r;
public:
	HyperSphere(V4 C, float r);
	V4 getIntersection(V4 o, V4 dir, float* time);
	V4 getNormal(V4 p);
};