#pragma once

#include <fstream>
#include <sstream>
#include <string>
#include <iostream>
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

enum ShaderType
{
    VERTEX = GL_VERTEX_SHADER,
    FRAG = GL_FRAGMENT_SHADER
};

class Shader
{
private:
    uint shaderId_;

public:
    Shader();
    Shader(const char *vertSrc, const char *fragSrc);
    ~Shader();
    void setInt(const char *location, int value);
    void setVec3f(const char *location, glm::vec3 value);
    void setMatrix4(const char *location, const glm::mat4 transform);
    void bind() const;
    void unbind() const;

private:
    int createShaderType(const char *source, ShaderType type);
    int linkShaders(int vertShaderID, int fragShaderID);
    int linkShaders(int vertShaderID, int fragShaderID, int geomShaderID);

protected:
    std::string convertToString(ShaderType type) const;
};
