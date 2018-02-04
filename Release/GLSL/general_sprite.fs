#version 330 core

in vec2 TexCoords;
uniform sampler2D image;
uniform vec3 color;

void main()
{
    color = vec4(color, 1.0) * texture(image, TexCoords);
}
