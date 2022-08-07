#include "Ibo.hpp"

Ibo::Ibo(const std::vector<unsigned int> buffer)
{
    glGenBuffers(1, &iboId_);
    bind();

    size_ = buffer.size();
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * buffer.size(), &buffer[0], GL_STATIC_DRAW);
}

void Ibo::bind() const
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, iboId_);
}

void Ibo::unbind() const
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void Ibo::cleanUp() const
{
    glDeleteBuffers(1, &iboId_);
}

unsigned int Ibo::getIboId() const
{
    return iboId_;
}

int Ibo::getSize() const
{
    return size_;
}
