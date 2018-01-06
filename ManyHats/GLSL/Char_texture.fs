#version 330 core
out vec4 FragColor;

in vec3 ourColor;
in vec2 TexCoord;

// texture sampler
uniform sampler2D Char_texture;

// layout(location = 0) in vec3 vertexPosition_modelspace;
// uniform mat4 transform;

void main()
{
	FragColor = texture(Char_texture, TexCoord);

	// gl_Position =  transform * vec4(vertexPosition_modelspace, 1);
}
