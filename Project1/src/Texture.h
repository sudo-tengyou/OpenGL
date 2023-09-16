#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stb_image.h>
#include "glerror.h"

class Texture {
private:
	unsigned int textureID;
	GLenum textureType;
	unsigned int textureUnit;
	std::string type;
public:
	Texture(const char* path, unsigned int textUnit, std::string type, GLenum colorFormat,
		GLenum texType = GL_TEXTURE_2D, GLint sWrap = GL_REPEAT, GLint tWrap = GL_REPEAT,
		GLint minFilter = GL_NEAREST, GLint magFilter = GL_LINEAR);
	std::string getType() const;
	unsigned int getID() const;
	void Bind();
	void UnBind();
};