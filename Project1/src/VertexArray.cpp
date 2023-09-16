#include "VertexArray.h"

VertexArray::VertexArray()
{
	GLCHECK(glGenVertexArrays(1, &m_RendererID));
}

VertexArray::~VertexArray()
{
	GLCHECK(glDeleteVertexArrays(1, &m_RendererID));
}

void VertexArray::AddBuffer(const Buffer& vb, const VertexBufferLayout& layout)
{
	Bind();
	vb.bind();
	const auto& elements = layout.GetElements();
	unsigned int offset = 0;
	for (unsigned int i = 0; i < elements.size(); ++i) {
		const auto& element = elements[i];
		GLCHECK(glEnableVertexAttribArray(i));
		GLCHECK(glVertexAttribPointer(i, element.count, element.type, element.normalized, layout.GetStride(), (void*)offset));
		offset += element.count * VertexBufferElement::GetSizeOfType(element.type);
	}
}

void VertexArray::Bind() const
{
	GLCHECK(glBindVertexArray(m_RendererID));
}

void VertexArray::Unbind() const
{
	GLCHECK(glBindVertexArray(0));
}
