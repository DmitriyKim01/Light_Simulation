#pragma once

#include <shapes/Box.h>
#include <glad/glad.h>

class ElementBuffer {
private:
    unsigned int m_id;

public:
    ElementBuffer();
    ~ElementBuffer();

    void bind() const;
    void unbind() const;

    void setLayout(const Box& box);

    unsigned int getID() const;
};
