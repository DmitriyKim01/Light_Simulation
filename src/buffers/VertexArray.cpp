#include <buffers/VertexArray.h>

VertexArray::VertexArray()
{
    glGenVertexArrays(1, &m_id);
}

VertexArray::~VertexArray()
{
    glDeleteVertexArrays(1, &m_id);
}

void VertexArray::bind() const
{
    glBindVertexArray(m_id);
}

void VertexArray::unbind() const
{
    glBindVertexArray(0);
}

unsigned int VertexArray::getID() const
{
    return m_id;
}

void VertexArray::setLayout(const Box& box)
{
    bind();

    GLsizei stride = static_cast<GLsizei>(box.getStrideBytes());

    // Position: location 0
    glVertexAttribPointer(
        0,
        3,
        GL_FLOAT,
        GL_FALSE,
        stride,
        reinterpret_cast<void*>(box.getPositionOffsetBytes())
    );
    glEnableVertexAttribArray(0);

    // Color: location 1
    if (box.hasColor())
    {
        glVertexAttribPointer(
            1,
            3,
            GL_FLOAT,
            GL_FALSE,
            stride,
            reinterpret_cast<void*>(box.getColorOffsetBytes())
        );
        glEnableVertexAttribArray(1);
    }

    // Texture coordinate: location 2
    if (box.hasTextureCoordinate())
    {
        glVertexAttribPointer(
            2,
            2,
            GL_FLOAT,
            GL_FALSE,
            stride,
            reinterpret_cast<void*>(box.getTextureCoordinatesOffsetBytes())
        );
        glEnableVertexAttribArray(2);
    }

    // Normal: location 3
    if (box.hasNormal())
    {
        glVertexAttribPointer(
            3,
            3,
            GL_FLOAT,
            GL_FALSE,
            stride,
            reinterpret_cast<void*>(box.getNormalOffsetBytes())
        );
        glEnableVertexAttribArray(3);
    }
}