#version 430
layout( triangles) in;
layout( line_strip, max_vertices = 6) out;

layout(location = 3) uniform mat4 mvp;

in VS_OUT {
    vec3 normal;
	vec4 color;
} gs_in[];

out vec4 fragcolor;

void DrawNormals(int index) {
	gl_Position = mvp * gl_in[index].gl_Position;
	fragcolor = gs_in[index].color;
    EmitVertex();
	vec3 normal =  gs_in[index].normal;
	gl_Position = mvp * (gl_in[index].gl_Position + vec4(normal,0.0f));
    EmitVertex();
    EndPrimitive();
}

void DrawUtilNormals(int index, vec3 in_normal) {
	gl_Position = mvp * gl_in[index].gl_Position;
	fragcolor = gs_in[index].color;
	EmitVertex();
	vec4 normal = vec4(in_normal, 0.0f);
	gl_Position =  mvp * (gl_in[index].gl_Position + normal);
    EmitVertex();
    EndPrimitive();
}

void main() {
	vec3 n = normalize(cross( vec3(gl_in[1].gl_Position - gl_in[0].gl_Position), vec3(gl_in[2].gl_Position - gl_in[0].gl_Position)));
	for(int i = 0; i < gl_in.length(); i++) {
		//DrawUtilNormals(i, n);
		DrawNormals(i);
		}
}