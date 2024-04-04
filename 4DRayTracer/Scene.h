#pragma once

#include "Shape.h"
#include "PPC.h"
#include "FrameBuffer.h"
#include "V3.h"
#include "V4.h"
#include "PointLight.h"

#include <vector>

class Scene {
private:
	std::vector<Shape *> *shapes;
	std::vector<PointLight*>* lights;
	V3 bgrCol;
	V3 ambientCol;
	size_t maxDepth;

	V4 intersect(Shape *curShape, V4 o, V4 dir, Shape **shape, float* time); // Cannot intersect self
	V4 intersect(V4 o, V4 dir, Shape** shape, float* time);
	V4 reflect(V4 V, V4 N);
	bool isLightVisible(V4 p, Shape* shape, PointLight* light);
	V3 phong(Shape* shape, V4 p, V4 dir, PointLight* light);
public:
	Scene(V3 ambientCol, V3 bgrCol, size_t maxDepth, std::vector<Shape *> *shapes, std::vector<PointLight *> *lights);
	Scene(V3 ambientCol, V3 bgrCol, size_t maxDepth) : Scene(ambientCol, bgrCol, maxDepth, new std::vector<Shape *>(), new std::vector<PointLight*>()) {};
	~Scene();

	void AddShape(Shape *shape);
	void AddLight(PointLight* light);

	V3 RayTrace(Shape* curShape, V4 o, V4 dir, size_t depth);
	V3 RayTrace(V4 o, V4 dir, size_t depth);

	void RenderRows(PPC* ppc, FrameBuffer* fb, size_t start, size_t end);
	void RenderRT(PPC *ppc, FrameBuffer* fb);
};