#include <core/Color.h>
#include <shapes/Box.h>
#include <window/Window.h>
#include <window/GLFWindow.h>
#include <camera/Camera.h>
#include <camera/OpenGLCamera.h>
#include <buffers/VertexBuffer.h>
#include <buffers/VertexArray.h>
#include <texture/OpenGLTexture.h>

#include <shader/OpenGLShader.h>

#include <glad/glad.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <stb/stb_image.h>
#include <iostream>

const int SCR_WIDTH = 1920;
const int SCR_HEIGHT = 1080;

int main() {

	Camera* camera = new OpenGLCamera(
		glm::vec3(0.0f, 0.0f, 3.0f),
		glm::vec3(0.0f, 1.0f, 0.0f)
	);

	Window* window = new GLFWindow(SCR_WIDTH, SCR_HEIGHT, "OpenGL Window");
    window->setCamera(*camera);
	window->lockCursor();

	OpenGLShader shader("shaders/base.vert", "shaders/base.frag");
	OpenGLShader lightShader("shaders/light.vert", "shaders/light.frag");

	Box box(0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, Color::White);
    box.includeTextureCoordinates();
    box.includeNormal();

	Box lightBox(1.2f, 1.0f, 2.0f, 1.0f, 1.0f, 1.0f, Color::White);

    OpenGLTexture openGLTexture("textures/container.jpg");

    VertexBuffer VBO;
    VBO.bind();
    VBO.setData(box.getVertices());

    VertexArray VAO;
    VAO.bind();
    VAO.setLayout(box);

    VBO.unbind();
    VAO.unbind();

    VertexBuffer lightVBO;
    lightVBO.bind();
    lightVBO.setData(lightBox.getVertices());

    VertexArray lightVAO;
    lightVAO.bind();
    lightVAO.setLayout(lightBox);

    lightVBO.unbind();
    lightVAO.unbind();

	while (!window->shouldClose())
	{
		window->processInput();

		window->setBackgroundColor(Color::Black);
        glClear(GL_DEPTH_BUFFER_BIT);

        shader.use();
        shader.setVec3("lightColor", lightBox.getColorVec3());
		shader.setVec3("viewPos", camera->getPosition());

        shader.setVec3("material.ambient", 1.0f, 0.5f, 0.31f);
        shader.setVec3("material.diffuse", 1.0f, 0.5f, 0.31f);
        shader.setVec3("material.specular", 0.5f, 0.5f, 0.5f);
        shader.setFloat("material.shininess", 32.0f);

        shader.setVec3("light.ambient", 0.2f, 0.2f, 0.2f);
        shader.setVec3("light.diffuse", 0.5f, 0.5f, 0.5f); // darken diffuse light a bit
        shader.setVec3("light.specular", 1.0f, 1.0f, 1.0f);
        shader.setVec3("light.position", lightBox.getPosition());

        // View
        glm::mat4 view = camera->getViewMatrix();
        shader.setMat4("view", view);

		// Projection
        glm::mat4 projection = glm::perspective(glm::radians(camera->getZoom()), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
        shader.setMat4("projection", projection);

        // world transformation
        glm::mat4 model = glm::mat4(1.0f);
        shader.setMat4("model", model);

        openGLTexture.bind();
        VAO.bind();
        glDrawArrays(GL_TRIANGLES, 0, box.getVertexCount());

        lightShader.use();
        lightShader.setMat4("projection", projection);
        lightShader.setMat4("view", view);
        lightShader.setVec3("lightColor", lightBox.getColorVec3());

        model = glm::mat4(1.0f);
        model = glm::translate(model, lightBox.getPosition());
        model = glm::scale(model, glm::vec3(0.2f)); // a smaller cube
        lightShader.setMat4("model", model);

        lightVAO.bind();
        glDrawArrays(GL_TRIANGLES, 0, lightBox.getVertexCount());

		window->update();
	}

    delete camera;
    delete window;
}
