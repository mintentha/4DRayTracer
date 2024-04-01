#pragma once

#include "Shape.h"
#include "PPC.h"
#include "FrameBuffer.h"
#include "V3.h"
#include "V4.h"

#include <vector>

class Scene {
private:
	std::vector<Shape *> *shapes;
	V3 bgrCol;
	size_t maxDepth;

	V4 intersect(Shape *curShape, V4 o, V4 dir, Shape **shape, float* time); // Cannot intersect self
	V4 intersect(V4 o, V4 dir, Shape** shape, float* time);
public:
	Scene(V3 bgrCol, size_t maxDepth, std::vector<Shape *> *shapes);
	Scene(V3 bgrCol, size_t maxDepth) : Scene(bgrCol, maxDepth, new std::vector<Shape *>()) {};
	~Scene();

	void AddShape(Shape *shape);

	V3 RayTrace(Shape* curShape, V4 o, V4 dir, size_t depth);
	V3 RayTrace(V4 o, V4 dir, size_t depth);

	void RenderRT(PPC *ppc, FrameBuffer* fb, float ow, float dw);
};