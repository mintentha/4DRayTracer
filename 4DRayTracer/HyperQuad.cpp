#include "HyperQuad.h"
#include "M44.h"

HyperQuad::HyperQuad(V4 a, V4 b, V4 c, V4 d) {
	abcd[0] = a;
	abcd[1] = b;
	abcd[2] = c;
	abcd[3] = d;
	normal = (b - a) ^ (c - a) ^ (d - a);
}

V4 HyperQuad::intersectionBarycentric(V4 o, V4 dir) {
	// Instead of using uvw, which would be natural, I'm using suv
	// Just because w is one of our 4D coordinates.
	V4 tsuv = intersectionBarycentric(o, dir, a, b, c, d);
	return tsuv;
}

V4 HyperQuad::getIntersection(V4 o, V4 dir, float* time) {
	dir.normalize();
	V4 tsuv = intersectionBarycentric(o, dir);
	// This check is now being done in the moller trumbore
	//if ((tsuv[0] < 0.0f) ||
	//	(tsuv[1] < 0.0f || tsuv[1] > 1.0f) ||
	//	(tsuv[2] < 0.0f || tsuv[2] > 1.0f) ||
	//	(tsuv[3] < 0.0f || tsuv[3] > 1.0f)) {
	//	tsuv[0] = -1.0f;
	//}
	*time = tsuv[0];
	return o + dir * tsuv[0];
}

V4 HyperQuad::getNormal() {
	return normal;
}

V4 HyperQuad::getNormal(V4 p) {
	return normal;
}



// Straightforward ray-hyperplane intersection
//V4 HyperQuad::intersectionBarycentric(V4 o, V4 dir, V4 a, V4 b, V4 c, V4 d) {
//	// p = (1 - s - u - v)a + sb + uc + vd
//	M44 m = M44(-dir, b - a, c - a, d - a).Transposed();
//	m.Invert();
//	return m * (o - a);
//}



/* Möller–Trumbore Generalization */
V4 HyperQuad::intersectionBarycentric(V4 o, V4 dir, V4 a, V4 b, V4 c, V4 d) {
	V4 ret(-1.0f, 0.0f, 0.0f, 0.0f);
	dir.normalize();

	V4 p = b - a;
	V4 q = c - a;
	V4 r = d - a;
	V4 tmp1 = dir ^ q ^ r;
	float det = tmp1 * p;
	float epsilon = 1e-5;
	if (fabsf(det) < epsilon) {
		return ret;
	}
	float f = 1.0f / det;
	V4 s = o - a;
	ret[1] = f * s * tmp1;
	if (ret[1] < 0.0f || ret[1] > 1.0f) {
		return ret;
	}
	V4 tmp2 = s ^ p ^ r;
	ret[2] = f * dir * tmp2;
	if (ret[2] < 0.0f || ret[2] > 1.0f) {
		return ret;
	}
	V4 tmp3 = s ^ q ^ p;
	ret[3] = f * dir * tmp3;
	if (ret[3] < 0.0f || ret[3] > 1.0f) {
		return ret;
	}
	ret[0] = f * r * tmp3;
	return ret;
}