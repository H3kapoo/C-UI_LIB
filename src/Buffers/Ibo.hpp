#pragma once

#include <GL/glew.h>
#include <vector>

class Ibo
{
private:
    int size_;
    unsigned int iboId_{};

public:
    Ibo(const std::vector<unsigned int> buffer);
    void bind() const;
    void unbind() const;
    void cleanUp() const;
    unsigned int getIboId() const;
    int getSize() const;
};
