#include "ppc.h"
#include "M33.h"
#include "framebuffer.h"

PPC::PPC(float hfov, int _w, int _h) {

	w = _w;
	h = _h;
	a = V3(1.0f, 0.0f, 0.0f); // horizontal
	b = V3(0.0f, -1.0f, 0.0f); // vertical
	C = V3(0.0f, 0.0f, 0.0f); // camera
	float hfovRad = hfov * M_PI / 180.0f;
	c = V3(-(float)w / 2.0f, (float)h / 2.0f, -(float)w / (2.0f * tanf(hfovRad / 2.0f)));
	// depth
}

int PPC::Project(V3 P, V3& pP) {
	// 0 point behind head
	// 1 point in front of head

	M33 M;
	M.SetColumn(0, a);
	M.SetColumn(1, b);
	M.SetColumn(2, c);

	M33 Minv = M.Inverted();
	V3 Q = Minv * (P - C);
	if (Q[2] <= 0.0f)
		return 0;

	pP = V3(Q[0] / Q[2], Q[1] / Q[2], 1.0f / Q[2]);
	return 1;

}

int PPC::UnProject(V3 pP, V3& P) {

	if (pP[2] == 0.0f) {
		return 0;
	}

	P = C + (a * pP[0] + b * pP[1] + c) / pP[2];

	return 1;

}

float PPC::GetF() {

	V3 vd = (a ^ b).normalized();
	return c * vd;

}

void PPC::SetF(float f) {
	// want f = c * (a^b)
	c = c * f / GetF();
}

void PPC::SetPose(V3 newC, V3 LaP, V3 upgv) {
	V3 newa, newb, newc;

	V3 newvd = (LaP - newC).normalized();
	newa = (newvd ^ upgv).normalized();
	newb = (newvd ^ newa).normalized();
	float f = GetF();
	newc = newvd * f - newa * (float)(w / 2) - newb * (float)h / 2;

	a = newa;
	b = newb;
	c = newc;
	C = newC;
}

V3 PPC::getPos() {
	return C;
}

V3 PPC::GetVD() {
	return (a ^ b).normalized();
}

V3 PPC::GetPixelCenter(int u, int v) {
	return C + a * (.5f + (float)u) + b * (.5f + (float)v) + c;
}

V3 PPC::GetRay(int u, int v) {
	return (GetPixelCenter(u, v) - C).normalized();
}

V3 PPC::GetRaySubPixel(float fu, float fv) {
	return (a * fu + b * fv + c).normalized();
}

int PPC::getW() {
	return w;
}

int PPC::getH() {
	return h;
}

// Still not perfect, TODO
void PPC::resize(int w, int h) {
	// oldW * oldH = 2 * tan(hfov/2) * oldF
	// oldW * oldH / oldF = 2 * tan(hfov/2) = newW * newH / newF
	// newF = oldF * newW * newH / (oldW * oldH)
	int oldCanvSize = this->w * this->h;
	int newCanvSize = w * h;
	float oldF = GetF();
	this->w = w;
	this->h = h;
	float scaleF = static_cast<float>(newCanvSize) / static_cast<float>(oldCanvSize);
	this->c = GetVD() * GetF() * sqrtf(scaleF) - a * (static_cast<float>(w) / 2) - b * (static_cast<float>(h) / 2);
}