#pragma once
#ifndef VERTEXARRAY_H
#define VERTEXARRAY_H

#include "Buffer.h"
#include "VertexBufferLayout.h"

class VertexArray {
private:
	unsigned int m_RendererID;

public:
	VertexArray();
	~VertexArray();

	void AddBuffer(const Buffer& vb, const VertexBufferLayout& layout);

	void Bind() const;
	void Unbind() const;
};

#endif // !VERTEXARRAY_H