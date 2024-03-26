#pragma once

#include "V3.h"
#include <ostream>

class Shape {
public:
	virtual V3 intersection(V3 o, V3 dir, float *time) = 0;
	virtual V3 getNormal(V3 p) = 0;
	V3 diffuse;
	V3 specular;
	float shininess;
	float reflectivity;

	virtual std::ostream& print(std::ostream& ostr) = 0;
	friend std::ostream& operator<<(std::ostream& ostr, Shape& shape) {
		return shape.print(ostr);
	}
};