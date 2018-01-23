#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 2) in vec2 aTexCoord;

out vec2 TexCoords;

uniform mat4 transform;
uniform vec2 texOffset0;
uniform vec2 texOffset1;

void main()
{
    gl_Position = transform * vec4(aPos, 1.0f);
    TexCoords = texOffset0 * aTexCoord + texOffset1;
}
