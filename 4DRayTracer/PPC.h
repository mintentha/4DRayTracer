#pragma once

#include "V3.h"

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