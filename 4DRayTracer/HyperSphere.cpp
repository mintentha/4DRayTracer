#include "HyperSphere.h"
#include "V4.h"

HyperSphere::HyperSphere(V4 C, float r, Material material) {
	this->C = C;
	this->r = r;
	this->material = material;
}

V4 HyperSphere::getIntersection(V4 o, V4 dir, float *time) {
	// TODO:
}

V4 HyperSphere::getNormal(V4 p) {
	return (p - C).normalized();
}