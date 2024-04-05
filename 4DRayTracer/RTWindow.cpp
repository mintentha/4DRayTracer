#include "RTWindow.h"

#include "FrameBuffer.h"
#include "PPC.h"
#include "Scene.h"

#include <glad/gl.h>
#include <GLFW/glfw3.h>

RTWindow::RTWindow(const char* name, int width, int height, float samplesPerPixel, RESIZE_MODE resizeMode, PPC* ppc, Scene* scene) {
	this->resizeMode = resizeMode;
	float sampleRatio = sqrtf(samplesPerPixel);
	int fbWidth = width * sampleRatio;
	int fbHeight = height * sampleRatio;
	this->backfbWidth = fbWidth;
	this->backfbHeight = fbHeight;
	this->goalNumSamples = width * height * samplesPerPixel;
	this->width = width;
	this->height = height;
	this->ppc = ppc;
	this->ppc->resize(fbWidth, fbHeight);
	this->scene = scene;
	textureID = 0;
	texFBO = 0;
	error = OK;
	isOpen = false;
	hasSwapped = false;
	reallocTex = true;
	clusterIsReady = false;
	clusterNumCompleted = 0;
	frontfb = new FrameBuffer(fbWidth, fbHeight);
	backfb = new FrameBuffer(fbWidth, fbHeight);
	if (resizeMode == OFF) {
		glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
	}
	else {
		glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);
	}
	window = glfwCreateWindow(width, height, name, NULL, NULL);
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
	//glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	glfwSetMouseButtonCallback(window, mouseButtonCallback);
	glfwSetScrollCallback(window, scrollCallback);
	glfwSetFramebufferSizeCallback(window, fbSizeCallback);
	if (glfwRawMouseMotionSupported()) {
		glfwSetInputMode(window, GLFW_RAW_MOUSE_MOTION, GLFW_TRUE);
	}
	if (resizeMode == RATIO_LOCKED || resizeMode == SS_RATIO_LOCKED) {
		glfwSetWindowAspectRatio(window, width, height);
	}
	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_2D, textureID);
	glGenFramebuffers(1, &texFBO);
	glBindFramebuffer(GL_READ_FRAMEBUFFER, texFBO);
	glFramebufferTexture2D(GL_READ_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, textureID, 0);
	renderThread = std::thread(&RTWindow::renderBackBuffer, this);
	for (size_t i = 0; i < NUM_THREADS; ++i) {
		cluster[i] = std::thread(&RTWindow::renderSection, this, i);
	}
}

RTWindow::~RTWindow() {
	delete frontfb;
	delete backfb;
	glfwSetWindowShouldClose(window, true);
	renderThread.join();
	for (size_t i = 0; i < NUM_THREADS; i++) {
		cluster[i].join();
	}
	glfwDestroyWindow(window);
}

/* Static functions */
// We aren't necessarily using all of these callback functions, but it is nice to have them
void RTWindow::kbdCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
	RTWindow* rtw = static_cast<RTWindow*>(glfwGetWindowUserPointer(window));
	double time = glfwGetTime();
	using namespace AXES_PLANES;
	AXIS axis = AXIS_X;
	POSNEG pn = POS;
	switch (key) {
		case GLFW_KEY_A:
			axis = AXIS_X;
			pn = NEG;
			break;
		case GLFW_KEY_D:
			axis = AXIS_X;
			pn = POS;
			break;
		case GLFW_KEY_W:
			axis = AXIS_Z;
			pn = POS;
			break;
		case GLFW_KEY_S:
			axis = AXIS_Z;
			pn = NEG;
			break;
		case GLFW_KEY_SPACE:
			axis = AXIS_Y;
			pn = POS;
			break;
		case GLFW_KEY_LEFT_CONTROL:
			axis = AXIS_Y;
			pn = NEG;
			break;
		case GLFW_KEY_Q:
			axis = AXIS_W;
			pn = POS;
			break;
		case GLFW_KEY_E:
			axis = AXIS_W;
			pn = NEG;
			break;
		default:
			return;
	}
	switch (action) {
		case GLFW_PRESS:
			rtw->buttonLock.lock();
			rtw->timePressedDir[axis][pn] = time;
			rtw->isPressedDir[axis][pn] = true;
			rtw->buttonLock.unlock();
			break;
		case GLFW_RELEASE:
			rtw->buttonLock.lock();
			float deltaTime = time - rtw->timePressedDir[axis][pn];
			if (pn == NEG) {
				deltaTime *= -1.0f;
			}
			rtw->deltadir[axis] += deltaTime * TRANSLATION_SPEED;
			rtw->isPressedDir[axis][pn] = false;
			rtw->buttonLock.unlock();
			break;
	}
}

void RTWindow::mouseCallback(GLFWwindow* window, double x, double y) {
	RTWindow* rtw = static_cast<RTWindow*>(glfwGetWindowUserPointer(window));

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
			float sizeRatio = (width * height) / static_cast<float>(rtw->width * rtw->height);
			rtw->goalNumSamples *= sizeRatio;
			// Fallthrough
		}
		case ARBITRARY: {
			float sampleRatio = sqrtf(rtw->goalNumSamples / static_cast<float>(width * height));
			rtw->backfbWidth = width * sampleRatio;
			rtw->backfbHeight = height * sampleRatio;
			break;
		}
		// RATIO_LOCKED and OFF need no changes
	}
	rtw->width = width;
	rtw->height = height;
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

