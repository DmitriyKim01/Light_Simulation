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
    glm::vec3(2.0f,  5.0f, -15.0f),
    glm::vec3(-1.5f, -2.2f, -2.5f),
    glm::vec3(-3.8f, -2.0f, -12.3f),
    glm::vec3(2.4f, -0.4f, -3.5f),
    glm::vec3(-1.7f,  3.0f, -7.5f),
    glm::vec3(1.3f, -2.0f, -2.5f),
    glm::vec3(1.5f,  2.0f, -2.5f),
    glm::vec3(1.5f,  0.2f, -1.5f),
    glm::vec3(-1.3f,  1.0f, -1.5f)
    };

	while (!window->shouldClose())
	{
		window->processInput();

		window->setBackgroundColor(Color::Gray);
        glClear(GL_DEPTH_BUFFER_BIT);

        shader.use();
        shader.setVec3("lightColor", lightBox.getColorVec3());
		shader.setVec3("viewPos", camera->getPosition());

        //shader.setVec3("material.ambient", 1.0f, 0.5f, 0.31f);
        //shader.setVec3("material.diffuse", 1.0f, 0.5f, 0.31f);
        shader.setInt("material.diffuse", 0);
        shader.setInt("material.specular", 1);
        shader.setFloat("material.shininess", 64.0f);

        shader.setVec3("light.position", lightBox.getPosition());

        shader.setVec3("light.ambient", 0.2f, 0.2f, 0.2f);
        shader.setVec3("light.diffuse", 0.5f, 0.5f, 0.5f); // darken diffuse light a bit
        shader.setVec3("light.specular", 1.0f, 1.0f, 1.0f);

		// Distance 50 attenuation
		shader.setFloat("light.constant", 1.0f);
		shader.setFloat("light.linear", 0.09f);
		shader.setFloat("light.quadratic", 0.032f);

        // View
        glm::mat4 view = camera->getViewMatrix();
        shader.setMat4("view", view);

		// Projection
        glm::mat4 projection = glm::perspective(glm::radians(camera->getZoom()), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
        shader.setMat4("projection", projection);

        // world transformation
        //glm::mat4 model = glm::mat4(1.0f);
        //shader.setMat4("model", model);
        glActiveTexture(GL_TEXTURE0);
        diffuseMap.bind();

        glActiveTexture(GL_TEXTURE1);
		specularMap.bind();

        VAO.bind();

        for (unsigned int i = 0; i < 10; i++)
        {
            glm::mat4 model = glm::mat4(1.0f);
            model = glm::translate(model, cubePositions[i]);
            float angle = 20.0f * i;
            model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
            shader.setMat4("model", model);
            glDrawArrays(GL_TRIANGLES, 0, 36);
        }


        //glDrawArrays(GL_TRIANGLES, 0, box.getVertexCount());

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
