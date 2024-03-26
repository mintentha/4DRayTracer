#include "Scene.h"
#include "FrameBuffer.h"
#include "Shape.h"
#include "V3.h"
#include "Sphere.h"

#include <vector>

Scene::Scene(FrameBuffer *fb, PPC *ppc, V3 ambientCol, V3 bgrCol, size_t maxDepth) {
	this->fb = fb;
	this->ppc = ppc;
	this->shapes = new std::vector<Shape *>();
	this->lights = new std::vector<PointLight *>();
	this->ambientCol = ambientCol;
	this->bgrCol = bgrCol;
	this->maxDepth = maxDepth;
}


Scene::Scene(FrameBuffer *fb, PPC *ppc, V3 ambientCol, V3 bgrCol, size_t maxDepth, std::vector<Shape *> *shapes, std::vector<PointLight *> *lights) {
	this->fb = fb;
	this->ppc = ppc;
	this->shapes = shapes;
	this->lights = lights;
	this->ambientCol = ambientCol;
	this->bgrCol = bgrCol;
	this->maxDepth = maxDepth;
}

Scene::~Scene() {
	while (shapes->size() > 0) {
		delete shapes->back();
		shapes->pop_back();
	}
	while (lights->size() > 0) {
		delete lights->back();
		lights->pop_back();
	}
	delete shapes;
	delete lights;
	delete fb;
	delete ppc;
}

void Scene::AddShape(Shape *shape) {
	shapes->push_back(shape);
}

void Scene::AddLight(PointLight *light) {
	lights->push_back(light);
}

void Scene::RenderRT() {
	for (size_t u = 0; u < ppc->getW(); u++) {
		for (size_t v = 0; v < ppc->getH(); v++) {
			V3 col = RayTrace(ppc->getPos(), ppc->GetRay(u, v), maxDepth);
			col.x = fminf(col.x, 1.0f);
			col.y = fminf(col.y, 1.0f);
			col.z = fminf(col.z, 1.0f);
			fb->SetColor(u, v, col);
		}
	}
}


V3 Scene::intersect(Shape* curShape, V3 o, V3 dir, Shape** shape, float* time) {
	float curTime = -1.0f;
	float closestTime = -1.0f;
	size_t closestShape = 0;
	V3 closestP = V3(0.0f);
	for (size_t i = 0; i < shapes->size(); i++) {
		if (shapes->at(i) == curShape) {
			continue;
		}
		V3 p = shapes->at(i)->intersection(o, dir, &curTime);
		if ((closestTime < 0 && curTime > 0) ||
			(curTime > 0 && curTime < closestTime)) {
			closestTime = curTime;
			closestShape = i;
			closestP = p;
		}
	}
	*time = closestTime;
	*shape = shapes->at(closestShape);
	return closestP;
}

V3 Scene::intersect(V3 o, V3 dir, Shape **shape, float *time) {
	return intersect(nullptr, o, dir, shape, time);
}

bool Scene::isLightVisible(V3 p, Shape *shape, PointLight *light) {
	V3 o = light->pos;
	V3 dir = p - o;
	dir.normalize();
	Shape* firstShape = nullptr;
	float time = 0.0f;
	intersect(o, dir, &firstShape, &time);
	return (time >= 0) && (firstShape == shape);
}

V3 Scene::reflect(V3 V, V3 N) {
	return (2 * (V * N) * N - V).normalized();
}

V3 Scene::phong(Shape *shape, V3 p, V3 dir, PointLight *light) {
	V3 L = light->pos - p;
	L.normalize();
	V3 N = shape->getNormal(p);
	N.normalize();
	V3 dif = (light->diffuse % shape->diffuse) * fmaxf(L * N, 0.0f);
	V3 R = reflect(L, N);
	R.normalize();
	V3 V = -dir;
	V.normalize();
	V3 spec = (light->specular % shape->specular) * powf(fmaxf(R * V, 0.0f), shape->shininess);
	return dif + spec;
}

V3 Scene::RayTrace(Shape *curShape, V3 o, V3 dir, size_t depth) {
	V3 col = V3(0.0f);
	Shape *shape = nullptr;
	float time = 0;
	V3 p = intersect(curShape, o, dir, &shape, &time);
	if (time < 0 || shape == nullptr) {
		// There was no intersection
		return bgrCol;
	}
	for (size_t i = 0; i < lights->size(); i++) {
		if (isLightVisible(p, shape, lights->at(i))) {
			col += phong(shape, p, dir, lights->at(i));
			if (col == 0.0f) {
				phong(shape, p, dir, lights->at(i));
			}
		}
	}
	col += ambientCol;
	if (depth == 0 || shape->reflectivity <= 0.0f) {
		return col;
	}
	// for now, forget refraction

	V3 reflected = reflect(-dir, shape->getNormal(p));
	if (dynamic_cast<Sphere*>(shape)) {
		reflected = reflect(reflected, ppc->a ^ ppc->b);
		// i dont know why but on spheres the reflection is vertically and horizontally flipped, but depth wise is correct
		// this is a band-aid solution
		// and actually doesn't even fully work, 
		// and probably doesnt make sense to reflect off of where the camera is facing when not all rays have origin from camera
	}
	
	// We had a few options
	// (1) Just do intersections as is (there will be a lot of times where the ray intersects the point it starts at and looks messy)
	// (2) Offset the point slightly to avoid self-intersection
	// (3) Specify the shape and skip checking intersections with that shape
	// (4) Or change the intersection functions of our shapes to take a point and try to ignore that point
	// I chose option 3
	col += shape->reflectivity * RayTrace(shape, p, reflected, depth - 1);
	return col;
}


V3 Scene::RayTrace(V3 o, V3 dir, size_t depth) {
	return RayTrace(nullptr, o, dir, depth);
}

void Scene::SaveAsTIFF(const char *filename) {
	fb->SaveAsTiff(filename);
}