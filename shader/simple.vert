#version 330

in vec4 position;
in vec3 color;

uniform mat4 mvp;

out vec3 fragmentColor;

void main()
{
	fragmentColor = color;
	gl_Position   = mvp * position;
}