#pragma once

#include "V3.h"
class FrameBuffer {
private:
	unsigned int w;
	unsigned int h;
	unsigned int* pix;
	unsigned int& operator[](int i);

public:
	FrameBuffer(unsigned int w, unsigned int h);
	~FrameBuffer();

	void SetColor(int u, int v, unsigned int col);
	void SetColor(int u, int v, V3 col);
	unsigned int getColor(int u, int v);

	unsigned int getW() {
		return w;
	}

	unsigned int getH() {
		return h;
	}
	void SaveAsTiff(const char* fname);
};