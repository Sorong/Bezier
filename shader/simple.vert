#version 430

layout (location = 0 ) in vec4 position;
layout (location = 1 ) in vec4 color;

layout(location = 3) uniform mat4 mvp;
layout(location = 4) uniform mat3 nm;
layout(location = 5) uniform mat4 projection;

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