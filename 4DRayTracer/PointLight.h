#pragma once

#include "V3.h"

class PointLight {
public:
	V3 pos;
	V3 diffuse;
	V3 specular;

	PointLight(V3 pos, V3 diffuse, V3 specular);
};