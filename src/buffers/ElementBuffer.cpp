#include <buffers/ElementBuffer.h>

#include <glad/glad.h>

ElementBuffer::ElementBuffer()
{
	glGenBuffers(1, &m_id);
}

ElementBuffer::~ElementBuffer()
{
	glDeleteBuffers(1, &m_id);
}

void ElementBuffer::bind() const
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_id);
}

void ElementBuffer::unbind() const
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

unsigned int ElementBuffer::getID() const
{
	return m_id;
}

void ElementBuffer::setLayout(const Box& box)
{
	bind();
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, box.getIndexCount() * sizeof(unsigned int), box.getIndices().data(), GL_STATIC_DRAW);
}