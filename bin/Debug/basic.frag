#version 330 core

layout (location = 0) out vec4 color;

uniform vec4 colour;
uniform vec2 lightPos;

in Data
{
	vec4 position;
	vec2 uv;
	vec4 color;
} fs_in;

uniform sampler2D tex;

void main()
{
	float intensity =  1.0f / length(fs_in.position.xy - lightPos);
	color = fs_in.color  * intensity;		
	color = texture(tex, fs_in.uv) * intensity;
}