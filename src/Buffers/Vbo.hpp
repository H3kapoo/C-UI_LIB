#pragma once

#include <GL/glew.h>

#include <vector>

class Vbo
{
private:
    int stride_{ 0 };
    std::vector<int> offsets_;
    std::vector<int> layout_;
    int typeSize_{ 4 };
    unsigned int vboId_{};

public:
    Vbo(const std::vector<unsigned int>& layout, const std::vector<float> buffer);
    void bind() const;
    void unbind() const;
    int getStride() const;
    const std::vector<int>& getOffsets() const;
    const std::vector<int>& getLayout() const;
    unsigned int getVboId() const;
    void cleanUp() const;
};
