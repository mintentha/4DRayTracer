#pragma once

#include "FrameBuffer.h"
#include "PPC.h"
#include "Scene.h"
#include "defines.h"

#include <glad/gl.h>
#include <GLFW/glfw3.h>

#include <thread>
#include <mutex>

class RTWindow {
private:
	float goalNumSamples;
	int width, height; // Dimensions of what we're displaying
	GLFWwindow* window;
	FrameBuffer* frontfb;
	FrameBuffer* backfb;
	GLuint textureID;
	GLuint texFBO;
	bool isOpen;

	static enum POSNEG {
		POS,
		NEG,
		POSNEGSIZE
	};
	bool isPressedDir[AXES_PLANES::AXIS_SIZE][POSNEGSIZE];
	bool isPressedRot[AXES_PLANES::AXIS_SIZE][POSNEGSIZE];
	double timePressedDir[AXES_PLANES::AXIS_SIZE][POSNEGSIZE];
	double timePressedRot[AXES_PLANES::PLANE_SIZE][POSNEGSIZE];
	float deltadir[AXES_PLANES::AXIS_SIZE];		// Changes in translation since last frame
	float deltatheta[AXES_PLANES::PLANE_SIZE];	// Changes in rotation since last frame
	std::mutex buttonLock;

	std::mutex bufferLock;
	std::mutex sizeLock;
	std::thread renderThread;

	int backfbWidth, backfbHeight;
	bool hasSwapped;
	bool reallocTex;

	void renderBackBuffer();
	void swapBuffers();

	std::thread cluster[NUM_THREADS];
	std::mutex clusterLock;
	std::condition_variable cv;
	bool clusterIsReady;
	size_t clusterNumCompleted;

	void renderSection(size_t ind);

	// both of these are temporary, later refactor PPC to exist in 4D space. Also add rotation matrices
	// For now this just helps with controlling the tanslation, which can be done in kbdCallback
	// callback functions
	static void kbdCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
	static void mouseCallback(GLFWwindow* window, double x, double y);
	static void mouseButtonCallback(GLFWwindow* window, int button, int state, int mods);
	static void scrollCallback(GLFWwindow* window, double xoffset, double yoffset);
	static void fbSizeCallback(GLFWwindow* window, int width, int height);
public:
	static enum ERROR {
		OK,
		CREATE_WINDOW,
		LOAD_GL
	};
	static enum RESIZE_MODE {
		OFF,				// Do not allow resizing of the window at all
		RATIO_LOCKED,		// Allow resizing but the aspect ratio is locked. Same number of total samples
		SS_RATIO_LOCKED,	// Allow resizing but the aspect ratio is locked. Same number of samples per pixel
		ARBITRARY,			// Allow resizing window without restriction. Same number of total samples
		SS_ARBITRARY,		// Allow resizing window without restriction. Same number of samples per pixel
		TRUE,				// Same as SS_ARBITRARY
	};
	PPC* ppc;
	Scene* scene;
	RTWindow(const char* name, int width, int height, float samplesPerPixel, RESIZE_MODE resizeMode, PPC* ppc, Scene* scene);
	RTWindow(const char* name, int width, int height, RESIZE_MODE resizeMode, PPC* ppc, Scene* scene) : RTWindow(name, width, height, 1, resizeMode, ppc, scene) {};
	RTWindow(const char* name, int width, int height, float samplesPerPixel, PPC* ppc, Scene* scene) : RTWindow(name, width, height, samplesPerPixel, OFF, ppc, scene) {};
	RTWindow(const char* name, int width, int height, PPC* ppc, Scene* scene) : RTWindow(name, width, height, 1, OFF, ppc, scene) {};
	RTWindow(int width, int height, float samplesPerPixel, RESIZE_MODE resizeMode, PPC* ppc, Scene* scene) : RTWindow("4D Ray Tracer", width, height, samplesPerPixel, resizeMode, ppc, scene) {};
	RTWindow(int width, int height, RESIZE_MODE resizeMode, PPC* ppc, Scene* scene) : RTWindow("4D Ray Tracer", width, height, 1, resizeMode, ppc, scene) {};
	RTWindow(int width, int height, float samplesPerPixel, PPC* ppc, Scene* scene) : RTWindow("4D Ray Tracer", width, height, samplesPerPixel, OFF, ppc, scene) {};
	RTWindow(int width, int height, PPC* ppc, Scene* scene) : RTWindow("4D Ray Tracer", width, height, 1, OFF, ppc, scene) {};
	~RTWindow();
	ERROR hasError();
	void show();
	void hide();
	bool isShown();
	bool shouldClose();
	bool draw();
private:
	ERROR error;
	RESIZE_MODE resizeMode;
};