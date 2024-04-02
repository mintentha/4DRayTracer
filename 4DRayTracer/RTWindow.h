#pragma once

#include <glad/gl.h>
#include <GLFW/glfw3.h>

#include "FrameBuffer.h"
#include "PPC.h"
#include "Scene.h"

// TODO: possible make the window resizable

class RTWindow {
private:
	float goalNumSamples;
	int fbWidth, fbHeight; // Dimensions of what we're actually rendering
	int vpWidth, vpHeight; // Dimensions of what we're displaying
	int mousex, mousey;
	GLFWwindow* window;
	FrameBuffer* fb;
	GLuint textureID;
	GLuint texFBO;
	bool isOpen, rotIn;
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
	void draw();
	bool shouldClose();
private:
	ERROR error;
	RESIZE_MODE resizeMode;
};