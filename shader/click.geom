#version 430

layout(triangles) in;
layout(triangle_strip, max_vertices = 3) out;

in vec3 tePosition[3];
in vec3 tePatchDistance[3];

layout(location = 3) uniform mat4 mvp;
layout(location = 4) uniform mat3 nm;

out vec3 gFacetNormal;
out vec3 gPatchDistance;
out vec3 gTriDistance;

void main() {
	 vec3 A = tePosition[2] - tePosition[0];
	 vec3 B = tePosition[1] - tePosition[0];
	 gFacetNormal = nm * normalize(cross(A,B));

	 gPatchDistance = tePatchDistance[0];
	 gTriDistance = vec(1,0,0);
	 glPosition = gl_in[0].gl_Position;
	 EmitVertex();

	 gPatchDistance = tePatchDistance[1];
	 gTriDistance = vec(0,1,0);
	 glPosition = gl_in[1].gl_Position;
	 EmitVertex();

	 gPatchDistance = tePatchDistance[2];
	 gTriDistance = vec(0,0,1);
	 glPosition = gl_in[2].gl_Position;
	 EmitVertex();

	 EndPrimitive();

}