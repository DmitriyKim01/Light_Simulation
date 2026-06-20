#include <core/Color.h>

#include <window/Window.h>
#include <window/GLFWindow.h>

const int SCR_WIDTH = 1920;
const int SCR_HEIGHT = 1080;

int main() {
	Window* window = new GLFWindow(SCR_WIDTH, SCR_HEIGHT, "OpenGL Window");

	while (!window->shouldClose())
	{
		window->pollEvents();

		window->setBackgroundColor(Color::White);

		window->update();
		window->swapBuffers();
	}
}