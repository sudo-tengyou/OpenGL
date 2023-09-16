#pragma once
#ifndef CAMERA_H
#define CAMERA_H

#include <iostream>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Camera {
private:
	float cameraSpeed;
	float mouseSensitivity;
	float yaw;
	float pitch;
	glm::vec3 WorldUp;
	glm::vec3 cameraPos;
	glm::vec3 cameraFront;
	glm::vec3 cameraUp;
	void updateCameraVectors();
public:
	Camera();
	Camera(const glm::vec3& cPos, const glm::vec3& cFront, const glm::vec3& cUp);
	const glm::vec3& getPos() const;
	const glm::vec3& getFrontDire() const;
	const glm::vec3& getUpDire() const;
	void move(const glm::vec3& cPos);
	void setFront(const glm::vec3& cFront);
	void setUp(const glm::vec3& cUp);
	void processInput(GLFWwindow* window);
	void ProcessMouseMovement(float xoffset, float yoffset, GLboolean constrainPitch = true);
};

#endif // !CAMERA_H