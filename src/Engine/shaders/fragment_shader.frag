// shadertype=glsl

#version 450 core

out vec4 color;

in DATA
{
	vec4 pos;
	vec4 color;
	vec2 texcoords;
	vec4 light_pos;
	float tid;
} fs_in;

uniform sampler2D sampler[32];

uniform vec4 light_color;
uniform vec2 light_position;

void main(void)
{
	float intensity = 1.0 / length(fs_in.pos.xy - fs_in.light_pos.xy) * 0.1;
	//color = texture(sampler, fs_in.texcoords) * fs_in.color;
	//color = texture(sampler, fs_in.texcoords) * fs_in.color;
	vec4 texColor = fs_in.color;
	if(fs_in.tid > 0.0)
	{
		int tid = int(fs_in.tid - 0.5);
		texColor = texture(sampler[tid], fs_in.texcoords);
	}

	color = texColor;// * light_color * intensity;
}