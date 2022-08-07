#version 330 core
layout (location = 0) in vec3 aPos;

uniform mat4 model;
uniform mat4 proj;
uniform vec3 color;

out vec3 outColor;

void main()
{
    outColor = color;
    gl_Position = proj * model * vec4(aPos.xyz, 1.0);
}