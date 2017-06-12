#version 330

in vec4 position;
in vec4 color;

uniform mat4 mvp;

out vec4 fragmentColor;

void main()
{	

	fragmentColor = color;
	vec4 pos = position;
	if(pos.w != 0) {
		pos /= pos.w;
	}
	gl_Position   = mvp * pos;
}