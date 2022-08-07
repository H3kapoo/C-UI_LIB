#include "Vao.hpp"

Vao::Vao(const std::vector<unsigned int> layout, const std::vector<float> data,
    const std::vector<unsigned int> indices)
{
    glGenVertexArrays(1, &vaoId_);
    bind();

    vbo_ = std::make_unique<Vbo>(layout, data);
    for (int attrId = 0; attrId < vbo_->getOffsets().size(); attrId++)
    {
        glVertexAttribPointer(attrId, vbo_->getLayout()[attrId],
            GL_FLOAT,
            GL_FALSE,
            vbo_->getStride(),
            (void*)vbo_->getOffsets()[attrId]);

        glEnableVertexAttribArray(attrId);
    }

    if (!indices.empty())
        ibo_ = std::make_unique<Ibo>(indices);
}

void Vao::draw() const
{
    if (ibo_ == nullptr)
        glDrawArrays(GL_TRIANGLES, 0, 6);
    else
        glDrawElements(GL_TRIANGLES, ibo_->getSize(), GL_UNSIGNED_INT, 0);
}

int Vao::getVertexCount()
{
    return ibo_->getSize();
}

void Vao::bind() const
{
    glBindVertexArray(vaoId_);
}

void Vao::unbind() const
{
    glBindVertexArray(0);
}

void Vao::cleanUp()
{
    glDeleteVertexArrays(1, &vaoId_);
    vbo_->cleanUp();
    ibo_->cleanUp();
}