#include <buffers/VertexBuffer.h>

VertexBuffer::VertexBuffer()
{
    glGenBuffers(1, &m_id);
}

VertexBuffer::~VertexBuffer()
{
    glDeleteBuffers(1, &m_id);
}

void VertexBuffer::setData(const std::vector<float>& data, GLenum usage)
{
    bind();

    glBufferData(
        GL_ARRAY_BUFFER,
        data.size() * sizeof(float),
        data.data(),
        usage
    );
}

void VertexBuffer::bind() const
{
    glBindBuffer(GL_ARRAY_BUFFER, m_id);
}

void VertexBuffer::unbind() const
{
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

unsigned int VertexBuffer::getID() const
{
    return m_id;
}