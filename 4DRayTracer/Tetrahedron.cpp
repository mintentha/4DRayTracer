#include "Tetrahedron.h"

#include "HyperQuad.h"
#include "V4.h"

Tetrahedron::Tetrahedron(V4 a, V4 b, V4 c, V4 d) {
	this->abcd[0] = a;
	this->abcd[1] = b;
	this->abcd[2] = c;
	this->abcd[3] = d;
}

V4 Tetrahedron::intersectionBarycentric(V4 o, V4 dir) {
	return HyperQuad::intersectionBarycentric(o, dir, a, b, c, d);
}

V4 Tetrahedron::getIntersection(V4 o, V4 dir, float *time) {
	dir.normalize();
	V4 tsuv = intersectionBarycentric(o, dir);
	if ((tsuv[0] < 0.0f) ||
		(tsuv[1] < 0.0f || tsuv[1] > 1.0f) ||
		(tsuv[2] < 0.0f || tsuv[2] > 1.0f) ||
		(tsuv[3] < 0.0f || tsuv[3] > 1.0f) ||
		(tsuv[1] + tsuv[2] + tsuv[3] > 1.0f)) {
		tsuv[0] = -1.0f;
	}
	*time = tsuv[0];
	return o + dir * tsuv[0];
}

V4 Tetrahedron::getNormal() {
	return ((b - a) ^ (c - a) ^ (d - a)).normalized();
}

V4 Tetrahedron::getNormal(V4 p) {
	return getNormal();
}