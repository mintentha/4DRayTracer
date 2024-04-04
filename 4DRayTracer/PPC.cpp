#include "PPC.h"
#include "V4.h"
#include "M44.h"
#include <GLFW/glfw3.h>

PPC::PPC(float hfov, int w, int h) {
	this->w = w;
	this->h = h;
	a = V4(1.0f, 0.0f, 0.0f, 0.0f);
	b = V4(0.0f, -1.0f, 0.0f, 0.0f);
	c = V4(0.0f, 0.0f, 0.0f, 1.0f);
	C = V4(0.0f);
	float hfovRad = hfov * M_PI / 180.0f;
	float fw = static_cast<float>(w);
	float fh = static_cast<float>(h);
	d = V4(-fw / 2.0f, fh / 2.0f, fw / (2.0f * tanf(hfovRad / 2.0f)), 0.0f);
}

V4 PPC::geta() {
	return a.normalize();
}

V4 PPC::getb() {
	return b.normalize();
}

V4 PPC::getc() {
	return c.normalize();
}

V4 PPC::getC() {
	return C;
}

V4 PPC::getVD() {
	// b is negative because b is down instead of up
	// (I would make b down but pixels on screen start at top left)
	return (a ^ -b ^ c).normalize();
}

float PPC::getF() {
	return d * getVD();
}

void PPC::setF(float f) {
	d *= f / getF();
}

void PPC::setPose(V4 C, V4 LaP, V4 upV, V4 anaV) {
	V4 newVd = LaP - C;
	newVd.normalize();
	// y ^ z ^ w
	V4 newa = upV ^ newVd ^ anaV;
	newa.normalize();
	// x ^ z ^ w
	V4 newb = newa ^ newVd ^ anaV;
	newb.normalize();
	// x ^ y ^ z
	V4 newc = newa ^ newb ^ newVd;
	newc.normalize();

	V4 newd = newVd * getF() - newa * static_cast<float>(w) / 2.0f - newb * static_cast<float>(h) / 2.0f;
	a = newa;
	b = newb;
	c = newc;
	d = newd;
	this->C = c;
}

void PPC::setPose(V4 _a, V4 _b, V4 _c) {
	a = _a.normalized();
	b = _b.normalized();
	c = _c.normalized();
	V4 vd = (a ^ b ^ c).normalized();
	d = vd * getF() - a * static_cast<float>(w) / 2.0f - b * static_cast<float>(h) / 2.0f;
}

V4 PPC::getRay(int u, int v) {
	return getRaySubPixel(static_cast<float>(u) + 0.5f, static_cast<float>(v) + 0.5f);
}

V4 PPC::getRaySubPixel(float fu, float fv) {
	return (d + a * fu + b * fv/* + c * (fu + fv) / 10*/).normalize();
}

V4 PPC::getPixelCenter(int u, int v) {
	return getSubPixelPoint(static_cast<float>(u) + 0.5f, static_cast<float>(v) + 0.5f);
}

V4 PPC::getSubPixelPoint(float fu, float fv) {
	return C + d + a * fu + b * fv;
}

void PPC::resize(int w, int h) {
	int oldCanvSize = this->w * this->h;
	int newCanvSize = w * h;
	float oldF = getF();
	this->w = w;
	this->h = h;
	float scaleF = static_cast<float>(newCanvSize) / static_cast<float>(oldCanvSize);
	this->d = getVD() * getF() * sqrtf(scaleF) - a * (static_cast<float>(w) / 2) - b * (static_cast<float>(h) / 2);
}

void PPC::press(int key) {
	switch (key) {
		case GLFW_KEY_A:
			this->left = true;
			break;
		case GLFW_KEY_D:
			this->right = true;
			break;
		case GLFW_KEY_W:
			this->front = true;
			break;
		case GLFW_KEY_S:
			this->back = true;
			break;
		case GLFW_KEY_SPACE:
			this->up = true;
			break;
		case GLFW_KEY_LEFT_CONTROL:
			this->down = true;
			break;
		case GLFW_KEY_Q:
			this->in = true;
			break;
		case GLFW_KEY_E:
			this->out = true;
			break;
	}
}

void PPC::release(int key) {
	switch (key) {
		case GLFW_KEY_A:
			this->left = false;
			break;
		case GLFW_KEY_D:
			this->right = false;
			break;
		case GLFW_KEY_W:
			this->front = false;
			break;
		case GLFW_KEY_S:
			this->back = false;
			break;
		case GLFW_KEY_SPACE:
			this->up = false;
			break;
		case GLFW_KEY_LEFT_CONTROL:
			this->down = false;
			break;
		case GLFW_KEY_Q:
			this->in = false;
			break;
		case GLFW_KEY_E:
			this->out = false;
			break;
	}
}

void PPC::updateC() {
	//std::cout << this->left << this->right << this->front << this->back << this->up << this->down << this->in << this->out << "\n";

	V4 mov = V4(0.0f);
	if (this->left && !this->right) {
		mov.x -= 0.5f;
	}
	if (this->right && !this->left) {
		mov.x += 0.5f;
	}
	if (this->down && !this->up) {
		mov.y += 0.5f;
	}
	if (this->up && !this->down) {
		mov.y -= 0.5f;
	}
	if (this->back && !this->front) {
		mov.z -= 0.5f;
	}
	if (this->front && !this->back) {
		mov.z += 0.5f;
	}
	if (this->out && !this->in) {
		mov.w -= 0.5f;
	}
	if (this->in && !this->out) {
		mov.w += 0.5f;
	}

	this->C += mov.z * getVD();
	this->C += mov.x * a;
	this->C += mov.y * b;
	this->C += mov.w * c;
}