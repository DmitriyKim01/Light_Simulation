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

	OpenGLShader boxShader("shaders/cube.vert", "shaders/cube.frag");
	OpenGLShader lightShader("shaders/light.vert", "shaders/light.frag");

	Box box(0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, Color::White);
    box.includeTextureCoordinates();
    box.includeNormal();

	Box lightBox(-0.2f, -1.0f, -0.3f, 1.0f, 1.0f, 1.0f, Color::White);

	OpenGLTexture diffuseMap("textures/container2.png");
	OpenGLTexture specularMap("textures/container2_specular.png");

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

    glm::vec3 cubePositions[] = {
    glm::vec3(0.0f,  0.0f,  0.0f),
    glm::vec3(1.0f,  0.0f, 0.0f),
    glm::vec3(-1.0f, 0.0f, 0.0f),
    glm::vec3(0.0f, 1.0f, 0.0f),
    glm::vec3(1.0f, 1.0f, 0.0f),
    glm::vec3(-1.0f, 1.0f, 0.0f),
    glm::vec3(0.0f, -1.0f, 0.0f),
    glm::vec3(1.0f, -1.0f, 0.0f),
    glm::vec3(-1.0f, -1.0f, 0.0f)
    };

	while (!window->shouldClose())
	{
		window->processInput();
		window->setBackgroundColor(Color::Gray);
		window->clearDepthBuffer();

        boxShader.use();

        boxShader.setVec3("viewPos", camera->getPosition());



		// Set material properties
        boxShader.setInt("material.diffuse", 0);
        boxShader.setInt("material.specular", 1);
        boxShader.setFloat("material.shininess", 64.0f);

		// Set light properties
        boxShader.setVec3("light.position", camera->getPosition());
        boxShader.setVec3("light.direction", camera->getFront());
        boxShader.setFloat("light.cutOff", glm::cos(glm::radians(12.5f)));
        boxShader.setFloat("light.outerCutOff", glm::cos(glm::radians(17.5f)));

        boxShader.setVec3("light.ambient", 0.2f, 0.2f, 0.2f);
        boxShader.setVec3("light.diffuse", 0.5f, 0.5f, 0.5f); // darken diffuse light a bit
        boxShader.setVec3("light.specular", 1.0f, 1.0f, 1.0f);

        boxShader.setFloat("light.constant", 1.0f);
        boxShader.setFloat("light.linear", 0.09f);
        boxShader.setFloat("light.quadratic", 0.032f);

        // View
        glm::mat4 view = camera->getViewMatrix();
        boxShader.setMat4("view", view);

		// Projection
        glm::mat4 projection = glm::perspective(glm::radians(camera->getZoom()), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
        boxShader.setMat4("projection", projection);

        // Set textures
        glActiveTexture(GL_TEXTURE0);
        diffuseMap.bind();
        glActiveTexture(GL_TEXTURE1);
        specularMap.bind();

        VAO.bind();
        for (unsigned int i = 0; i < 9; i++)
        {
            glm::mat4 model = glm::mat4(1.0f);
            model = glm::translate(model, cubePositions[i]);
            //float angle = 20.0f * i;
            //model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
            boxShader.setMat4("model", model);
            glDrawArrays(GL_TRIANGLES, 0, 36);
        }

        lightShader.use();
        lightShader.setMat4("projection", projection);
        lightShader.setMat4("view", view);
        lightShader.setVec3("lightColor", lightBox.getColorVec3());

        glm::mat4 model = glm::mat4(1.0f);
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
