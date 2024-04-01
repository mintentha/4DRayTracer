#pragma once

#include "V3.h"
class FrameBuffer {
private:
	unsigned int w;
	unsigned int h;
public:
	unsigned int* pix;
	unsigned int& operator[](int i);
	FrameBuffer(unsigned int w, unsigned int h);
	~FrameBuffer();

	void SetColor(int u, int v, unsigned int col);
	void SetColor(int u, int v, V3 col);
	unsigned int getColor(int u, int v);
	unsigned int getW();
	unsigned int getH();
	void resize(int w, int h); // does not keep data
	void SaveAsTiff(const char* fname);
};