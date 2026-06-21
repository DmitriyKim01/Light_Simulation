#include <camera/Camera.h>
#include <camera/OpenGLCamera.h>

#include <glm/gtc/matrix_transform.hpp>

OpenGLCamera::OpenGLCamera(
    glm::vec3 position,
    glm::vec3 up,
    float yaw,
    float pitch
)
    : Position(position),
    Front(glm::vec3(0.0f, 0.0f, -1.0f)),
    WorldUp(up),
    Yaw(yaw),
    Pitch(pitch),
    MovementSpeed(SPEED),
    MouseSensitivity(SENSITIVITY),
    Zoom(ZOOM)
{
    updateCameraVectors();
}

OpenGLCamera::OpenGLCamera(
    float posX,
    float posY,
    float posZ,
    float upX,
    float upY,
    float upZ,
    float yaw,
    float pitch
)
    : Position(glm::vec3(posX, posY, posZ)),
    Front(glm::vec3(0.0f, 0.0f, -1.0f)),
    WorldUp(glm::vec3(upX, upY, upZ)),
    Yaw(yaw),
    Pitch(pitch),
    MovementSpeed(SPEED),
    MouseSensitivity(SENSITIVITY),
    Zoom(ZOOM)
{
    updateCameraVectors();
}

glm::mat4 OpenGLCamera::getViewMatrix() const
{
    return glm::lookAt(Position, Position + Front, Up);
}

void OpenGLCamera::processKeyboard(Camera::Movement direction, float deltaTime)
{
    float velocity = MovementSpeed * deltaTime;

    if (direction == FORWARD)
    {
        Position += Front * velocity;
    }

    if (direction == BACKWARD)
    {
        Position -= Front * velocity;
    }

    if (direction == LEFT)
    {
        Position -= Right * velocity;
    }

    if (direction == RIGHT)
    {
        Position += Right * velocity;
    }
}

void OpenGLCamera::processMouseMovement(float xoffset, float yoffset, bool constrainPitch)
{
    xoffset *= MouseSensitivity;
    yoffset *= MouseSensitivity;

    Yaw += xoffset;
    Pitch += yoffset;

    if (constrainPitch)
    {
        if (Pitch > 89.0f)
        {
            Pitch = 89.0f;
        }

        if (Pitch < -89.0f)
        {
            Pitch = -89.0f;
        }
    }

    updateCameraVectors();
}

void OpenGLCamera::processMouseScroll(float yoffset)
{
    Zoom -= yoffset;

    if (Zoom < 1.0f)
    {
        Zoom = 1.0f;
    }

    if (Zoom > 45.0f)
    {
        Zoom = 45.0f;
    }
}

void OpenGLCamera::updateCameraVectors()
{
    glm::vec3 front;

    front.x = cos(glm::radians(Yaw)) * cos(glm::radians(Pitch));
    front.y = sin(glm::radians(Pitch));
    front.z = sin(glm::radians(Yaw)) * cos(glm::radians(Pitch));

    Front = glm::normalize(front);

    Right = glm::normalize(glm::cross(Front, WorldUp));
    Up = glm::normalize(glm::cross(Right, Front));
}

float OpenGLCamera::getZoom() const
{
	return Zoom;
}