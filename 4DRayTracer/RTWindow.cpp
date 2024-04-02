#include "RTWindow.h"

#include "FrameBuffer.h"
#include "PPC.h"
#include "Scene.h"

#include <glad/gl.h>
#include <GLFW/glfw3.h>

RTWindow::RTWindow(const char* name, int width, int height, float samplesPerPixel, RESIZE_MODE resizeMode, PPC* ppc, Scene* scene) {
	this->resizeMode = resizeMode;
	float sampleRatio = sqrtf(samplesPerPixel);
	this->fbWidth = width * sampleRatio;
	this->fbHeight = height * sampleRatio;
	this->goalNumSamples = width * height * samplesPerPixel;
	this->vpWidth = width;
	this->vpHeight = height;
	this->ppc = ppc;
	this->ppc->resize(fbWidth, fbHeight);
	this->scene = scene;
	this->mousex, this->mousey = 0;
	this->rotIn = false;
	textureID = 0;
	texFBO = 0;
	error = OK;
	isOpen = false;
	fb = new FrameBuffer(fbWidth, fbHeight);
	if (resizeMode == OFF) {
		glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
	}
	else {
		glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);
	}
	window = glfwCreateWindow(vpWidth, vpHeight, name, NULL, NULL);
	if (window == nullptr) {
		error = CREATE_WINDOW;
		return;
	}
	glfwMakeContextCurrent(window);
	int version = gladLoadGL(glfwGetProcAddress);
	if (version == 0) {
		error = LOAD_GL;
		return;
	}
	// Unfortunatley with how GLFW works callback functions have to be static
	// I could change them to static now but then they couldnt really modify the ppc or scene locations
	// I think I can come up with an alternative by just keeping a GLFWWindow* member variable and set that on initialization
	// trying that next
	glfwSetWindowUserPointer(window, this);
	glfwSetKeyCallback(window, kbdCallback);
	glfwSetCursorPosCallback(window, mouseCallback);
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	glfwSetMouseButtonCallback(window, mouseButtonCallback);
	glfwSetScrollCallback(window, scrollCallback);
	glfwSetFramebufferSizeCallback(window, fbSizeCallback);
	if (glfwRawMouseMotionSupported()) {
		glfwSetInputMode(window, GLFW_RAW_MOUSE_MOTION, GLFW_TRUE);
	}
	if (resizeMode == RATIO_LOCKED || resizeMode == SS_RATIO_LOCKED) {
		glfwSetWindowAspectRatio(window, vpWidth, vpHeight);
	}
	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_2D, textureID);
	glGenFramebuffers(1, &texFBO);
	glBindFramebuffer(GL_READ_FRAMEBUFFER, texFBO);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, fbWidth, fbHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, fb->pix);
	glFramebufferTexture2D(GL_READ_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, textureID, 0);
}

RTWindow::~RTWindow() {
	delete fb;
	glfwDestroyWindow(window);
}

/* Static functions */
// We aren't necessarily using all of these callback functions, but it is nice to have them
void RTWindow::kbdCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
	RTWindow* rtw = static_cast<RTWindow*>(glfwGetWindowUserPointer(window));

	switch (action) {
		case GLFW_PRESS:
			if (key == GLFW_KEY_LEFT_SHIFT) {
				rtw->rotIn = true;
			}
			else {
				std::cout << "Pressed: " << key << "\n";
				rtw->ppc->press(key);
			}
			break;
		case GLFW_RELEASE:
			if (key == GLFW_KEY_LEFT_SHIFT) {
				rtw->rotIn = false;
			}
			else {
				std::cout << "Released: " << key << "\n";
				rtw->ppc->release(key);
			}
			break;
	}
}

