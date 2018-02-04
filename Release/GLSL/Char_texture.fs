#version 330 core
out vec4 FragColor;

in vec2 TexCoord;

// texture sampler
uniform sampler2D Char_texture;

void main()
{
	FragColor = texture(Char_texture, TexCoord);
}
