#pragma once

#include "V3.h"

class Material {
public:
	V3 diffuse;
	V3 specular;
	float shininess;
	float reflectivity;
};