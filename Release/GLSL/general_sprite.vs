#version 330 core
layout (location = 0) in vec3 position;
layout (location = 1) in vec2 aTexCoord;

uniform mat4 transformation;
out vec2 TexCoords;


void main()
{
    TexCoords = aTexCoord;
    gl_Position = transformation * vec4(position, 1.0);
}
