#include "Shader.hpp"

// use default vert/frag
Shader::Shader() : Shader("res/bvert.glsl", "res/bfrag.glsl") {}

Shader::Shader(const char *vertSrc, const char *fragSrc)
{
    shaderId_ = linkShaders(createShaderType(vertSrc, ShaderType::VERTEX),
                            createShaderType(fragSrc, ShaderType::FRAG));
}

Shader::~Shader()
{
    glDeleteProgram(shaderId_);
}

int Shader::createShaderType(const char *source, ShaderType type)
{
    std::ifstream inStream;
    inStream.open(source);

    if (!inStream)
    {
        std::cerr << "Could not open " << convertToString(type) << "_FILE at: " << source << std::endl;
        return -1;
    }

    std::stringstream inStringStream;
    inStringStream << inStream.rdbuf();
    inStream.close();
    std::string content = inStringStream.str();

    uint shaderPartId = glCreateShader(type);
    const char *c_str = content.c_str();

    glShaderSource(shaderPartId, 1, &c_str, nullptr);
    glCompileShader(shaderPartId);

    int success;
    char infoLog[512];
    glGetShaderiv(shaderPartId, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(shaderPartId, 512, nullptr, infoLog);
        std::cerr << "Could not create shader part " << convertToString(type)
                  << ": " << infoLog << std::endl;
        return -1;
    }

    return shaderPartId;
}

int Shader::linkShaders(int vertShaderID, int fragShaderID)
{

    if (!vertShaderID || !fragShaderID)
        return -1;

    uint shaderProgram = glCreateProgram();

    glAttachShader(shaderProgram, vertShaderID);
    glAttachShader(shaderProgram, fragShaderID);
    glLinkProgram(shaderProgram);

    int success;
    char infoLog[512];
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);

    if (!success)
    {
        glGetProgramInfoLog(shaderProgram, 512, nullptr, infoLog);
        std::cerr << "Could not link program: "
                  << ": " << infoLog << std::endl;
        return -1;
    }

    glDeleteShader(vertShaderID);
    glDeleteShader(fragShaderID);

    return shaderProgram;
}

int Shader::linkShaders(int vertShaderID, int fragShaderID, int geomShaderID)
{
    if (!vertShaderID || !fragShaderID || geomShaderID)
        return -1;

    uint shaderProgram = glCreateProgram();

    glAttachShader(shaderProgram, vertShaderID);
    glAttachShader(shaderProgram, fragShaderID);
    glAttachShader(shaderProgram, geomShaderID);
    glLinkProgram(shaderProgram);

    int success;
    char infoLog[512];
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);

    if (!success)
    {
        glGetProgramInfoLog(shaderProgram, 512, nullptr, infoLog);
        std::cerr << "Could not link program: "
                  << ": " << infoLog << std::endl;
        return -1;
    }

    glDeleteShader(vertShaderID);
    glDeleteShader(fragShaderID);
    glDeleteShader(geomShaderID);

    return shaderProgram;
}

void Shader::bind() const
{
    glUseProgram(shaderId_);
}

void Shader::unbind() const
{
    glUseProgram(0);
}

std::string Shader::convertToString(ShaderType type) const
{
    switch (type)
    {
    case ShaderType::VERTEX:
        return "VERTEX";
    case ShaderType::FRAG:
        return "FRAG";
    default:
        return "UNKNOWN";
    }
}

void Shader::setInt(const char *location, int value)
{
    bind();
    unsigned int loc = glGetUniformLocation(shaderId_, location);
    if (loc == -1)
    {
        std::cerr << "Uniform '" << location << "' has not been found in bound shader!" << std::endl;
        return;
    }
    glUniform1i(loc, value);
}

void Shader::setVec3f(const char *location, glm::vec3 value)
{
    bind();
    unsigned int loc = glGetUniformLocation(shaderId_, location);
    if (loc == -1)
    {
        std::cerr << "Uniform '" << location << "' has not been found in bound shader!" << std::endl;
        return;
    }
    glUniform3f(loc, value.x, value.y, value.z);
}

void Shader::setMatrix4(const char *location, const glm::mat4 transform)
{
    bind();
    unsigned int transformLoc = glGetUniformLocation(shaderId_, location);
    if (transformLoc == -1)
    {
        std::cerr << "Uniform '" << location << "' has not been found in bound shader!" << std::endl;
        return;
    }
    glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(transform));
}
