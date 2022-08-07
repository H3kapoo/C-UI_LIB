#include "Quad.hpp"

Quad::Quad(const std::shared_ptr<Shader> shader)
{
    shader_ = shader;

    std::vector<float> data = {
        // positions, centered at 0,0
        /*
            (-0.5,-0.5) --------  (0.5,-0.5)
                       |        |
                       | (0,0)  |
                       |        |
            (-0.5,0.5) ---------- (0.5,0.5)

        */
         0.5f,  0.5f, 1.0f, // top right
         0.5f, -0.5f, 1.0f, // bottom right
        -0.5f, -0.5f, 1.0f, // bottom left
        -0.5f,  0.5f, 1.0f, // top left 
    };
    std::vector<unsigned int> indices = {
        0, 1, 3, // first triangle
        1, 2, 3  // second triangle
    };

    std::vector<unsigned int> layout = { 3 };

    vao_ = std::make_unique<Vao>(layout, data, indices);
    computeModelMatrix();
}

Quad::~Quad()
{
    vao_->cleanUp();
}

void Quad::draw(const glm::mat4& projMat) const {
    shader_->bind();
    shader_->setMatrix4("proj", projMat);
    shader_->setMatrix4("model", modelMat_);
    vao_->bind();
    vao_->draw();
}

void Quad::setPos(const glm::vec3& pos)
{
    pos_ = pos;
    computeModelMatrix();
}

void Quad::addPos(const glm::vec3& pos)
{
    pos_ += pos;
    computeModelMatrix();
}

void Quad::setScale(const glm::vec2& scale)
{
    scale_ = scale;
    computeModelMatrix();
}

void Quad::addScale(const glm::vec2& scale)
{
    scale_ += scale;
    computeModelMatrix();
}

void Quad::setModelMatrix(const glm::mat4& mat)
{
    modelMat_ = mat;
}

void Quad::computeModelMatrix() {
    modelMat_ = glm::mat4(1.0f);
    modelMat_ = glm::translate(modelMat_, pos_);
    modelMat_ = glm::translate(modelMat_, glm::vec3(pivotPoint_, 0));
    // modelMat_ = glm::rotate(modelMat_, glm::radians(glm::degrees(rot_)), glm::vec3(0, 0, 1));
    modelMat_ = glm::scale(modelMat_, glm::vec3(scale_, 1.0f));
    modelMat_ = glm::translate(modelMat_, glm::vec3(-pivotPoint_, 0));

}