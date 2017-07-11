#version 430

layout (location = 0 ) in vec4 position;
layout (location = 1 ) in vec4 color;
layout (location = 2) in vec4 normal;

layout(location = 3) uniform mat4 mvp;
layout(location = 4) uniform mat3 nm;
layout(location = 5) uniform mat4 projection;
layout(location = 6) uniform mat4 mv;

out vec4 fragnormal;
out vec4 fragcolor;
out vec4 fragposition;

void main()
{
	fragnormal = normal;
	fragcolor = color;
	vec4 pos = position;
	if(pos.w != 0) {
		pos /= pos.w;
	}
	fragposition = mv * pos;
	gl_Position   = mvp * pos;
}