#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <memory>

#include "../Shaders/Shader.hpp"
#include "../Buffers/Vao.hpp"

class Quad
{
private:
    glm::vec3 pos_{ 0 };
    float rot_{ 0 };
    glm::vec2 scale_{ 100 };
    glm::vec2 pivotPoint_{ -0.5f };
    glm::mat4 modelMat_;
    std::unique_ptr<Vao> vao_;
    std::shared_ptr<Shader> shader_; // make unique
private:
    void computeModelMatrix();
public:
    Quad(const std::shared_ptr<Shader> shader); // to be removed
    ~Quad();
    void setPos(const glm::vec3& pos);
    void addPos(const glm::vec3& pos);
    void setScale(const glm::vec2& scale);
    void addScale(const glm::vec2& scale);
    void setModelMatrix(const glm::mat4& mat);
    const glm::mat4& getModelMatrix() const;
    void draw(const glm::mat4& projMat) const;
};