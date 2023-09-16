#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include <stb_image.h>
#include "shader.h"
#include "glerror.h"
#include "Buffer.h"
#include "VertexBufferLayout.h"
#include "VertexArray.h"
#include "Texture.h"
#include "Camera.h"
#include "Light.h"
#include "Material.h"

// window size
static const unsigned int SCR_WIDTH = 800;
static const unsigned int SCR_HEIGHT = 600;
// define the camera
Camera mainCamera(glm::vec3(0.0f, 0.0f, 3.0f), glm::vec3(0.0f, 0.0f, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f));
void mouse_callback(GLFWwindow* window, double xposIn, double yposIn);

int main() {
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 4);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);


	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Hello", NULL, NULL);
	if (window == NULL) {
		std::cout << "create window failed!" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cout << "init glad failed!" << std::endl;
		return -1;
	}

	// anti-aliasing
	glEnable(GL_MULTISAMPLE);
	glfwWindowHint(GLFW_SAMPLES, 4);

	glViewport(0, 0, 600, 600);
	glfwSetInputMode(window, GLFW_STICKY_KEYS, GLFW_TRUE);
	glClearColor(0.0f, 0.0f, 0.0f, 1.0);

	glfwSetCursorPosCallback(window, mouse_callback);

	// open color blend and depth test
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	// OpenGL expects (0,0) at the left bottom, but in image it's at the left top
	stbi_set_flip_vertically_on_load(true);

	float vertexs[] = {
		// positions          // normals           // texture coords
		-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,
		 0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 0.0f,
		 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
		 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
		-0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,

		-0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 0.0f,
		 0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 1.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 1.0f,
		-0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 0.0f,

		-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
		-0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
		-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
		-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,

		 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
		 0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
		 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
		 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
		 0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,

		-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,
		 0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 1.0f,
		 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
		 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 0.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,

		-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f,
		 0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 1.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
		-0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 0.0f,
		-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f
	};

	// tranform matrix
	glm::mat4 modelTrans(1.0f);

	{
		VertexArray cubeVAO;
		Buffer VBO(GL_ARRAY_BUFFER, vertexs, sizeof(vertexs), GL_STATIC_DRAW);

		VertexBufferLayout bufferLayout;
		bufferLayout.Push<float>(3);
		bufferLayout.Push<float>(3);
		bufferLayout.Push<float>(2);

		cubeVAO.Bind();
		cubeVAO.AddBuffer(VBO, bufferLayout);

		Shader lightingShader(".\\res\\shaders\\basicLight.vs", ".\\res\\shaders\\basicLight.fs");
		
		Light light(glm::vec3(1.2f, 1.0f, 2.0f), glm::vec3(0.2f, 0.2f, 0.2f), glm::vec3(0.7f, 0.7f, 0.7f),
			        glm::vec3(1.0f, 1.0f, 1.0f));
		// material map
		Texture boxDiffuTex(".\\res\\container2.png", 0, "diffuse texture", GL_RGBA);
		Texture boxSpecuTex(".\\res\\container2_specular.png", 1, "specular texture", GL_RGBA);
		Material material(32.0f, glm::vec3(1.0f, 0.5f, 0.31f), glm::vec3(1.0f, 0.5f, 0.31f), glm::vec3(0.5f, 0.5f, 0.5f));

		while (!glfwWindowShouldClose(window)) {
			mainCamera.processInput(window);

			lightingShader.use();

			// set light attribute
			lightingShader.setVec3("lightPos", light.getPos());
			lightingShader.setVec3("light.ambient", light.getAmb());
			lightingShader.setVec3("light.diffuse", light.getDiffu());
			lightingShader.setVec3("light.specular", light.getSpecu());

			// set view position
			lightingShader.setVec3("viewPos", mainCamera.getPos());

			// set object's material
			/*lightingShader.setVec3("material.ambient", material.getAmb());
			lightingShader.setVec3("material.diffuse", material.getDiffu());
			lightingShader.setVec3("material.specular", material.getSpecu());*/
			lightingShader.setFloat("material.shininess", material.getShini());
			lightingShader.setInt("material.aTex", 0);
			lightingShader.setInt("material.dTex", 0);
			lightingShader.setInt("material.sTex", 1);

			// view/projection transformations
			glm::mat4 projectTrans = glm::perspective(glm::radians(45.0f), 1.0f, 1.0f, 100.0f);
			glm::mat4 viewTrans = glm::lookAt(mainCamera.getPos(), mainCamera.getPos() + mainCamera.getFrontDire(), 
				mainCamera.getUpDire());
			lightingShader.setMat4("projection", projectTrans);
			lightingShader.setMat4("view", viewTrans);

			// world transformation
			glm::mat4 model = glm::mat4(1.0f);
			lightingShader.setMat4("model", model);

			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			// render the cube
			cubeVAO.Bind();
			GLCHECK(glDrawArrays(GL_TRIANGLES, 0, 36));

			glfwSwapBuffers(window);
			glfwPollEvents();
		}
		lightingShader.deleteProgram();
	}
	glfwTerminate();
	return 0;
}

float lastX = SCR_WIDTH / 2.0f;
float lastY = SCR_HEIGHT / 2.0f;
bool firstMouse = true;

void mouse_callback(GLFWwindow* window, double xposIn, double yposIn)
{
	float xpos = static_cast<float>(xposIn);
	float ypos = static_cast<float>(yposIn);

	if (firstMouse)
	{
		lastX = xpos;
		lastY = ypos;
		firstMouse = false;
	}

	float xoffset = xpos - lastX;
	float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top

	lastX = xpos;
	lastY = ypos;

	mainCamera.ProcessMouseMovement(xoffset, yoffset);
}