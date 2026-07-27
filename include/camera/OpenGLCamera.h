#pragma once
#include <camera/Camera.h>

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

inline constexpr float YAW = -90.0f;
inline constexpr float PITCH = 0.0f;
inline constexpr float SPEED = 2.5f;
inline constexpr float SENSITIVITY = 0.1f;
inline constexpr float ZOOM = 45.0f;

class OpenGLCamera : public Camera {
public:
	// camera Attributes
	glm::vec3 Position;
	glm::vec3 Front;
	glm::vec3 Up;
	glm::vec3 Right;
	glm::vec3 WorldUp;
	// euler Angles
	float Yaw;
	float Pitch;
	// camera options
	float MovementSpeed;
	float MouseSensitivity;
	float Zoom;
    // constructor with vectors
    OpenGLCamera(
        glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f),
        glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f),
        float yaw = YAW,
        float pitch = PITCH
    );

    // constructor with scalar values
    OpenGLCamera(
        float posX,
        float posY,
        float posZ,
        float upX,
        float upY,
        float upZ,
        float yaw,
        float pitch
    );
    glm::mat4 getViewMatrix() const;

    void processKeyboard(Camera::Movement direction, float deltaTime) override;
    void processMouseMovement(float xoffset, float yoffset, bool constrainPitch = true) override;
    void processMouseScroll(float yoffset) override;
    float getZoom() const override;
	glm::vec3 getPosition() const override;
	glm::vec3 getFront() const override;

private:
    // calculates the front vector from the Camera's (updated) Euler Angles
    void updateCameraVectors();
};