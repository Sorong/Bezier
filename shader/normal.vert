#version 430

layout (location = 0) in vec4 position;
layout (location = 2) in vec4 normal;

layout(location = 3) uniform mat4 mvp;
layout(location = 4) uniform mat3 nm;
layout(location = 5) uniform mat4 projection;



out VS_OUT {
    vec3 normal;
	vec4 color;
} vs_out;


void main() {	
	vec4 pos = position;
	if(pos.w != 0) {
		pos /= pos.w;
	}
	gl_Position = pos;
	//vs_out.normal = normalize(vec3(projection * vec4(nm * vec3(normal), 1.0)));
	vs_out.normal = vec3(normal);
	vs_out.color = vec4(0.0f, 0.0f, 0.0f, 1.0f);
}