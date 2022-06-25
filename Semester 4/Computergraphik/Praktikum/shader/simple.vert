#version 330 core

in vec3 position;
in vec3 color;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

out vec3 fragmentColor;

void main()
{
	fragmentColor = color;
	gl_Position   = projection * view * model * vec4(position,  1.0);
}