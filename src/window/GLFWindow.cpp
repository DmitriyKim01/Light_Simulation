
#include <core/Color.h>
#include <window/GLFWindow.h>
#include <camera/Camera.h>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <stdexcept>
#include <iostream>

int GLFWindow::validateDimension(int value, const std::string& name)
{
	if (value <= 0)
		throw std::invalid_argument(name + " must be a positive integer.");

	return value;
}

// Constructors ==========================================

GLFWindow::GLFWindow()
	: m_width(Defaults::WIDTH), m_height(Defaults::HEIGHT), m_title(Defaults::TITLE)
{
	init();
}

GLFWindow::GLFWindow(int width, int height)
	: m_width(validateDimension(width, "width")),
	m_height(validateDimension(height, "height")),
	m_title(Defaults::TITLE)
{
	init();
}

GLFWindow::GLFWindow(int width, int height, const std::string& title)
	: m_width(validateDimension(width, "width")),
	m_height(validateDimension(height, "height")),
	m_title(title)
{
	init();
}

void GLFWindow::shutdown()
{
	if (m_window)
	{
		glfwDestroyWindow(m_window);
		m_window = nullptr;
	}
	glfwTerminate();
}

GLFWindow::~GLFWindow()
{
	shutdown();
}

// IWindow Interface Implementation =====================

void GLFWindow::init()
{
	if (!glfwInit())
		throw std::runtime_error("OpenGLWindow: glfwInit() failed");

	setGLFWHints();

	m_window = glfwCreateWindow(m_width, m_height, m_title.c_str(), nullptr, nullptr);

	if (!m_window)
	{
		glfwTerminate();
		throw std::runtime_error("OpenGLWindow: glfwCreateWindow() failed");
	}
	glfwMakeContextCurrent(m_window);
	glfwSetFramebufferSizeCallback(m_window, framebuffer_size_callback);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
		throw std::runtime_error("OpenGLWindow: gladLoadGLLoader() failed");

	// Keep stored dimensions in sync if GLFW adjusted them
	glfwGetFramebufferSize(m_window, &m_width, &m_height);
	glViewport(0, 0, m_width, m_height);
}

void GLFWindow::pollEvents()
{
	glfwPollEvents();
}

void GLFWindow::swapBuffers()
{
	glfwSwapBuffers(m_window);
}

bool GLFWindow::shouldClose()
{
	return glfwWindowShouldClose(m_window);
}

int GLFWindow::getWidth()  const { return m_width; }
int GLFWindow::getHeight() const { return m_height; }

void GLFWindow::setGLFWHints()
{
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, Defaults::GL_MAJOR);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, Defaults::GL_MINOR);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);  // required on macOS
#endif
	glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);
}

void GLFWindow::framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

void::GLFWindow::update()
{
	float currentFrame = glfwGetTime();
	m_deltaTime = currentFrame - m_lastFrame;
	m_lastFrame = currentFrame;

	swapBuffers();
	pollEvents();
}

void GLFWindow::processInput(Camera& camera)
{

	if (glfwGetKey(m_window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(m_window, true);

	if (glfwGetKey(m_window, GLFW_KEY_W) == GLFW_PRESS)
		camera.ProcessKeyboard(FORWARD, m_deltaTime);
	if (glfwGetKey(m_window, GLFW_KEY_S) == GLFW_PRESS)
		camera.ProcessKeyboard(BACKWARD, m_deltaTime);
	if (glfwGetKey(m_window, GLFW_KEY_A) == GLFW_PRESS)
		camera.ProcessKeyboard(LEFT, m_deltaTime);
	if (glfwGetKey(m_window, GLFW_KEY_D) == GLFW_PRESS)
		camera.ProcessKeyboard(RIGHT, m_deltaTime);
}

void GLFWindow::lockCursor()
{
	glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
}

void GLFWindow::unlockCursor()
{
	glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
}

void GLFWindow::setBackgroundColor(const Color& color)
{
	glClearColor(color.getRed(), color.getGreen(), color.getBlue(), color.getAlpha());
	glClear(GL_COLOR_BUFFER_BIT);
}