void RTWindow::mouseCallback(GLFWwindow* window, double x, double y) {
	RTWindow* rtw = static_cast<RTWindow*>(glfwGetWindowUserPointer(window));

	float sens = 0.0002;
	float dx = (x - rtw->mousex) * sens;
	float dy = (y - rtw->mousey) * sens;
	rtw->mousex = x;
	rtw->mousey = y;
	std::cout << "Mouse moved: " << dx << ", " << dy << "\n";

	V4 a = rtw->ppc->geta();
	V4 b = rtw->ppc->getb();
	V4 c = rtw->ppc->getc();
	V4 vd = rtw->ppc->getVD();

	M44 wtocBasis = M44();
	wtocBasis.SetColumn(0, a);
	wtocBasis.SetColumn(1, b);
	wtocBasis.SetColumn(2, c);
	wtocBasis.SetColumn(3, vd);
	M44 ctowBasis = wtocBasis.Inverted();

	a = wtocBasis * a;
	b = wtocBasis * b;
	c = wtocBasis * c;

	M44 rotationMatrix = M44();
	if (rtw->rotIn) {
		rotationMatrix.SetColumn(0, V4(cos(dx), -sin(dx)*sin(dy), 0, -sin(dx)*cos(dy)));
		rotationMatrix.SetColumn(1, V4(0, cos(dy), 0, -sin(dy)));
		rotationMatrix.SetColumn(2, V4(0, 0, 1, 0));
		rotationMatrix.SetColumn(3, V4(sin(dx), cos(dx)*sin(dy), 0, cos(dx)*cos(dy)));
	}
	else {
		rotationMatrix.SetColumn(0, V4(cos(dx), 0, -sin(dx), 0));
		rotationMatrix.SetColumn(1, V4(sin(dx) * sin(dy), cos(dy), cos(dx) * sin(dy), 0));
		rotationMatrix.SetColumn(2, V4(sin(dx) * cos(dy), -sin(dy), cos(dx) * cos(dy), 0));
		rotationMatrix.SetColumn(3, V4(0, 0, 0, 1));
	}

	a = ctowBasis * (rotationMatrix * a);
	b = ctowBasis * (rotationMatrix * b);
	c = ctowBasis * (rotationMatrix * c);

	rtw->ppc->setPose(a, b, c);
}

void RTWindow::mouseButtonCallback(GLFWwindow* window, int button, int state, int mods) {
	RTWindow* rtw = static_cast<RTWindow*>(glfwGetWindowUserPointer(window));
}

void RTWindow::scrollCallback(GLFWwindow* window, double xoffset, double yoffset) {
	RTWindow* rtw = static_cast<RTWindow*>(glfwGetWindowUserPointer(window));
}

void RTWindow::fbSizeCallback(GLFWwindow* window, int width, int height) {
	RTWindow* rtw = static_cast<RTWindow*>(glfwGetWindowUserPointer(window));
	switch (rtw->resizeMode) {
		case SS_RATIO_LOCKED:
		case SS_ARBITRARY:
		case TRUE: {
			float sizeRatio = (width * height) / static_cast<float>(rtw->vpWidth * rtw->vpHeight);
			rtw->goalNumSamples *= sizeRatio;
			// Fallthrough
		}
		case ARBITRARY: {
			float sampleRatio = sqrtf(rtw->goalNumSamples / static_cast<float>(width * height));
			int fbWidth = width * sampleRatio;
			int fbHeight = height * sampleRatio;
			rtw->fb->resize(fbWidth, fbHeight);
			rtw->ppc->resize(fbWidth, fbHeight);
			rtw->fbWidth = fbWidth;
			rtw->fbHeight = fbHeight;
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, fbWidth, fbHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, rtw->fb->pix);
			break;
		}
		// RATIO_LOCKED and OFF need no changes
	}
	rtw->vpWidth = width;
	rtw->vpHeight = height;
}
/********************/

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
	scene->RenderRT(ppc, fb);
	glfwMakeContextCurrent(window);
	glViewport(0, 0, vpWidth, vpHeight);
	glClear(GL_COLOR_BUFFER_BIT);
	glBindTexture(GL_TEXTURE_2D, textureID);
	glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, fbWidth, fbHeight, GL_RGBA, GL_UNSIGNED_BYTE, fb->pix);
	glBindFramebuffer(GL_READ_FRAMEBUFFER, texFBO);
	glFramebufferTexture2D(GL_READ_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, textureID, 0);
	glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
	glBlitFramebuffer(0, 0, fbWidth, fbHeight, 0, 0, vpWidth, vpHeight, GL_COLOR_BUFFER_BIT, GL_LINEAR);
	glfwSwapBuffers(window);
	glfwPollEvents();
}

bool RTWindow::shouldClose() {
	return glfwWindowShouldClose(window);
}