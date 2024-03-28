#include "HyperQuad.h"
#include "M44.h"

HyperQuad::HyperQuad(V4 a, V4 b, V4 c, V4 d)
{
	abcd[0] = a;
	abcd[1] = b;
	abcd[2] = c;
	abcd[3] = d;
	normal = (b - a) ^ (c - a) ^ (d - a);
}

V4 HyperQuad::intersectionBarycentric(V4 o, V4 dir)
{
	// Instead of using uvw, which would be natural, I'm using suv
	// Just because w is one of our 4D coordinates.
	V4 tsuv = intersectionBarycentric(o, dir, a, b, c, d);
	return tsuv;
}

V4 HyperQuad::getIntersection(V4 o, V4 dir, float* time)
{
	dir.normalize();
	V4 tsuv = intersectionBarycentric(o, dir);
	if ((tsuv[0] < 0.0f) ||
		(tsuv[1] < 0.0f || tsuv[1] > 1.0f) ||
		(tsuv[2] < 0.0f || tsuv[2] > 1.0f) ||
		(tsuv[3] < 0.0f || tsuv[3] > 1.0f)) {
		tsuv[0] = -1.0f;
	}
	*time = tsuv[0];
	return o + dir * tsuv[0];
}

V4 HyperQuad::getNormal()
{
	return normal;
}

V4 HyperQuad::getNormal(V4 p)
{
	return normal;
}

V4 HyperQuad::intersectionBarycentric(V4 o, V4 dir, V4 a, V4 b, V4 c, V4 d)
{
	// p = (1 - s - u - v)a + sb + uc + vd
	M44 m = M44(-dir, b - a, c - a, d - a).Transposed();
	M44 test = m.Transposed();
	m.Invert();
	return m * (o - a);
}
