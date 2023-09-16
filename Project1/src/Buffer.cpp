#include "Buffer.h"

Buffer::Buffer(GLenum type, const void* vertexSource, unsigned int size, GLenum usage)
{
	bufferType = type;
	GLCHECK(glGenBuffers(1, &ID));
	bind();
	GLCHECK(glBufferData(type, size, vertexSource, usage));
}

Buffer::~Buffer()
{
	GLCHECK(glDeleteBuffers(1, &ID));
}

void Buffer::bind() const
{
	GLCHECK(glBindBuffer(bufferType, ID));
}

void Buffer::unBind() const
{
	GLCHECK(glBindBuffer(bufferType, 0));
}
