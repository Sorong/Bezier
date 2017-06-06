#version 330

in vec4 position;
in vec4 color;

uniform mat4 mvp;

out vec4 fragmentColor;

void main()
{	

	fragmentColor = color;
	vec4 blubb = vec4(1,0,1,0.2);
	fragmentColor = fragmentColor;
	gl_Position   = mvp * position;
}