/*
 * Does the work to calculate all pixels in this section of the display
 */
void RTWindow::renderSection(size_t ind) {
	while (!shouldClose()) {
		{
			std::unique_lock<std::mutex> lock(clusterLock);
			cv.wait(lock, [this] { return clusterIsReady; }); // Wait until signaled by primary thread
		}
		size_t rowsPerSection = backfb->getH() / NUM_THREADS;
		size_t start = rowsPerSection * ind;
		size_t end = rowsPerSection + start;

		// divide the remainder among the last ones
		size_t remainder = backfb->getH() % NUM_THREADS;
		size_t distFromEnd = NUM_THREADS - ind - 1;
		if (distFromEnd < remainder) {
			size_t offset = remainder - distFromEnd;
			start += offset - 1;
			end += offset;
		}

		scene->RenderRows(ppc, backfb, start, end);
		{
			std::unique_lock<std::mutex> lock(clusterLock);
			++clusterNumCompleted;
			clusterIsReady = false;
			cv.notify_all();
		}
	}
}

void RTWindow::renderBackBuffer() {
	while (!shouldClose()) {
		int fbWidth, fbHeight;
		bool changeFBSize;
		sizeLock.lock();
		fbWidth = backfbWidth;
		fbHeight = backfbHeight;
		sizeLock.unlock();
		changeFBSize = (backfb->getW() != fbWidth) || (backfb->getH() != fbHeight);
		if (changeFBSize) {
			ppc->resize(fbWidth, fbHeight);
			backfb->resize(fbWidth, fbHeight);
		}
		buttonLock.lock();
		double time = glfwGetTime();	// Is this safe to run on a separate thread?
		for (size_t axis = 0; axis < AXES_PLANES::AXIS_SIZE; axis++) {
			if (isPressedDir[axis][POS]) {
				float deltaTime = time - timePressedDir[axis][POS];
				timePressedDir[axis][POS] = time;
				deltadir[axis] += deltaTime * TRANSLATION_SPEED;
			}
			if (isPressedDir[axis][NEG]) {
				float deltaTime = time - timePressedDir[axis][NEG];
				timePressedDir[axis][NEG] = time;
				deltadir[axis] -= deltaTime * TRANSLATION_SPEED;
			}
			if (deltadir[axis] != 0.0f) {
				ppc->translate(static_cast<AXES_PLANES::AXIS>(axis), deltadir[axis]);
				deltadir[axis] = 0.0f;
			}
		}
		buttonLock.unlock();
		{
			std::unique_lock<std::mutex> lock(clusterLock);
			clusterIsReady = true;
			cv.notify_all();
		}
		//scene->RenderRT(ppc, backfb);
		{
			std::unique_lock<std::mutex> lock(clusterLock);
			cv.wait(lock, [this] { return clusterNumCompleted == NUM_THREADS; });
			clusterNumCompleted = 0;
		}

		bufferLock.lock();
		swapBuffers();
		if (changeFBSize) {
			reallocTex = true;
		}
		hasSwapped = true;
		bufferLock.unlock();
		backfb->resize(frontfb->getW(), frontfb->getH());
		// We don't need to lock around this because we know the only time we ever resize the framebuffer is within this same thread
		// We could just not resize this yet and save it for the next loop, but then we would end up reallocating the texture twice
	}
}

void RTWindow::swapBuffers() {
	FrameBuffer* temp = frontfb;
	frontfb = backfb;
	backfb = temp;
}

/*
 * Returns true if a new frame was rendered.
 */
bool RTWindow::draw() {
	int fbWidth, fbHeight;
	bool shouldUpdate;
	bufferLock.lock();
	shouldUpdate = hasSwapped;
	hasSwapped = false;
	if (shouldUpdate) {
		fbWidth = frontfb->getW();
		fbHeight = frontfb->getH();
		if (reallocTex) {
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, fbWidth, fbHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, frontfb->pix);
		}
		else {
			glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, fbWidth, fbHeight, GL_RGBA, GL_UNSIGNED_BYTE, frontfb->pix);
		}
	}
	bufferLock.unlock();
	if (shouldUpdate) {
		glfwMakeContextCurrent(window);
		glViewport(0, 0, width, height);
		glClear(GL_COLOR_BUFFER_BIT);
		glBindTexture(GL_TEXTURE_2D, textureID);
		glBindFramebuffer(GL_READ_FRAMEBUFFER, texFBO);
		glFramebufferTexture2D(GL_READ_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, textureID, 0);
		glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
		glBlitFramebuffer(0, 0, fbWidth, fbHeight, 0, 0, width, height, GL_COLOR_BUFFER_BIT, GL_LINEAR);
		glfwSwapBuffers(window);
	}
	glfwPollEvents();
	return shouldUpdate;
}

bool RTWindow::shouldClose() {
	return glfwWindowShouldClose(window);
}