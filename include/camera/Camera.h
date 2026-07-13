#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Camera {
public:
	enum Movement {
		FORWARD,
		BACKWARD,
		LEFT,
		RIGHT
	};

	virtual ~Camera() = default;

	virtual glm::mat4 getViewMatrix() const = 0;
	virtual void processKeyboard(Movement direction, float deltaTime) = 0;
	virtual void processMouseMovement(float xoffset, float yoffset, bool constrainPitch = true) = 0;
	virtual void processMouseScroll(float yoffset) = 0;
	virtual float getZoom() const = 0;
	virtual glm::vec3 getPosition() const = 0;
};
