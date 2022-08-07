#pragma once

#include <GL/glew.h>
#include <vector>
#include <memory>
#include "Vbo.hpp"
#include "Ibo.hpp"

class Vao
{
private:
    std::unique_ptr<Vbo> vbo_;
    std::unique_ptr<Ibo> ibo_;
    unsigned int vaoId_{ 0 };

public:
    Vao(const std::vector<unsigned int> layout, const std::vector<float> data,
        const std::vector<unsigned int> indices = {});
    void draw() const;
    void bind() const;
    void unbind() const;
    void cleanUp();
    int getVertexCount();
};
