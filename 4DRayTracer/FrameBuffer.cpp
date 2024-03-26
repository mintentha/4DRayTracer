#include "FrameBuffer.h"
#include "V3.h"

#include <tiffio.h>

FrameBuffer::FrameBuffer(unsigned int w, unsigned int h) {
	this->w = w;
	this->h = h;
	pix = new unsigned int[w * h];
}

FrameBuffer::~FrameBuffer() {
	delete[] pix;
}

unsigned int& FrameBuffer::operator[](int i) {
	return pix[i];
}

void FrameBuffer::SetColor(int u, int v, unsigned int col) {
	int uv = (h - 1 - v) * w + u;
	pix[uv] = col;
}

void FrameBuffer::SetColor(int u, int v, V3 col) {
	SetColor(u, v, col.GetColor());
}

unsigned int FrameBuffer::getColor(int u, int v) {
	int uv = (h - 1 - v) * w + u;
	return pix[uv];
}

void FrameBuffer::SaveAsTiff(const char* fname) {

	TIFF* out = TIFFOpen(fname, "w");

	if (out == NULL) {
		std::cerr << fname << " could not be opened" << std::endl;
		return;
	}

	TIFFSetField(out, TIFFTAG_IMAGEWIDTH, w);
	TIFFSetField(out, TIFFTAG_IMAGELENGTH, h);
	TIFFSetField(out, TIFFTAG_SAMPLESPERPIXEL, 4);
	TIFFSetField(out, TIFFTAG_BITSPERSAMPLE, 8);
	TIFFSetField(out, TIFFTAG_ORIENTATION, ORIENTATION_TOPLEFT);
	TIFFSetField(out, TIFFTAG_PLANARCONFIG, PLANARCONFIG_CONTIG);
	TIFFSetField(out, TIFFTAG_PHOTOMETRIC, PHOTOMETRIC_RGB);

	for (uint32 row = 0; row < (unsigned int)h; row++) {
		TIFFWriteScanline(out, &pix[(h - row - 1) * w], row);
	}

	TIFFClose(out);
}