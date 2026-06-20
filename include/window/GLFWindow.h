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

	float m_deltaTime = 0.0f;
	float m_lastFrame = 0.0f;

	std::string m_title;
	
	void init();
	void setGLFWHints();
	static int validateDimension(int value, const std::string& name);
	static void framebuffer_size_callback(GLFWwindow* window, int width, int height);

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
	void processInput(Camera& camera) override;

	void lockCursor() override;
	void unlockCursor() override;

	void setBackgroundColor(const Color& color) override;

	int getWidth()	const override;
	int getHeight() const override;

};