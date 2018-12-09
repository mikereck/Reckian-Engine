#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNor;

uniform mat4 MVMatrix;
uniform mat4 VMatrix;
uniform mat4 PMatrix;
uniform mat3 NMatrix;

out vec3 position;
out vec3 lightPos;
out vec3 norm;

void main()
{
	gl_Position = PMatrix * MVMatrix * vec4(aPos, 1.0);
	vec4 position4v = (MVMatrix * vec4(aPos, 1.0));
	vec4 lightPos4v = (VMatrix * vec4(0,0,20,1.0));
	lightPos = lightPos4v.xyz/lightPos4v.w;
	position = position4v.xyz/position4v.w;
	norm = normalize(NMatrix * aNor);
}

