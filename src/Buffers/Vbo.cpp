#include "Vbo.hpp"

Vbo::Vbo(const std::vector<unsigned int>& layout, const std::vector<float> buffer)
{
    glGenBuffers(1, &vboId_);
    bind();
    typeSize_ = sizeof(float);
    glBufferData(GL_ARRAY_BUFFER, typeSize_ * buffer.size(), &buffer[0], GL_STATIC_DRAW);

    for (const int attrib : layout)
    {
        offsets_.push_back(stride_);
        layout_.push_back(attrib);
        stride_ += typeSize_ * attrib;
    }
}

void Vbo::bind() const
{
    glBindBuffer(GL_ARRAY_BUFFER, vboId_);
}

void Vbo::unbind() const
{
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

int Vbo::getStride() const
{
    return stride_;
}

const std::vector<int>& Vbo::getOffsets() const
{
    return offsets_;
}

const std::vector<int>& Vbo::getLayout() const
{
    return layout_;
}

void Vbo::cleanUp() const
{
    glDeleteBuffers(1, &vboId_);
}

unsigned int Vbo::getVboId() const
{
    return vboId_;
}
