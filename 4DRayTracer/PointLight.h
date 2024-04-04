#pragma once

#include "V4.h"
#include "V3.h"

class PointLight {
public:
	V4 pos;
	V3 diffuse;
	V3 specular;

	PointLight(V4 pos, V3 diffuse, V3 specular);
};