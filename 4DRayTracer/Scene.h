#pragma once

#include "FrameBuffer.h"
#include "Shape.h"
#include "PPC.h"
#include "PointLight.h"

#include <vector>

class Scene {
private:
	FrameBuffer *fb;
	PPC *ppc;
	std::vector<Shape *> *shapes;
	std::vector<PointLight *> *lights;
	V3 ambientCol;
	V3 bgrCol; // background color
	size_t maxDepth;

	V3 intersect(V3 o, V3 dir, Shape **shape, float *time);
	V3 intersect(Shape *curShape, V3 o, V3 dir, Shape **shape, float* time);
	bool isLightVisible(V3 p, Shape* shape, PointLight* light);
	V3 reflect(V3 V, V3 N);
	V3 phong(Shape *shape, V3 p, V3 dir, PointLight *light);

public:
	Scene(FrameBuffer* fb, PPC* ppc, V3 ambientCol, V3 bgrCol, size_t maxDepth);
	Scene(FrameBuffer* fb, PPC* ppc, V3 ambientCol, V3 bgrCol, size_t maxDepth, std::vector<Shape *> *shapes, std::vector<PointLight *> *lights);
	~Scene();

	void AddShape(Shape *shape);
	void AddLight(PointLight *light);
	void RenderRT();

	void SaveAsTIFF(const char *filename);

	V3 RayTrace(Shape *curShape, V3 o, V3 dir, size_t depth);
	V3 RayTrace(V3 o, V3 dir, size_t depth);
};