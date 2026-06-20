#pragma once

#include <core/Color.h>
#include <camera/Camera.h>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
class Window {
public:
	virtual ~Window() = default;

	virtual void pollEvents() = 0;
	virtual void swapBuffers() = 0;
	virtual void update() = 0;
	virtual bool shouldClose() = 0;
	virtual void shutdown() = 0;
	virtual void processInput(Camera& camera) = 0;

	virtual int getWidth() const = 0;
	virtual int getHeight() const = 0;

	virtual void lockCursor() = 0;
	virtual void unlockCursor() = 0;
	
	virtual void setBackgroundColor(const Color& color) = 0;
	
	GLFWwindow* m_window = nullptr;
};

