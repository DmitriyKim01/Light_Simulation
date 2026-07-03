#pragma once

#include <glad/glad.h>
#include <shapes/Box.h>

class VertexArray {
private:
    unsigned int m_id;

public:
    VertexArray();
    ~VertexArray();

    void bind() const;
    void unbind() const;

    void setLayout(const Box& box);

    unsigned int getID() const;
};