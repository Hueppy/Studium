#version 330 core

in vec3 position;
in vec3 color;
in vec3 normal;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform mat3 normalMatrix;
uniform vec4 light;

flat out vec3 fragmentColor;

void main()
{
    vec3  n     = normalize(normalMatrix * normal);
 	float fDiff = clamp(dot(n, light.xyz), 0.0, 1.0);

    fragmentColor = color * fDiff;

	gl_Position = projection * view * model * vec4(position,  1.0);
}