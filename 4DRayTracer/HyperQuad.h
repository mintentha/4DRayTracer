#pragma once

#include "V4.h"
#include "Shape.h"

// I called it a HyperQuad because its a subsection of a HyperPlane
// Really its just a rectangular prism
class HyperQuad : public Shape {
private:
	V4 abcd[4];
	V4 &a = abcd[0];
	V4 &b = abcd[1];
	V4 &c = abcd[2];
	V4 &d = abcd[3];
	V4 normal;
public:
	HyperQuad(V4 a, V4 b, V4 c, V4 d);
	V4 intersectionBarycentric(V4 o, V4 dir);
	V4 getIntersection(V4 o, V4 dir, float* time);
	V4 getNormal();
	V4 getNormal(V4 p);

	// this is static so it can also be used for Tetrahedrons
	// this does not for a fact tell you if the ray intersects
	// it just gives you the tsuv vector
	static V4 intersectionBarycentric(V4 o, V4 dir, V4 a, V4 b, V4 c, V4 d);
};