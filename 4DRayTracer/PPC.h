#pragma once

#include "V4.h"
#include "M44.h"

class PPC {
private:
	V4 a; // Right direction;
	V4 b; // Up direction
	V4 c; // Ana direction
	// in 3d, we know that vd() (forward) is just a ^ b
	// in 4d, we would either need to specify a forward direction, or an ana direction
	// I chose to track ana
	V4 d; // Points to top left of projection plane
	V4 C; // Camera position
	int w; // Width of projection plane
	int h; // Height of projection plane
	float left, right, back, front, down, up, out, in;
public:
	PPC(float hfov, int w, int h);

	/*
	* Havent implemented these, we dont really need them.
	* For the 3d PPC these were leftover from a projection-based renderer
	// p - point, pP - pointer to projected Point. Returns true if point in front of camera
	bool project(V4 p, V4* pP);
	bool unproject(V4 p, V4* P);
	*/

	V4 getC(); // Get Camera Center
	V4 getVD(); // Get view direction (i.e. forward)
	float getF(); // Get focal length
	void setF(float f);
	void setPose(V4 C, V4 LaP, V4 upV, V4 anaV);
	V4 getRay(int u, int v);
	V4 getRaySubPixel(float fu, float fv);
	V4 getPixelCenter(int u, int v);
	V4 getSubPixelPoint(float fu, float fv);
	void resize(int w, int h);
	void press(int key);
	void release(int key);
	void updateC();
};