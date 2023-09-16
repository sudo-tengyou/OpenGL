#pragma once
#ifndef BUFFER_H
#define BUFFER_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "glerror.h"

class Buffer
{
private:
	unsigned int ID;
	GLenum bufferType;
public:
	Buffer(GLenum type, const void* vertexSource, unsigned int size, GLenum usage);
	~Buffer();
	void bind() const;
	void unBind() const;
};

#endif // !BUFFER_H