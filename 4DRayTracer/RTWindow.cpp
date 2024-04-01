#include "RTWindow.h"

#include "FrameBuffer.h"
#include "PPC.h"
#include "Scene.h"

#include <glad/gl.h>
#include <GLFW/glfw3.h>

RTWindow::RTWindow(const char* name, int width, int height, PPC* ppc, Scene* scene) {
	this->width = width;
	this->height = height;
	this->ppc = ppc;
	this->scene = scene;
	textureID = 0;
	texFBO = 0;
	error = OK;
	isOpen = false;
	fb = new FrameBuffer(width, height);
	window = glfwCreateWindow(width, height, name, NULL, NULL);
	if (window == nullptr) {
		error = CREATE_WINDOW;
		return;
	}
	glfwMakeContextCurrent(window);
	int version = gladLoadGL(glfwGetProcAddress);
	if (version == 0) {
		error = LOAD_GL;
	}
	// Unfortunatley with how GLFW works callback functions have to be static
	// I could change them to static now but then they couldnt really modify the ppc or scene locations
	// I think I can come up with an alternative by just keeping a GLFWWindow* member variable and set that on initialization
	// trying that next
	//glfwSetKeyCallback(window, kbdCallback);
	//glfwSetCursorPosCallback(window, mouseCallback);
	//glfwSetMouseButtonCallback(window, mouseButtonCallback);
	glViewport(0, 0, width, height);
	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_2D, textureID);
	glGenFramebuffers(1, &texFBO);
	glBindFramebuffer(GL_READ_FRAMEBUFFER, texFBO);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, fb->pix);
	glFramebufferTexture2D(GL_READ_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, textureID, 0);
}

RTWindow::~RTWindow() {
	delete fb;
	glfwDestroyWindow(window);
}

void RTWindow::kbdCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {

}

void RTWindow::mouseCallback(GLFWwindow* window, double x, double y) {

}

void RTWindow::mouseButtonCallback(GLFWwindow* window, int button, int state, int mods) {

}

RTWindow::ERROR RTWindow::hasError() {
	return error;
}

void RTWindow::show() {
	glfwShowWindow(window);
	isOpen = true;
}

void RTWindow::hide() {
	glfwHideWindow(window);
	isOpen = false;
}

bool RTWindow::isShown() {
	return isOpen;
}

void RTWindow::draw() {
	scene->RenderRT(ppc, fb, ow, dw);
	glfwMakeContextCurrent(window);
	glClear(GL_COLOR_BUFFER_BIT);
	glBindTexture(GL_TEXTURE_2D, textureID);
	glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, width, height, GL_RGBA, GL_UNSIGNED_BYTE, fb->pix);
	glBindFramebuffer(GL_READ_FRAMEBUFFER, texFBO);
	glFramebufferTexture2D(GL_READ_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, textureID, 0);
	glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
	glBlitFramebuffer(0, 0, width, height, 0, 0, width, height, GL_COLOR_BUFFER_BIT, GL_NEAREST);
	glfwSwapBuffers(window);
	glfwPollEvents();
}

bool RTWindow::shouldClose() {
	return glfwWindowShouldClose(window);
}