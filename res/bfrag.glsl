#version 330 core

layout(origin_upper_left) in vec4 gl_FragCoord;

in vec3 outColor;
out vec4 pixelColor;

uniform vec3 bottomRight;
uniform vec3 topLeft;
uniform int borderWidth;

void main()
{
    pixelColor = vec4(outColor, 1.0f);

    if((gl_FragCoord.x >= bottomRight.x - borderWidth)
       || (gl_FragCoord.x < topLeft.x + borderWidth - 1))
    {
        pixelColor = vec4(vec3(0.5), 1);
    }

    if((gl_FragCoord.y < topLeft.y + borderWidth - 1)
        || (gl_FragCoord.y >= bottomRight.y - borderWidth)
        )
    {
        pixelColor = vec4(vec3(0.5), 1);
    }
}