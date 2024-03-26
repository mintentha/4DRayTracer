#include "Tetrahedron.h"
#include "V4.h"
#include "util.h"

Tetrahedron::Tetrahedron(V4 a, V4 b, V4 c, V4 d, Material material) {
	this->abcd[0] = a;
	this->abcd[1] = b;
	this->abcd[2] = c;
	this->abcd[3] = d;
	this->material = material;
}

V4 Tetrahedron::getIntersection(V4 o, V4 dir, float *time) {
	dir.normalize();

	float t = distToHyperplane(o, dir, this->getNormal(), this->abcd[0]);

	if (t > 0) {
		V4 p = o + t * dir;
		V4 u = bary4D(p, abcd[0], abcd[1], abcd[2], abcd[3]);
		if (u.x < 0 || u.y < 0 || u.z < 0 || u.w < 0) {
			*time = -1.0f;
			return V4(0.0f);
		} else {
			*time = t;
			return p;
		}
	} else {
		*time = -1.0f;
		return V4(0.0f);
	}

}

V4 Tetrahedron::getNormal() {
	return hypernormal(this->abcd[1]-this->abcd[0], this->abcd[2]-this->abcd[0], this->abcd[3]-this->abcd[0]);
}

V4 Tetrahedron::getNormal(V4 p) {
	return hypernormal(this->abcd[1]-this->abcd[0], this->abcd[2]-this->abcd[0], this->abcd[3]-this->abcd[0]);
}