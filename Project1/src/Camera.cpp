#include "Camera.h"

Camera::Camera() {
	cameraSpeed = 0.05f;
	WorldUp = glm::vec3(0, 1, 0);
	yaw = -90.0f;
	pitch = 0.0f;
	mouseSensitivity = 0.1f;
	cameraPos = glm::vec3(0, 0, 0);
	cameraFront = glm::vec3(0, 0, -1);
	cameraUp = glm::vec3(0, 1, 0);
}

Camera::Camera(const glm::vec3& cPos, const glm::vec3& cFront, const glm::vec3& cUp) {
	cameraPos = cPos;
	cameraFront = cFront;
	cameraUp = cUp;
	cameraSpeed = 0.05f;
	WorldUp = glm::vec3(0, 1, 0);
	yaw = -90.0f;
	pitch = 0.0f;
	mouseSensitivity = 0.1f;
}

const glm::vec3& Camera::getPos() const {
	return cameraPos;
}

const glm::vec3& Camera::getFrontDire() const {
	return cameraFront;
}
const glm::vec3& Camera::getUpDire() const {
	return cameraUp;
}

void Camera::move(const glm::vec3& cPos) {
	cameraPos += cPos;
	// std::cout << cameraPos.x << ' ' << cameraPos.y << ' ' << cameraPos.z << std::endl;
}

void Camera::setFront(const glm::vec3& cFront) {
	cameraFront = cFront;
}

void Camera::setUp(const glm::vec3& cUp) {
	cameraUp = cUp;
}

void Camera::processInput(GLFWwindow* window) {
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		move(cameraFront * cameraSpeed);
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		move(-cameraFront * cameraSpeed);
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		move(-glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed);
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		move(glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed);
}

void Camera::ProcessMouseMovement(float xoffset, float yoffset, GLboolean constrainPitch) {
	xoffset *= mouseSensitivity;
	yoffset *= mouseSensitivity;

	yaw += xoffset;
	pitch += yoffset;

	// make sure that when pitch is out of bounds, screen doesn't get flipped
	if (constrainPitch)
	{
		if (pitch > 89.0f) {
			pitch = 89.0f;
		}
		if (pitch < -89.0f) {
			pitch = -89.0f;
		}
	}

	// update Front, Right and Up Vectors using the updated Euler angles
	updateCameraVectors();
}

void Camera::updateCameraVectors()
{
	// calculate the new Front vector
	glm::vec3 front;
	front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	front.y = sin(glm::radians(pitch));
	front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
	cameraFront = glm::normalize(front);
	// re-calculate the Up vector
	cameraUp = glm::normalize(glm::cross(glm::cross(front, WorldUp), cameraFront));
}