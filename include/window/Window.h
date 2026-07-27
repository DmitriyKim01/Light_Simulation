#pragma once

#include <core/Color.h>
#include <camera/Camera.h>

class Window {
public:
	virtual ~Window() = default;

	virtual void pollEvents() = 0;
	virtual void swapBuffers() = 0;
	virtual void update() = 0;
	virtual bool shouldClose() = 0;
	virtual void shutdown() = 0;
	virtual void processInput() = 0;

	virtual int getWidth() const = 0;
	virtual int getHeight() const = 0;

	virtual void lockCursor() = 0;
	virtual void unlockCursor() = 0;
	
	virtual void setBackgroundColor(const Color& color) = 0;
	virtual void enableDepthBuffer() = 0;
	virtual void disableDepthBuffer() = 0;
	virtual void clearDepthBuffer() = 0;

	virtual void setCamera(Camera& camera) = 0;
};

