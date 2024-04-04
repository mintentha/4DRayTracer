#include "PointLight.h"

PointLight::PointLight(V4 pos, V3 diffuse, V3 specular) {
	this->pos = pos;
	this->diffuse = diffuse;
	this->specular = specular;
}