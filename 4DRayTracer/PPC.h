#pragma once

#include "V3.h"

// For now, for the sake of immediate testing results, PPC is actually only in 3D space
// And while raytracing we will give it a constant depth
// Later on it can be adapted to be a 2D projection plane in 4D space
// That just will take some math to figure out how to best accomplish that

class PPC {
public:
	V3 a, b, c, C;
	int w, h;
	PPC(float hfov, int _w, int _h);
	int Project(V3 P, V3& pP);
	int UnProject(V3 pP, V3& P);
	void SetPose(V3 newC, V3 LaP, V3 upgv);
	float GetF();
	int getW();
	int getH();
	void SetF(float f);
	V3 GetVD();
	V3 getPos();
	V3 GetPixelCenter(int u, int v);
	V3 GetRay(int u, int v);
	V3 GetRaySubPixel(float fu, float fv);
};