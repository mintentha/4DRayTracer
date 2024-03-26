#include "Scene.h"

#include "Shape.h"
#include "PPC.h"
#include "FrameBuffer.h"
#include "V3.h"
#include "V4.h"

Scene::Scene(PPC* ppc, V3 bgrCol, size_t maxDepth, std::vector<Shape*>* shapes) {
	this->ppc = ppc;
	this->bgrCol = bgrCol;
	this->maxDepth = maxDepth;
	this->shapes = shapes;
}

Scene::~Scene() {
	while (shapes->size() > 0) {
		delete shapes->back();
		shapes->pop_back();
	}
	delete shapes;
	delete ppc;
}


void Scene::AddShape(Shape* shape) {
	shapes->push_back(shape);
}

V4 Scene::intersect(Shape* curShape, V4 o, V4 dir, Shape** shape, float* time) {
	float curTime = -1.0f;
	float closestTime = -1.0f;
	size_t closestShape = 0;
	V4 closestP(0.0f);
	for (size_t i = 0; i < shapes->size(); i++) {
		if (shapes->at(i) == curShape) {
			continue;
		}
		V4 p = shapes->at(i)->getIntersection(o, dir, &curTime);
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


V4 Scene::intersect(V4 o, V4 dir, Shape** shape, float* time) {
	return intersect(nullptr, o, dir, shape, time);
}

V3 Scene::RayTrace(Shape* curShape, V4 o, V4 dir, size_t depth) {
	V3 col(0.0f);
	Shape *shape = nullptr;
	float time = 0;
	V4 p = intersect(curShape, o, dir, &shape, &time);
	if (time < 0 || shape == nullptr) {
		return bgrCol;
	}
	// TODO: Lighting
	// For now, just return the material diffuse color
	if (shape->material) {
		return shape->material->diffuse;
	}
	return V3(0.0f); // default material is black
}

V3 Scene::RayTrace(V4 o, V4 dir, size_t depth) {
	return RayTrace(nullptr, o, dir, depth);
}

void Scene::RenderRT(FrameBuffer* fb, float ow, float dw) {
	for (size_t u = 0; u < ppc->getW(); u++) {
		for (size_t v = 0; v < ppc->getH(); v++) {
			V3 col = RayTrace(V4(ppc->getPos(), ow), V4(ppc->GetRay(u, v), dw), maxDepth);
			col.x = fminf(col.x, 1.0f);
			col.y = fminf(col.y, 1.0f);
			col.z = fminf(col.z, 1.0f);
			fb->SetColor(u, v, col);
		}
	}
}