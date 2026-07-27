#pragma once

#include <core/Color.h>
#include <window/Window.h>
#include <camera/Camera.h>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <string>

class GLFWindow : public Window {
private:
	int m_width;
	int m_height;

	double m_deltaTime = 0.0f;
	double m_lastFrame = 0.0f;

	std::string m_title;

	GLFWwindow* m_window = nullptr;
	Camera* m_camera = nullptr;
	
	float m_lastX;
	float m_lastY;
	bool m_firstMouse = true;

private:
	void init();

	void setGLFWHints();
	static int validateDimension(int value, const std::string& name);
	static void framebuffer_size_callback(GLFWwindow* window, int width, int height);

	void handleMouseMove(double xposIn, double yposIn);
	void handleScroll(double xoffset, double yoffset);

	static void mouseCallback(GLFWwindow* window, double xpos, double ypos);
	static void scrollCallback(GLFWwindow* window, double xoffset, double yoffset);

public:
	struct Defaults {
		static constexpr int WIDTH = 1920;
		static constexpr int HEIGHT = 1080;
		static constexpr const char* TITLE = "OpenGL Window";
		static constexpr int         GL_MAJOR = 3;
		static constexpr int         GL_MINOR = 3;
	};

	GLFWindow();
	GLFWindow(int width, int height);
	GLFWindow(int width, int height, const std::string& title);
	~GLFWindow();

	void pollEvents()		override;
	void swapBuffers()		override;
	void update() 		override;
	bool shouldClose()	override;
	void shutdown() 	override;
	void processInput() override;

	void lockCursor() override;
	void unlockCursor() override;

	void setBackgroundColor(const Color& color) override;
	void enableDepthBuffer() override;
	void disableDepthBuffer() override;
	void clearDepthBuffer() override;

	int getWidth()	const override;
	int getHeight() const override;

	void setCamera(Camera& camera) override;

};