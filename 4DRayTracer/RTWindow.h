#pragma once

#include <glad/gl.h>
#include <GLFW/glfw3.h>

#include "FrameBuffer.h"
#include "PPC.h"
#include "Scene.h"

// TODO: possible make the window resizable

class RTWindow {
private:
	int width, height;
	GLFWwindow* window;
	FrameBuffer* fb;
	GLuint textureID;
	GLuint texFBO;
	bool isOpen;
	// both of these are temporary, later refactor PPC to exist in 4D space. Also add rotation matrices
	// For now this just helps with controlling the tanslation, which can be done in kbdCallback
	float ow; // w component of ray origin
	float dw; // w component of ray direction
	// callback functions
	void kbdCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
	void mouseCallback(GLFWwindow* window, double x, double y);
	void mouseButtonCallback(GLFWwindow* window, int button, int state, int mods);
public:
	static enum ERROR {
		OK,
		CREATE_WINDOW,
		LOAD_GL
	};
	PPC* ppc;
	Scene* scene;
	RTWindow(const char* name, int width, int height, PPC* ppc, Scene* scene);
	RTWindow(int width, int height, PPC* ppc, Scene* scene) : RTWindow("4D Ray Tracer", width, height, ppc, scene) {};
	~RTWindow();
	ERROR hasError();
	void show();
	void hide();
	bool isShown();
	void draw();
	bool shouldClose();
private:
	ERROR error;
};