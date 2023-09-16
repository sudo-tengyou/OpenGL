#include "shader.h"

Shader::Shader(const char* vertexPath, const char* framentPath) {
	std::string vertexCode;
	std::string fragmentCode;
	std::ifstream vShaderFile;
	std::ifstream fShaderFile;

	vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	try {
		vShaderFile.open(vertexPath);
		fShaderFile.open(framentPath);

		std::stringstream vertexStream, fragmentStream;
		vertexStream << vShaderFile.rdbuf();
		fragmentStream << fShaderFile.rdbuf();

		vShaderFile.close();
		fShaderFile.close();

		vertexCode = vertexStream.str();
		fragmentCode = fragmentStream.str();
	} catch(std::ifstream::failure e) {
		std::cout << "read shader file failed!" << std::endl;
	}
	const char* vShaderCode = vertexCode.c_str();
	const char* fShaderCode = fragmentCode.c_str();

	unsigned int vertex, fragment;
	int success;
	char infoLog[512];

	vertex = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertex, 1, &vShaderCode, NULL);
	glCompileShader(vertex);
	glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(vertex, 512, NULL, infoLog);
		std::cout << "compile vertex shader failed!\nerror:" << infoLog << std::endl;
	}

	fragment = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragment, 1, &fShaderCode, NULL);
	glCompileShader(fragment);
	glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(fragment, 512, NULL, infoLog);
		std::cout << "compile fragment shader failed!\nerror:" << infoLog << std::endl;
	}

	ID = glCreateProgram();
	glAttachShader(ID, vertex);
	glAttachShader(ID, fragment);
	glLinkProgram(ID);
	glGetProgramiv(ID, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(ID, 512, NULL, infoLog);
		std::cout << "shader program linked failed!\nerror:" << infoLog << std::endl;
	}

	glDeleteShader(vertex);
	glDeleteShader(fragment);
}

void Shader::use() {
	GLCHECK(glUseProgram(ID));
}

void Shader::deleteProgram() {
	GLCHECK(glDeleteProgram(ID));
}

void Shader::setBool(const std::string& name, bool value) const {
	GLCHECK(glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value));
}

void Shader::setInt(const std::string& name, int value) const {
	GLCHECK(glUniform1i(glGetUniformLocation(ID, name.c_str()), value));
}

void Shader::setFloat(const std::string& name, float value) const {
	GLCHECK(glUniform1f(glGetUniformLocation(ID, name.c_str()), value));
}

void Shader::setVec3(const std::string& name, const glm::vec3& value) const
{
	GLCHECK(glUniform3fv(glGetUniformLocation(ID, name.c_str()), 1, glm::value_ptr(value)));
}

void Shader::setVec3(const std::string& name, float v1, float v2, float v3) const
{
	GLCHECK(glUniform3f(glGetUniformLocation(ID, name.c_str()), v1, v2, v3));
}

void Shader::setMat4(const std::string& name, const glm::mat4& value) const
{
	GLCHECK(glUniformMatrix4fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, glm::value_ptr(value)));
}
