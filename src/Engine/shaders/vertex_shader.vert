// shadertype=glsl

#version 450 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec4 color;
layout (location = 2) in vec2 texcoords;
layout (location = 3) in float tid;

out DATA
{
	vec4 pos;
	vec4 color;
	vec2 texcoords;
	vec4 light_pos;
	float tid;
} vs_out;

uniform mat4 pr_matrix = mat4(1.0);
uniform mat4 vw_matrix = mat4(1.0);
uniform mat4 ml_matrix = mat4(1.0);
uniform vec2 light_position;

void main(void)
{
	vec4 out_pos = vec4(position, 1.0);

	vs_out.pos = pr_matrix * vw_matrix * ml_matrix * out_pos;
	vs_out.color = color;
	vs_out.texcoords = texcoords;
	vs_out.light_pos = pr_matrix * vec4(light_position, vs_out.pos.z, 1.0);
	vs_out.tid = tid;
	gl_Position = vs_out.pos;
}