#version 330 core
layout (location = 0) in vec3 aPos;
//layout (location = 1) in vec3 aColor;
layout (location = 1) in vec2 aTexCoord;

out vec3 ourColor;
out vec2 TexCoord;

uniform mat4 transform;
uniform vec2 uvScale = vec2(1.0, 1.0);
uniform vec2 uvOffset = vec2(0.0, 0.0);
uniform bool xFlip = false;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
    // gl_Position = transform * vec4(aPos.x, aPos.y, aPos.z, 1.0); 
    gl_Position = projection * view * model * vec4 (aPos, 1.0f);
    ourColor = aPos;
    TexCoord = aTexCoord * uvScale + uvOffset;
    if(xFlip)
    {
        TexCoord.x = (2.0 * uvOffset.x + uvScale.x) - TexCoord.x;
    }
}