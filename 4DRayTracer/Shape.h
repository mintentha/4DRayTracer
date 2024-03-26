#pragma once

#include "V4.h"
#include "Material.h"

class Shape {
public:
	virtual V4 getIntersection(V4 o, V4 dir, float* time) = 0;
	virtual V4 getNormal(V4 p) = 0;
	Material material;
};