#include "Scene.h"

#include "Shape.h"
#include "PPC.h"
#include "FrameBuffer.h"
#include "V3.h"
#include "V4.h"

Scene::Scene(V3 ambientCol, V3 bgrCol, size_t maxDepth, std::vector<Shape*>* shapes, std::vector<PointLight*>* lights) {
	this->ambientCol = ambientCol;
	this->bgrCol = bgrCol;
	this->maxDepth = maxDepth;
	this->shapes = shapes;
	this->lights = lights;
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
}


void Scene::AddShape(Shape* shape) {
	shapes->push_back(shape);
}

void Scene::AddLight(PointLight* light) {
	lights->push_back(light);
}

V4 Scene::intersect(Shape* curShape, V4 o, V4 dir, Shape** shape, float* time) {
	float curTime = -1.0f;
	float closestTime = -1.0f;
	Shape* closestShape = 0;
	V4 closestP(0.0f);
	for (auto &shapeIt : (*shapes)) {
		if (shapeIt == curShape) {
			continue;
		}
		V4 p = shapeIt->getIntersection(o, dir, &curTime);
		if ((closestTime < 0 && curTime > 0) ||
			(curTime > 0 && curTime < closestTime)) {
			closestTime = curTime;
			closestShape = shapeIt;
			closestP = p;
		}
	}
	*time = closestTime;
	*shape = closestShape;
	return closestP;
}

V3 Scene::phong(Shape* shape, V4 p, V4 dir, PointLight* light) {
	V4 L = light->pos - p;
	L.normalize();
	V4 N = shape->getNormal(p);
	N.normalize();
	V3 dif = (light->diffuse % shape->material->diffuse) * fmaxf(L * N, 0.0f);
	V4 R = reflect(L, N);
	R.normalize();
	V4 V = -dir;
	V.normalize();
	V3 spec = (light->specular % shape->material->specular) * powf(fmaxf(R * V, 0.0f), shape->material->shininess);
	return dif + spec;
}

bool Scene::isLightVisible(V4 p, Shape* shape, PointLight* light) {
	V4 o = light->pos;
	V4 dir = p - o;
	dir.normalize();
	Shape* firstShape = nullptr;
	float time = 0.0f;
	intersect(o, dir, &firstShape, &time);
	return (time >= 0) && (firstShape == shape);
}

V4 Scene::intersect(V4 o, V4 dir, Shape** shape, float* time) {
	return intersect(nullptr, o, dir, shape, time);
}

V4 Scene::reflect(V4 V, V4 N) {
	return (2 * (V * N) * N - V).normalized();
}

V3 Scene::RayTrace(Shape* curShape, V4 o, V4 dir, size_t depth) {
	V3 col(0.0f);
	Shape *shape = nullptr;
	float time = 0;
	V4 p = intersect(curShape, o, dir, &shape, &time);
	if (time < 0 || shape == nullptr) {
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
	if (depth == 0 || shape->material->reflectivity <= 0.0f) {
		return col;
	}

	V4 reflected = reflect(-dir, shape->getNormal(p));

	col += shape->material->reflectivity * RayTrace(shape, p, reflected, depth - 1);
	return col;
}

V3 Scene::RayTrace(V4 o, V4 dir, size_t depth) {
	return RayTrace(nullptr, o, dir, depth);
}

/*
 * Renders all rows from [start, end)
 */
void Scene::RenderRows(PPC* ppc, FrameBuffer* fb, size_t start, size_t end) {
	for (int v = end - 1; v >= static_cast<int>(start); v--) {
		for (int u = fb->getW() - 1; u >= 0; u--) {
			V3 col = RayTrace(ppc->getC(), ppc->getRay(u, v), maxDepth);
			col.x = fminf(col.x, 1.0f);
			col.y = fminf(col.y, 1.0f);
			col.z = fminf(col.z, 1.0f);
			fb->SetColor(u, v, col);
		}
	}
}

void Scene::RenderRT(PPC *ppc, FrameBuffer* fb) {
	RenderRows(ppc, fb, 0, fb->getH());
}