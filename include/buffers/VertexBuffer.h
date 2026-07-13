#pragma once

#include <glad/glad.h>
#include <vector>

class VertexBuffer {
private:
    unsigned int m_id;

public:
    VertexBuffer();
    ~VertexBuffer();

    void setData(const std::vector<float>& data, GLenum usage = GL_STATIC_DRAW);

    void bind() const;
    void unbind() const;

    unsigned int getID() const;
};