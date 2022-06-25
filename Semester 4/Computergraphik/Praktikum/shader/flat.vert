#version 330 core

in vec3 position;
in vec3 color;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

out vec3 fragmentColor;
out vec3 viewPosition;

void main()
{
	fragmentColor = color;
	vec4 mpos = view * model * vec4(position,  1.0);
	gl_Position = projection * mpos;
	viewPosition = -mpos.xyz;
}