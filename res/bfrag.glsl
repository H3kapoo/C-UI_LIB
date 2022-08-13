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

    if(gl_FragCoord.y <= topLeft.y + borderWidth &&
            gl_FragCoord.y >= topLeft.y - 1 &&
            gl_FragCoord.x < bottomRight.x && gl_FragCoord.x > topLeft.x-1)
    {
        pixelColor = vec4(outColor*0.5, 1.0f);
    }

    else if(gl_FragCoord.y >= bottomRight.y - borderWidth &&
            gl_FragCoord.y <= bottomRight.y &&
            gl_FragCoord.x < bottomRight.x&& gl_FragCoord.x > topLeft.x)
    {
        pixelColor = vec4(outColor*0.5, 1.0f);
    }

    else if(gl_FragCoord.x <= topLeft.x + borderWidth  &&
            gl_FragCoord.x >= topLeft.x - 1 &&
            gl_FragCoord.y > topLeft.y && gl_FragCoord.y < bottomRight.y)
    {
        pixelColor = vec4(outColor*0.5, 1.0f);
    }

    else if(gl_FragCoord.x >= bottomRight.x - borderWidth &&
            gl_FragCoord.x <= bottomRight.x &&
            gl_FragCoord.y > topLeft.y && gl_FragCoord.y < bottomRight.y)
    {
        pixelColor = vec4(outColor*0.5, 1.0f);
    }
}