#include <core/Color.h>

#include <window/Window.h>
#include <window/GLFWindow.h>
#include <camera/Camera.h>

const int SCR_WIDTH = 1920;
const int SCR_HEIGHT = 1080;



int main() {
	Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));
	Window* window = new GLFWindow(SCR_WIDTH, SCR_HEIGHT, "OpenGL Window");
    window->setCamera(camera);

	while (!window->shouldClose())
	{
		window->processInput();
		window->pollEvents();

		window->setBackgroundColor(Color::White);

		window->update();
		window->swapBuffers();
	}
}
